#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
	int a = atoi(argv[1]);
	switch(a)
	{
	case 1:
		fputs("STDOUT\n", stdout);
    		fflush(stdout);
    		fputs("STDERR\n", stderr);
    		fflush(stderr);
		break;
	case 2:
		fputs("STDOUT\n", stdout);
    		fputs("STDERR\n", stderr);
		break;
	case 3:
		freopen("nn.txt", "a+", stdout);
    		freopen("nn.txt", "a+", stderr);
    		fputs("STDOUT\n", stdout);
    		fflush(stdout);
    		fputs("STDERR\n", stderr);
    		fflush(stderr);
		break;
	default:
		fputs("Unknown parameter: ", stdout);
		break;
	}
	
    }
    else
	{
    	fputs("STDOUT", stdout);
    	fflush(stdout);
    	fputs("STDERR", stderr);
    	fflush(stderr);
	}
    return 0;
}
