#include <string.h>
#include <stdio.h>

#define BUF_LEN 1500 
#define SMALL_BUF_LEN 14

int eval( char* str ) {
    int i;
    for (i = 0; i < BUF_LEN-1; i++) {
        if ( str[i] != 'a' ) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char* argv[])
{
    if (argc == 2) {
        FILE *file = fopen( argv[1], "r" );
        if ( file != NULL ) {    
           char input[BUF_LEN];
	   if ( fgets( input, BUF_LEN, file ) != NULL) {
                if (eval(input)){
                     char buf[SMALL_BUF_LEN];
                     strcpy(buf,input);
	   }
           fclose(file);
    }
  }
}
return 0;
}
