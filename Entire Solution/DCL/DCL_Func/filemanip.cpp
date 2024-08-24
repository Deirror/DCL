#include "filemanip.h"

DCL_BEGIN

size_t getFileSize(dcl::ifstream& in)
{
	size_t current = in.tellg();

	in.seekg(0, dcl::ios::end);
	size_t size = in.tellg();

	in.seekg(current, dcl::ios::beg);

	return size;
}

int getCharCountFromFile(std::ifstream& ifs, char ch)
{
	if (!ifs.is_open()) 
	{
		return -1;
	}

	int count = 0;

	while (true) 
	{
		char current = ifs.get();
		if (ifs.eof()) 
		{
			break;
		}

		if (current == ch) 
		{
			count++;
		}
	}

	return count;
}

int getLinesCount(const char* fileName)
{
	dcl::ifstream myFile(fileName);

	if (!myFile.is_open())
	{
		return -1;
	}

	return getCharCountFromFile(myFile, '\n') + 1;
}

int replaceCharacterInFile(const char* fileName, const char toReplace, const char replacement)
{
	dcl::fstream file(fileName, dcl::ios::in | dcl::ios::out);

	if (!file.is_open())
	{
		return -1;
	}

	char current;

	while (true)
	{
		file.get(current);

		if (file.eof())
		{
			break;
		}

		if (current == toReplace)
		{
			file.seekp(-1, dcl::ios::cur);
			file.put(replacement);
			file.flush();
		}
	}

	file.close();
	return 1;
}

DCL_END