#include "gui.hpp"
#include "debug.hpp"
#include "main.hpp"

#include <fstream>
#include <string.h>
#include <unistd.h>

using namespace std;

#define BACKGROUND_COLOR       0xEEEEEE
#define FOREGROUND_COLOR       0xFFFFFF
#define CONTAINER_MARGIN       100
#define BAR_HEIGHT             100
#define BAR_RADIUS             BAR_HEIGHT / 3
#define EXIT_BUTTON_SIZE       BAR_HEIGHT * 0.65
#define EXIT_BUTTON_IMAGE_SIZE BAR_HEIGHT * 0.55
#define BAR_PAD                (BAR_HEIGHT - EXIT_BUTTON_SIZE) / 2
#define LINE_WIDTH             4
#define PANEL_HEIGHT           60

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

    // void gui::short_click_event_callback(lv_event_t *const event)
    // {
    //     lv_obj_t *const event_trigger = (lv_obj_t *)lv_event_get_target(event);
    //     gui *const data = ((gui *)lv_event_get_user_data(event));
    //     if (event_trigger == data->exit_button)
    //     {
    //         Debug_Log("exit");
    //         exit(0);
    //     }
    //     else if (event_trigger == data->name_editor)
    //     {
    //         Debug_Log("name_editor trigger short_click_event");
    //         lv_keyboard_set_textarea(data->keyboard, event_trigger);
    //         lv_anim_t animation;
    //         lv_anim_init(&animation);
    //         lv_anim_set_exec_cb(&animation, (lv_anim_exec_xcb_t)lv_obj_set_y);
    //         lv_anim_set_var(&animation, data->input_container);
    //         lv_anim_set_duration(&animation, 500);
    //         lv_anim_set_values(&animation, lv_obj_get_y_aligned(data->input_container), 0);
    //         lv_anim_set_path_cb(&animation, lv_anim_path_ease_out);
    //         lv_anim_start(&animation);
    //     }
    //     else if (event_trigger == data->password_editor)
    //     {
    //         Debug_Log("password_editor trigger short_click_event");
    //         lv_keyboard_set_textarea(data->keyboard, event_trigger);
    //         lv_anim_t animation;
    //         lv_anim_init(&animation);
    //         lv_anim_set_exec_cb(&animation, (lv_anim_exec_xcb_t)lv_obj_set_y);
    //         lv_anim_set_var(&animation, data->input_container);
    //         lv_anim_set_duration(&animation, 500);
    //         lv_anim_set_values(&animation, lv_obj_get_y_aligned(data->input_container), 0);
    //         lv_anim_set_path_cb(&animation, lv_anim_path_ease_out);
    //         lv_anim_start(&animation);
    //     }
    //     else if (event_trigger == data->disconnect_button)
    //     {
    //         Debug_Log("disconnect_button trigger short_click_event");
    //     }
    //     else if (event_trigger == data->connect_button)
    //     {
    //         Debug_Log("connect_button trigger short_click_event");
    //     }
    //     else
    //     {
    //         Debug_Log("screen or container trigger short_click_event");
    //         lv_keyboard_set_textarea(data->keyboard, nullptr);
    //         lv_anim_t animation;
    //         lv_anim_init(&animation);
    //         lv_anim_set_exec_cb(&animation, (lv_anim_exec_xcb_t)lv_obj_set_y);
    //         lv_anim_set_var(&animation, data->input_container);
    //         lv_anim_set_duration(&animation, 500);
    //         lv_anim_set_values(&animation, lv_obj_get_y_aligned(data->input_container),
    //                            lv_obj_get_height(data->input_container));
    //         lv_anim_set_path_cb(&animation, lv_anim_path_ease_out);
    //         lv_anim_start(&animation);
    //     }
    //     Debug_Log("click");
    // }

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
            << "Complete Deploy." << Debug_Complete;
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