#include "bberror.h"
#include "md/debug.h"
#include <string.h>

void bbFatalHalt( const char* error ) {
    char buffer[ 50 ] = { 0 };

    strcpy( buffer, "fatal: " );
    strcat( buffer, error );

    mdDebugPrint( buffer, VDP_PLANE_A, 1, 1 );
    mdDebugPrint( "system halted", VDP_PLANE_A, 1, 2 );
    while( 1 );
}