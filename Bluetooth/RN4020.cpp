#include "RN4020.h"

// std libraries
#include <string.h>

// RN4020 Constants
#define MAX_SERIALIZED_NAME 15
#define MAX_NAME_LEN 20

// RN4020 Commands
#define CMD_SET_SERIALIZED_NAME "S-,"
#define CMD_GET_SERIALIZED_NAME "G-"

#define CMD_SET_NAME "SN,"
#define CMD_GET_NAME "GN"

namespace Bluetooth
{
	bool RN4020::SetName(const char* name, uint8_t len) const
	{
		if (len > MAX_NAME_LEN)
			return false;

		char buf[MAX_NAME_LEN + sizeof(CMD_SET_NAME)] = CMD_SET_NAME;
		strncpy(buf + sizeof(CMD_SET_NAME) - 1, name, len);

		if (!ReadWrite(buf, strlen(buf), buf, sizeof(buf)))
			return false;

		return strncmp(buf, "AOK", 3) == 0;
	}

	bool RN4020::GetName(char* name, uint8_t len) const
	{
		char buf[] = CMD_GET_NAME;
		return ReadWrite(buf, strlen(buf), name, len);
	}

	bool RN4020::SetSerializedName(const char* name, uint8_t len) const
	{
		if (len > MAX_SERIALIZED_NAME)
			return false;

		char buf[MAX_SERIALIZED_NAME + sizeof(CMD_SET_SERIALIZED_NAME)] = CMD_SET_SERIALIZED_NAME;
		strncpy(buf + sizeof(CMD_SET_SERIALIZED_NAME) - 1, name, len);

		if (!ReadWrite(buf, strlen(buf), buf, sizeof(buf)))
			return false;

		return strncmp(buf, "AOK", 3) == 0;
	}

	bool RN4020::GetSerializedName(char* name, uint8_t len) const
	{
		char buf[] = CMD_SET_SERIALIZED_NAME;
		return ReadWrite(buf, sizeof(buf), name, len);
	}
}
