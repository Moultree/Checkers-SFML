#pragma once
////////////////////
// FOR MICROSOFT WINDOWS ONLY
///////////////////
#ifdef _WIN32
#include "ResourcePath.h"

std::string getResourcePath(const std::string& relativePath) {
 return "resources/" + relativePath;
}
#endif