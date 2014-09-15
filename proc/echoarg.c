#include "apue.h"
/****
打印所有的变量参数 其中arg[0]的值就是函数名
注意：
1.arg和env的类型都是一致的
2.arg env的类型必须是指针的指针类型，不允许是其他的指针或数组形式
即：必须是**argv或者*argv[]
	不允许是*argv或者argv[][]的形式
**/
int
main(int argc, char **argv,char *env[])
{
	int		i;

	for (i = 0; i < argc; i++)		/* echo all command-line args */
		printf("argv[%d]: %s\n", i, argv[i]);
	exit(0);
}
