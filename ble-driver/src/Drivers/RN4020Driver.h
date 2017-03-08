#ifndef RN4020_H_
#define RN4020_H_

#include "../Models/BluetoothLEPeripheral.h"
#include "../Serial/ISerial.h"
#include "../Models/ServerCharacteristic.h"
#include "../Models/ClientCharacteristic.h"
#include "../Serial/DelimiterSerial.h"
#include "../Models/ClientCharacteristicConfiguration.h"

namespace Bluetooth
{
	class RN4020Device;

	namespace Drivers
	{
		extern char g_NewLineDelimiter[];

		class RN4020Driver
		{
			friend class RN4020Device;

		public:
			enum BaudRate;
			enum Features;

			typedef uint32_t Services;

			explicit RN4020Driver(const Serial::ISerial& serial);

			/// 
			/// This command sets the baud rate of the UART communication. The input parameter
			/// is a single digit number in the range of 0 to 7, representing a baud rate from 2400 to
			///	921K, as shown in Table 2 - 5. When the baud rate is set to 2400, there is no need to
			///	wake the RN4020 module by pulling WAKE_SW high for UART communication.
			///
			/// @param baud		Baud rate to set
			/// @return			true if operation completed succesfully	
			/// 
			bool SetBaudRate(BaudRate baud) const;

			/// 
			/// This command gets the baud rate of the UART communication.
			///
			/// @param baud		Current baud rate
			/// @return			true if operation completed succesfully			
			/// 
			bool GetBaudRate(BaudRate* baud) const;

			/// 
			/// This command sets the supported features of current RN4020 module. The input
			/// parameter is a 32 - bit bitmap that indicates features to be supported.After changing
			///	the features, a reboot is necessary to make the changes effective.The bitmap of
			///	features is shown in Table 2 - 7.
			///
			/// @param features		Features to set
			/// @return true if operation completed succesfully
			/// 
			bool SetFeatures(Features features) const;

			/// 
			/// This command gets the current features
			///
			/// @param features		Current features
			/// @return true if operation completed succesfully
			/// 
			bool GetFeatures(Features* features) const;

			/// 
			/// This command sets the value of the firmware revision characteristic in the Device
			/// Information Service.\n
			///	The Device Information Service is used to identify the device. Since all of its
			///	characteristics rarely change, the values of the characteristics in the Device
			///	Information Service can be set and saved into NVM.
			///
			/// @param version		Firmware version to set
			/// @return true if operation completed succesfully
			/// 
			bool SetFirmwareVersion(const char* version) const;

			/// 
			/// This command gets the current firmware version.
			///
			/// @param version		Current Firmware version
			/// @param len			Length of buffer
			/// @return true if operation completed succesfully
			/// 
			bool GetFirmwareVersion(char* version, uint8_t len) const;

			/// 
			/// This command sets the value of the hardware revision characteristics in the Device
			/// Information Service	
			///
			/// @param version		Firmware version to set
			/// @return true if operation completed succesfully
			/// 
			bool SetHardwareVersion(const char* version) const;

			/// 
			/// This command gets the current hardware version.
			///
			/// @param version		Current Hardware version
			/// @param len			Length of buffer
			/// @return true if operation completed succesfully
			/// 
			bool GetHardwareVersion(char* version, uint8_t len) const;

			/// 
			/// This command sets the value of the model characteristics in the Device Information
			/// Service.
			///
			/// @param model		Model name to set
			/// @return true if operation completed succesfully
			/// 
			bool SetModel(const char* model) const;

			/// 
			/// This command gets the current model name.
			///
			/// @param version		Current Model name
			/// @param len			Length of buffer
			/// @return true if operation completed succesfully
			/// 
			bool GetModel(char* version, uint8_t len) const;

			/// 
			/// This command sets the value of the manufacturer name characteristics in the Device
			///	Information Service.
			///
			/// @param manufacturer	Manufacturer name to set
			/// @return true if operation completed succesfully
			/// 
			bool SetManufacturer(const char* manufacturer) const;

			/// 
			/// This command gets the current manufacturer name.
			///
			/// @param manufacturer		Current Manufacturer name
			/// @param len			Length of buffer
			/// @return true if operation completed succesfully
			/// 
			bool GetManufacturer(char* manufacturer, uint8_t len) const;

			/// 
			/// This command sets the device name, where <string> is up to 20 alphanumeric
			/// characters.
			///
			/// @param name		Device name to set
			/// @return			true if operation completed succesfully			
			/// 
			bool SetName(const char* name) const;

			/// 
			/// 
			///
			/// @param name		Current device name
			/// @param len		Length of buffer
			/// @return			true if operation completed succesfully
			///
			bool GetName(char* name, uint8_t len) const;

