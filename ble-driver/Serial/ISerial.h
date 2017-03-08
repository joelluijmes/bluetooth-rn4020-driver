#ifndef ISERIAL_H_
#define ISERIAL_H_

// libraries
#include <inttypes.h>

namespace Serial
{
	class ISerial
	{
	public:
		virtual ~ISerial() = default;

		/// 
		/// Send the buffer.
		///
		/// @param buffer		Buffer to send
		/// @param len			Length of the buffer
		/// @return				-1 if failed, else the amount of bytes sent
		/// 
		virtual int32_t Send(const char* buffer, uint32_t len) const = 0;

		/// 
		/// Receives data from the endpoint and store it in the buffer.
		///
		/// @param buffer		Buffer to store the data
		/// @param len			Length of the buffer
		/// @return				-1 if failed, else the amount of bytes received
		/// 
		virtual int32_t Receive(char* buffer, uint32_t len) const = 0;

		/// 
		/// If serial transmit supports it, flushes the transmit and receive buffers.
		/// 
		virtual void Flush() const = 0;
	};
}
#endif // !ISERIAL_H_
