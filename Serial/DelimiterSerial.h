#ifndef LINE_READER_WRITER_H_
#define LINE_READER_WRITER_H_

#include "ISerial.h"
#include "../Util/CircularBuffer.h"

#include <cstring>


namespace Serial
{
	/// 
	/// Seperates Serial messages by a Delimiter. It uses an internal CircularBuffer to store additional
	/// data if more was received than needed. Make sure that TLen is at least as big as the biggest
	/// message. \n
	/// If TLen is smaller than the delimiter, -1 will be returned and the communication is corrupt. Any
	/// messages received in that call (and possibly the next) are inrecoverable. To restore from this state
	/// call Flush to reset the communication.\n
	/// Note that this doesn't fix the state with the connected device which may also have to be restored.
	///
	/// @tparam TType			Type to use to hold the indexes (uint8_t, uint16_t ..)
	/// @tparam TLen			Length of the buffer (must be power of two)
	/// @tparam TDelimiter		Delimiter to seperate messages
	/// 
	template <typename TType, TType TLen, const char* TDelimiter>
	class DelimiterSerial : public ISerial
	{
	public:
		/// 
		/// Constructs a new DelimiterSerial
		///
		/// @param serial		Serial to wrap around
		/// 
		explicit DelimiterSerial(const ISerial& serial);

		/// 
		/// Sends the buffer followed by the TDelimiter
		///
		/// @param buffer		Buffer to send
		/// @param len			Length of the buffer
		/// @return				-1 if failed, else the amount of bytes sent	
		/// 
		int32_t Send(const char* buffer, uint32_t len) const override;
		
		/// 
		/// Only sends the buffer directly
		///
		/// @param buffer		Buffer to send
		/// @param len			Length of the buffer
		/// @return				-1 if failed, else the amount of bytes sent				
		/// 
		int32_t SendRaw(const char* buffer, uint32_t len) const;
		
		/// 
		/// Receives data from the endpoint and searches for the TDelimiter. If found it stores the 
		/// data up to the delimiter and stores (if any) additional data in a circular buffer.\n
		/// If there is data in the circular buffer before calling this, it first fetches it from the
		/// buffer.
		///
		/// @param buffer		Buffer to store the data
		/// @param len			Length of the buffer
		/// @return				-1 if failed, else the amount of bytes received
		/// 
		int32_t Receive(char* buffer, uint32_t len) const override;
		
		/// 
		/// Receives data from the endpoint and store it in the buffer.
		///
		/// @param buffer		Buffer to store the data
		/// @param len			Length of the buffer
		/// @return				-1 if failed, else the amount of bytes received
		/// 
		int32_t ReceiveRaw(char* buffer, uint32_t len) const;
		
		/// 
		/// Calls flush on the underlying serial device and flushes the internal buffer
		/// 
		void Flush() const override;


		/// 
		/// Calls flush on the underlying serial device if internalBufferOnly is false, and
		/// flushes the internal buffer.
		///
		/// @param internalBufferOnly		Specify to flush only the internal buffer
		/// 
		void Flush(bool internalBufferOnly) const;

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
		int32_t sent = 0;
		if (buffer && len > 0)
		{
			sent = m_Serial.Send(buffer, len);
			if (sent == -1)
				return -1;
		}

		int32_t lineSent = m_Serial.Send(TDelimiter, m_DelimiterLength);
		if (lineSent == -1)
			return -1;

		return sent + lineSent;
	}

	template <typename TType, TType TLen, const char* TDelimiter>
	int32_t DelimiterSerial<TType, TLen, TDelimiter>::SendRaw(const char* buffer, uint32_t len) const
	{
		return m_Serial.Send(buffer, len);
	}

	template <typename TType = uint32_t, TType TLen, const char* TDelimiter>
	void DelimiterSerial<TType, TLen, TDelimiter>::Flush() const
	{
		Flush(false);
	}

	template <typename TType, TType TLen, const char* TDelimiter>
	void DelimiterSerial<TType, TLen, TDelimiter>::Flush(bool internalBufferOnly) const
	{
		m_Circular.Flush();
		
		if (!internalBufferOnly)
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

	template <typename TType, TType TLen, const char* TDelimiter>
	int32_t DelimiterSerial<TType, TLen, TDelimiter>::ReceiveRaw(char* buffer, uint32_t len) const
	{
		return m_Serial.Receive(buffer, len);
	}
}

#endif // !LINE_READER_WRITER_H_
