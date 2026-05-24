#include <stdexcept>
#include <string>

#include "../Resources.h"

namespace exceptions
{
    class FileException : public std::runtime_error
    {
	public:
		FileException(const std::string& msg)
			: std::runtime_error(msg)
		{
		}
    };

    class FileOpenException : public std::runtime_error
	{
	public:
		FileOpenException()
			: FileException(resources::exception_strings::file_open)
		{
		}
	};
}