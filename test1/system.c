#include "apue.h"

int main(int argc, char const *argv[])
{

	printf("父亲实际的用户id%d,有效的用户id%d\n",getuid(),geteuid() );
	pid_t p;
	if((p=fork())==0){
		seteuid(getuid());
		//seteuid(0);
		//system("./system2");
		execl("./system2",NULL);
	//printf("儿子实际的用户id%d,有效的用户id%d\n",getuid(),geteuid() );

	}
	// system("date");
	// system("ls -al
	printf("%s\n",getlogin() );
	printf("%d\n",getpwuid() );

		return 0;
}