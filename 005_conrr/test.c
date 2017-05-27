#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "cdata_ioctl.h"

int main(void)
{
    int fd;
    int ret_val=0;
    char hostname[128];
    pid_t child;
    char* private_d="hi, hugh is here";
    hostname[127] = '\0';

		//get host name via unistd.h
    gethostname(hostname, 128);
		printf("hostname=%s\n", hostname);
		
		//fork a child
    child = fork();
		
		//open device 
    fd = open("/dev/cdata", O_RDWR);
 
    if(fd==-1){
			printf("1 open file failed fd=%d\n\n", fd);
    }
    
    #if 1
    if (child > 0 ){
    	write(fd, "parent:hello", 12);
    }
    else{
    	write(fd, "child:hello", 11);
    }
    #endif

    
    //1. send device name to buf firse
    ret_val = ioctl(fd, IOCTL_WRITE, hostname);
    if (ret_val < 0) {
   	 printf ("ioctl_write failed:%d\n", ret_val);
    }
	return 0;    
    //2. print device name via IOCTL_SYNC
    ret_val = ioctl(fd, IOCTL_SYNC, 0);
    if (ret_val < 0) {
   	 printf ("ioctl_sync failed:%d\n", ret_val);
    }
    
    //3. clean buf via IOCTL_EMPTY
    ret_val = ioctl(fd, IOCTL_EMPTY, 0);
    if (ret_val < 0) {
   	 printf ("ioctl_enpty failed:%d\n", ret_val);
    }

    //4. print again
    ret_val = ioctl(fd, IOCTL_SYNC, 0);
    if (ret_val < 0) {
   	 printf ("ioctl_sync failed:%d\n", ret_val);
    }

    //5. send another string to buf
    ret_val = ioctl(fd, IOCTL_WRITE, private_d);
    if (ret_val < 0) {
   	 printf ("ioctl_write failed:%d\n", ret_val);
    }

    //6. print again
    ret_val = ioctl(fd, IOCTL_SYNC, 0);
    if (ret_val < 0) {
   	 printf ("ioctl_sync failed:%d\n", ret_val);
    }

    close(fd);
    return 0;
}

