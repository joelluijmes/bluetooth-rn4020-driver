#ifndef LINE_READER_WRITER_H_
#define LINE_READER_WRITER_H_

#include "ISerial.h"
#include "Util/CircularBuffer.h"

#include <cstring>


namespace Serial
{
	template <typename TType, TType TLen, const char* TDelimiter>
	class DelimiterSerial : public ISerial
	{
		

	public:
		explicit DelimiterSerial(const ISerial& serial);

		int32_t Send(const char* buffer, uint32_t len) const override;
		int32_t Receive(char* buffer, uint32_t len) const override;
		void Flush() const override;

	private:
		const uint8_t m_DelimiterLength = strlen(TDelimiter);
		const ISerial& m_Serial;

		mutable Util::CircularBuffer<TType, TLen> m_Circular;
	};

	template <typename TType = uint32_t, TType TLen, const char* TDelimiter>
	DelimiterSerial<TType, TLen, TDelimiter>::DelimiterSerial(const ISerial& serial) 
		: m_Serial(serial)
	{
	}

	template <typename TType = uint32_t, TType TLen, const char* TDelimiter>
	int32_t DelimiterSerial<TType, TLen, TDelimiter>::Send(const char* buffer, uint32_t len) const
	{
		int32_t sent = m_Serial.Send(buffer, len);
		if (sent == -1)
			return -1;

		int32_t lineSent = m_Serial.Send(TDelimiter, m_DelimiterLength);
		if (lineSent == -1)
			return -1;

		return sent + lineSent;
	}

	template <typename TType = uint32_t, TType TLen, const char* TDelimiter>
	void DelimiterSerial<TType, TLen, TDelimiter>::Flush() const
	{
		m_Serial.Flush();
	}

	template <typename TType = uint32_t, TType TLen, const char* TDelimiter>
	int32_t DelimiterSerial<TType, TLen, TDelimiter>::Receive(char* buffer, uint32_t len) const
	{
		int32_t read;
		char* ptr;

		if (m_Circular.GetCount() == 0)
		{
			read = m_Serial.Receive(buffer, len);
			if (read < 1)	// nothing received or error
				return read;

			ptr = strstr(buffer, TDelimiter);
			if (ptr == NULL) // not found
				return -1;
		}
		else
		{
			read = m_Circular.Load(buffer, len);
			buffer[read] = 0;

			ptr = strstr(buffer, TDelimiter);

			// not found
			if (ptr == NULL)
			{
				TType left = len - read;

				// there is still room in the target buf, the next call will read data from the
				// serial device (m_Serial)
				if (left > 0)
					return Receive(buffer + read, left);
				
				// we already filled the target buffer, we didn't found our delimiter
				return -1;
			}
		}

		// calculate how much actual data we have (strip off the delimiter)
		TType lineLength = ptr - buffer;
		TType dataLeft = read - lineLength - m_DelimiterLength;

		// store the rest
		if (dataLeft > 0)
		{
			// failed to store all the data in our buffer -> data corrupt
			if (m_Circular.Store(ptr + m_DelimiterLength, dataLeft) < dataLeft)
				return -1;
		}

		buffer[lineLength] = 0;
		return lineLength;
	}
}

#endif // !LINE_READER_WRITER_H_
