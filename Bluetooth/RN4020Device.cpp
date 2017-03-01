﻿#include "RN4020Device.h"
#include <ctime>


using namespace Bluetooth::Drivers;

namespace Bluetooth
{
	RN4020Device::RN4020Device(const Serial::ISerial& serial)
		: m_RN4020(serial), m_ShouldReboot(false)
	{
		m_RN4020.ResetDefaults();
	}

	bool RN4020Device::GetMACAddress(uint8_t macAddress[]) const
	{
		// BTA= + 6 byte mac address
		// (Dump flushes internally so we don't need to read all of the dump)
		char buf[17];
		if (!m_RN4020.Dump(buf, sizeof(buf) - 1))
			return false;

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

		return true;
	}

	bool RN4020Device::SetName(const char* name) const
	{
		if (!m_RN4020.SetName(name))
			return false;

		m_ShouldReboot = true;
		return true;
	}

	bool RN4020Device::SetServices(Services services) const
	{
		if (!m_RN4020.SetServerServices(services))
			return false;

		m_ShouldReboot = true;
		return true;
	}

	bool RN4020Device::StartAdvertise(bool directAdvertisementOnly, bool autoAdvertise) const
	{
		uint32_t features = 0;
		if (!directAdvertisementOnly)
			features |= RN4020Driver::FEATURE_NO_DIRECT_ADVERTISEMENT;
		if (autoAdvertise)
			features |= RN4020Driver::FEATURE_AUTO_ADVERTISE;
		if (!m_RN4020.SetFeatures(static_cast<RN4020Driver::Features>(features)))
			return false;

		if (!CheckReboot())
			return false;

		if (autoAdvertise)
			return true;

		return m_RN4020.Advertise(GetInterval(), GetTimeout());
	}

	bool RN4020Device::CheckReboot() const
	{
		if (!m_ShouldReboot)
			return true;

		if (!m_RN4020.Reboot())
			return false;

		m_ShouldReboot = false;
		return true;
	}
}