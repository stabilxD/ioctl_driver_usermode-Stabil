#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include "driver.h"

void init() {
	while (true) {
		hello_kernel_a();
	}
}

int main() {
	driver_connecting = CreateFileA("\\\\.\\stabildriverxd", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	if (driver_connecting) {
		std::cout << "driver loaded.\n";
		init();
	}
	else {
		std::cout << "driver not loaded.\n";
		std::cin.get();
		return EXIT_SUCCESS;
	}
}