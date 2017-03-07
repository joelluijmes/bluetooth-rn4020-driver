#ifndef BLUETOOTH_LE_DEVICE_H_
#define BLUETOOTH_LE_DEVICE_H_

// user libraries
#include "Models/BluetoothLEPeripheral.h"
#include "Models/Services.h"

namespace Bluetooth
{
	/// 
	/// Base class for a Bluetooth Low Energy Device. The interface assumes that the
	/// device understands all the GATT roles (Peripheral, Central, Observer and Broadcaster)
	/// 
	class BluetoothLEDevice
	{
	public:
		enum Role;

		/// 
		/// Constructs a new BLE Device
		///
		/// 
		BluetoothLEDevice()
			: m_Interval(),
			  m_Window(),
			  m_Timeout(),
			  m_Role(ROLE_NONE), m_IsConnected(false)
		{
		}

		virtual ~BluetoothLEDevice() = default;

		/// 
		/// Gets the MAC Address of the current BLE Device
		///
		/// @param address		Output to store the MAC Address
		/// @return	true if operation completed succesfully			
		/// 
		virtual bool GetMACAddress(MACAddress* address) const = 0;

		/// 
		/// Gets the current public Bluetooth Name 
		///
		/// @param name		The name
		/// @param len		Maximum length to store the name in
		/// @return	true if operation completed succesfully		
		/// 
		virtual bool GetName(char* name, uint8_t len) const = 0;

		/// 
		/// Sets the public Bluetooth Name
		///
		/// @param name		Null terminated name
		/// @return	true if operation completed succesfully		
		/// 
		virtual bool SetName(const char* name) const = 0;

		/// 
		/// Sets the Server Services of the current BLE Device
		///
		/// @param services		The servicese
		/// @return	true if operation completed succesfully		
		/// 
		virtual bool SetServices(Services services) const = 0;

		/// 
		/// Starts the device to Advertise as a Peripheral
		///
		/// @param autoAdvertise		If set, the device should restart advertising 
		///								when disconnected or rebooted.
		/// @return	true if operation completed succesfully		
		/// 
		virtual bool StartAdvertise(bool autoAdvertise = true) const = 0;

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
		virtual bool ScanPeripherals(BluetoothLEPeripheral* peripherals, uint8_t len, uint8_t* found, uint8_t timeout = 10) const = 0;
		
		/// 
		/// Starts the BLE Device as a Central to connect with a Peripheral 
		///
		/// @param peripheral			Peripheral to connect with
		/// @return	true if operation completed succesfully		
		/// 
		bool Connect(const BluetoothLEPeripheral& peripheral);

		/// 
		/// Gets the connected Peripheral, if it isn't connected it'll return NULL
		///
		/// @return	if connected, the connected Peripheral			
		/// 
		const BluetoothLEPeripheral* GetConnectedPeripheral() const
		{
			return m_IsConnected ? &m_ConnectedPeripheral : NULL;
		}

		Role GetRole() const
		{
			return m_Role;
		}

		uint16_t GetInterval() const
		{
			return m_Interval;
		}

		void SetInterval(uint16_t a_Interval)
		{
			m_Interval = a_Interval;
		}

		uint16_t GetWindow() const
		{
			return m_Window;
		}

		void SetWindow(uint16_t a_Window)
		{
			m_Window = a_Window;
		}

		uint16_t GetTimeout() const
		{
			return m_Timeout;
		}

		void SetTimeout(uint16_t a_Timeout)
		{
			m_Timeout = a_Timeout;
		}

		enum Role
		{
			ROLE_NONE,
			NONE_PERIPHERAL,
			ROLE_CENTRAL,
			ROLE_OBSERVER,
			ROLE_BROADCASTER
		};

	protected:
		virtual bool ConnectImpl(const BluetoothLEPeripheral& peripheral) = 0;

	private:
		uint16_t m_Interval;
		uint16_t m_Window;
		uint16_t m_Timeout;
		Role m_Role;

		bool m_IsConnected;
		BluetoothLEPeripheral m_ConnectedPeripheral;
	};
}

#endif // !BLUETOOTH_LE_DEVICE_H_
