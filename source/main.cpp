#include "main.hpp"
#include "argument.hpp"
#include "cmdline.hpp"
#include "context.hpp"
#include "debug.hpp"
#include "gui.hpp"

using namespace std;
using namespace cmdline;
using namespace NameSpace;

int main(const int argument_count, char **const argument_value)
{
    // Check Command Line Options and Arguments
    parser argument_parser;
    argument_parser.add<string>(Argument_Fbdev, Argument_Fbdev_Short, Argument_Fbdev_Refer,
                                Argument_Fbdev_Need, Argument_Fbdev_Default);
    argument_parser.add<string>(Argument_Evdev, Argument_Evdev_Short, Argument_Evdev_Refer,
                                Argument_Evdev_Need, Argument_Evdev_Default);
    argument_parser.add<string>(Argument_Model, Argument_Model_Short, Argument_Model_Refer,
                                Argument_Model_Need, Argument_Model_Default);
    argument_parser.parse_check(argument_count, argument_value);
    debug::get_single_instance()->notice(__FILE__, __LINE__)
        << "Complete Command Line Argument Validation." << Debug_Complete;

    // Deploy GUI and Execute LVGL
    gui::get_single_instance()
        ->initialize(argument_parser.get<string>(Argument_Fbdev),
                     argument_parser.get<string>(Argument_Evdev))
        ->execute();

    return 0;
}
