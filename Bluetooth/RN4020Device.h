#ifndef RN4020_DEVICE_H_
#define RN4020_DEVICE_H_

#include "BluetoothLEDevice.h"
#include "Drivers/RN4020Driver.h"
#include "Models/Services.h"

class MACAddress;

namespace Bluetooth
{
	/// 
	/// Higher level wrapper around RN4020 Driver implementing the BluetoothLEDevice base interface
	/// 
	class RN4020Device : public BluetoothLEDevice
	{
	public:
		/// 
		/// Constructs a RN4020Device
		///
		/// @param serial		Serial interface passed to RN4020 Driver
		/// 
		explicit RN4020Device(const Serial::ISerial& serial);

		/// 
		/// Gets the MAC Address of the current BLE Device
		///
		/// @param address		Output to store the MAC Address
		/// @return	true if operation completed succesfully			
		/// 
		bool GetMACAddress(MACAddress* address) const override;

		/// 
		/// Gets the current public Bluetooth Name 
		///
		/// @param name		The name
		/// @param len		Maximum length to store the name in
		/// @return	true if operation completed succesfully		
		/// 
		bool GetName(char* name, uint8_t len) const override;

		/// 
		/// Sets the public Bluetooth Name
		///
		/// @param name		Null terminated name
		/// @return	true if operation completed succesfully		
		/// 
		bool SetName(const char* name) const override;

		/// 
		/// Sets the Server Services of the current BLE Device
		///
		/// @param services		The servicese
		/// @return	true if operation completed succesfully		
		/// 
		bool SetServices(Services services) const override;

		/// 
		/// Starts the device to Advertise as a Peripheral
		///
		/// @param autoAdvertise		If set, the device should restart advertising 
		///								when disconnected or rebooted.
		/// @return	true if operation completed succesfully		
		/// 
		bool StartAdvertise(bool autoAdvertise = true) const override;

		/// 
		/// Starts the device as a Central to scan for public Peripherals. It relies 
		/// on the driver to have a specific timeout if no device has been found, the
		/// amount of times it tries to wait for the timeout is specified by the 
		/// 'timeout' argument.\n
		///
		/// @param peripherals			Array to Peripherals to store
		/// @param len					Length of the array of Peripherals
		/// @param found				Amount of Peripherals found
		/// @param timeout				Maximum tries to stop scanning
		/// @return	true if operation completed succesfully		
		/// 
		bool ScanPeripherals(BluetoothLEPeripheral* peripherals, uint8_t len, uint8_t* found, uint8_t timeout = 10) const override;

	protected:
		bool ConnectImpl(const BluetoothLEPeripheral& peripheral) override;

	private:
		const Drivers::RN4020Driver m_RN4020;
		
		mutable bool m_ShouldReboot;

		bool CheckReboot() const;
	};
}

#endif // !RN4020_DEVICE_H_
