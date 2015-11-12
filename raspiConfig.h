#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <dirent.h>
#include <sched.h>
#include <string.h>
#include <pthread.h>


extern 	void Init();
extern 	volatile unsigned int* addMapping(int add);
extern 	void gpioConfig(int pin, int mode);
extern 	void pinSet(int pin, int out);
extern 	void pwmConfig();
extern 	void pwmSet(int v);
    

#define PERI_ADD 0x20000000
#define GPIO_ADD PERI_ADD + 0x00200000
#define PWM_ADD PERI_ADD + 0x0020C000
#define CLOCK_ADD PERI_ADD + 0x00101000


#define BLOCK_SIZE 4096
#define BCM_PASS 0x5A000000


// pwm address offset
#define PWM_CTL 0
#define PWM_STA 1
#define PWM_RNG1 4
#define PWM_DAT1 5
#define PWM_RNG2 8
#define PWM_DAT2 9

#define PWM1_MS_MODE 0x8000  // Run in MS mode
#define PWM1_USEFIFO 0x2000  // Data from FIFO
#define PWM1_REVPOLAR 0x1000  // Reverse polarity
#define PWM1_OFFSTATE 0x0800  // Ouput Off state
#define PWM1_REPEATFF 0x0400  // Repeat last value if FIFO empty
#define PWM1_SERIAL 0x0200  // Run in serial mode
#define PWM1_ENABLE 0x0100  // Channel Enable

#define PWM0_MS_MODE 0x0080  // Run in MS mode
#define PWM0_USEFIFO 0x0020  // Data from FIFO
#define PWM0_REVPOLAR 0x0010  // Reverse polarity
#define PWM0_OFFSTATE 0x0008  // Ouput Off state
#define PWM0_REPEATFF 0x0004  // Repeat last value if FIFO empty
#define PWM0_SERIAL 0x0002  // Run in serial mode
#define PWM0_ENABLE 0x0001  // Channel Enable

#define CM_CTL 40
#define CM_DIVI 41


#define High 1 
#define Low 0 
#define GPIO_INTPUT 0x0
#define GPIO_OUTPUT 0x1


