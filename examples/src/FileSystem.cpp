#include <boost/filesystem/operations.hpp>

#include "FileSystem.h"

std::string FileSystem::currentPath() {
    return boost::filesystem::current_path().string();
}