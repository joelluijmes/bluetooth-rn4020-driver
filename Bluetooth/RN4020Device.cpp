#include "RN4020Device.h"
#include <ctime>


using namespace Bluetooth::Drivers;

namespace Bluetooth
{
	RN4020Device::RN4020Device(const Serial::ISerial& serial)
		: m_RN4020(serial), m_ShouldReboot(false)
	{
		m_RN4020.ResetDefaults();
	}

	bool RN4020Device::GetMACAddress(MACAddress* address) const
	{
		// BTA= + 6 byte mac address
		// (Dump flushes internally so we don't need to read all of the dump)
		char buf[17];
		if (!m_RN4020.Dump(buf, sizeof(buf) - 1))
			return false;

		// skip BTA=
		const char* ptr = buf + 4;
		*address = MACAddress(ptr);

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

	bool RN4020Device::StartAdvertise(bool autoAdvertise) const
	{
		uint32_t features = 0;
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

	bool RN4020Device::ScanPeripherals(BluetoothLEPeripheral* peripherals, uint8_t len, uint8_t* found) const
	{
		if (!CheckReboot())
			return false;

		if (!m_RN4020.Find(0, 0))
			return false;

		m_RN4020.ReadScan(peripherals, len, found);
		
		return m_RN4020.StopScan();
	}

	bool RN4020Device::Connect(const BluetoothLEPeripheral& peripheral)
	{
		if (!m_RN4020.Establish(peripheral.GetRandomAddress() == 0, peripheral.GetMACAddress()))
			return false;

		char buf[12]; // 'Connected\r\n'
		if (!m_RN4020.WaitString(buf, sizeof(buf)))
			return false;

		if (strncmp(buf, "Connected", 9) != 0)
			return false;

		SetConnectedPeripheral(peripheral);
		return true;
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
