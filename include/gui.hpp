#pragma once

#include "context.hpp"
#include "lvgl.h"
#include "main.hpp"

#include <string>

namespace NameSpace
{
    class gui
    {
    private:
        static gui *single_instance; /* A unique instance of the object or component, ensuring
                                          that only one instance exists at any given time. */
        lv_display_t *display = nullptr;
        lv_indev_t *indev = nullptr;
        lv_obj_t *screen = nullptr;
        lv_obj_t *button = nullptr;
        lv_obj_t *image = nullptr;
        lv_obj_t *label = nullptr;

        gui();
        void deploy();
        ~gui();

    public:
        /**
         * @brief Retrieve and return the unique instance of the object or component, ensuring only
         * one instance exists.
         */
        static gui *get_single_instance();
        /**
         * @brief Initialize the LVGL (Light and Versatile Graphics Library) to set up the
         * graphical user interface components and prepare the system for rendering and event
         * handling.
         */
        gui *initialize(const std::string &fbdev, const std::string &evdev);
        /**
         * @brief Begin the execution of the LVGL (Light and Versatile Graphics Library) code to
         * initialize the graphical user interface and handle display updates.
         */
        void execute();
    };
} // namespace NameSpace
