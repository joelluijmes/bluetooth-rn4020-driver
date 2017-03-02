#ifndef MACADDRESS_H_
#define MACADDRESS_H_

#include <inttypes.h>
#include <ostream>

class MACAddress
{
public:
	explicit MACAddress();
	explicit MACAddress(uint64_t a_Value);
	explicit MACAddress(const uint8_t a_Array[6]);
	explicit MACAddress(const char* a_String);

	MACAddress(const MACAddress& a_Other);
	MACAddress& operator=(const MACAddress& a_Other);

	uint64_t GetValue() const;
	const uint8_t* GetArray() const;
	void ToCharArray(char* buf, uint8_t len, char seperator = ':') const;

private:
	union
	{
		uint8_t m_Array[6];
		uint64_t m_Value;
	};
};


#endif // !MACADDRESS_H_
