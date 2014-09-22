#include "apue.h"
#include <setjmp.h>
#include <time.h>
/*****
实验现象：
	1.信号在执行的时候，系统会自动设置当前进程的信号屏蔽位置以阻塞重发新发送到该进程的当前喜好继续执行
	但是，信号执行完，一般都是直接推出了，没有办法再返回到主进程如果需要返回需要使用sigsetjmp siglongjmp 也就是说信号编程不同于事件编程的
	地方，在高级的语言中我们从来感觉不到sigsetjmp siglongjmpc存在的必要性，但是在c的信号编程中，这个类似的就是硬件的中断，面向底层的开发必然
	要设置更多的工作，而不是都是别人提供好的
	2.使用alrm需要特别注意 如果alarm的参数为0 并不是表示立即执行而是表示取消之前的闹钟，另外如果定时时间没到的适合程序终止，也是不会执行的 这是alarm使用
	最容易出错的两个地方
	3.为了正确的返回到断点处，我们使用了sigsetjmp 但是一位信号已经在前面注册好啦，就表示信号就随时可以发生处理啦，但是如果在断点设置好之前发生了信号处理
	那么就不能调回来拉。所以可以设置一个锁来保证返回点设置好之前不允许处理信号 就是sig_atomic_t canjump  
	注意：这个变量赋值操作是个原子操作，不必担心标志也出现上述问题。。 另外因为这个变量出现在main 和sig_usr1这两个异步执行的程序中，可以会发生抢资源所以
	用volatile修饰
	4.在信号发生处理期间新发生的信号被屏蔽啦，但是并没有被丢弃而是当当前信号处理完成后立即处理的，但是被记录的只有一个，也就说信号执行期间如果重复又发生了多次
	这个信号，那么信号处理完成后只会处理上述多个信号的一个。
	这里信号自动屏蔽适合中端不能嵌套相对应的，中断处理的时候会首先关中断和这里首先设置屏蔽位是一个意思
	5.


***/
static void sig_usr1(int signo);
static void sig_alrm(int signo);
static void check(char *str);
static sigjmp_buf jmpbuf;
static volatile sig_atomic_t canjump;
int main(int argc, char const *argv[])
{
	
	if(signal(SIGUSR1,sig_usr1)==SIG_ERR)
		err_sys("SIGUSR1信号处理函数注册失败");
	if(signal(SIGALRM,sig_alrm)==SIG_ERR)
		err_sys("SIGALRM信号处理函数注册失败");
	check("函数初始化。。");
	// alarm(1);

	sigsetjmp(jmpbuf,1);//这里如同是在设置断点，信号会返回到这个断点的位置
	canjump=1;
	printf("%s\n","信号跳转回来啦\n" );


	pause();


	return 0;
}

static void sig_usr1(int signo){
	if(canjump==0)return;//等于0是默认值
	check("sig_usr1");
	time_t start;
	start=time(NULL);
	//alarm(5);//这是知识触发3秒后执行alarm操作而不是阻塞等待
	for(;;)
		if(time(NULL)>start+5) break;

	siglongjmp(jmpbuf,1);

}

static void sig_alrm(int signo){
	check("sig_alrm");

}
static void check(char * str){
	sigset_t old;
	if(sigprocmask(0,NULL,&old)<0)
		err_sys("获取当前进程的信号屏蔽字失败\n");
	printf("执行检查，显示被屏蔽信号  位置是:%s\n",str);
	if(sigismember(&old,SIGINT)) printf("%s\n", "SIGINT---");
	if(sigismember(&old,SIGQUIT)) printf("%s\n", "SIGQUIT---");
	if(sigismember(&old,SIGUSR1)) printf("%s\n", "SIGUSR1---");
	if(sigismember(&old,SIGALRM)) printf("%s\n", "SIGALRM---");
}