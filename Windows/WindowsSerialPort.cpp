#include "WindowsSerialPort.h"

namespace Serial
{
	WindowsSerialPort::WindowsSerialPort(const char* comPort, BaudRate baudrate, DataBit databits, ParityBit parity, StopBit stopbits)
		: IUartDriver(baudrate, databits, parity, stopbits), m_ComPort(comPort), m_hComPort(NULL)
	{
	}

	WindowsSerialPort::~WindowsSerialPort()
	{
		Close();
	}

	bool WindowsSerialPort::Open()
	{
		m_hComPort = CreateFile(GetComPort(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
		if (m_hComPort == INVALID_HANDLE_VALUE)
			return false;

		// first retrieve the current configuration before altering it
		DCB dcb = { 0 };
		dcb.DCBlength = sizeof(DCB);
		if (!GetCommState(m_hComPort, &dcb))
			return false;

		// set our configuration
		dcb.BaudRate = GetBaudrate();
		dcb.ByteSize = GetDatabits();
		dcb.Parity = GetParity();
		dcb.StopBits = GetStopbits();

		COMMTIMEOUTS timeouts;

		timeouts.ReadIntervalTimeout = 1;
		timeouts.ReadTotalTimeoutMultiplier = 1;
		timeouts.ReadTotalTimeoutConstant = 1;
		timeouts.WriteTotalTimeoutMultiplier = 1;
		timeouts.WriteTotalTimeoutConstant = 1;
		if (!SetCommTimeouts(m_hComPort, &timeouts))
			return false;
		
		return SetCommState(m_hComPort, &dcb);
	}

	bool WindowsSerialPort::Close()
	{
		if (m_hComPort)
		{
			if (!CloseHandle(m_hComPort))
				return false;

			m_hComPort = NULL;
		}

		return true;
	}

	int32_t WindowsSerialPort::Send(const char* buffer, uint32_t len) const
	{
		if (!m_hComPort)
			return -1;

		DWORD written;
		if (!WriteFile(m_hComPort, buffer, len, &written, NULL))
			return -1;

		return written;
	}

	int32_t WindowsSerialPort::Receive(char* buffer, uint32_t len) const
	{
		if (!m_hComPort)
			return -1;

		DWORD read;
		if (!ReadFile(m_hComPort, buffer, len, &read, NULL))
			return -1;

		return read;
	}
}
