#include "apue.h"
#include <sys/times.h>
int main(int argc, char const *argv[])
{
	
	long clktck=sysconf(_SC_CLK_TCK);
	printf("每秒钟的时钟滴答数，即对于本机器一秒等于多少滴答---%ld\n", clktck);
	struct tms tmsstart,tmsend;
	clock_t start,end;
	start=times(&tmsstart);
	//system("");
	int i=0;
	for(i=0;i<100;i++){
		printf("%d\n",i );
	}

	end=times(&tmsend);

	printf("墙上时钟运行的时间是%ld\n",(end-start)/(clktck) );
	printf("用户空间cpu运行的时间是%ld\n",(tmsend.tms_utime - tmsstart.tms_utime)/(clktck) );
	printf("系统空间cpu运行的时间是%ld\n",(tmsend.tms_stime -tmsstart.tms_stime)/(clktck) );

	printf("子进程用户空间cpu运行的时间是%ld\n",(tmsend.tms_cutime - tmsstart.tms_cutime)/(clktck) );
	printf("子进程系统空间cpu运行的时间是%ld\n",(tmsend.tms_cstime -tmsstart.tms_cstime)/(clktck) );

	return 0;
}