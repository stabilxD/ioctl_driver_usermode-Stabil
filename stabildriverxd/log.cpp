#include <ntifs.h>
#include <stdarg.h>
#include "log.h"


void Log::Print(const char* text, ...)
{
	va_list(args);
	va_start(args, text);

	vDbgPrintExWithPrefix(" ", 0, 0, text, args);

	va_end(args);
}