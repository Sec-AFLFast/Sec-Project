#include <stdio.h>
#include <string.h>
void eval( int x, int y ) {
   int z=2*y;
   if(x==100000)
   {
    if(x<z)
    {
        abort(); // error
    }
   }
}
int main(int argc, char* argv[])
{
    if (argc == 2) {
        FILE *file = fopen( argv[1], "r" );
        int i = 0, j=0;
        if ( file != NULL ) {
           fscanf (file, "%d %d", &i, &j);
                 eval( i,j );
            }
            fclose( file );
        }
   return 0;
    }