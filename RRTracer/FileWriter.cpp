#include "FileWriter.h"

namespace RRT
{
	void FileWriter::Write(const std::string& pixel_map)
	{
		file << pixel_map;
	}
}