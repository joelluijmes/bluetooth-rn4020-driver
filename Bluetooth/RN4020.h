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

		bool SetDisplayName(const char* name, uint8_t len) const override;
		bool GetDisplayName(char* name, uint8_t len) const override;
	};
}

#endif // !RN4020_H_

