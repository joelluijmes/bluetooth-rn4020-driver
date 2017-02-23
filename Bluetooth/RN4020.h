#ifndef RN4020_H_
#define RN4020_H_

#include "IBluetooth.h"

namespace Bluetooth
{
	class RN4020 : public IBluetooth
	{
	public:
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
	};
}

#endif // !RN4020_H_

