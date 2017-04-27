#include <stdio.h>
#include <string.h>
#define BUF_LEN 12
#define SMALL_BUF_LEN 8
int eval( char* str ) {
    if ( strlen( str ) > 4  &&
        str[2] == 'r'       &&
        str[0] == 'o'       &&
        str[6] == 'a'       &&
        str[7] == 'm'       &&
        str[4] == 't'       &&
        str[1] == 'u'       &&
        str[5] == 'e') {
        return 1;
    }
    return 0;
}
int main(int argc, char* argv[])
{
    if (argc == 2) {
        FILE *file = fopen( argv[1], "r" );
        if ( file != NULL ) {
            char str[BUF_LEN];
            if ( fgets( str, BUF_LEN, file ) != NULL) {
                if ( eval( str ) ) {
                    char buf[SMALL_BUF_LEN];
                    strcpy( buf, str );
                }
            }
            fclose( file );
        }
    }
    return 0;
}
