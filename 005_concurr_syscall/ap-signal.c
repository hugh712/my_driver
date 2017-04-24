#include <linux/unistd.h>
#include <stdio.h>
#include <stdlib.h>

int CustomEvent_signal(int flag){
	return syscall(__NR_CustomEvent_signal,flag);
}

int main(int argc, char ** argv)
{
	int i;
	if(argc !=2)
		return -1;

	i=CustomEvent_signal(atoi(argv[1]));
	printf("%d\n", i)
	return 0;
}
