from subprocess import call
import glob
import os

currentDir = os.path.dirname(os.path.abspath(__file__))

offscreenRenderPath = currentDir + "/../build/offscreen_render"
imageDiffPath = currentDir + "/../build/image_dif"
offscreenOutputFolder = currentDir + "/actual"
compareFolder = currentDir + "/expected"
compareOutputFolder = currentDir + "/diff"

def prepareFolders():
	if not os.path.isdir(offscreenOutputFolder):
		os.makedirs(offscreenOutputFolder)
	if not os.path.isdir(compareOutputFolder):
		os.makedirs(compareOutputFolder)

def offscreenRender():
	call(offscreenRenderPath + " " + offscreenOutputFolder, shell=True)

def compareImages():
	images = glob.glob(offscreenOutputFolder + "/*.png")
	for im in images:
		if im.find("_diff.png") != -1:
			continue
		imageName = os.path.basename(im)
		imageToCompare = compareFolder + "/" + imageName
		call(imageDiffPath + " " + im + " " + imageToCompare
			+ " " + compareOutputFolder, shell=True)

prepareFolders()
offscreenRender()
compareImages()
