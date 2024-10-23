#include "context.hpp"
#include "debug.hpp"
#include "main.hpp"

#include <fstream>
#include <unistd.h>

using namespace std;

char *lvgl_file_system = nullptr;

namespace NameSpace
{
    context::context()
    {
        char temporary_buffer[256] = "";
        if (-1 == readlink("/proc/self/exe", temporary_buffer, 256))
        {
            debug::get_single_instance()->error(__FILE__, __LINE__)
                << "Failed to Read the '/proc/self/exe' Link" << Debug_Complete;
            exit(-1);
        }
        this->program_directory = temporary_buffer;
        this->program_directory.erase(this->program_directory.find_last_of("/") + 1,
                                      this->program_directory.length() -
                                          this->program_directory.find_last_of("/") + 1);
        debug::get_single_instance()->info(__FILE__, __LINE__)
            << "program_directory:" << this->program_directory << Debug_Complete;

        string temporary_string(this->program_directory + "%s");
        lvgl_file_system = new char[temporary_string.length() + 1];
        if (temporary_string.copy(lvgl_file_system, temporary_string.length() + 1, 0) <
            temporary_string.length())
        {
            debug::get_single_instance()->error(__FILE__, __LINE__)
                << "String Copy Failed." << Debug_Complete;
            exit(-2);
        }
        debug::get_single_instance()->info(__FILE__, __LINE__)
            << "lvgl_file_system:" << lvgl_file_system << Debug_Complete;

        debug::get_single_instance()->notice(__FILE__, __LINE__)
            << "Context Initialization Completed" << Debug_Complete;
    }

    context *context::get_single_instance()
    {
        if (context::single_instance)
            return context::single_instance;
        return context::single_instance = new context();
    }

    context *context::single_instance = context::get_single_instance();

    inline const string &context::get_program_directory() { return this->program_directory; }

    context::~context() {}
} // namespace NameSpace
