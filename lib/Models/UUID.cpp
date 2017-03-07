#include "UUID.h"

#include <cstring>
#include <cstdio>
#include <cstdlib>

namespace Bluetooth
{
	const uint8_t MAX_STR_LEN = 37;

	UUID::UUID(const UUID& a_Other): m_ShortUUID(a_Other.m_ShortUUID)
	{
		memcpy(m_UUID, a_Other.m_UUID, sizeof(m_UUID));
	}

	UUID& UUID::operator=(const UUID& a_Other)
	{
		if (this == &a_Other)
			return *this;

		m_ShortUUID = a_Other.m_ShortUUID;
		memcpy(m_UUID, a_Other.m_UUID, sizeof(m_UUID));

		return *this;
	}

	UUID::UUID() : m_ShortUUID(-1)
	{
		memset(m_UUID, -1, sizeof(m_UUID));
	}

	UUID::UUID(uint8_t longUUID[]) : m_ShortUUID(longUUID[2] << 8 | longUUID[3])
	{
		memcpy(m_UUID, longUUID, sizeof(m_UUID));
	}

	UUID::UUID(uint16_t shortUUID) : m_ShortUUID(shortUUID)
	{
		// 128_bit_value = 16_bit_value * 2^96 + Bluetooth_Base_UUID
		// Or, to put it more simply, the 16-bit Attribute UUID replaces the x’s in the follow- ing:
		// 0000xxxx - 0000 - 1000 - 8000 - 00805F9B34FB

		m_UUID[2] = (shortUUID >> 8) & 0xFF;
		m_UUID[3] = (shortUUID) & 0xFF;
	}

	UUID::UUID(const char* hexString)
	{
		uint8_t len = strnlen(hexString, MAX_STR_LEN);
		if (len != 4 && len != 36 && len != 32)
			return; // invalid
		
		// short UUID
		if (len == 4) 
		{
			unsigned long value = strtoul(hexString, NULL, 16);
			m_ShortUUID = static_cast<uint16_t>(value);
			m_UUID[2] = (m_ShortUUID >> 8) & 0xFF;
			m_UUID[3] = (m_ShortUUID) & 0xFF;

			return;
		}
		
		const char* ptr = hexString;
		char buf[33] = { 0 };

		// long UUID with seperators
		if (len == 36)
		{
			memcpy(buf, hexString, 8);
			memcpy(buf + 8, hexString + 9, 4);
			memcpy(buf + 12, hexString + 14, 4);
			memcpy(buf + 16, hexString + 19, 4);
			memcpy(buf + 20, hexString + 24, 12);

			ptr = buf;
		}

		char tmp[3] = { 0 };
		for (uint8_t i = 0; i < 32; i += 2)
		{
			tmp[0] = ptr[i];
			tmp[1] = ptr[i + 1];

			unsigned long value = strtoul(tmp, NULL, 16);
			m_UUID[i/2] = static_cast<uint8_t>(value);
		}

		m_ShortUUID = m_UUID[2] << 8 | m_UUID[3];
	}

	void UUID::ToCharArray(char* buf, uint8_t len) const
	{
		char tmp[MAX_STR_LEN] = { 0 };
		snprintf(tmp, sizeof(tmp) - 1, "%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X",
			m_UUID[0], m_UUID[1], m_UUID[2], m_UUID[3], m_UUID[4], m_UUID[5], m_UUID[6], m_UUID[7],
			m_UUID[8], m_UUID[9], m_UUID[10], m_UUID[11], m_UUID[12], m_UUID[13], m_UUID[14], m_UUID[15]);

		strncpy(buf, tmp, len);
	}

	uint16_t UUID::GetShortUUID() const
	{
		return m_ShortUUID;
	}

	const uint8_t* UUID::GetLongUUID() const
	{
		return m_UUID;
	}

	bool operator==(const UUID& a_Lhs, const UUID& a_Rhs)
	{
		return a_Lhs.m_ShortUUID == a_Rhs.m_ShortUUID;
	}

	bool operator!=(const UUID& a_Lhs, const UUID& a_Rhs)
	{
		return !(a_Lhs == a_Rhs);
	}
}
