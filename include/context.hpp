#pragma once

#include "main.hpp"

#include <string>

namespace NameSpace
{
    class context
    {
    private:
        static context *single_instance; /* A unique instance of the object or component, ensuring
                                          that only one instance exists at any given time. */

        std::string program_directory; /* The location of this program's directory within the file
                                          system, where its files and resources are stored. */

        context();

        ~context();

    public:
        /**
         * @brief Retrieve and return the unique instance of the object or component, ensuring only
         * one instance exists.
         */
        static context *get_single_instance();

        /**
         * @brief Retrieve and return the path to the directory where this program is located within
         * the file system.
         */
        const std::string &get_program_directory();
    };
} // namespace NameSpace
