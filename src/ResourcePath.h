#pragma once
////////////////////////////////////////////////////////////
// GENERAL RESOURCE LOADER
////////////////////////////////////////////////////////////

#include <string>
#include <iostream>

////////////////////////////////////////////////////////////
/// \brief Get file path specified
/// \param relativePath file path inside `Resources` dir
/// \return The path to the file relative to the resources folder
///
////////////////////////////////////////////////////////////
std::string getResourcePath(const std::string& relativePath);

