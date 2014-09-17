#include "apue.h"
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
/***
睡觉之前不是应该先打印开始睡觉的吗  为什么不是啊
***/
jmp_buf env;
int sleep2(int sec);
void alm(int signo);
int main(int argc, char const *argv[])
{
	
	printf("%s\n", "开始睡觉");
	//sleep2(5);
	sleep(4);
	printf("%s\n", "睡醒啦");
	return 0;
}

int sleep2(int sec){
	if(signal(SIGALRM,alm)==SIG_ERR)return sec;
	if(setjmp(env)==0){
		alarm(sec);
		pause();
	}
	return alarm(0);


}

void alm(int signo){
	longjmp(env,1);

}