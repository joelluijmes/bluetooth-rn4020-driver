#ifndef RN4020_H_
#define RN4020_H_

#include "IBluetooth.h"

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

		bool SetName(const char* name, uint8_t len) const override;
		bool GetName(char* name, uint8_t len) const override;

		/// 
		/// This command sets the serialized Bluetooth-friendly name of the device, where
		/// <string> is up to 15 alphanumeric characters.This command automatically appends
		///	the last 2 bytes of the Bluetooth MAC address to the name, which is useful for
		///	generating a custom name with unique numbering
		///
		/// @param name		Bluetooth-friendly name
		/// @param len		Length of name, maximum is 15
		/// @return			true if operation completed succesfully
		/// 
		bool SetSerializedName(const char* name, uint8_t len) const;

		/// 
		/// This command gets the serialized Bluetooth-friendly name of the device.
		///
		/// @param name		Bluetooth-friendly name
		/// @param len		Length of name, maximum is 15
		/// @return			true if operation completed succesfully
		/// 
		bool GetSerializedName(char* name, uint8_t len) const;
		
		/// 
		/// This command sets the baud rate of the UART communication. The input parameter
		/// is a single digit number in the range of 0 to 7, representing a baud rate from 2400 to
		///	921K, as shown in Table 2 - 5. When the baud rate is set to 2400, there is no need to
		///	wake the RN4020 module by pulling WAKE_SW high for UART communication.
		///
		/// @param baud		Baud rate to set
		/// @return			true if operation completed succesfully	
		/// 
		bool SetBaudRate(BaudRate baud) const;
				
		/// 
		/// This command gets the baud rate of the UART communication.
		///
		/// @param baud		Current baud rate
		/// @return			true if operation completed succesfully			
		/// 
		bool GetBaudRate(BaudRate* baud) const;

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
	};
}

#endif // !RN4020_H_

