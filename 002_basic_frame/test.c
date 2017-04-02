#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "cdata_ioctl.h"

int main(int argc, char **argv)
{
	//file descriptor
	int fd;
	int rc=0;
	char *rd_buf[16];
	int ret;
	printf("%s: entered\n", argv[0]);

	//open the device
	fd=open("/dev/cdata", O_RDWR);
	if (fd==-1)
	{
		perror("open failed");
		rc=fd;
		exit(-1);
	}
	printf("%s: open: successful\n", argv[0]);

	//Issue a read
	rc=read(fd, rd_buf,0);
	if(rc==-1)
	{
		perror("read failed");
		close(fd);
		exit(-1);
	}

	printf("%s: read: returning %d bytes!\n", argv[0], rc);

	//send ioctl
	ret=ioctl(fd,IOCTL_WRITE,"test");
	if(ret < 0)
	{
		printf("ioctl_write failed:%d\n", ret);
	}
	

	close(fd);
	return 0;

}
