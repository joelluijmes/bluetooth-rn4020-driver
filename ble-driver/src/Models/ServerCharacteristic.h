#ifndef SERVER_CHARACTERISTIC_H_
#define SERVER_CHARACTERISTIC_H_

#include "UUID.h"

namespace Bluetooth
{
	/// 
	/// Class to hold Server Characteristic
	///
	/// @tparam TUUID		Type of the UUID (should probably be UUID or uint16_t)
	/// 
	template <class TUUID>
	class ServerCharacteristic
	{
	public:
		/// 
		/// Constructs empty ServerCharacteristic
		/// 
		ServerCharacteristic(): m_Handle(0), m_IsConfigurationHandle(false)
		{
		}

		/// 
		/// Constructs new ServerCharacteristic
		///
		/// @param a_ServiceUuid				The service UUID
		/// @param a_CharacteristicUuid			The characteristic UUID
		/// @param a_Handle						Handle of the characteristic
		/// @param a_IsConfigurationHandle		Specifies if the characteristic is configuration
		/// 
		ServerCharacteristic(const TUUID& a_ServiceUuid, const TUUID& a_CharacteristicUuid, uint16_t a_Handle, bool a_IsConfigurationHandle)
			: m_ServiceUUID(a_ServiceUuid),
			  m_CharacteristicUUID(a_CharacteristicUuid),
			  m_Handle(a_Handle),
			  m_IsConfigurationHandle(a_IsConfigurationHandle)
		{
		}

		ServerCharacteristic(const ServerCharacteristic& a_Other)
			: m_ServiceUUID(a_Other.m_ServiceUUID),
			  m_CharacteristicUUID(a_Other.m_CharacteristicUUID),
			  m_Handle(a_Other.m_Handle),
			  m_IsConfigurationHandle(a_Other.m_IsConfigurationHandle)
		{
		}
		
		ServerCharacteristic& operator=(const ServerCharacteristic& a_Other)
		{
			if (this == &a_Other)
				return *this;
			m_ServiceUUID = a_Other.m_ServiceUUID;
			m_CharacteristicUUID = a_Other.m_CharacteristicUUID;
			m_Handle = a_Other.m_Handle;
			m_IsConfigurationHandle = a_Other.m_IsConfigurationHandle;
			return *this;
		}

		/// 
		/// Gets the Service UUID
		///
		/// @return				service UUID
		/// 
		TUUID GetServiceUuid() const
		{
			return m_ServiceUUID;
		}

		/// 
		/// Gets the characteristic UUID
		///
		/// @return				characteristic UUID
		/// 
		TUUID GetCharacteristicUuid() const
		{
			return m_CharacteristicUUID;
		}

		/// 
		/// Gets the handle of the characteristic
		///
		/// @return				handle
		/// 
		uint16_t GetHandle() const
		{
			return m_Handle;
		}

		/// 
		/// Gets if the characteristic is configuration
		///
		/// @return				true if characteristic is configuration
		/// 
		bool GetIsConfigurationHandle() const
		{
			return m_IsConfigurationHandle;
		}

	private:
		TUUID m_ServiceUUID;
		TUUID m_CharacteristicUUID;
		uint16_t m_Handle;
		bool m_IsConfigurationHandle;
	};

	typedef ServerCharacteristic<UUID> LongServerCharacteristic;
	typedef ServerCharacteristic<uint16_t> ShortServerCharacteristic;
}

#endif // !SERVER_CHARACTERISTIC_H_
