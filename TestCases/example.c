#include <stdio.h>
#include <string.h>

#define BUF_LEN 1024
#define SMALL_BUF_LEN 5
#define MOD_BASE 1000
#define DIV 2
#define REF_VAL (MOD_BASE - (MOD_BASE / DIV))

void crashme(char* s) {
    if (s[0] == 'b')
	if (s[1] == 'a')
	     if(s[2] == 'd')
		if (s[3] == '!')
		    abort();
}


int main(int argc, char* argv[])
{
    if (argc == 2) {
        FILE *file = fopen( argv[1], "r" );
        if ( file != NULL ) {
            char str[BUF_LEN];
            if ( fgets( str, BUF_LEN, file ) != NULL) {
    		crashme(str);
		}
	}
    fclose(file);
    }
    return 0;
}
