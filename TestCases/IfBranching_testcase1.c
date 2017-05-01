include <stdio.h>
#include <string.h>
#define BUF_LEN 12
#define SMALL_BUF_LEN 6
int eval( char* str ) {
    if ( strlen( str ) > 4)
     {
        if(str[0]=='a')
        {
            if(str[1]=='b')
            {
                if(str[2]=='c')
                {
                    if(str[3]=='d')
                    {
                        if(str[4]=='d')
                        {
                            if(str[5]=='c')
                            {
                                if(str[6]=='b')
                                {
                                    if(str[7]=='a')
                                    {
                                       return 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
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