			/// 
			/// This command sets the transmission power. The transmission power value will be
			/// saved in NVM and retrievable by the command “GP”.\n
			/// Note: A reboot is not needed for the new power value to become effective
			///
			/// SP Value	TX Power(dBm)
			///		0		-19.1
			///		1		-15.1
			///		2		-10.9
			///		3		-6.9
			///		4		-2.5 (default)
			///		5		1.6
			///		6		5.8
			///		7		7.5
			///
			/// @param value		value to set
			/// @return	true if operation completed succesfully			
			/// 
			bool SetPower(uint8_t value) const;

			/// 
			/// This commands get the transmission power.
			///
			/// @param value		output of value
			/// @return	true if operation completed succesfully			
			/// 
			bool GetPower(uint8_t* value) const;

			/// 
			/// This command sets the serialized Bluetooth-friendly name of the device, where
			/// <string> is up to 15 alphanumeric characters.This command automatically appends
			///	the last 2 bytes of the Bluetooth MAC address to the name, which is useful for
			///	generating a custom name with unique numbering
			///
			/// @param name		Bluetooth-friendly name
			/// @return			true if operation completed succesfully
			/// 
			bool SetSerializedName(const char* name) const;

			/// 
			/// This command gets the serialized Bluetooth-friendly name of the device.
			///
			/// @param name		Bluetooth-friendly name
			/// @param len		Length of buffer
			/// @return			true if operation completed succesfully
			/// 
			bool GetSerializedName(char* name, uint8_t len) const;

			/// 
			/// This command sets the value of the software revision characteristics in the Device
			///	Information Service.
			///
			/// @param revision		Revision to set
			/// @return true if operation completed succesfully
			/// 
			bool SetSoftwareRevision(const char* revision) const;

			/// 
			/// This command gets the current software revision.
			///
			/// @param revision		Current revision
			/// @param len			Length of buffer
			/// @return true if operation completed succesfully
			/// 
			bool GetSoftwareRevision(char* revision, uint8_t len) const;

			/// 
			/// This command sets the value of the serial number characteristics in the Device
			/// Information Service.
			///
			/// @param serial		Serial to set
			/// @return true if operation completed succesfully
			/// 
			bool SetSerialNumber(const char* serial) const;

			/// 
			/// This command gets the current serial number.
			///
			/// @param serial		Current serial
			/// @param len			Length of buffer
			/// @return true if operation completed succesfully
			/// 
			bool GetSerialNumber(char* serial, uint8_t len) const;

			/// 
			/// This command sets the initial connection parameters for future connections. The
			/// three input parameters are all 16 - bit values in hexadecimal format.To modify the
			///	current connection parameters, refer to the action command “T”.\n
			///	For a central device, the connection parameters will be used to establish connections
			///	with peripherals.For a peripheral device, the connection parameters are used to
			///	request the connection update once a new connection is established.Acceptance of
			///	the connection update from a peripheral device depends on the central device.\n
			///
			/// @param interval		The time interval of communication between two
			///						connected devices. (unit: 1.25 ms; default: 0x06)
			/// @param latency		The number of consecutive connection events that
			///						the peripheral does not need to communicate with
			/// 					central. (default: 0x00)
			/// @param timeout		The maximum time between raw communications
			///						before the link is considered lost. (unit: 10 ms; default: 0x64)
			/// @return true if operation completed succesfully			
			/// 
			bool SetTiming(uint16_t interval, uint16_t latency, uint16_t timeout) const;

			/// 
			///	Returns the desirable connection parameters	set by the SetTiming command when a connection 
			/// is not established. Once a connection is established, the actual connection parameters 
			/// will be displayed in response to the command.
			///
			/// @param interval		Current interval
			/// @param latency		Current latency
			/// @param timeout		Current timeout
			/// @return true if operation completed succesfully				
			/// 
			bool GetTiming(uint16_t* interval, uint16_t* latency, uint16_t* timeout) const;

			/// 
			/// This command sets the services supported by the device in a server role. The input
			/// parameter is a 32 - bit bitmap that indicates the services supported as a server.
			///	Supporting the service - as - server role means that the host MCU needs to supply the
			///	values of all characteristics in the supported services and provides client access to
			///	those values upon request.The values for the service characteristics are written to
			///	the server database using the “SUW” or “SHW” commands.Once the service bitmap
			///	is modified, the device must reboot to make the new services effective.The 32 - bit
			///	bitmap is provided in Table 2 - 8.
			///
			/// @param services		Services to set
			/// @return true if operation completed succesfully
			/// 
			bool SetServerServices(Services services) const;

			/// 
			/// This command gets the current Server Services
			///
			/// @param services		Current Server Services
			/// @return true if operation completed succesfully
			/// 
			bool GetServerServices(Services* services) const;

