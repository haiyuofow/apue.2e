#include "apue.h"

int main(int argc, char const *argv[])
{

	printf("实际的用户id%d,有效的用户id%d\n",getuid(),geteuid() );

	return 0;
}