#include "apue.h"

/***
实验现象
如果用printf会自动对指定的文件索引设置缓冲区，因为这是设置在索引节点上的缓冲区，
而fork的适合，子进程会自动继承父进程的索引信息，所以如果缓冲区没有被fflush的话，那么缓冲区的数据也会被继承，
在子进程返回的适合会自动flush所有的缓冲区信息。。。
**/
void exit_action();
int main(int argc, char const *argv[])
{
	if(atexit(exit_action)<0)err_sys("析构函数注册失败");
	pid_t p;
	char *buf="你好\n";
	write(STDOUT_FILENO,buf,sizeof(buf));
	printf("%s\n","测试一下文件带的缓冲区" );
	//fflush(stdout);
	// printf("%s\n",buf );
	// fflush(stdout);
	if((p=fork())>0){
		printf("%s\n","子进程" );
		//调用return和exit都有一样的行为就是都会执行缓冲区的数据flush，但是调用_exit是不会执行fflush操作的，另外这里的缓冲区是进程内部的缓冲区而不是内核的
		//_exit(0);
		//exit(0);
		return 0;
	}

	return 0;
}

void exit_action(){
	printf("%s%d\n", "推出适合调用的，类似析构函数。。。\n",getpid());
}
