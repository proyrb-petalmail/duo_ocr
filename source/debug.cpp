#include "debug.hpp"

using namespace std;

namespace NameSpace
{
    debug::debug() {}

    debug *debug::get_single_instance()
    {
        if (debug::single_instance)
            return debug::single_instance;
        return debug::single_instance = new debug();
    }

    debug *debug::single_instance = debug::get_single_instance();

    void debug::prepare(const int level)
    {
        if (Debug_Level < level)
            clog.rdbuf(this->dustbin.rdbuf());
        else
            clog.rdbuf(this->original_buffer);
    }

    const string debug::extract(const string &file_name)
    {
        const size_t index = file_name.rfind("/");
        return (string::npos != index) ? file_name.substr(index + 1) : file_name;
    }

    ostream &debug::info(const string &file_name, const int line)
    {
        this->prepare(4);
        return clog << "\033[0;30m" << "[" << extract(file_name) << ":" << line << "]";
    }

    ostream &debug::notice(const string &file_name, const int line)
    {
        this->prepare(3);
        return clog << "\033[0;32m" << "[" << extract(file_name) << ":" << line << "]";
    }

    ostream &debug::warning(const string &file_name, const int line)
    {
        this->prepare(2);
        return clog << "\033[1;33m" << "[" << extract(file_name) << ":" << line << "]";
    }

    ostream &debug::error(const string &file_name, const int line)
    {
        this->prepare(1);
        return clog << "\033[1;31m" << "[" << extract(file_name) << ":" << line << "]";
    }

    debug::~debug() {}
} // namespace NameSpace
