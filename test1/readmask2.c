#include "apue.h"


static void  alarm_1(int signo);
int main(int argc, char const *argv[])
{
	sigset_t oldset;
	if(sigprocmask(0,NULL,&oldset)<0) err_sys("获取屏蔽码失败");
	if(sigismember(&oldset,SIGALRM)) printf("%s\n","被屏蔽啦" );
	else
		printf("%s\n", "没有被屏蔽");

	if(signal(SIGALRM,alarm_1)==SIG_ERR) err_sys("信号注册失败！");
	//pause();
	alarm(10);
	printf("%s\n","--" );


	return 0;
}

static void alarm_1(int signo){
	pause();
	//printf("%s\n","信号到达！" );
}
