#ifndef BLUETOOTH_LE_PERIPHERAL_H_
#define BLUETOOTH_LE_PERIPHERAL_H_

// user libraries
#include "MACAddress.h"

// std libraries
#include <cstring>
#include "UUID.h"


namespace Bluetooth
{
	/// 
	/// Model for a BLE Peripheral
	/// 
	class BluetoothLEPeripheral
	{
	public:
		/// 
		/// Constructs an empty Peripheral (everything is initialized as 0)
		/// 
		BluetoothLEPeripheral() : m_IsRandomMAC(false), m_RSSI(0)
		{
			memset(m_Name, 0, sizeof(m_Name));
		}

		/// 
		/// Constructs a Peripheral from MAC Address
		///
		/// @param macAddress			MAC Address of the Peripheral
		/// @param a_IsRandomMAC		Specify if the MAC Address is random
		/// 
		explicit BluetoothLEPeripheral(const MACAddress& macAddress, bool a_IsRandomMAC = false)
			: m_MACAddress(macAddress),
			  m_IsRandomMAC(a_IsRandomMAC),
			  m_RSSI(0)
		{
			memset(m_Name, 0, sizeof(m_Name));
		}


		/// 
		/// Fully constructs a Peripheral with all members
		///
		/// @param macAddress			MAC Address of the Peripheral
		/// @param a_IsRandomMAC		Specify if the MAC Address is random
		/// @param a_Name				BLE Name of the Peripheral
		/// @param a_PrimaryService		The primary service UUID
		/// @param a_Rssi				RSSI of the Peripheral
		/// 
		BluetoothLEPeripheral(const MACAddress& macAddress,
		                      bool a_IsRandomMAC,
		                      char a_Name[21],
		                      const UUID& a_PrimaryService,
		                      int8_t a_Rssi)
			: m_MACAddress(macAddress),
			  m_IsRandomMAC(a_IsRandomMAC),
			  m_PrimaryService(a_PrimaryService),
			  m_RSSI(a_Rssi)
		{
			memcpy(m_Name, a_Name, sizeof(m_Name));
		}

		/// 
		/// Gets the MAC Address
		///
		/// @return				the MAC Address
		/// 
		const MACAddress& GetMACAddress() const
		{
			return m_MACAddress;
		}

		/// 
		/// Gets if the MAC Address is random
		///
		/// @return				true if MAC Address is random
		/// 
		bool GetIsRandomMAC() const
		{
			return m_IsRandomMAC;
		}

		/// 
		/// Gets the name
		///
		/// @return				the name
		/// 
		const char* GetName() const
		{
			return m_Name;
		}

		/// 
		/// Gets the primary UUID 
		///
		/// @return				the primary UUID
		/// 
		const UUID& GetPrimaryService() const
		{
			return m_PrimaryService;
		}

		/// 
		/// Gets the RSSI
		///
		/// @return				the RSSI
		/// 
		int8_t GetRssi() const
		{
			return m_RSSI;
		}

	private:
		MACAddress m_MACAddress;
		bool m_IsRandomMAC;
		char m_Name[21];
		UUID m_PrimaryService;
		int8_t m_RSSI;
	};
}

#endif // !BLUETOOTH_LE_PERIPHERAL_H_
