#include "IBluetooth.h"

using namespace Serial;

namespace Bluetooth
{
	bool IBluetooth::ReadWrite(const char* send, uint8_t sendLen, char* recv, uint8_t recvLen, bool sendLineFeed) const
	{
		const ISerial& serial = GetSerial();

		if (serial.Send(send, sendLen) == -1)
			return false;

		// send the new line
		if (sendLineFeed && serial.Send("\r\n", 2) == -1)
			return false;
		
		int32_t received = serial.Receive(recv, recvLen);
		if (received == -1)
			return false;

		recv[received] = 0;
		return true;
	}
}
