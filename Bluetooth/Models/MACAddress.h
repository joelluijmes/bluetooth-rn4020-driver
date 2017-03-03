#ifndef MACADDRESS_H_
#define MACADDRESS_H_

#include <inttypes.h>

class MACAddress
{
public:
	/// 
	/// Constructs empty MAC Address
	/// 
	explicit MACAddress();

	/// 
	/// Constructs MAC Address from a 64 bit integer
	///
	/// @param a_Value		zero extended value of 48 bit MAC Address
	/// 
	explicit MACAddress(uint64_t a_Value);
	
	/// 
	/// Cosntructs MAC Address from 6 byte array
	///
	/// @param a_Array		6 byte long array of MAC Address
	/// 
	explicit MACAddress(const uint8_t a_Array[6]);
	
	/// 
	/// Constructs MAC Address from hex string (no seperators!!)
	///
	/// @param a_String		12 char long hex string (no seperators)
	/// 
	explicit MACAddress(const char* a_String);

	MACAddress(const MACAddress& a_Other);
	MACAddress& operator=(const MACAddress& a_Other);

	/// 
	/// Gets the MAC Address as zero extended 64 bit integer
	///
	/// @return				zero extended 64 bit value
	/// 
	uint64_t GetValue() const;

	/// 
	/// Gets the MAC Address as a 6 byte array
	///
	/// @return				the array
	/// 
	const uint8_t* GetArray() const;

	/// 
	/// Outputs the MAC Address to a char buffer (in hex), if specified the MAC Address
	/// will be seperated by the argument 'seperator'.
	///
	/// @param buf			output buffer
	/// @param len			length of the buffer
	/// @param seperator	seperator to put between the bytes
	/// 
	void ToCharArray(char* buf, uint8_t len, char seperator = ':') const;

private:
	union
	{
		uint8_t m_Array[6];
		uint64_t m_Value;
	};
};


#endif // !MACADDRESS_H_
