#include <Windows.h>
#include <iostream>

#define hello_kernel CTL_CODE(FILE_DEVICE_UNKNOWN, 0x650, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

HANDLE driver_connecting;

void hello_kernel_a() {
	if (driver_connecting) {
		DeviceIoControl(driver_connecting, hello_kernel, 0, 0, 0, 0, 0, NULL);
	}
}
