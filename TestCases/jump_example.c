#include<stdio.h>
#include<setjmp.h>
jmp_buf buf;

void func(char* str)
{
    printf("func\n");
 
    int sum = 0;
    int len = strlen( str );
    int i;
    for (i = 0; i < len; i++) {
        sum += str[i];
    }
    int n = sum % 10240;
    // Jump to the point setup by setjmp
    longjmp(buf, n);
}
 
int main(int argc, char* argv[])
{
    int num = setjmp(buf);
    // Setup jump position using buf and return 0
    if (num != 0) {
	printf("enter setjmp");
	return 1000/(num-1);
    }
    else
    {	
	FILE *file = fopen( argv[1], "r" );
	char str[2048];
	fgets(str, 2048, file);
        printf("call func\n");
        func(str);
	//return 1000/num;
    }
    return 0;
}