			/// 
			/// This command resets the configurations to the factory default at the next reboot. The
			/// parameters for this command can be either ‘1’ and ‘2’.\n
			///	When the input parameter is ‘1’, a majority of the settings will be restored to the
			///	factory default, but some settings, such as device name, device info, script and
			///	private services, stay the same. When the input parameter is ‘2’, all parameters are
			///	restored to factory default.
			///
			/// @param fullReset	if true, parameter is ‘2’
			/// @return true if operation completed succesfully
			/// 
			bool ResetDefaults(bool fullReset = false) const;

			/// 
			/// This command is only available to a device that operates as a peripheral in a
			/// broadcaster role.\n
			///	The “A” command is used to start advertisement.When the device acts in a
			///	broadcaster role, which is enabled by the “N” command, the advertisement is an
			///	undirected, unconnectable, manufacturer - specific broadcast message.The payload
			///	of the message is set by the “N” command.\n
			///	When the device acts in a peripheral role and it is not bonded, the advertisement is
			///	undirected connectable, which means it is discoverable by all BTLE central devices.
			///	When the device is bonded, the advertisement is directed if the no_direct_adv bit is
			///	cleared using the “SR” command; otherwise, the advertisement is undirected if the
			///	no_direct_adv bit is set.When direct advertisement is used, it is directed to the
			///	bonded device so that other BTLE devices are not heard.
			///
			/// @param interval		interval between advertisements [ms]
			/// @param window		total time to advertise, must be larger than interval [ms]
			/// @return true if operation completed succesfully			
			/// 
			bool Advertise(uint16_t interval, uint16_t window) const;

			/// 
			/// This command is used to secure the connection and bond two connected devices.
			///	The “B” command is only effective if two devices are already connected.Bonding can
			///	be issued from either a central or a peripheral device.\n
			///	If no input parameter is provided or the input parameter is ‘1’, the connection will be
			///	secured and the peer device remembered.In this situation, the two devices are
			///	considered bonded.If the input parameter is ‘0’, the connection is secured; however,
			///	the peer device is not saved into NVM.In this situation, the connection is not bonded.\n
			///	Once bonded, security information is saved to both ends of the connection if the
			///	“do_not_save_bonding” setting is cleared using the “SR” command.Therefore,
			///	reconnection between bonded devices does not require authentication, allowing
			///	reconnection to be done in a short amount of time.For bonded peripheral devices,
			///	advertisement can only be directed.As a result, bonded peripheral devices are not
			///	available for inquiry or connection.
			///
			/// @param enable		Enables the bonding ‘1’
			/// @return true if operation completed succesfully			
			/// 
			bool Bond(bool enable = true) const;

			/// 
			/// Note: This command is only available to devices in a central role\n\n
			/// If the central device is already bonded with a peripheral, issuing the “E” command
			/// without parameters will automatically start the process of connecting with the bonded
			///	peripheral.Usually, the bonded central device needs to first issue the “E” command,
			///	and then the bonded peripheral starts the directed advertisement.\n
			///	If the central device is not bonded with the peripheral, two input parameters are
			///	required to establish connection with a peripheral device.The first parameter is the
			///	MAC address type, and second parameter is the MAC address of the peripheral
			///	device.The MAC address type is either ‘0’ for public address or ‘1’ for a random
			///	address.The address type will be available in the result of an inquiry using the “F”
			///	command.The second parameter is a 6 - byte MAC address, which is also available
			///	as a result of using the “F” command.
			///
			/// @param usePublicAddress		MAC address type
			/// @param macAddress			6 - byte MAC adress
			/// @return	true if operation completed succesfully					
			/// 
			bool Establish(bool usePublicAddress, const MACAddress& macAddress) const;

			/// 
			/// This command is only available to a device in a central or observer role. For a central
			/// device, it is used to query the peripheral devices before establishing a connection.
			///	For the observer role, it is used to receive broadcast messages.\n
			///	If no parameter is provided, the “F” command starts the active scan process with a
			///	default scan interval of 375 milliseconds and a scan window of 250 milliseconds.The
			///	user has the option to specify the scan interval and scan window as the first and
			///	second parameter, respectively, as a 16 - bit hex value in milliseconds\n\n
			/// If both interval and window '0' the defaults will be used.
			///
			/// @param interval		scan interval
			/// @param window		windows interval
			/// @return	true if operation completed succesfully				
			/// 
			bool Find(uint16_t interval, uint16_t window) const;

			/// 
			/// This command places the device into or out of an observer role.\n
			/// If the input parameter is ‘1’, the RN4020 module enters Observer mode.After issuing
			///	the “F” command, the RN4020 module is able to receive undirected, unconnectable
			///	advertisements from broadcasters.If the input parameter is ‘0’, the RN4020 module
			///	exits Observer mode.
			///
			/// @param enable		true means 't't, the module enters Observer mode
			/// @return	true if operation completed succesfully					
			/// 
			bool Observer(bool enable = true) const;

