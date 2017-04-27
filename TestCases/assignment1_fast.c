#include <stdio.h>
#include <string.h>

#define BUF_LEN 1024
#define SMALL_BUF_LEN 5
#define MOD_BASE 1000
#define DIV 2
#define REF_VAL (MOD_BASE - (MOD_BASE / DIV))

int f(char* str) {
    int sum = 0;
    int len = strlen( str );
    int i;
    for (i = 0; i < len; i++) {
        sum += str[i];
    }
    return sum % MOD_BASE;
}

int main(int argc, char* argv[])
{
    if (argc == 2) {
        FILE *file = fopen( argv[1], "r" );
        if ( file != NULL ) {
            char str[BUF_LEN];
            if ( fgets( str, BUF_LEN, file ) != NULL) {
                if ( f(str) == REF_VAL ) {
                    char buf[SMALL_BUF_LEN];
                    strcpy( buf, str );
                }
            }
            fclose( file );
        }
    }
    return 0;
}
