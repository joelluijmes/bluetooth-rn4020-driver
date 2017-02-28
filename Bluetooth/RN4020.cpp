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
	bool RN4020::SetBaudRate(BaudRate baud) const
	{
		char buf[] = {static_cast<char>(baud + '0'), '\0'};
		return Set("SB", buf);
	}

	bool RN4020::GetBaudRate(BaudRate* baud) const
	{
		// 1 for result; 2 for \r\n
		char buf[3];
		if (!Get("GB", buf, sizeof(buf), NULL))
			return false;

		*baud = static_cast<BaudRate>(buf[0] - '0');
		return true;
	}

	bool RN4020::SetTiming(uint16_t interval, uint16_t latency, uint16_t timeout) const
	{
		char buf[15] = {0};
		snprintf(buf, 14, "%04X,%04X,%04X", interval, latency, timeout);

		return Set("ST", buf);
	}

	bool RN4020::GetTiming(uint16_t* interval, uint16_t* latency, uint16_t* timeout) const
	{
		char buf[17] = {0};
		if (!GetString("GT", buf, sizeof(buf) - 1))
			return false;

		char* end;

#if ULONG_MAX >= 0xFFFFU
		unsigned long val = strtoul(buf, &end, 16);
		*interval = static_cast<uint16_t>(val);
		val = strtoul(end + 1, &end, 16);
		*latency = static_cast<uint16_t>(val);
		val = strtoul(end + 1, NULL, 16);
		*timeout = static_cast<uint16_t>(val);
#elif ULLONG_MAX >= 0xFFFFU
			unsigned long long val = strtoull(buf, &end, 16);
			*interval = static_cast<uint16_t>(val);
			val = strtoull(end + 1, &end, 16);
			*latency = static_cast<uint16_t>(val);
			val = strtoull(end + 1, NULL, 16);
			*timeout = static_cast<uint16_t>(val);
#else
#error "unable to convert hex16 string to the largest integer (unsigned long long) type using std library (strtoull)"
#endif

		return true;
	}

	bool RN4020::ResetDefaults(bool fullReset) const
	{
		char buf[] = {(fullReset ? '2' : '1'), '\0'};
		return Set("SF", buf);
	}

	bool RN4020::Advertise(uint16_t interval, uint16_t window) const
	{
		if (interval == 0 && window == 0)
			return Set("A", NULL);

		char buf[10] = {0};
		snprintf(buf, 9, "%04X,%04X", interval, window);

		return Set("A", buf);
	}

	bool RN4020::Bond(bool enable) const
	{
		char buf[] = { (enable ? '1' : '0'), '\0' };
		return Set("B", buf);
	}

	bool RN4020::Establish(bool usePublicAddress, uint8_t macAddress[6]) const
	{
		char buf[9] = { (usePublicAddress ? '0' : '1'), ','};
		memcpy(buf + 2, macAddress, 6);

		return Set("E", buf);
	}

	bool RN4020::Find(uint16_t interval, uint16_t window) const
	{
		if (interval == 0 && window == 0)
			return Set("F", NULL);

		char buf[10] = { 0 };
		snprintf(buf, 9, "%04X,%04X", interval, window);

		return Set("F", buf);
	}

	bool RN4020::Observer(bool enable) const
	{
		char buf[] = { (enable ? '1' : '0'), '\0' };
		return Set("J", buf);
	}

	int8_t RN4020::SignalStrength() const
	{
		char buf[16] = { 0 };	// No Connection + \r\n

		if (!GetString("M", buf, sizeof(buf)))
			return 0;

		if (strcmp(buf, "No Connection") == 0)
			return 0;

		long rssi = strtol(buf, NULL, 16);
		return static_cast<int8_t>(rssi);
	}

	bool RN4020::Broadcast(uint8_t data[25], uint8_t len) const
	{
		char buf[51] = { 0 };
		for (uint8_t i = 0; i < len; ++i)
			snprintf(buf + 2, 2, "%02X", data[i]);

		return Set("N", buf);
	}

	bool RN4020::UpdateTimings(uint16_t interval, uint16_t latency, uint16_t timeout) const
	{
		char buf[15] = { 0 };
		snprintf(buf, 14, "%04X,%04X,%04X", interval, latency, timeout);

		return Set("T", buf);
	}

	bool RN4020::Set(const char* command, const char* param) const
	{
		const Serial::ISerial& serial = GetSerial();

		if (serial.Send(command, strlen(command)) == -1)
			return false;

		if (param)
		{
			if (serial.Send(",", 1) == -1)
				return false;
			if (serial.Send(param, strlen(param)) == -1)
				return false;
		}

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
