#include "RN4020.h"

// std libraries
#include <string.h>

// RN4020 Constants
#define MAX_NAME_LEN 20
#define CMD_NAME_LEN 24

// RN4020 Commands
#define CMD_SET_NAME "SN,"
#define CMD_GET_NAME "GN"

namespace Bluetooth
{
	bool RN4020::SetDisplayName(const char* name, uint8_t len) const
	{
		if (len > MAX_NAME_LEN)
			return false;

		char buf[CMD_NAME_LEN] = CMD_SET_NAME;
		strncpy(buf + sizeof(CMD_SET_NAME), name, len);

		if (!ReadWrite(buf, strlen(buf), buf, sizeof(buf)))
			return false;

		return strncmp(buf, "AOK", 3) == 0;
	}

	bool RN4020::GetDisplayName(char* name, uint8_t len) const
	{
		char buf[] = CMD_GET_NAME;

		return ReadWrite(buf, strlen(buf), name, len);
	}
}
