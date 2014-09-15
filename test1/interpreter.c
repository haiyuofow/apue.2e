#include "apue.h"

int main(int argc, char const *argv[])
{
	
	pid_t p;
	int uid=getuid();
	printf("父进程的UID是%d\n",uid);
	setuid(200);
	printf("父进程的UID是%d\n",uid);
	if((p=fork())==0){
		int	uid=getuid();
		//execl("../proc/echoarg","arg0","arg1","arg2","arg3");
		printf("子进程1的UID是%d\n",uid);
		_exit(0);
	}
	waitpid(p,NULL,0);
	if((p=fork())==0){
		//实验说明 实际参数不是filename而是awk
		int	uid=getuid();
		//setuid(500);
		printf("子进程2的UID是%d\n",uid);
		//_exit(0);
		//execl("/Users/zhanghaiyu/Documents/apue.2e/test1/echo","echo","arg1","arg2","arg3",NULL);
	}
	return 0;
}