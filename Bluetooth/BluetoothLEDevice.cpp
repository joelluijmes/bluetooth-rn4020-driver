#include "BluetoothLEDevice.h"

namespace Bluetooth
{
	bool BluetoothLEDevice::Connect(const BluetoothLEPeripheral& peripheral)
	{
		m_IsConnected = ConnectImpl(peripheral);
		if (m_IsConnected)
			m_ConnectedPeripheral = peripheral;
				
		return m_IsConnected;
	}
}
