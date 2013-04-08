#include <stdio.h>
#include "user.h"

void user_show( U )
    user * U;
{
//        printf("at %p ", U );
        printf("%s ", U -> name );    
        printf("(%d) ", U -> user_ID );
        printf("[%s]", U -> account_handle );
//        printf(": ", U -> number_of_BFFs );

        printf(": ");
        int i;
        for ( i = 0; i < U -> number_of_BFFs; i++ ){
            if ( i > 0 ) printf(", " );
            printf( "%s",
                U -> BFF_list[i] -> name
//                U -> BFF_list[i] -> user_ID
            );

        }
        printf("\n");
        return;
}

