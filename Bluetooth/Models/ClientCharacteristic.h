#ifndef CLIENT_CHARACTERISTIC_H_
#define CLIENT_CHARACTERISTIC_H_

// user libraries
#include "UUID.h"
#include "CharacteristicProperty.h"
#include <utility>

namespace Bluetooth
{
	/// 
	/// Class to hold Client Characteristic
	///
	/// @tparam TUUID		Type of the UUID (should probably be UUID or uint16_t)
	/// 
	template <class TUUID>
	class ClientCharacteristic
	{
	public:
		/// 
		/// Constructs empty ClientCharacteristic
		/// 
		ClientCharacteristic(): m_Handle(0), m_CharacteristicProperty()
		{
		}

		/// 
		/// Constructs new ClientCharacteristic
		///
		/// @param a_ServiceUuid				The service UUID
		/// @param a_CharacteristicUuid			The characteristic UUID
		/// @param a_Handle						Handle of the characteristic
		/// @param a_CharacteristicProperty		Specifies if the characteristic is configuration
		/// 
		ClientCharacteristic(const TUUID& a_ServiceUuid, const TUUID& a_CharacteristicUuid, uint16_t a_Handle, CharacteristicProperty a_CharacteristicProperty)
			: m_ServiceUUID(a_ServiceUuid),
			  m_CharacteristicUUID(a_CharacteristicUuid),
			  m_Handle(a_Handle),
			  m_CharacteristicProperty(a_CharacteristicProperty)
		{
		}


		ClientCharacteristic(const ClientCharacteristic& a_Other)
			: m_ServiceUUID(a_Other.m_ServiceUUID),
			  m_CharacteristicUUID(a_Other.m_CharacteristicUUID),
			  m_Handle(a_Other.m_Handle),
			  m_CharacteristicProperty(a_Other.m_CharacteristicProperty)
		{
		}

		ClientCharacteristic& operator=(const ClientCharacteristic& a_Other)
		{
			if (this == &a_Other)
				return *this;
			m_ServiceUUID = a_Other.m_ServiceUUID;
			m_CharacteristicUUID = a_Other.m_CharacteristicUUID;
			m_Handle = a_Other.m_Handle;
			m_CharacteristicProperty = a_Other.m_CharacteristicProperty;
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
		/// Gets the characteristic property
		///
		/// @return				characteristic property
		/// 
		CharacteristicProperty GetCharacteristicProperty() const
		{
			return m_CharacteristicProperty;
		}

	private:
		TUUID m_ServiceUUID;
		TUUID m_CharacteristicUUID;
		uint16_t m_Handle;
		CharacteristicProperty m_CharacteristicProperty;
	};

	typedef ClientCharacteristic<UUID> LongClientCharacteristic;
	typedef ClientCharacteristic<uint16_t> ShortClientCharacteristic;
}

#endif // !CLIENT_CHARACTERISTIC_H_
