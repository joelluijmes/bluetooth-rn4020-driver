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

	bool RN4020::SetHex32(const char* command, uint32_t value) const
	{
		char buf[9] = { 0 };
		snprintf(buf, 8, "%08X", value);

		return Set(command, buf);
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

	bool RN4020::GetHex32(const char* command, uint32_t* value) const
	{
		char buf[11] = { 0 };
		if (!GetString("GS", buf, sizeof(buf) - 1))
			return false;

#if ULONG_MAX >= 0xFFFFFFFFU
		unsigned long val = strtoul(buf, NULL, 16);		
#elif ULLONG_MAX >= 0xFFFFFFFFU
		unsigned long long val = strtoull(buf, NULL, 16);
#else
#error "unable to convert hex32 string to the largest integer (unsigned long long) type using std library (strtoull)"
#endif

		*value = static_cast<uint32_t>(val);
		return true;
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
