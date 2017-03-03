#ifndef CHARACTERISTIC_PROPERTY_H_
#define CHARACTERISTIC_PROPERTY_H_

namespace Bluetooth
{
	enum CharacteristicProperty
	{
		/// 
		/// Additional property available
		/// 
		CHARACTERISTIC_PROPERTY_EXTENDED = 1 << 7,
		
		/// 
		/// Write characteristic with authentication from client to server.
		/// 
		CHARACTERISTIC_PROPERTY_AUTHWRITE = 1 << 6,
		
		/// 
		/// Indicate value of characteristic with acknowledgment from server to client
		/// 
		CHARACTERISTIC_PROPERTY_INDICATE = 1 << 5,
		
		/// 
		/// Notify value of characteristic without acknowledgment from server to client
		/// 
		CHARACTERISTIC_PROPERTY_NOTIFY = 1 << 4,
		
		/// 
		/// Write value of characteristic with acknowledgment from client to server.
		/// 
		CHARACTERISTIC_PROPERTY_WRITE = 1 << 3,
		
		/// 
		/// Write value of characteristic without acknowledgment from client to server.
		/// 
		CHARACTERISTIC_PROPERTY_WRITE_NAK = 1 << 2,
		
		/// 
		/// Read value of characteristic. Value is sent from server to client.
		///
		CHARACTERISTIC_PROPERTY_READ = 1 << 1,

		/// 
		/// Broadcast value of characteristic.
		/// 
		CHARACTERISTIC_PROPERTY_BROADCAST = 1 << 0
	};
}

#endif // !CHARACTERISTIC_PROPERTY_H_
