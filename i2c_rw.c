//==================================================================================
// This code is provided by “EmbeddedCraft.org” without any warranty.
// You are free to use it for whatever is the your purpose and redistribute it and please give credit to “EmbeddedCraft.org”
// EmbeddedCraft is the information portal for Embedded System.
// This site is useful for those who are working in embedded system domain or start new career in this field. We provide informative articles from various fields of the embedded technologies.
// If you have any comment or suggestions,please feel free to reach us at
// query at embeddedcraft.org
//==================================================================================
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <time.h>
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)       ;
}
/* Address of the EEPROM on the BeagleBone Black board */
#define I2C_ADDRESS 0x50

int main(void)
{
	int f,i=0;
	int n=0;
	char buf[10];

	/* Open the adapter and set the address of the I2C device */
	f = open("/dev/i2c-2", O_RDWR);
	if (f < 0) {
		perror("/dev/i2c-2:");
		return 1;
	}

	/* Set the address of the i2c slave device */
	if (ioctl(f, I2C_SLAVE, I2C_ADDRESS) == -1) {
		perror("ioctl I2C_SLAVE");
		return 1;
	}
	delay(1);// delay of one second
// write 9  bytes at 0x50*/
	buf[0] = 0x50; // starting address of eeprom
	buf[1] = 0x30; // 0x30 will be stored in location 0x50
	buf[2] = 0x31; // 0x31 will be stored in location 0x51
	buf[3] = 0x32; // 0x32 will be stored in location 0x52
	buf[4] = 0x33; // 0x33 will be stored in location 0x53
	buf[5] = 0x34; // 0x34 will be stored in location 0x54
	buf[6] = 0x35; // 0x35 will be stored in location 0x55
	buf[7] = 0x36; // 0x36 will be stored in location 0x56
	buf[8] = 0x37; // 0x37 will be stored in location 0x57
	buf[9] = 0x38; // 0x38 will be stored in location 0x58

// writing data to memory location 0x50 onwards.
	n = write(f, buf, 10);
	if (n == -1) {
		perror("\n 63 write");
		return 1;
	}
	delay(1);   // delay of one second
//========================
// read
//===============
/* Set the 8-bit address to read (0x50) */
buf[0] = 0x50;	/* address byte 1 */

n = write(f, buf,1);
if (n == -1) {
	perror("\n 75 write");
	return 1;
}
	delay(1);   // delay of one second
// clear buffer
for (i=0;i<10;i++)
{
	buf[i]= 0;
}

/* Now read 9 bytes from memory location 0x50 address */
n = read(f, buf, 9);
if (n == -1) {
		perror("read");
		return 1;
	}

printf("\nReading ..\n");
printf("0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",buf[0], buf[1], buf[2], buf[3],buf[4],buf[5],buf[6],buf[7],buf[8]);
close(f);
return 0;
}
