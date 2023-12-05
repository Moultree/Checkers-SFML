#pragma once
////////////////////
// FOR MICROSOFT WINDOWS ONLY
///////////////////
#ifdef _WIN32
#include "ResourcePath.hpp"

std::string getResourcePath(const std::string& relativePath) {
 return "resources/" + relativePath;
}
#endif