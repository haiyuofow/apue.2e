#include "apue.h"
#include <pwd.h>

void 
my_alarm(){
		struct passwd  *pwd;
		pwd=getpwnam("zhanghaiyu");
		printf("%s\n",pwd->pw_name );
		printf("%s\n", "信号产生！！");
		alarm(1);
}

int main(int argc, char const *argv[])
{
	
	struct passwd  *pwd;

	signal(SIGALRM,my_alarm);
	alarm(1);
	int i=0;
	for(;;){

		pwd=getpwnam("zhanghaiyu");
		printf("%s\n",pwd->pw_name );
	}

	return 0;
}