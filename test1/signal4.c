#include "apue.h"
#include <signal.h>

/****
	1.sigsuspend函数会自动实现pause功能，他在等待到一个信号后会用自己的屏蔽字来代替信号处理函数默认设置的屏蔽字，
	并且他会在信号执行完成后把信号带回到自己执行的位置，也就是说suspend本身还实现了sigsetjmp siglongjmp功能，并且在返回后恢复函数执行前的屏蔽字
***/
static void sig_int(int signo);
int main(int argc, char const *argv[])
{
	sigset_t newmask,oldmask,waitmask;

	pr_mask("默认的屏蔽字：");

	sigemptyset(&newmask);
	sigemptyset(&oldmask);
	sigemptyset(&waitmask);
	sigaddset(&newmask,SIGUSR1);
	sigaddset(&waitmask,SIGUSR2);
	signal(SIGUSR1,sig_int);

	if(sigprocmask(SIG_BLOCK,&newmask,NULL)<0)
		err_sys("更改默认屏蔽字");

	pr_mask("默认对照组suspend前：");
	sigsuspend(&waitmask);
	pr_mask("默认对照组suspend后：");


	return 0;
}

static void sig_int(int signo){
	pr_mask("USR1默认对照组suspend中：");

}