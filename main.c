#include <stdlib.h>
#include "hw_md.h"

int main(void) {
    put_str("Hello world", 0x2000, 1, 1);

    while ( 1 );

    return 0;
}
