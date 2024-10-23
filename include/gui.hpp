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

        // context *context_pointer = nullptr;
        // lv_obj_t *screen = nullptr;
        // lv_obj_t *container = nullptr;
        // lv_obj_t *bar = nullptr;
        // lv_obj_t *exit_button = nullptr;
        // lv_obj_t *title_label = nullptr;
        // lv_obj_t *status_led = nullptr;
        // lv_obj_t *name_group = nullptr;
        // lv_obj_t *name_editor = nullptr;
        // lv_obj_t *name_item = nullptr;
        // lv_obj_t *name_label = nullptr;
        // lv_obj_t *name_line = nullptr;
        // lv_obj_t *password_group = nullptr;
        // lv_obj_t *password_editor = nullptr;
        // lv_obj_t *password_item = nullptr;
        // lv_obj_t *password_label = nullptr;
        // lv_obj_t *password_line = nullptr;
        // lv_obj_t *button_group = nullptr;
        // lv_obj_t *disconnect_button = nullptr;
        // lv_obj_t *disconnect_label = nullptr;
        // lv_obj_t *connect_button = nullptr;
        // lv_obj_t *connect_label = nullptr;
        // lv_obj_t *button_line = nullptr;
        // lv_obj_t *input_container = nullptr;
        // lv_obj_t *keyboard = nullptr;

        gui();

        void deploy();

        ~gui();

        // static void animation_complete_callback(lv_anim_t *const animation);
        // static void short_click_event_callback(lv_event_t *const event);

    public:
        /**
         * @brief Retrieve and return the unique instance of the object or component, ensuring only
         * one instance exists.
         */
        static gui *get_single_instance();

        /* Initialize the LVGL (Light and Versatile Graphics Library) to set up the graphical user
         * interface components and prepare the system for rendering and event handling. */
        gui *initialize(const std::string &fbdev, const std::string &evdev);

        /* Begin the execution of the LVGL (Light and Versatile Graphics Library) code to initialize
         * the graphical user interface and handle display updates. */
        void execute();
    };
} // namespace NameSpace
