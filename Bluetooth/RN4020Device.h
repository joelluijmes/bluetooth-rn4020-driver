#ifndef RN4020_DEVICE_H_
#define RN4020_DEVICE_H_

#include "BluetoothLEDevice.h"
#include "Drivers/RN4020Driver.h"

namespace Bluetooth
{
	class RN4020Device : public BluetoothLEDevice
	{
	public:
		explicit RN4020Device(const Serial::ISerial& serial);

		void GetMACAddress(uint8_t macAddress[]) const override;
		void GetName(char* name, uint8_t len) const override
		{
			m_RN4020.GetName(name, len);
		}

		void SetName(const char* name) const override
		{
			m_RN4020.SetName(name);
		}

		Role GetRole() const override
		{
			return m_Role;
		}



	private:
		const Drivers::RN4020Driver m_RN4020;
		Role m_Role;
	};
}

#endif // !RN4020_DEVICE_H_
