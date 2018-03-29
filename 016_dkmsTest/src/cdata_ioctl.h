#ifndef _CDATA_IOCTL_H_
#define _CDATA_IOCTL_H_

#include <linux/ioctl.h>

#define IOCTL_EMPTY  _IO(0xD0, 1)
#define IOCTL_SYNC  _IO(0xD1, 2)
#define IOCTL_NAME _IOW(0XD2, 3, int)
#define MEM_CLEAR _IO(0XD3, 4)
#define PORT1_SET _IOW(0XD4, 4, int)
#define PORT2_SET _IOW(0XD5, 4, int)
#endif
