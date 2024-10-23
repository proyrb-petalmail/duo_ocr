#include "gui.hpp"
#include "debug.hpp"
#include "main.hpp"

#include <fstream>
#include <string.h>
#include <unistd.h>

using namespace std;

#define BACKGROUND_COLOR 0xEEEEEE
#define FOREGROUND_COLOR 0xFFFFFF

namespace NameSpace
{
    gui::gui() {}

    gui *gui::get_single_instance()
    {
        if (gui::single_instance)
            return gui::single_instance;
        return gui::single_instance = new gui();
    }

    gui *gui::single_instance = nullptr;

    gui *gui::initialize(const string &fbdev, const string &evdev)
    {
        lv_init();
        this->display = lv_linux_fbdev_create();
        if (!display)
        {
            debug::get_single_instance()->error(__FILE__, __LINE__)
                << "Failed to Create LVGL Frame Buffer Device." << Debug_Complete;
            exit(-1);
        }
        lv_linux_fbdev_set_file(display, fbdev.data());
        lv_display_set_rotation(display, LV_DISPLAY_ROTATION_0);
        this->indev = lv_evdev_create(LV_INDEV_TYPE_POINTER, evdev.data());
        if (!this->indev)
        {
            debug::get_single_instance()->error(__FILE__, __LINE__)
                << "Failed to Create LVGL Input Device." << Debug_Complete;
        }
        this->deploy();
        debug::get_single_instance()->notice(__FILE__, __LINE__)
            << "Complete GUI Initialization." << Debug_Complete;
        return this->single_instance;
    }
    void gui::deploy()
    {
        this->screen = lv_screen_active();
        lv_obj_set_style_bg_color(this->screen, lv_color_hex(BACKGROUND_COLOR),
                                  LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_remove_flag(this->screen, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_update_layout(this->screen);
        debug::get_single_instance()->notice(__FILE__, __LINE__)
            << "Complete GUI Deploy." << Debug_Complete;
    }

    void gui::execute()
    {
        debug::get_single_instance()->notice(__FILE__, __LINE__)
            << "Start Executing LVGL Code." << Debug_Complete;
        while (true)
            usleep(lv_timer_handler());
    }

    gui::~gui() {}
} // namespace NameSpace