#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include "libtempsensor.h"

#define DEV_I2C "/dev/i2c-1"
#define SLAVE_ADDR 0x4C

unsigned char buf[2];

unsigned char* getTemp(void)
{
    int fd;
    int ret;

    fd = open(DEV_I2C, O_RDWR);

    if (fd < 0) {
        printf("ERROR open %s ret=%d\n", DEV_I2C, fd);
        return NULL;
    }

    if (ioctl(fd, I2C_SLAVE, SLAVE_ADDR) < 0) {
        printf("ERROR ioctl() set slave address\n");
        return NULL;
    }

    buf[0] = 0x04;
    buf[1] = 0x04;

    ret = write(fd, buf, 2);

    if (ret != 2) {
        printf("ERROR write() conversion rate\n");
        return NULL;
    }

    buf[0] = 0x00;

    ret = write(fd, &buf[0], 1);

    if (ret != 1) {
        printf("ERROR write() register address\n");
        return NULL;
    }

    buf[1] = 0;

    ret = read(fd, &buf[1], 1);

    if (ret != 1) {
        printf("ERROR read() data\n");
        return NULL;
    }
    
    close(fd);

    return (unsigned char *)buf;
}
