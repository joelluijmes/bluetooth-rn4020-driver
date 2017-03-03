#include "UUID.h"

#include <cstring>
#include <cstdio>

namespace Bluetooth
{
	UUID::UUID() : m_ShortUUID(-1)
	{
		memset(m_UUID, -1, sizeof(m_UUID));
	}

	UUID::UUID(uint8_t longUUID[]) : m_ShortUUID(-1)
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

	void UUID::ToCharArray(char* buf, uint8_t len) const
	{
		char tmp[37] = { 0 };
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
}