			/// 
			/// This command is used to disconnect the active BTLE link. The “K” command can be
			/// used in a central or peripheral role.An error is returned if there is no connection
			///
			/// @return	true if operation completed succesfully				
			/// 
			bool Kill() const;

			/// 
			/// This command is used to obtain the signal strength of the last communication with
			/// the peer device.The signal strength can be used to estimate the distance between
			///	the device and its peer.\n
			///	The return value of the “M” command is the Received Signal Strength Indication
			///	(RSSI) in dBm.The accuracy of the result is within 6 dBm
			///
			/// @return				RSSI if connected, else 0
			/// 
			int8_t SignalStrength() const;

			/// 
			/// This command is used to place the RN4020 module into a broadcaster role and to
			/// set the advertisement content.The input parameter is in hexadecimal format, with a
			///	limit of up to 25 bytes.After setting the advertisement content, use the “A” command
			///	to start advertisement.
			///
			/// @param data		data to broadcast
			/// @param len		length of the data (maximum is 25)
			/// @return	true if operation completed succesfully				
			/// 
			bool Broadcast(uint8_t data[25], uint8_t len) const;

			/// 
			/// This command places the module into a Dormant mode that consumes very little
			/// power, and can be issued by either a central or peripheral device.\n
			///	When the RN4020 module is in Dormant mode, power consumption is less than 700
			///	nA.For comparison, power consumption is less than 5 µA in Deep Sleep mode.
			///	Once the RN4020 module enters Dormant mode, the WS pin(pin 10, PIO1 / BLUE
			///		LED) will assert low and all connection will be lost, as well as any data in RAM.To
			///	exit Dormant mode and enter Deep Sleep, pull the WAKE_HW pin(pin 15) high.
			///	Once the module has exited from Dormant mode, it behaves the same as after a
			///	reboot.To exit Deep Sleep and enter Active mode, pull WAKE_SW high
			///
			void Dormant() const;

			/// 
			/// This command displays critical information about the current device over the UART.
			/// The following information will be output after issuing a “D” command :\n
			/// • Device MAC Address\n
			///	• Device Name\n
			///	• Device Connection Role(Central or Peripheral)\n
			///	• Connected Device : Show the MAC address and address type(Public or Random)\n
			///	if connected, or “no” if no active connection\n
			///		• Bonded Device : Show the MAC address and address type(Public or Random) if
			///		connected, or “no” if no bonding device\n
			///		• Server Services : Bitmap of services that are supported in the server role\n\n
			///
			/// Note: it flushes the serial after performing the command to make sure it is empty
			/// for the next command.
			///
			/// @param buf		Buffer where to dump to
			/// @param len		Length of the buffer
			/// 
			bool Dump(char* buf, uint8_t len) const;

			/// 
			/// This command forces a complete device reboot (similar to a power cycle). It has one
			/// mandatory parameter of ‘1’.After rebooting the RN4020 module, all prior change
			/// settings take effect.
			/// 
			bool Reboot() const;

			/// 
			/// This command is used to change the connection parameters, interval, latency, and
			/// time - out for the current connection.The parameters of the “T” command are lost after
			///	a power cycle.All parameters are 16 - bit values in hexadecimal format.The “T”
			///	command is only effective if an active connection exists when the command is
			///	issued.\n
			///	For the definitions, ranges and relationships of connection interval, latency, and
			///	timeout, please refer to the “ST” command and Table 2 - 9 for details.\n
			///	When a “T” command with valid parameters is issued by a peripheral device, a
			///	minimum time - out interval is required between the two connection parameter update
			///	requests.Also, whether to accept the connection parameter update request is up to
			///	the central device.When the RN4020 module acts as a central device, it accepts all
			///	valid connection parameter update requests.
			///
			/// @param interval		The time interval of communication between two
			///						connected devices. (unit: 1.25 ms; default: 0x06)
			/// @param latency		The number of consecutive connection events that
			///						the peripheral does not need to communicate with
			/// 					central. (default: 0x00)
			/// @param timeout		The maximum time between raw communications
			///						before the link is considered lost. (unit: 10 ms; default: 0x64)
			/// @return true if operation completed succesfully			
			/// 
			bool UpdateTimings(uint16_t interval, uint16_t latency, uint16_t timeout) const;

			/// 
			/// This command removes the existing bonding. The “U” command not only removes
			/// the bonding, but it also changes the advertisement method.If a peripheral is
			///	advertising when a “U” command is issued, the RN4020 module will remove the
			///	bonding, stop the directed advertisement, and then start undirected advertisement.
			///
			/// @return	true if operation completed succesfully		
			/// 
			bool Unbond() const;

