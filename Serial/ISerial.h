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

		virtual int32_t Send(const char* buffer, uint32_t len) const = 0;
		virtual int32_t Receive(char* buffer, uint32_t len) const = 0;
	};
}
#endif // !ISERIAL_H_
