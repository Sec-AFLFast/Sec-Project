#include <stdio.h>
#include <string.h>
int eval( int i ) {
    if (i%2==0)
    {
        int k=i*4;
        if(k==256)
        {
         int x=0;
         while(x<600)
         {
            x=x+3;;
         }
         if(x==600)
         {
            return 1;
         }
        }
    }
    return 0;
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
