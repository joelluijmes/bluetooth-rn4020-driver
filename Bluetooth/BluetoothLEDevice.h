#ifndef BLUETOOTH_LE_DEVICE_H_
#define BLUETOOTH_LE_DEVICE_H_

#include <inttypes.h>

namespace Bluetooth
{
	class BluetoothLEDevice
	{
	public:
		enum Role;

		virtual ~BluetoothLEDevice() = default;

		virtual void GetMACAddress(uint8_t macAddress[]) const = 0;
		
		virtual void GetName(char* name, uint8_t len) const = 0;
		virtual void SetName(const char* name) const = 0;
		virtual Role GetRole() const = 0;


		enum Role
		{
			ROLE_NONE,
			NONE_PERIPHERAL,
			ROLE_CENTRAL,
			ROLE_OBSERVER,
			ROLE_BROADCASTER
		};
	};
}

#endif // !BLUETOOTH_LE_DEVICE_H_
