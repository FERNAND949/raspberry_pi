#include "raspiConfig.h"
#include <iostream>

static volatile unsigned int *Gpio = NULL;
static volatile unsigned int *Pwm = NULL;
static volatile unsigned int *Clk = NULL;


void Init()
{

	Gpio = addMapping(GPIO_ADD);
	Pwm = addMapping(PWM_ADD);
	Clk = addMapping(CLOCK_ADD);

	std::cout << "Init OK" << std::endl;
}

volatile unsigned int *addMapping(int add)
{

	int fd;
	void *add_map;  // gpio用の汎用アドレス

	fd = open("/dev/mem", O_RDWR | O_SYNC);
	if (fd == -1) std::cout << "error fd=open" << std::endl;

	// 物理アドレスと仮想アドレスの対応づけ
	add_map =
	    mmap(NULL, BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, add);
	if ((int)add_map == -1) std::cout << "error mmap" << std::endl;

	close(fd);

	return (unsigned int *)add_map;
}

/* gpio
 * p1: 2,3,4,7,8,9,10,11,14,15,17,18,22,23,24,25,27
 * p5: 28,29,30,31
 */
void gpioConfig(int pin, int mode)
{
	if (pin < 0 || pin > 31) {

		std::cout << "error fd=open" << std::endl;
		exit(-1);
	}

	int index = pin / 10;
	unsigned int mask = ~(0x7 << ((pin % 10) * 3));

	Gpio[index] = (Gpio[index] & mask) | ((mode & 0x7) << ((pin % 10) * 3));
}

// 出力
void pinSet(int pin, int out)
{
	// データシートより7番目がOUTPUT，10番目がOUTPUT CLEARの設定レジスタ
	if (out == 1) {
		// GPSET0
		Gpio[7] = 0x1 << pin;
	}
	if (out == 0) {
		// GPCLR0
		Gpio[10] = 0x1 << pin;
	}
}

void pwmConfig()
{
	// pwmの設定
	// pwm frequency = 19.2MHz / clock / range らしい
	// clockとrangeは自分で決める
	uint pwm_control;
	int divi=400;

	divi &=4095;

	pwm_control = *(Pwm + PWM_CTL);
	*(Pwm + PWM_CTL) = 0;

	*(Clk + CM_CTL) = BCM_PASS | 0x01;
	usleep(110);

	while ((*(Clk + CM_CTL) & 0x80) != 0) usleep(1);

	// 19.2MHz/1920 = 10KHz
	// オシロで見ると
	// 1920 = 200usになる
	*(Clk + CM_DIVI) = BCM_PASS | (divi << 12);

	// src=osc enable clock
	*(Clk + CM_CTL) = BCM_PASS | 0x11;
	*(Pwm + PWM_CTL) = pwm_control;

	*(Pwm + PWM_CTL) = PWM0_ENABLE | PWM1_ENABLE | PWM0_MS_MODE;

	*(Pwm + PWM_RNG1) = 1000;
	*(Pwm + PWM_DAT1) = 500;
}

void pwmSet(int v)
{
	*(Pwm + PWM_DAT1) = v;
}