			/// 
			/// This command displays the firmware version
			///
			/// @param buf		Buffer to store the firmware version
			/// @param len		Length of the buffer
			/// 
			bool FirmwareVersion(char* buf, uint8_t len) const;

			/// 
			/// This command is only available to a central or observer device. For a central device,
			/// it stops the inquiry process.For observers, it stops receiving broadcast messages.
			///
			/// @return	true if operation completed succesfully				
			/// 
			bool StopScan() const;

			/// 
			/// This command is only available to a peripheral or broadcaster device. It stops
			/// advertisement that was started by an “A” command.\n\n
			/// Note: SR,20000000 overrides this (FEATURE_AUTO_ADVERTISE)
			///
			/// @return	true if operation completed succesfully				
			/// 
			bool StopAdvertisement() const;

			/// 
			/// This command is only available to a central device. It stops the connection process
			/// that was started by an “E” command
			///
			/// @return	true if operation completed succesfully			
			/// 
			bool StopConnecting() const;

			/// 
			/// After issueuing the Find command use this to read the scanned devices. It relies on
			/// the serial.Read to timeout after a certain time, use the timeout argument to specify
			/// how many it will be called until it stops trying. For example if the serial timeout
			/// is 100 ms it blocks up to timeout x 100ms.\n
			/// It also stops when the len has been reached to indicate the length of the array.
			///
			/// @param devices		Scanned devices
			/// @param len			Maximum length of devices to store
			/// @param found		Devices found
			/// @return	true if operation completed succesfully					
			/// 
			bool ReadScan(BluetoothLEPeripheral* devices, uint8_t len, uint8_t* found, uint8_t timeout = 10) const;

			/// 
			/// Requests Server Services (LS command) and stores the UUID of each service in an array.
			///
			/// @param services		Array of service UUID to store
			/// @param len			Length of the array
			/// @param listed		Amount of services found
			/// @return	true if operation completed succesfully			
			/// 
			bool ListServerServices(UUID* services, uint8_t len, uint8_t* listed) const;

			/// 
			/// Requests Client Services (LC command) and stores the UUID of each service in an array.\n
			/// Note: must be connected to a client.
			///
			/// @param services		Array of service UUID to store
			/// @param len			Length of the array
			/// @param listed		Amount of services found
			/// @return	true if operation completed succesfully			
			/// 
			bool ListClientServices(UUID* services, uint8_t len, uint8_t* listed) const;

			/// 
			/// Request Server Services (LS) and stores all characteristics in an array.
			///
			/// @param characteristics		Array of characteristics to store
			/// @param len					Length of the array
			/// @param listed				Amount of characteristics found
			/// @return	true if operation completed succesfully				
			/// 
			bool ListServerCharacteristics(LongServerCharacteristic* characteristics, uint8_t len, uint8_t* listed) const;

			/// 
			/// Request Client Services (LC) and stores all characteristics in an array.\n
			/// Note: must be connected to a client.
			///
			/// @param characteristics		Array of characteristics to store
			/// @param len					Length of the array
			/// @param listed				Amount of characteristics found
			/// @return	true if operation completed succesfully				
			/// 
			bool ListClientCharacteristics(LongClientCharacteristic* characteristics, uint8_t len, uint8_t* listed) const;

			/// 
			/// Request Server Services (LS) and stores all characteristics of serviceUUID in an array.
			///
			/// @param serviceUUID			UUID of service to list characteristics from
			/// @param characteristics		Array of characteristics to store
			/// @param len					Length of the array
			/// @param listed				Amount of characteristics found
			/// @return	true if operation completed succesfully				
			///  
			bool ListServerCharacteristics(const UUID& serviceUUID, LongServerCharacteristic* characteristics, uint8_t len, uint8_t* listed) const;

			/// 
			/// Request Client Services (LC) and stores all characteristics of serviceUUID in an array.\n
			/// Note: must be connected to a client.
			///
			/// @param serviceUUID			UUID of service to list characteristics from
			/// @param characteristics		Array of characteristics to store
			/// @param len					Length of the array
			/// @param listed				Amount of characteristics found
			/// @return	true if operation completed succesfully				
			///  
			bool ListClientCharacteristics(const UUID& serviceUUID, LongClientCharacteristic* characteristics, uint8_t len, uint8_t* listed) const;

			/// 
			/// Writes a specific value to the Server Characteristic specified by the UUID
			///
			/// @tparam T		Type of integer
			/// @param uuid		UUID of characteristic
			/// @param value	value to write
			/// @return	true if operation completed succesfully					
			/// 
			template <typename T>
			bool WriteServerIntegerByUUID(uint16_t uuid, T value) const;

