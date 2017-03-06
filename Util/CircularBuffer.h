#ifndef CIRCULAR_BUFFER_H_
#define CIRCULAR_BUFFER_H_

namespace Util
{
	template <typename TType, TType TLen>
	class CircularBuffer
	{
		// for a fast modulo we need TLen to be a power of two
		typedef int assert_TLen_is_power_of_two[((TLen & (TLen - 1)) == 0) ? 1 : -1];

	public:
		CircularBuffer();

		TType Store(const char* data, TType len);
		TType Load(char* data, TType len);

		TType GetCount()
		{
			return ((m_StoreIndex - m_LoadIndex) & MASK);
		}

		TType GetFree()
		{
			return TLen - GetCount();
		}

		TType m_StoreIndex;
		TType m_LoadIndex;
		char m_Buffer[TLen];

	private:
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
}

#endif // !CIRCULAR_BUFFER_H_
