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

		void getMACAddress(uint8_t macAddress[]) const override;

	private:
		const Drivers::RN4020Driver m_RN4020;
	};
}

#endif // !RN4020_DEVICE_H_
