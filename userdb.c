#include <stdio.h>
#include <stdlib.h>

#include "user.h"
#include "userdb.h"

int const READLINE_BUFFER_SIZE = 1024;
int const MAXLIST_SIZE = 1024;

userdb * userdb_load( f )
    FILE * f;
{
    char *buff;
    buff = malloc( sizeof( char ) * READLINE_BUFFER_SIZE + 1 );
    fgets( buff, READLINE_BUFFER_SIZE, f );

    int nrecords;
    userdb *DB;
    DB = malloc( sizeof( userdb ) );
    //printf( "Created DB at %p\n", DB );

    sscanf( buff, "%d", &nrecords );

    DB -> usercount = nrecords;
    DB -> users = malloc( nrecords * sizeof( user * ) );
//    printf( "Created array of %d at %p\n", nrecords, DB -> users );

    int i;

    user *U;
    for ( i = 0; i < nrecords; i++ ){
  //      printf("reading user #%d ", i );
        fgets( buff, READLINE_BUFFER_SIZE, f );
    //    printf("buffer: [%.*s...]\n", 10, buff );
        U = malloc( sizeof( user ));
      //  printf( "created users at %p\n", U );

        sscanf( buff, "%d %ms %ms\n",
            & U->user_ID,
            & U->name,
            & U->account_handle
        );

        // the list is automatically allocated with default number of entries
        U -> BFF_list = malloc( MAXLIST_SIZE * sizeof( user * ) ); // FIXME 
        U -> number_of_BFFs = 0;

        DB -> users[i] = U;
    }

    fgets( buff, READLINE_BUFFER_SIZE, f );
    sscanf( buff, "%d", &nrecords );
//    printf( "RELATIONS: %d\n", nrecords );

    for ( i = 0; i < nrecords; i++ ){
        int a,b;
        user * user_a, * user_b;

        fgets( buff, READLINE_BUFFER_SIZE, f );
        sscanf( buff, "%d %d", &a, &b );
//        printf( "rel %d vs %d\n", a, b );

        user_a = userdb_find_by_id( DB, a );
        user_b = userdb_find_by_id( DB, b );

  //      printf( "is %s vs %s\n", user_a -> name, user_b -> name );

        user_a -> BFF_list[ user_a -> number_of_BFFs++ ] = user_b;
        user_b -> BFF_list[ user_b -> number_of_BFFs++ ] = user_a;

    }

    free( buff );

    return DB;
}

void userdb_show( DB )
    userdb * DB;
{
    int i;
    printf( "USERS (%d):\n", DB -> usercount );
    for ( i = 0; i < DB -> usercount ; i++ ){
//        printf("#%d:\n", i );
        user_show( DB -> users[ i ] );
    }
}

void userdb_destroy( DB )
    userdb * DB;
{
    int i;
    for ( i = 0; i < DB -> usercount ; i++ ){
  //      printf( "destroying user #%d at %p\n", i, DB -> users[i] );
        free( DB -> users[i] -> name );
        free( DB -> users[i] -> account_handle );
        free( DB -> users[i] -> BFF_list );
        free( DB -> users[i] );
    }
//    printf("destroying [%d] users at %p\n", DB -> usercount, DB -> users );
    free( DB -> users );
//    printf("destroying DB at %p\n", DB );
    free( DB );
}

user * userdb_find_by_id( DB, id )
    userdb * DB;
    int id;
{
    int i;
    for ( i = 0; i < DB -> usercount; i++ ){
        if ( DB -> users[i] -> user_ID == id ){
            return DB -> users[i];
        }
    }
    return (user *) NULL;
}

