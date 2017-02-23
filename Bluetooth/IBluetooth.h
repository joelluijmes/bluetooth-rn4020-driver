#ifndef IBLUETOOTH_H_
#define IBLUETOOTH_H_

// libraries
#include "../Serial/ISerial.h"

namespace Bluetooth
{
	class IBluetooth
	{
	public:
		explicit IBluetooth(const Serial::ISerial& serial)
			: m_Serial(serial) 
		{
		}

		virtual ~IBluetooth() = default;

		virtual bool SetName(const char* name, uint8_t len) const = 0;
		virtual bool GetName(char* name, uint8_t len) const = 0;

		const Serial::ISerial& GetSerial() const
		{
			return m_Serial;
		}

	protected:
		bool ReadWrite(const char* send, uint8_t sendLen, char* recv, uint8_t recvLen, bool sendLineFeed = true) const;

	private:
		const Serial::ISerial& m_Serial;
	};
}

#endif // !IBLUETOOTH_H_
