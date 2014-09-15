#include "apue.h"
#include <sys/wait.h>

/***
1.无论是env还是argv后面都需要以NULL或0或(char*)0结尾，因为他们是**char类型的*char必须和字符串一样保持0结尾的规则才能使用
2.虽然unix提供了四个exe函数，但是都是对系统调用execve的包装，他们的区别正如函数接口的要求是一样的，没有太大区别。。。
**/

char	*env_init[] = { "USER=unknown", "PATH=/Users/zhanghaiyu/Documents/apue.2e", NULL };
//char	*env_init[] = { NULL };

int
main(void)
{
	pid_t	pid;

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {	/* specify pathname, specify environment */
		/**
		1.首先是execle是栈内平衡的，必须传递规定参数的个数，否则编译不通过
		2.execle虽然是单独传了环境变量，但是第一个值还是必须给定的是文件路径，也就是说执行的时候，不会自动到path里寻找文件名，即使传过去的环境变量里
		指定了PATH，也不会触发这个搜索过程
		3.环境变量可以传值也可以不传值，但是指定位置必须占位
		4.argv[0]是从第二个位置开始的，好像你即使传的不是文件名也没有什么影响
		**/
		if (execle("../echoall", "echoall","-al", NULL,env_init) < 0)
			err_sys("execle error");
	}

	if (waitpid(pid, NULL, 0) < 0)
		err_sys("wait error");

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {	/* specify filename, inherit environment */
		/***
		1.只需要指定file不需要指定path，会自动在环境变量的path目录下寻找匹配
		2.不需要指定环境变量
		**/
		if (execlp("ls", "-al", (char *)0) < 0)
			err_sys("execlp error");


	if (waitpid(pid, NULL, 0) < 0)
		err_sys("wait error");

	}if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {	/* specify filename, inherit environment */
		/***
		1.这里的环境参数是单独罗列的，
		2.同样不需要环境变量选项
		**/
		char **avg[]={"cat","/etc/passwd",NULL};
		if (execvp("cat", avg) < 0)
			err_sys("execlp error");

	}
	if (waitpid(pid, NULL, 0) < 0)
		err_sys("wait error");

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {	/* specify filename, inherit environment */
		/***
		这里的调用方式才是和main的对应的。。。
		**/
		char *env[]={NULL};
		char **avg[]={"echo","+++++++++++++++++++++============",NULL};
		if (execve("/bin/echo", avg,env) < 0)
			err_sys("execlp error");

	}

	exit(0);
}
