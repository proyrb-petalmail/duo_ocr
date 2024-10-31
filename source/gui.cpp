#include "gui.hpp"
#include "configor/json.hpp"
#include "debug.hpp"
#include "main.hpp"

#include <fstream>
#include <string.h>
#include <unistd.h>

using namespace std;
using namespace configor;

#define BACKGROUND_COLOR 0xE0E0E0
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

        system("./boot.sh");

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

        this->image = lv_image_create(this->screen);
        lv_image_set_src(this->image, "test_imgs/gt_97_flip.jpg");
        lv_obj_align(this->image, LV_ALIGN_TOP_MID, 0, 0);

        ifstream in_file_stream("results/ppocr_system_results_b1.json");
        json::value json;
        in_file_stream >> json::wrap(json);
        debug::get_single_instance()->info(__FILE__, __LINE__)
            << setw(4) << json::wrap(json) << Debug_Complete;
        debug::get_single_instance()->info(__FILE__, __LINE__)
            << json::wrap(json["gt_97_flip"][0]["transcription"]) << Debug_Complete;
        this->label = lv_label_create(this->screen);
        lv_obj_set_style_text_font(this->label, &lv_font_custom_40,
                                   LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_label_set_text(this->label, json["gt_97_flip"][0]["transcription"].get<string>().data());
        lv_obj_align(this->label, LV_ALIGN_BOTTOM_MID, 0, 0);

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