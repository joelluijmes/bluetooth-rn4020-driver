#ifndef WINDOWS_SERIAL_PORT_H_
#define WINDOWS_SERIAL_PORT_H_

// user libraries
#include "../Serial/IUartDriver.h"

// std libraries
#include <string>
#include <Windows.h>

namespace Serial
{
	class WindowsSerialPort : public IUartDriver
	{
	public:
		WindowsSerialPort(const char* comPort, BaudRate baudrate, DataBit databits, ParityBit parity, StopBit stopbits);
		~WindowsSerialPort();

		bool Open();
		bool Close();
		int32_t Send(const char* buffer, uint32_t len) const override;
		int32_t Receive(char* buffer, uint32_t len) const override;

		const char* GetComPort() const
		{
			return m_ComPort;
		}

	private:
		const char* m_ComPort;
		HANDLE m_hComPort;
	};
}

#endif // !WINDOWS_SERIAL_PORT_H_
