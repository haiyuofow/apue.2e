#include "apue.h"
#include <fcntl.h>

/***
因为父子进程都需要对output文件进行操作，所以就会发生竞争
**/
char *out1="output information\n";

void print();
int main(int argc, char const *argv[])
{
	pid_t p;
	//fcntl(1);

	if((p=fork())>0){
		print();
	}
	else if(p==0){

	 print();	
	}
	return 0;
}

void
print(){
	char *out="output information\n";
	char *p;
	int c;
	setbuf(stdout,NULL);//取消缓存，使完成一次操作要多次调用系统调用，这同时说明这里的缓存是在用户空间的，因为数据本身就是用户空间的
	for((p=out);(c=*p++);)
		putc(c,stdout);
}