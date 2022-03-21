#include "windows_exports.h"
#include <ntddk.h>
#include "log.h"

#define hello_kernel CTL_CODE(FILE_DEVICE_UNKNOWN, 0x650, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)





NTSTATUS command(PDEVICE_OBJECT device_obj, PIRP irp) {
	auto control = IoGetCurrentIrpStackLocation(irp);
	ULONG ioctl = control->Parameters.DeviceIoControl.IoControlCode;
	ULONG bytes_io = 0;
	NTSTATUS status = STATUS_INVALID_PARAMETER;
		if (ioctl == hello_kernel)
		{
			Log::Print("kernel mi buuu");
		}
		else
		{
			status = STATUS_INVALID_PARAMETER;
			ULONG bytes_io = 0;
	    }

	IoCompleteRequest(irp, IO_NO_INCREMENT);
	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = sizeof(NULL);
	return irp->IoStatus.Status;
}


NTSTATUS driver_object(PDRIVER_OBJECT driver, PUNICODE_STRING registery_path) {
	auto status = STATUS_SUCCESS;
	UNICODE_STRING sym_link, dev_name;
	PDEVICE_OBJECT dev_obj;

	RtlInitUnicodeString(&dev_name, L"\\Device\\stabildriverxd");
	status = IoCreateDevice(driver, 0, &dev_name, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &dev_obj);

	if (status != STATUS_SUCCESS) {
		return status;
	}

	RtlInitUnicodeString(&sym_link, L"\\DosDevices\\stabildriverxd");
	status = IoCreateSymbolicLink(&sym_link, &dev_name);

	if (status != STATUS_SUCCESS) {
		return status;
	}

	dev_obj->Flags |= DO_BUFFERED_IO;

	for (int t = 0; t <= IRP_MJ_MAXIMUM_FUNCTION; t++)
		driver->MajorFunction[t] = unsupported_io;

	driver->MajorFunction[IRP_MJ_CREATE] = create_io;
	driver->MajorFunction[IRP_MJ_CLOSE] = close_io;
	driver->MajorFunction[IRP_MJ_DEVICE_CONTROL] = command;
	driver->DriverUnload = NULL;

	dev_obj->Flags &= ~DO_DEVICE_INITIALIZING;

	return status;
}

extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT object, PUNICODE_STRING registry)
{
	UNREFERENCED_PARAMETER(object);
	UNREFERENCED_PARAMETER(registry);
	auto status = STATUS_SUCCESS;
	UNICODE_STRING  drv_name;
	RtlInitUnicodeString(&drv_name, L"\\Driver\\stabildriverxd");
	status = IoCreateDriver(&drv_name, &driver_object);
	return STATUS_SUCCESS;
}
