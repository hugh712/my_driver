#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include "src/cdata_ioctl.h"

int main(int argc, char **argv)
{
	//file descriptor
	int fd;
	int rc=0;
	char rd_buf[200];
	char *harry="Harry Potter is The Boy Who Lived, singled out by Lord Voldemort at birth to be his greatest rival, and our hero";
	int ret;
	printf("%s: entered\n", argv[0]);
	
	printf("origin string=%s\n", harry);
	
	memset(rd_buf,'\0',strlen(rd_buf));
	//open the device
	fd=open("/dev/cdata", O_RDWR);
	if (fd==-1)
	{
		perror("open failed");
		rc=fd;
		exit(-1);
	}
	printf("%s: open: successful\n", argv[0]);

	//send ioctl set MEM_CLEAR
	ret=ioctl(fd,MEM_CLEAR,"");
	if(ret < 0)
	{
		printf("ioctl mem_clear failed:%d\n", ret);
		exit(-1);
	}
	
	//send ioctl set PORT1_SET
	ret=ioctl(fd,PORT1_SET,"");
	if(ret < 0)
	{
		printf("ioctl port1_set failed:%d\n", ret);
		exit(-1);
	}

	//Issue a write
	rc=write(fd, harry,strlen(harry));
	if(rc==-1)
	{
		perror("write failed");
		close(fd);
		exit(-1);
	}

	//Issue a seek
	rc=lseek(fd, 0,0);
	if(rc==-1)
	{
		perror("lseek failed");
		close(fd);
		exit(-1);
	}

	//Issue a read
	rc=read(fd, rd_buf,strlen(harry));
	if(rc==-1)
	{
		perror("read failed");
		close(fd);
		exit(-1);
	}
	printf("read buffer=\n");
	printf("%s\n", rd_buf);

	close(fd);
	return 0;

}