			/// 
			/// Writes a specific value to the Server Characteristic specified by the handle
			///
			/// @tparam T		Type of integer
			/// @param handle	Handle of characteristic
			/// @param value	value to write
			/// @return	true if operation completed succesfully					
			/// 
			template <typename T>
			bool WriteServerIntegerByHandle(uint16_t handle, T value) const;

			/// 
			/// Read a value from the Server Characteristic specified by the UUID
			///
			/// @tparam T		Type of integer
			/// @param uuid		UUID of characteristic
			/// @param value	value to read to
			/// @return	true if operation completed succesfully					
			template <typename T>
			bool ReadServerIntegerByUUID(uint16_t uuid, T* value) const;

			/// 
			/// Read a value from the Server Characteristic specified by the handle
			///
			/// @tparam T		Type of integer
			/// @param handle	handle of characteristic
			/// @param value	value to read to
			/// @return	true if operation completed succesfully	
			template <typename T>
			bool ReadServerIntegerByHandle(uint16_t handle, T* value) const;

			/// 
			/// Writes to the configuration characteristic at the connected client to enable/
			/// disable notifcation or indication as specified in the enable parameter.
			///
			/// @param uuid			UUID of characteristic
			/// @param enable		Enable indication or notification
			/// @return	true if operation completed succesfully	
			/// 
			bool WriteClientConfigurationByUUID(uint16_t uuid, bool enable) const;

			/// 
			/// Writes a specific value to the Client Characteristic specified by the UUID
			///
			/// @tparam T		Type of integer
			/// @param uuid		UUID of characteristic
			/// @param value	value to write
			/// @return	true if operation completed succesfully					
			/// 
			template <typename T>
			bool WriteClientIntegerValueByUUID(uint16_t uuid, T value) const;

			/// 
			/// Reads the configuration characteristic at the connected client.
			///
			/// @param uuid				UUID of characteristic
			/// @param configuration	Configuration to read to	
			/// @return	true if operation completed succesfully			
			/// 
			bool ReadClientConfigurationByUUID(uint16_t uuid, ClientCharacteristicConfiguration* configuration) const;

			/// 
			/// Reads the value characteristic as a integer by UUID.
			///
			/// @tparam T		Type of the integer
			/// @param uuid		UUID of characteristic
			/// @param value	value to read to
			/// @return	true if operation completed succesfully			
			/// 
			template <typename T>
			bool ReadClientIntegerByUUID(uint16_t uuid, T* value) const;

			/// 
			/// Reads the value characteristic as a integer by the handle.
			///
			/// @tparam T		Type of the integer
			/// @param handle	Handle of characteristic
			/// @param value	value to read to
			/// @return	true if operation completed succesfully			
			/// 
			template <typename T>
			bool ReadClientIntegerByHandle(uint16_t handle, T* value) const;

			enum BaudRate
			{
				RN4020_BAUD_2400 = 0,
				RN4020_BAUD_9600 = 1,
				RN4020_BAUD_19200 = 2,
				RN4020_BAUD_38400 = 3,
				RN4020_BAUD_115200 = 4,
				RN4020_BAUD_230400 = 5,
				RN4020_BAUD_460800 = 6,
				RN4020_BAUD_921600 = 7
			};

			enum Features
			{
				/// 
				/// If set, the device that starts the connection is central. If cleared, the device that
				/// starts advertisement as peripheral.
				/// Beginning with Firmware Version 1.20, this option is ignored as GAP roles are
				/// determined by Action commands. Refer to Section 2.2 “GAP Role Switching”
				/// for more information
				/// 
				FEATURE_CENTRAL = 0x80000000,

				///
				/// If set, the device request values from the host MCU through the UART and the
				/// host MCU must respond in a timely manner. If cleared, the device reads from the
				/// internal RAM of the RN4020 for the characteristic values that were previously
				/// set.
				///
				FEATURE_REALTIME_READ = 0x40000000,

				///
				/// This setting only applies to a peripheral device. If set, the device starts 
				/// advertisement after a power cycle, reboot, or disconnection. If cleared, the device 
				/// starts advertisement after receiving command “A” from the UART in Command mode.
				///
				FEATURE_AUTO_ADVERTISE = 0x20000000,

				/// 
				/// If set, the device enables the private service MLDP that provides asynchronous
				/// serial data over Bluetooth LE.If cleared, MLDP is disabled.See
				/// Section 2.3.7 “Microchip MLDP Commands” for more information.
				/// 
				FEATURE_MLDP = 0x10000000,

				/// 
				/// This setting is only effective when MLDP is enabled. If set, the device enters
				/// MLDP mode after receiving command “I” from the UART in Command mode, or
				/// when CMD / MLDP(pin 8) is set high.If cleared, the device enters MLDP mode
				/// not only by command “I” or the CMD / MLDP pin, but also by receiving an MLDP
				/// data stream from the peer device
				/// 
				FEATURE_AUO_MLDP_DISABLE = 0x08000000,

