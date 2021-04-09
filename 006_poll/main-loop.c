#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <sys/ioctl.h>
#include "cdata_ioctl.h"

int main(int argc, char **argv)
{
	//file descriptor
	int fd;
	int rc=0;
	char *rd_buf[16];
	int ret;
	struct pollfd fds;
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

	fds.fd=fd;
	fds.events=POLLIN;

	while(1)
	{
	
		ret = poll(&fds,sizeof(fds)/sizeof(struct pollfd),2000);

		if(ret==-1)
		{
			perror("poll failed\n");
			return -1;
		}

		if(fds.revents & POLLIN)
		{
			//Issue a read
			rc=read(fd, rd_buf,0);
			if(rc==-1)
			{
				perror("read failed");
				close(fd);
				exit(-1);
			}

			printf("%s: read: returning %d bytes!\n", argv[0], rc);
			break;
		}
	}//end of while

		close(fd);
		return 0;

}
