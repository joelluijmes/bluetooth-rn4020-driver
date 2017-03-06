#ifndef CIRCULAR_BUFFER_H_
#define CIRCULAR_BUFFER_H_

namespace Util
{
	/// 
	/// Type for a circular buffer. Note for performance reasons the TLen must be a power of two,
	/// for calculating the next index a modulo is used, by using a power of two an & operation
	/// can be used, which is significantly faster than a % operation.
	///
	/// @tparam TType		Type to use to hold the indexes (uint8_t, uint16_t ..)
	/// @tparam TLen		Length of the buffer (must be power of two)
	/// 
	template <typename TType, TType TLen>
	class CircularBuffer
	{
		// for a fast modulo we need TLen to be a power of two
		typedef int assert_TLen_is_power_of_two[((TLen & (TLen - 1)) == 0) ? 1 : -1];

	public:
		/// 
		/// Constructs an empty CircularBuffer
		///
		/// 
		CircularBuffer();

		/// 
		/// Store data in the circular buffer
		///
		/// @param data		Data to store
		/// @param len		Length of the data
		/// @return	amount of data stored (can be less than len if insufficient space is available)			
		/// 
		TType Store(const char* data, TType len);

		/// 
		/// Fetches data from the circular buffer
		///
		/// @param data		Target buffer to load data to
		/// @param len		Length of data to fetch from buffer
		/// @return	amount of data loaded (can be less than len if insufficient data is stored)					
		/// 
		TType Load(char* data, TType len);

		/// 
		/// Gets the amount of bytes stored in the buffer
		///
		/// @return				bytes stored
		/// 
		TType GetCount()
		{
			return ((m_StoreIndex - m_LoadIndex) & MASK);
		}

		/// 
		/// Gets the amount of bytes free to store in the buffer
		///
		/// @return				bytes free
		/// 
		TType GetFree()
		{
			return TLen - GetCount();
		}

		/// 
		/// Flushes the internal buffer pointers.
		/// 
		void Flush();

	private:
		TType m_StoreIndex;
		TType m_LoadIndex;
		char m_Buffer[TLen];
		const TType MASK = TLen - 1;
	};

	template <typename TType, TType TLen>
	CircularBuffer<TType, TLen>::CircularBuffer()
		: m_StoreIndex(0), m_LoadIndex(0)
	{
		memset(m_Buffer, 0, sizeof(m_Buffer));
	}

	template <typename TType, TType TLen>
	TType CircularBuffer<TType, TLen>::Store(const char* data, TType len)
	{
		for (TType i = 0; i < len; ++i)
		{
			// TLen must be divisable by 2 for our modulo to wrap around fast
			TType index = (m_StoreIndex + 1) & MASK;
			if (index == m_LoadIndex)
				return i; // full

			m_Buffer[m_StoreIndex] = data[i];
			m_StoreIndex = index;
		}

		return len;
	}

	template <typename TType, TType TLen>
	TType CircularBuffer<TType, TLen>::Load(char* data, TType len)
	{
		TType index = m_LoadIndex;
		TType i;

		for (i = 0; i < len; ++i)
		{
			if (m_StoreIndex == index)
				break; // empty

			data[i] = m_Buffer[index];
			m_Buffer[index] = 0xFF; // debugging only
			++index &= MASK;
		}

		m_LoadIndex = index;

		return i;
	}

	template <typename TType, TType TLen>
	void CircularBuffer<TType, TLen>::Flush()
	{
		m_LoadIndex = 0;
		m_StoreIndex = 0;
	}
}

#endif // !CIRCULAR_BUFFER_H_