				/// 
				/// This setting is only effective for peripheral devices. If set, the peripheral will not
				/// issue a direct advertisement even if it is bonded; therefore, it is discoverable
				/// whenever it is advertising.This setting is useful when working with iOS or
				/// Android devices
				/// 
				FEATURE_NO_DIRECT_ADVERTISEMENT = 0x04000000,

				/// 
				/// This setting is used to control RTS/CTS hardware flow control on the RN4020
				/// module UART port.If set, flow control is enabled and the host needs to support
				/// the UART hardware flow control feature.Flow control is recommended when
				/// MLDP is enabled
				/// 
				FEATURE_UART_FLOWCONTROL = 0x02000000,


				/// 
				/// This setting is used to control script execution. If set, after powering on, script
				/// execution will be automatically started by generating a @PW_ON event
				/// 
				FEATURE_STARTUP_SCRIPT = 0x01000000,


				/// 
				/// This setting enables authentication during connection, preventing a
				/// Man - In - The - Middle(MITM) attack.When authentication is enabled, I / O
				/// capability is set to be keyboard and / or display.For details, refer to Table 2.5:
				/// “Mapping of IO Capabilities to STK Generation Method” in Vol 3, Part H,
				/// Section 2.3.5.1 “Selecting STK Generation Method” in “Bluetooth Core
				/// Specification v4.1”
				/// 
				FEATURE_AUTHENTICATION = 0x00400000,

				/// 
				/// This setting is only effective if the MLDP feature is enabled. This setting enables
				/// the local device to receive remote commands from a remote device and to send
				/// command output to a remote device through the MLDP data stream.
				///
				FEATURE_REMOTE_COMMAND = 0x00200000,

				/// 
				/// Once set, the bonding information will not be saved in NVM and the bonding is
				/// only valid for the current connection.
				/// 
				FEATURE_DONT_SAVE_BONDING = 0x00100000,

				/// 
				/// If set, all “Set” commands are no longer effective in Remote Command mode.
				/// 
				FEATURE_BLOCK_REMOTE_SET = 0x00010000,

				/// 
				/// If set, DFU over the air is effective. Otherwise, support of DFU OTA is disabled
				/// 
				FEATURE_OTA = 0x00008000,

				/// 
				/// If set, connection parameters will be checked against Apple® Bluetooth
				///	Accessory Design Guidelines.See the ST, <interval>, <latency>, <timeout>
				///	command for details.
				/// 
				FEATURE_IOS_MODE = 0x00004000,


				/// 
				/// If set, the RN4020 module will not act as a client. No service discovery will be
				///	performed after connection to save connection time and power.
				/// 
				FEATURE_SERVER_ONLY = 0x00002000,

				/// 
				/// If set, allow normal UART output when running a script.
				/// 
				FEATURE_UART_SCRIPT = 0x00001000,

				/// 
				/// If set, and the Support MLDP bit is also set, once connected, the RN4020 module
				/// automatically enters MLDP mode.
				/// 
				FEATURE_AUTO_MLDP = 0x00000800,

				/// 
				/// If set, no additional status string, such as “CMD”, “Connected”, and “Connection
				///	End”, is in the UART output
				/// 
				FEATURE_MLDP_NO_STATUS = 0x00000400
			};

		private:
			static const uint8_t BUF_LEN = 32;

			bool Set(const char* command, const char* param) const;
			bool SetHex32(const char* command, uint32_t value) const;

			template <typename T>
			bool WriteCharacteristicInteger(const char* command, uint16_t handle, T value) const;

			template <typename T>
			bool ReadClientCharacteristicInteger(const char* command, uint16_t param, T* value) const;

			template <typename T>
			bool ReadServerCharacteristicInteger(const char* command, uint16_t param, T* value) const;

			bool Get(char* buf, uint32_t len, int32_t* received = NULL) const;
			bool Get(const char* command, char* buf, uint32_t len, int32_t* received = NULL) const;
			bool GetHex32(const char* command, uint32_t* value) const;

			bool WaitAnything(uint8_t timeout = 20) const;
			bool WaitAnything(char* buf, uint32_t len, int32_t* received = NULL, uint8_t timeout = 20) const;

			bool ListServices(const char* command, UUID* services, uint8_t len, uint8_t* listed) const;

			template <typename T>
			bool ListCharacteristics(const UUID* targetUUID, const char* command, T* characteristics, uint8_t len, uint8_t* listed) const;

			BluetoothLEPeripheral ParseScanLine(const char* line) const;
			Serial::DelimiterSerial<uint8_t, BUF_LEN, g_NewLineDelimiter> m_Serial;
		};

