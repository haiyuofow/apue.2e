#include "apue.h"

/*****
实验说明，系统自动传值过来的环境变量只能叫environ
如果更改了这个名字，程序是不能获得这个变量的内容的，当然如果没有用exten关键字，即使使用的是传过来的变量名，也不会被自动连接
但是可以在传值的位置出给变量重新起个变量名
****/
int
main(int argc, char *argv[],char** environ1)
{
	int			i;
	char		**ptr;
	//extern char	**environ;

	for (i = 0; i < argc; i++)		/* echo all command-line args */
		printf("argv[%d]: %s\n", i, argv[i]);

	for (ptr = environ1; *ptr != 0; ptr++)	/* and all env strings */
		printf("%s\n", *ptr);

	exit(0);
}
