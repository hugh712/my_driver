#include <linux/unistd.h>
#include <stdio.h>
#include <stdlib.h>

int CustomEven_wait(int flag){
	return syscall(__NR_CustomEvent_wait,flag);
}

int main(int argc, char ** argv)
{
	int i;
	if(argc !=2)
		return -1;

	i=CustomEvent_wait(atoi(argv[1]));
	printf("%d\n", i)
	return 0;
}
