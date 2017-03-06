#ifndef UUID_H_
#define UUID_H_

#include <inttypes.h>

namespace Bluetooth
{
	class UUID
	{
	public:
		/// 
		/// Constructs UUID with 0xFF as content
		/// 
		UUID();

		/// 
		/// Constructs a UUID from the long 128 bit version.
		///
		/// @param longUUID		Long 128 bit UUID
		/// 
		explicit UUID(uint8_t longUUID[]);

		/// 
		/// Constructs a UUID from a short version. Internally it creates the 128 bit format
		/// by using the Bluetooth_Base_UUID: 0000xxxx - 0000 - 1000 - 8000 - 00805F9B34FB
		///
		/// @param shortUUID		Short UUID to construct with
		/// 
		explicit UUID(uint16_t shortUUID);

		/// 
		/// Constructs a UUID from hex string
		///
		/// @param hexString		Hex string of UUID, either 16 or 128 bit
		/// 
		explicit UUID(const char* hexString);

		UUID(const UUID& a_Other);

		UUID& operator=(const UUID& a_Other);
		
		friend bool operator==(const UUID& a_Lhs, const UUID& a_Rhs);

		friend bool operator!=(const UUID& a_Lhs, const UUID& a_Rhs);

		/// 
		/// Gets the short 16 - bit UUID, only valid when constructed from UUID(uint16_t)
		///
		/// @return				the short UUID
		/// 
		uint16_t GetShortUUID() const;

		/// 
		/// Gets the long 128 bit UUID.
		///
		/// @return				pointer to the internal UUID
		/// 
		const uint8_t* GetLongUUID() const;

		/// 
		/// Formats it to a UUID, buffer should be at least 37 characters to store
		/// the whole string.
		///
		/// @param buf		Buffer to store the UUID
		/// @param len		Length of the buffer
		/// 
		void ToCharArray(char* buf, uint8_t len) const;

	private:
		// 0000xxxx - 0000 - 1000 - 8000 - 00805F9B34FB
		uint8_t m_UUID[16] = 
		{
			0x00,
			0x00,
			0x00, // place holder
			0x00, // place holder
			0x00,
			0x00,
			0x10,
			0x00,
			0x80,
			0x00,
			0x00,
			0x80,
			0x5F,
			0x9B,
			0x34,
			0xFB
		};

		uint16_t m_ShortUUID;
	};
}

#endif // !UUID_H_
