#ifndef UTIL_H_
#define UTIL_H_

#include <inttypes.h>

class Util
{
public:
	static void Parse6ByteMACAddressFromString(const char* str, uint8_t macAddress[]);
};

#endif // !UTIL_H_
