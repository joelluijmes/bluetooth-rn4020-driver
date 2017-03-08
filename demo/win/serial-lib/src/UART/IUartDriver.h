#ifndef IUART_DRIVER_H_
#define IUART_DRIVER_H_

// user libraries
#include "Serial/ISerial.h"
#include "ParityBit.h"
#include "BaudRate.h"
#include "DataBit.h"
#include "StopBit.h"

// libraries
#include <inttypes.h>

namespace Serial
{
	class IUartDriver : public ISerial
	{
	public:
		IUartDriver(BaudRate baudrate, DataBit databits, ParityBit parity, StopBit stopbits)
			: m_Baudrate(baudrate),
			m_Databits(databits),
			m_Parity(parity),
			m_Stopbits(stopbits)
		{
		}

		virtual ~IUartDriver() = default;

		BaudRate GetBaudrate() const
		{
			return m_Baudrate;
		}

		DataBit GetDatabits() const
		{
			return m_Databits;
		}

		ParityBit GetParity() const
		{
			return m_Parity;
		}

		StopBit GetStopbits() const
		{
			return m_Stopbits;
		}

	private:
		BaudRate m_Baudrate;
		DataBit m_Databits;
		ParityBit m_Parity;
		StopBit m_Stopbits;
	};
}

#endif // !IUART_DRIVER_H_
