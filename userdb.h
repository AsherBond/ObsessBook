#ifndef __USERDB_H__

typedef struct {
    unsigned int    usercount;
    user * *        users;
} userdb;

userdb * userdb_load( FILE * );
void userdb_destroy( userdb * );
void userdb_show( userdb * );
user * userdb_find_by_id( userdb *, int );

#endif
