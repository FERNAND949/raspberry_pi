#include "raspiPwm.h"

#include "server.h"
#include <iostream>

#define GPIO_INTPUT 0x0
#define GPIO_OUTPUT 0x1
#define GPIO_ALT1 0x4
#define GPIO_ALT2 0x5
#define GPIO_ALT3 0x6
#define GPIO_ALT4 0x3
#define GPIO_ALT5 0x2

#define High 1
#define Low 0

int main(int argc, char const* argv[])
{
//	TcpServer server;

	Init();
	// server.Init();

//	gpioConfig(25, GPIO_OUTPUT);
//	gpioConfig(18, GPIO_OUTPUT);

	// pwm
	pwmInit();
	gpioConfig(18, GPIO_ALT5);
	pwmConfig();
//	pwmSet20ms();


//	softPwmCreate(18,90);
	//softPwmWrite(18,90);


	std::cout << "system start" << std::endl;
	int command = 0;

	while (1) {


		// command = server.Read();
		// if (command == 1) pinSet(25, High);
		// if (command == 2) pinSet(25, Low);
		// if (command == 0) break;


	std::cout << "command in = " ;
		std::cin >> command;
	pwmSet(command);
		 if (command == 0) break;
	}


	std::cout << "system stop" << std::endl;
	return 0;
}
