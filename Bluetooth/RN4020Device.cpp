#include "RN4020Device.h"

namespace Bluetooth
{
	RN4020Device::RN4020Device(const Serial::ISerial& serial)
		: m_RN4020(serial), m_Role(ROLE_NONE)
	{
	}

	void RN4020Device::GetMACAddress(uint8_t macAddress[]) const
	{
		// BTA= + 6 byte mac address
		// (Dump flushes internally so we don't need to read all of the dump)
		char buf[17];
		m_RN4020.Dump(buf, sizeof(buf) - 1);

		// skip BTA=
		char* ptr = buf + 4;
		char tmp[3] = { 0 };
		for (uint8_t i = 0; i < 6; ++i)
		{
			// read the two hex nybbles
			tmp[0] = ptr[0];
			tmp[1] = ptr[1];

			unsigned long val = strtoul(tmp, NULL, 16);
			macAddress[i] = static_cast<uint8_t>(val);

			ptr += 2;
		}
	}

}
