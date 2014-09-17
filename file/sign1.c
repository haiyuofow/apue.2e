#include "apue.h"

void sign_ac();
int main(int argc, char const *argv[])
{
	signal(SIGUSR1,sign_ac);
	signal(SIGUSR2,sign_ac);
	for(;;)pause();
	return 0;
}

void
sign_ac(int no){
	switch(no){
		case SIGUSR1:
		printf("%s\n", "SIGUSER1被捕获啦");
		break;
		case SIGUSR2:
		printf("%s\n", "SIGUSER1被捕获啦");
		break;
		default:
		printf("Error No %d\n",no );
		break;
	}

}