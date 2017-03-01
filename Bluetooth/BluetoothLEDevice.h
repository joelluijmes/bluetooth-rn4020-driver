#ifndef BLUETOOTH_LE_DEVICE_H_
#define BLUETOOTH_LE_DEVICE_H_

#include "Services.h"

#include <inttypes.h>


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

		virtual bool GetMACAddress(uint8_t macAddress[]) const = 0;
		virtual bool GetName(char* name, uint8_t len) const = 0;
		virtual bool SetName(const char* name) const = 0;
		virtual bool SetServices(Services services) const = 0;
		virtual bool StartAdvertise(bool directAdvertisementOnly = false, bool autoAdvertise = true) const = 0;


		virtual Role GetRole() const
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
		void SetRole(Role role)
		{
			m_Role = role;
		}

	private:
		uint16_t m_Interval;
		uint16_t m_Window;
		uint16_t m_Timeout;
		Role m_Role;
	};
}

#endif // !BLUETOOTH_LE_DEVICE_H_
