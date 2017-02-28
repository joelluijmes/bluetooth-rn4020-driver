#ifndef BLUETOOTH_LE_DEVICE_H_
#define BLUETOOTH_LE_DEVICE_H_

#include <inttypes.h>

namespace Bluetooth
{
	class BluetoothLEDevice
	{
	public:
		virtual ~BluetoothLEDevice() = default;

	
		virtual void getMACAddress(uint8_t macAddress[]) const = 0;
	};
}

#endif // !BLUETOOTH_LE_DEVICE_H_
