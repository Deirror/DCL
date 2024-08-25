#pragma once
#include <tydefios.h>
#include <dcl_defines.h>

DCL_BEGIN

size_t getFileSize(dcl::ifstream& in);

int getCharCountFromFile(dcl::ifstream& ifs, char ch);

int getLinesCount(const char* fileName);

int replaceCharacterInFile(const char* fileName, const char toReplace, const char replacement);

DCL_END