#ifndef FILE_WRITER_H
#define FILE_WRITER_H

#include <fstream>
#include <string>

namespace RRT
{
	class FileWriter
	{
	public:
		FileWriter(const std::string& file_name) : file_name(file_name) { file.open(file_name); }
		~FileWriter() { file.close(); }

		void Write(const std::string& pixel_map);

	private:
		std::ofstream file;
		std::string file_name = "\0";
	};
}

#endif // !FILE_WRITER_H