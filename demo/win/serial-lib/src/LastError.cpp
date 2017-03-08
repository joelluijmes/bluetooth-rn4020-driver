#include "LastError.h"

// std libraries
#include <Windows.h>
#include <string>

std::string GetLastErrorMessage()
{
	DWORD errorMessageID = GetLastError();
	if (errorMessageID == 0)
		return std::string();

	LPSTR messageBuffer = NULL;
	size_t size = FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		errorMessageID,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&messageBuffer),
		0,
		NULL);

	std::string message(messageBuffer, size);
	LocalFree(messageBuffer);
	
	return message;
}
