#ifndef CLIENT_CHARACTERISTIC_CONFIGURATION_H_
#define CLIENT_CHARACTERISTIC_CONFIGURATION_H_

/// 
/// Configuration of a connected Client Characteristic. \n
/// (false if not started; true if started)
/// 
enum ClientCharacteristicConfiguration
{
	/// 
	/// No indication or notification started
	///
	CHARACTERISTIC_CONFIGURATION_NOTSTARTED = 0x0000,

	/// 
	/// Notification started
	/// 
	CHARACTERISTIC_CONFIGURATION_NOTIFICATION_STARTED = 0x0001,

	/// 
	/// Indication started
	/// 
	CHARACTERISTIC_CONFIGURATION_INDICATINO_STARTED = 0x0002
};

#endif // !CLIENT_CHARACTERISTIC_CONFIGURATION_H_
