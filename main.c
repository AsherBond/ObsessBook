#include <stdio.h>

#include "user.h"
#include "userdb.h"
#include "derpcon.h"

int main( argc, argv )
    int const argc;
    char const * const * const argv;
{
    userdb * OBook;

    FILE *f;
    f = fopen( "INPUT.TXT", "r" );
    OBook = userdb_load( f );
    fclose( f );

    userdb_show( OBook );

    user u1;
    user u2;

    u1 = *( userdb_find_by_id( OBook, 2002 ) );
    u2 = *( userdb_find_by_id( OBook, 1010 ) );

    printf( "[%d]\n", DERPCON( u1, u2 ) );

    userdb_destroy( OBook );

    return 0;
}
