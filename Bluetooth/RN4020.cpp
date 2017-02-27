#include "RN4020.h"

// std libraries
#include <string.h>

// RN4020 Constants
#define MAX_SERIALIZED_NAME 15
#define MAX_NAME_LEN 20

namespace
{
	void stripNewLines(char* str) 
	{
		char* p = str;
		while (*str)
		{
			if (*p != '\r' && *p != '\n')
				*p++ = *str++;
			else
				++str;
		}

		*p = '\0';
	}
}

namespace Bluetooth
{
	const char* const RN4020::CMD_SET_SERIALIZED_NAME = "S-";
	const char* const RN4020::CMD_GET_SERIALIZED_NAME = "G-";
	const char* const RN4020::CMD_SET_NAME = "SN";
	const char* const RN4020::CMD_GET_NAME = "GN";
	const char* const RN4020::CMD_SET_BAUD = "SB";
	const char* const RN4020::CMD_GET_BAUD = "GB";
	
	bool RN4020::Set(const char* command, const char* param) const
	{
		const Serial::ISerial& serial = GetSerial();

		if (serial.Send(command, strlen(command)) == -1)
			return false;
		if (serial.Send(",", 1) == -1)
			return false;
		if (serial.Send(param, strlen(param)) == -1)
			return false;
		if (serial.Send("\r\n", 2) == -1)
			return false;

		// RN4020 returns AOK of ERR for set commands
		// (don't forget the trailling \r\n)
		char buf[5] = {0};
		int32_t received = serial.Receive(buf, sizeof(buf));
		if (received == -1)
			return false;

		return strncmp(buf, "AOK", 3) == 0;
	}

	bool RN4020::Get(const char* command, char* buf, uint8_t len, uint8_t* received) const
	{
		const Serial::ISerial& serial = GetSerial();

		if (serial.Send(command, strlen(command)) == -1)
			return false;
		if (serial.Send("\r\n", 2) == -1)
			return false;

		uint8_t tmp = serial.Receive(buf, len);
		if (received)
			*received = tmp;

		return tmp != -1;
	}

	bool RN4020::GetString(const char* command, char* buf, uint8_t len, bool stripNewLine) const
	{
		uint8_t received;
		if (!Get(command, buf, len, &received))
			return false;

		buf[received] = '\0';
		if (stripNewLine)
			stripNewLines(buf);

		return true;
	}
}
