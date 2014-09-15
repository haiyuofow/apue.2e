#include "apue.h"
#include <sys/wait.h>
int main(int argc, char const *argv[])
{
	pid_t p;
	int status;
	/**
	退出的原因有很多种，每种都有一个标记数字，可以用wait获得，然后可以找到对应的意义
	**/

	if((p=fork())==0)exit(0);
	if(wait(&status)<0) err_sys("等待失败!");
	else printf("%s%d\n","exit(0)",status );

	if((p=fork())==0)exit(7);
	if(wait(&status)<0) err_sys("等待失败!");
	else printf("%s%d\n","exit(7)",status );

	if((p=fork())==0)abort();
	if(wait(&status)<0) err_sys("等待失败!");
	else printf("%s%d\n","abort()",status );

	if((p=fork())==0) return 0;
	if(wait(&status)<0) err_sys("等待失败!");
	else printf("%s%d\n","/0",status );
	


	return 0;
}