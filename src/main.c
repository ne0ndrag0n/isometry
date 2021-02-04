#include "md/debug.h"

int main(void) {
    mdWriteDebugFontColor( 0xEEE );
    mdLoadDebugFont();

    while ( 1 );

    return 0;
}
