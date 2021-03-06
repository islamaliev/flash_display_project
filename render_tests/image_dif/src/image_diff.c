#include <png.h>
#include <stdlib.h>
#include <memory.h>
#include <stdarg.h>

char outputFileName[1024];
char firstImageFolder[1024];

void abort_(const char* s, ...) {
    va_list args;
    va_start(args, s);
    vfprintf(stderr, s, args);
    fprintf(stderr, "\n");
    va_end(args);
    abort();
}

typedef struct {
    int width;
    int height;
    png_byte** data;
} ImageData;

void user_error_fn(png_structp png_ptr, png_const_charp error_msg) {
    fprintf(stderr, error_msg);
    fprintf(stderr, "\n");
}

void read_png_file(char* file_name, ImageData* imageData) {
    char header[8];

    FILE* fp = fopen(file_name, "rb");
    if (!fp)
        abort_("[read_png_file] File %s could not be opened for reading", file_name);
    fread(header, 1, 8, fp);
    if (png_sig_cmp((png_bytep) header, 0, 8))
        abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, &user_error_fn, &user_error_fn);

    if (!png_ptr)
        abort_("[read_png_file] png_create_read_struct failed");

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
        abort_("[read_png_file] png_create_info_struct failed");

    if (setjmp(png_jmpbuf(png_ptr)))
        abort_("[read_png_file] Error during init_io");

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);

    png_read_info(png_ptr, info_ptr);

    imageData->width = png_get_image_width(png_ptr, info_ptr);
    imageData->height = png_get_image_height(png_ptr, info_ptr);
    png_read_update_info(png_ptr, info_ptr);

    if (setjmp(png_jmpbuf(png_ptr)))
        abort_("[read_png_file] Error during read_image");

    imageData->data = (png_bytep*) malloc(sizeof(png_bytep) * imageData->height);
    for (int y = 0; y < imageData->height; y++)
        imageData->data[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr, info_ptr));

    png_read_image(png_ptr, imageData->data);

    fclose(fp);
}

float calculateDiff(ImageData* im1, ImageData* im2, png_byte* diffIm) {
    float diff = 0;
    float div = 1 / 255.f;

    for(int y = 0; y < im1->height; ++y) {
        png_byte* row1 = im1->data[y];
        png_byte* row2 = im2->data[y];
        for(int x = 0; x < im1->width; ++x) {
            png_byte* px1 = &(row1[x * 3]);
            png_byte* px2 = &(row2[x * 3]);

            int ind = (y * im1->width + x) * 3;
            float r = diffIm[ind] = (unsigned char) abs(px1[0] - px2[0]);
            float g = diffIm[ind + 1] = (unsigned char) abs(px1[1] - px2[1]);
            float b = diffIm[ind + 2] = (unsigned char) abs(px1[2] - px2[2]);
            // transform channel diff to [1, 2] so that exponent is more sensible
            r  = r * div + 1;
            g  = g * div + 1;
            b  = b * div + 1;
            diff += r * r * r - 1;
            diff += g * g * g - 1;
            diff += b * b * b - 1;
        }
    }
    return diff;
}

void savePNG(const char *filename, int width, int height, png_byte* data) {
    size_t i, nvals;
    const size_t format_nchannels = 3;
    FILE *f = fopen(filename, "wb");
    nvals = format_nchannels * width * height;

    png_byte* png_bytes = (png_byte*) malloc(nvals * sizeof(png_byte));
    png_byte** png_rows = (png_byte**) malloc(height * sizeof(png_byte*));
    for (i = 0; i < nvals; i++)
        (png_bytes)[i] = (data)[i];
    for (i = 0; i < height; i++)
        (png_rows)[i] = &(png_bytes)[i * width * format_nchannels];
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) abort();
    png_infop info = png_create_info_struct(png);
    if (!info) abort();
    if (setjmp(png_jmpbuf(png))) abort();
    png_init_io(png, f);
    png_set_IHDR(
            png,
            info,
            width,
            height,
            8,
            PNG_COLOR_TYPE_RGB,
            PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_DEFAULT,
            PNG_FILTER_TYPE_DEFAULT
    );
    png_write_info(png, info);
    png_write_image(png, png_rows);
    png_write_end(png, NULL);
    free(png_bytes);
    free(png_rows);
    fclose(f);
}

int main(int argc, char** argv) {
    size_t outputFolderLength = 0;
    if (argc < 3) {
        printf("Usage: %s <path_to_image1> <path_to_image2> [<outputFolder>]", argv[0]);
    } else if (argc > 3) {
        outputFolderLength = strlen(argv[3]);
    }

    char* nameBeg = strrchr(argv[1], '/');
    if (nameBeg == NULL) {
        nameBeg = argv[1];
    } else {
        nameBeg++;
    }
    char* dotPos = strrchr(argv[1], '.');
    if (dotPos == NULL) {
        fprintf(stderr, "File has no extension: %s", argv[1]);
        return -1;
    }

    unsigned long nameLen = dotPos - nameBeg + 1;
    char* name = malloc(nameLen);
    strncpy(name, nameBeg, dotPos - nameBeg);
    name[nameLen - 1] = '\0';

    printf("    %s", name);

    ImageData im1;
    read_png_file(argv[1], &im1);

    ImageData im2;
    read_png_file(argv[2], &im2);

    if (im1.width != im2.width || im1.height != im2.height) {
        fprintf(stderr, "images have different sizes: %dx%d - %dx%d", im1.width, im1.height, im2.width, im2.height);
        return -1;
    }

    unsigned char* diffIm = (unsigned char*) malloc(im1.width * im1.height * 3 * sizeof(unsigned char));
    float diff = calculateDiff(&im1, &im2, diffIm);

    if (diff > 0) {
        printf("    (%.2f)\n", diff);
    } else {
        printf("\n");
        return 0;
    }

    strncpy(firstImageFolder, argv[1], nameBeg - argv[1]);

    // if first image folder and output folder are the same
    if (!outputFolderLength || strcmp(argv[3], firstImageFolder) == 0) {
        strcpy(outputFileName, firstImageFolder);
        strncat(outputFileName, nameBeg, dotPos - nameBeg);
        strcat(outputFileName, "_diff");
        strcat(outputFileName, dotPos);
    } else {
        strcpy(outputFileName, argv[3]);
        outputFileName[outputFolderLength] = '/';
        outputFileName[outputFolderLength + 1] = '\0';
        strcat(outputFileName, nameBeg);
    }

    savePNG(outputFileName, im1.width, im1.height, diffIm);

    free(name);

    return 0;
}
