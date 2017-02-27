#ifndef RN4020_H_
#define RN4020_H_

#include "IBluetooth.h"

namespace
{

}

namespace Bluetooth
{
	class RN4020 : public IBluetooth
	{
	public:
		enum BaudRate;

		explicit RN4020(const Serial::ISerial& serial)
			: IBluetooth(serial)
		{
		}

		bool SetName(const char* name) const override
		{
			return Set(CMD_SET_NAME, name);
		}

		bool GetName(char* name, uint8_t len) const override
		{
			return GetString(CMD_GET_NAME, name, len);
		}

		/// 
		/// This command sets the serialized Bluetooth-friendly name of the device, where
		/// <string> is up to 15 alphanumeric characters.This command automatically appends
		///	the last 2 bytes of the Bluetooth MAC address to the name, which is useful for
		///	generating a custom name with unique numbering
		///
		/// @param name		Bluetooth-friendly name
		/// @return			true if operation completed succesfully
		/// 
		bool SetSerializedName(const char* name) const
		{
			return Set(CMD_SET_SERIALIZED_NAME, name);
		}

		/// 
		/// This command gets the serialized Bluetooth-friendly name of the device.
		///
		/// @param name		Bluetooth-friendly name
		/// @param len		Length of name, maximum is 15
		/// @return			true if operation completed succesfully
		/// 
		bool GetSerializedName(char* name, uint8_t len) const
		{
			return GetString(CMD_GET_SERIALIZED_NAME, name, len);
		}
		
		/// 
		/// This command sets the baud rate of the UART communication. The input parameter
		/// is a single digit number in the range of 0 to 7, representing a baud rate from 2400 to
		///	921K, as shown in Table 2 - 5. When the baud rate is set to 2400, there is no need to
		///	wake the RN4020 module by pulling WAKE_SW high for UART communication.
		///
		/// @param baud		Baud rate to set
		/// @return			true if operation completed succesfully	
		/// 
		bool SetBaudRate(BaudRate baud) const
		{
			char buf[] = { static_cast<char>(baud + '0'), '\0' };
			return Set(CMD_SET_BAUD, buf);
		}
				
		/// 
		/// This command gets the baud rate of the UART communication.
		///
		/// @param baud		Current baud rate
		/// @return			true if operation completed succesfully			
		/// 
		bool GetBaudRate(BaudRate* baud) const
		{
			// 1 for result; 2 for \r\n
			char buf[3];
			if (!Get(CMD_GET_BAUD, buf, sizeof(buf), NULL))
				return false;

			*baud = static_cast<BaudRate>(buf[0] - '0');
			return true;
		}

		enum BaudRate
		{
			RN4020_BAUD_2400 = 0,
			RN4020_BAUD_9600 = 1,
			RN4020_BAUD_19200 = 2,
			RN4020_BAUD_38400 = 3,
			RN4020_BAUD_115200 = 4,
			RN4020_BAUD_230400 = 5,
			RN4020_BAUD_460800 = 6,
			RN4020_BAUD_921600 = 7
		};

	private:
		bool Set(const char* command, const char* param) const;
		bool Get(const char* command, char* buf, uint8_t len, uint8_t* received) const;
		bool GetString(const char* command, char* buf, uint8_t len, bool stripNewLine = true) const;

		// RN4020 Commands
		static const char* const CMD_SET_SERIALIZED_NAME;
		static const char* const CMD_GET_SERIALIZED_NAME;
		static const char* const CMD_SET_NAME;
		static const char* const CMD_GET_NAME;
		static const char* const CMD_SET_BAUD;
		static const char* const CMD_GET_BAUD;
	};
}

#endif // !RN4020_H_

