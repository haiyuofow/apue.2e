#include "apue.h"

#define VARNAME(name)(#name)
void test(sigset_t *set,int signal);
int main(int argc, char const *argv[])
{
	/*sigset_t one;
	//信号全部请0 都不是屏蔽信号
	sigemptyset(&one);
	test(&one,SIGALRM);
	test(&one,SIGINT);
	//信号添加 添加进入的是屏蔽信号
	sigaddset(&one,SIGALRM);
	sigaddset(&one,SIGINT);
	test(&one,SIGALRM);
	test(&one,SIGINT);
	//信号全部填充  都是屏蔽信号
	sigfillset(&one);
	test(&one,SIGALnews
	test(&one,SIGINT);
	//删除指定的 指定的不是屏蔽信号
	//sigdelset(&one,SIGINT);
	sigdelset(&one,SIGALRM);
	test(&one,SIGALRM);
	test(&one,SIGINT);*/


	sigset_t oldset,newset,settmp,pending;
	//1.获取屏蔽字 
	if(sigprocmask(0,NULL,&oldset)<0) err_sys("获取屏蔽字失败!");
	test(&oldset,SIGALRM);
	test(&oldset,SIGINT);
	test(&oldset,SIGUSR1);
	test(&oldset,SIGKILL);
	//说明新上述四个都没有被默认屏蔽
	puts("-------------");

	//1.屏蔽INT信号 和alrm信号
	sigemptyset(&settmp);
	//想要测试设置信号，就要把这俩个喜好设置到里面
	sigaddset(&oldset,SIGALRM);
	sigaddset(&oldset,SIGINT);
	sigaddset(&oldset,SIGKILL);//发现对kill设置屏蔽是没有效果的
	sigaddset(&oldset,SIGQUIT);//但是对quit设置屏蔽是可以的

	test(&oldset,SIGALRM);
	test(&oldset,SIGINT);
	//设置为0，只有设置并集才能设置成功  对0设置交集是没有效果的
	//这里获得屏蔽码是系统默认的旧的屏蔽码而不是新的屏蔽码  所以才能在这里保存默认的屏蔽吗
	if((sigprocmask(SIG_SETMASK,&oldset,&newset))<0)err_sys("获取屏蔽字失败！2");
	//if((sigprocmask(SIG_BLOCK,&oldset,NULL))<0)err_sys("获取屏蔽字失败！2");
	if((sigprocmask(0,NULL,&newset))<0)err_sys("获取屏蔽字失败！2");

	test(&newset,SIGALRM);
	test(&newset,SIGINT);
	test(&newset,SIGKILL);
	test(&newset,SIGQUIT);
	puts("---------");
	//pending是悬而未决的意思，就是信号产生啦，但是因为屏蔽啦，所以信号不能立即执行而要等屏蔽解除了才能传递到 这段时间就是悬而未决的就是sigpending
	if(sigpending(&pending)<0) err_sys("悬而未决的\n");
	test(&newset,SIGQUIT);



	
	
	return 0;
}

void test(sigset_t *set,int signal){
	if(sigismember(set,signal)){
		printf("%s    %d是屏蔽信号\n",VARNAME(signal) ,signal);
	}else{
		printf("%s     %d不是屏蔽信号\n",VARNAME(signal),signal );
	}
}