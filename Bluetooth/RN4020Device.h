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

		bool GetMACAddress(uint8_t macAddress[]) const override;
		bool GetName(char* name, uint8_t len) const override
		{
			return m_RN4020.GetName(name, len);
		}

		bool SetName(const char* name) const override;
		bool SetServices(Services services) const override;

		bool StartAdvertise(bool autoAdvertise = true) const override;

	private:
		const Drivers::RN4020Driver m_RN4020;
		
		mutable bool m_ShouldReboot;

		bool CheckReboot() const;
	};
}

#endif // !RN4020_DEVICE_H_
