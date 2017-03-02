#include "Util.h"

#include <stdlib.h>

void Util::Parse6ByteMACAddressFromString(const char* str, uint8_t macAddress[])
{
	char tmp[3] = { 0 };
	for (uint8_t i = 0; i < 6; ++i)
	{
		// read the two hex nybbles
		tmp[0] = str[0];
		tmp[1] = str[1];

		unsigned long val = strtoul(tmp, NULL, 16);
		macAddress[i] = static_cast<uint8_t>(val);

		str += 2;
	}
}
