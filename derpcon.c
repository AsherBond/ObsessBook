#include <stdio.h>
#include <stdlib.h>

#include "user.h"
#include "derpcon.h"

int const MAX_LIST = 1024;

int DERPCON( ua, ub )
    user ua;
    user ub;
{

    user *a, *b;

    a = &ua;
    b = &ub;

    user ** seen, ** current, ** later;
    int nseen = 0, ncurrent = 0, nlater = 0;

    seen = malloc( sizeof( user * ) * MAX_LIST );
    current = malloc( sizeof( user * ) * MAX_LIST );
    later = malloc( sizeof( user * ) * MAX_LIST );

    int result = 0;
    int distance = 0;

    int i,j;

//    printf( "[%s]vs[%s]\n", a -> name, b -> name );

//    printf("distance = %d\n", distance );
    current[ ncurrent++ ] = a;

    while( ( ncurrent || nlater ) && distance < 7 ){
        if ( ncurrent ){
  //          printf( "Current: %s\n", current[ncurrent-1] -> name );
            if ( current[ncurrent-1] -> user_ID == b -> user_ID ){
                result = distance;
                break;
            }
            else {
                seen[ nseen++ ] = current[ ncurrent-1 ];
                for ( i = 0; i < current[ ncurrent-1 ] -> number_of_BFFs; i++ ){
//                    printf("adding %s's friend %s\n", current[ ncurrent-1 ]->name, current[ ncurrent-1 ] -> BFF_list[i] -> name );
                    int already = 0;
                    for ( j = 0; j < nseen; j++ ){
                        if ( seen[j] == current[ ncurrent-1 ] -> BFF_list[i] ){
                            already = 1;
                            break;
                        }
                    }
                    if ( already == 0 ){
                        later[ nlater++ ] = current[ ncurrent-1 ] -> BFF_list[i];
                    }
                }
            }
            ncurrent--;
            continue;
        }
        if ( nlater ){
            distance++;
//            printf("increasing distance = %d\n", distance);

            user ** tmp;
            tmp = current;
            current = later;
            later = tmp;

            ncurrent = nlater;
            nlater = 0;
        }
    }

    free( seen );
    free( current );
    free( later );

    return result;
}

