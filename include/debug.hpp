#pragma once

#include "main.hpp"

#include <iostream>
#include <sstream>
#include <string>

/**
 * @brief Configure the level of detail for the debugging information output.
 * @param 0 Invalid.
 * @param 1 error.
 * @param 2 error & warning.
 * @param 3 error & warning & notice.
 * @param 4 error & warning & notice & info.
 */
#define Debug_Level    4

/**
 * @brief Ensure that this cleanup procedure is executed after every debug message is output
 * to maintain system stability and performance.
 */
#define Debug_Complete "\033[0m" << endl

namespace NameSpace
{
    class debug
    {
    private:
        static debug *single_instance; /* A unique instance of the object or component, ensuring
                                         that only one instance exists at any given time. */
        std::streambuf *original_buffer =
            std::clog.rdbuf(); /* The buffer used by the output device to temporarily store data
                             before it is sent to the output destination. */
        std::ostringstream
            dustbin; /* The output buffer that becomes invalid following the redirection of debug
                        information, potentially leading to data loss or errors. */

        debug();

        void prepare(const int level);

        const std::string extract(const std::string &file_name);

        ~debug();

    public:
        /**
         * @brief Retrieve and return the unique instance of the object or component, ensuring only
         * one instance exists.
         */
        static debug *get_single_instance();

        /**
         * @brief Enable the output of debug information categorized at the 'info' level, typically
         * providing general operational details.
         */
        std::ostream &info(const std::string &file_name, const int line);

        /**
         * @brief Enable the output of debug information categorized at the 'notice' level,
         * typically providing general operational details.
         */
        std::ostream &notice(const std::string &file_name, const int line);

        /**
         * @brief Enable the output of debug information categorized at the 'warning' level,
         * typically providing general operational details.
         */
        std::ostream &warning(const std::string &file_name, const int line);

        /**
         * @brief Enable the output of debug information categorized at the 'error' level, typically
         * providing general operational details.
         */
        std::ostream &error(const std::string &file_name, const int line);
    };
} // namespace NameSpace
