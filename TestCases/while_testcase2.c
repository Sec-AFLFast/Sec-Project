#include <stdio.h>
#include <string.h>
int eval( int i ) {
    int n=10, k=1, prod=1, max=9999;
    while(k<=n)
    {
        if((max/i)<prod)
        {
           return 0;
        }
        prod=prod*i;
        k++;
    }
    return 1;
}
int main(int argc, char* argv[])
{
    if (argc == 2) {
        FILE *file = fopen( argv[1], "r" );
        int i = 0;
        if ( file != NULL ) {
           fscanf (file, "%d", &i);
                if ( eval( i ) ) {
                    abort();
                }
            }
            fclose( file );
        }
   return 0;
    }