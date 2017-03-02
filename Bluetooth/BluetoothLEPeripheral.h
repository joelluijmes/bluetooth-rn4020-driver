#ifndef BLUETOOTH_LE_PERIPHERAL_H_
#define BLUETOOTH_LE_PERIPHERAL_H_

#include <cstring>
#include "MACAddress.h"

class BluetoothLEPeripheral
{
public:
	BluetoothLEPeripheral(): m_RandomAddress(0), m_PrimaryService(0), m_RSSI(0)
	{
		memset(m_Name, 0, sizeof(m_Name));
	}

	BluetoothLEPeripheral(const MACAddress& macAddress, uint8_t a_RandomAddress)
		: m_MACAddress(macAddress),
		  m_RandomAddress(a_RandomAddress),
		  m_PrimaryService(0),
		  m_RSSI(0)
	{
		memset(m_Name, 0, sizeof(m_Name));
	}

	BluetoothLEPeripheral(const MACAddress& macAddress,
	                      uint8_t a_RandomAddress,
	                      char a_Name[21],
	                      uint16_t a_PrimaryService,
	                      int8_t a_Rssi)
		: m_MACAddress(macAddress),
		  m_RandomAddress(a_RandomAddress),
		  m_PrimaryService(a_PrimaryService),
		  m_RSSI(a_Rssi)
	{
		memcpy(m_Name, a_Name, sizeof(m_Name));
	}

	const MACAddress& GetMACAddress() const
	{
		return m_MACAddress;
	}

	uint8_t GetRandomAddress() const
	{
		return m_RandomAddress;
	}

	const char* GetName() const
	{
		return m_Name;
	}

	uint16_t GetPrimaryService() const
	{
		return m_PrimaryService;
	}

	int8_t GetRssi() const
	{
		return m_RSSI;
	}

private:
	MACAddress m_MACAddress;
	uint8_t m_RandomAddress;
	char m_Name[21];
	uint16_t m_PrimaryService;
	int8_t m_RSSI;
};

#endif // !BLUETOOTH_LE_PERIPHERAL_H_
