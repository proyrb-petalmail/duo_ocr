#pragma once

#define Argument_Fbdev       "fbdev"
#define Argument_Fbdev_Short 'f'
#define Argument_Fbdev_Refer                                                                       \
    "Define the specific device responsible for managing the frame buffer, which holds the image " \
    "data to be displayed."
#define Argument_Fbdev_Need    false
#define Argument_Fbdev_Default "/dev/fb0"

#define Argument_Evdev         "evdev"
#define Argument_Evdev_Short   'e'
#define Argument_Evdev_Refer                                                                       \
    "Define the specific device used for input operations, such as keyboard, mouse, or sensor."
#define Argument_Evdev_Need    false
#define Argument_Evdev_Default "/dev/input/event0"

#define Argument_Model         "model"
#define Argument_Model_Short   'm'
#define Argument_Model_Refer                                                                       \
    "Define the specific program that represents the model used for computations or simulations."
#define Argument_Model_Need    false
#define Argument_Model_Default ""
