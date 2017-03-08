#include "MACAddress.h"
#include <cstring>
#include <iomanip>

MACAddress::MACAddress() : m_Value(ULLONG_MAX)
{
}

MACAddress::MACAddress(uint64_t a_Value): m_Value(a_Value)
{
}

MACAddress::MACAddress(const uint8_t a_Array[6]) : m_Value(0)
{
	memcpy(m_Array, a_Array, 6);
}

MACAddress::MACAddress(const char* a_String) : m_Value(0)
{
	char tmp[3] = { 0 };
	for (uint8_t i = 0; i < 6; ++i)
	{
		// read the two hex nybbles
		tmp[0] = a_String[0];
		tmp[1] = a_String[1];

		unsigned long val = strtoul(tmp, NULL, 16);
		m_Array[i] = static_cast<uint8_t>(val);

		a_String += 2;
	}
}

MACAddress::MACAddress(const MACAddress& a_Other): m_Value(a_Other.m_Value)
{
}

MACAddress& MACAddress::operator=(const MACAddress& a_Other)
{
	if (this == &a_Other)
		return *this;
	m_Value = a_Other.m_Value;
	return *this;
}

uint64_t MACAddress::GetValue() const
{
	return m_Value;
}

const uint8_t* MACAddress::GetArray() const
{
	return m_Array;
}

void MACAddress::ToCharArray(char* buf, uint8_t len, char seperator) const
{
	char tmp[18] = {0};

	uint8_t copied = 0;
	for (uint8_t i = 0; i < 6; ++i)
	{
		if (!seperator)
		{
			snprintf(tmp + i * 2, 3, "%02X", m_Array[i]);
			continue;
		}

		snprintf(tmp + i * 3, 3, "%02X", m_Array[i]);
		if (i < 5)
			tmp[i*3 + 2] = seperator;
	}

	strncpy(buf, tmp, len);
}
