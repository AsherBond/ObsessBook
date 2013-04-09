#include <stdio.h>
#include <stdlib.h>

#include "user.h"
#include "userdb.h"
#include "derpcon.h"

int main( argc, argv )
    int const argc;
    char const * const * const argv;
{
    userdb * OBook;

    if ( argc < 3 ){
        fprintf( stderr, "usage: %s USERID1 USERID2\n", argv[0] );
        return 1;
    }

    int id1, id2;

    id1 = atoi( argv[1] );
    id2 = atoi( argv[2] );

    FILE *f;
    f = fopen( "INPUT.TXT", "r" );
    OBook = userdb_load( f );
    fclose( f );

    userdb_show( OBook );

    user u1;
    user u2;

    if (
        userdb_find_by_id( OBook, id1 ) == NULL
        ||
        userdb_find_by_id( OBook, id2 ) == NULL
    ){
        fprintf( stderr, "unable to find at least one of users: %d, %d\nbye\n", id1, id2 );
        return 1;
    }

    u1 = *( userdb_find_by_id( OBook, id1 ) );
    u2 = *( userdb_find_by_id( OBook, id2 ) );

    printf( "DERPCON = %d\n", DERPCON( u1, u2 ) );

    userdb_destroy( OBook );

    return 0;
}