		template <typename T>
		T ParseCharacteristic(const UUID& serviceUUID, char* line)
		{
			typedef int assert_no_generic_implementation[-1];
			return NULL;
		}

		void ParseCharacteristic(char** token, UUID* characteristicUUID, uint16_t* handle);

		template <>
		LongServerCharacteristic ParseCharacteristic<LongServerCharacteristic>(const UUID& serviceUUID, char* line);

		template <>
		LongClientCharacteristic ParseCharacteristic<LongClientCharacteristic>(const UUID& serviceUUID, char* line);

		template <typename T>
		bool RN4020Driver::WriteCharacteristicInteger(const char* command, uint16_t handle, T value) const
		{
			// handle + T + 0
			char buf[4 + 2 * sizeof(T) + 2] = { 0 };
			snprintf(buf, sizeof(buf), "%04X,%0*X", handle, sizeof(T) * 2, value);

			return Set(command, buf);
		}

		template <typename T>
		bool RN4020Driver::ReadClientCharacteristicInteger(const char* command, uint16_t param, T* value) const
		{
			// uint32_t is max 8 bytes + R + , + .
			char buf[12] = { 0 };
			snprintf(buf, sizeof(buf), "%.4s,%04X", command, param);

			if (!Get(buf, buf, sizeof(buf)))
				return false;

			char* start = strchr(buf, ',') + 1;
			char* end = strchr(start, '.');

			// null terminate the value
			*end = 0;

			// get the value
			unsigned long val = strtoul(start, NULL, 16);
			*value = static_cast<T>(val);

			return true;
		}

		template <typename T>
		bool RN4020Driver::ReadServerCharacteristicInteger(const char* command, uint16_t param, T* value) const
		{
			// max command lenght is 4 CUWC/CUWV + param + 0
			char buf[9] = { 0 };
			snprintf(buf, sizeof(buf), "%.4s,%04X", command, param);

			// largest integer returned is 32 bits
			uint32_t x;
			if (!GetHex32(buf, &x))
				return false;

			*value = static_cast<T>(x);
			return true;
		}

		template <typename T>
		bool RN4020Driver::ListCharacteristics(const UUID* targetUUID, const char* command, T* characteristics, uint8_t len, uint8_t* listed) const
		{
			char line[BUF_LEN];

			UUID serviceUUID;
			uint8_t index = 0;

			bool receiving = Get(command, line, sizeof(line));
			bool isTargetUUID = false;

			while (receiving && index < len && strncmp(line, "END", 3) != 0)
			{
				// starts with two spaces means a characteristic else its a new service
				if (strncmp(line, "  ", 2) == 0)
				{
					// if we want all characteristics or it is our target
					if (targetUUID == NULL || isTargetUUID)
						characteristics[index++] = ParseCharacteristic<T>(serviceUUID, line);
				}
				else
				{
					// stop when we already have looped over the target UUID
					if (isTargetUUID)
						break;

					serviceUUID = UUID(line);
					isTargetUUID = targetUUID && *targetUUID == serviceUUID;
				}

				receiving = Get(line, sizeof(line));
			}

			if (listed)
				*listed = index;

			// true if we requested everything or got the target characteristics
			return targetUUID == NULL || isTargetUUID;
		}

		template <typename T>
		bool RN4020Driver::WriteServerIntegerByUUID(uint16_t uuid, T value) const
		{
			return WriteCharacteristicInteger("SUW", uuid, value);
		}

		template <typename T>
		bool RN4020Driver::WriteServerIntegerByHandle(uint16_t handle, T value) const
		{
			return WriteCharacteristicInteger("SHW", handle, value);
		}

		template <typename T>
		bool RN4020Driver::ReadServerIntegerByUUID(uint16_t uuid, T* value) const
		{
			return ReadServerCharacteristicInteger("SUR", uuid, value);
		}

		template <typename T>
		bool RN4020Driver::ReadServerIntegerByHandle(uint16_t handle, T* value) const
		{
			return ReadServerCharacteristicInteger("SHR", handle, value);
		}

		template <typename T>
		bool RN4020Driver::WriteClientIntegerValueByUUID(uint16_t uuid, T value) const
		{
			return WriteCharacteristicInteger("CUWV", uuid, value);
		}

		template <typename T>
		bool RN4020Driver::ReadClientIntegerByUUID(uint16_t uuid, T* value) const
		{
			return ReadClientCharacteristicInteger("CURV", uuid, value);
		}

		template <typename T>
		bool RN4020Driver::ReadClientIntegerByHandle(uint16_t handle, T* value) const
		{
			return ReadClientCharacteristicInteger("CHR", handle, value);
		}
	}
}

#endif // !RN4020_H_
