#ifndef BLUETOOTH_LE_DEVICE_H_
#define BLUETOOTH_LE_DEVICE_H_

#include "Services.h"

#include <inttypes.h>
#include "BluetoothLEPeripheral.h"


namespace Bluetooth
{
	class BluetoothLEDevice
	{
	public:
		enum Role;

		BluetoothLEDevice()
			: m_Interval(),
			  m_Window(),
			  m_Timeout(),
			  m_Role(ROLE_NONE)
		{
		}

		virtual ~BluetoothLEDevice() = default;

		virtual bool GetMACAddress(MACAddress* address) const = 0;
		virtual bool GetName(char* name, uint8_t len) const = 0;
		virtual bool SetName(const char* name) const = 0;
		virtual bool SetServices(Services services) const = 0;
		virtual bool StartAdvertise(bool autoAdvertise = true) const = 0;
		virtual bool ScanPeripherals(BluetoothLEPeripheral* peripherals, uint8_t len, uint8_t* found) const = 0;
		virtual bool Connect(const BluetoothLEPeripheral& peripheral) = 0;

		const BluetoothLEPeripheral& GetConnectedPeripheral() const
		{
			return	m_ConnectedPeripheral;
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
		void SetConnectedPeripheral(const BluetoothLEPeripheral& peripheral)
		{
			m_ConnectedPeripheral = peripheral;
		}

		void SetRole(Role role)
		{
			m_Role = role;
		}

	private:
		uint16_t m_Interval;
		uint16_t m_Window;
		uint16_t m_Timeout;
		Role m_Role;
		BluetoothLEPeripheral m_ConnectedPeripheral;
	};
}

#endif // !BLUETOOTH_LE_DEVICE_H_
