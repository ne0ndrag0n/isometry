#include "md/joypad.h"

int mdJoyButtonSelected( uint16_t button ) {
    return button & ~joypad1;
}