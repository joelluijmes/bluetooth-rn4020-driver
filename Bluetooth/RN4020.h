#ifndef RN4020_H_
#define RN4020_H_

#include "IBluetooth.h"
#include <cstdio>
#include <stdlib.h>

namespace
{
}

namespace Bluetooth
{
	class RN4020 : public IBluetooth
	{
	public:
		enum BaudRate;
		enum Features;
		enum Services;

		explicit RN4020(const Serial::ISerial& serial)
			: IBluetooth(serial)
		{
		}

		/// 
		/// This command sets the baud rate of the UART communication. The input parameter
		/// is a single digit number in the range of 0 to 7, representing a baud rate from 2400 to
		///	921K, as shown in Table 2 - 5. When the baud rate is set to 2400, there is no need to
		///	wake the RN4020 module by pulling WAKE_SW high for UART communication.
		///
		/// @param baud		Baud rate to set
		/// @return			true if operation completed succesfully	
		/// 
		bool SetBaudRate(BaudRate baud) const
		{
			char buf[] = {static_cast<char>(baud + '0'), '\0'};
			return Set("SB", buf);
		}

		/// 
		/// This command gets the baud rate of the UART communication.
		///
		/// @param baud		Current baud rate
		/// @return			true if operation completed succesfully			
		/// 
		bool GetBaudRate(BaudRate* baud) const
		{
			// 1 for result; 2 for \r\n
			char buf[3];
			if (!Get("GB", buf, sizeof(buf), NULL))
				return false;

			*baud = static_cast<BaudRate>(buf[0] - '0');
			return true;
		}

		/// 
		/// This command sets the supported features of current RN4020 module. The input
		/// parameter is a 32 - bit bitmap that indicates features to be supported.After changing
		///	the features, a reboot is necessary to make the changes effective.The bitmap of
		///	features is shown in Table 2 - 7.
		///
		/// @param features		Features to set
		/// @return				true if operation completed succesfully
		/// 
		bool SetFeatures(Features features) const
		{
			return SetHex32("SR", static_cast<uint32_t>(features));
		}

		/// 
		/// This command gets the current features
		///
		/// @param features		Current features
		/// @return				true if operation completed succesfully
		/// 
		bool GetFeatures(Features* features) const
		{
			return GetHex32("GR", reinterpret_cast<uint32_t*>(features));
		}

		/// 
		/// This command sets the value of the firmware revision characteristic in the Device
		/// Information Service.\n
		///	The Device Information Service is used to identify the device. Since all of its
		///	characteristics rarely change, the values of the characteristics in the Device
		///	Information Service can be set and saved into NVM.
		///
		/// @param version		Firmware version to set
		/// @return				true if operation completed succesfully
		/// 
		bool SetFirmwareVersion(const char* version) const
		{
			return Set("SDF", version);
		}

		/// 
		/// This command gets the current firmware version.
		///
		/// @param version		Current Firmware version
		/// @param len			Length of buffer
		/// @return				true if operation completed succesfully
		/// 
		bool GetFirmwareVersion(char* version, uint8_t len) const
		{
			return GetString("GDF", version, len);
		}

		/// 
		/// This command sets the value of the hardware revision characteristics in the Device
		/// Information Service	
		///
		/// @param version		Firmware version to set
		/// @return				true if operation completed succesfully
		/// 
		bool SetHardwareVersion(const char* version) const
		{
			return Set("SDH", version);
		}

		/// 
		/// This command gets the current hardware version.
		///
		/// @param version		Current Hardware version
		/// @param len			Length of buffer
		/// @return				true if operation completed succesfully
		/// 
		bool GetHardwareVersion(char* version, uint8_t len) const
		{
			return GetString("SDH", version, len);
		}

		/// 
		/// This command sets the value of the model characteristics in the Device Information
		/// Service.
		///
		/// @param model		Model name to set
		/// @return				true if operation completed succesfully
		/// 
		bool SetModel(const char* model) const
		{
			return Set("SDM", model);
		}

		/// 
		/// This command gets the current model name.
		///
		/// @param version		Current Model name
		/// @param len			Length of buffer
		/// @return				true if operation completed succesfully
		/// 
		bool GetModel(char* version, uint8_t len) const
		{
			return GetString("GDM", version, len);
		}

		/// 
		/// This command sets the value of the manufacturer name characteristics in the Device
		///	Information Service.
		///
		/// @param manufacturer	Manufacturer name to set
		/// @return				true if operation completed succesfully
		/// 
		bool SetManufacturer(const char* manufacturer) const
		{
			return Set("SDN", manufacturer);
		}

		/// 
		/// This command gets the current manufacturer name.
		///
		/// @param manufacturer		Current Manufacturer name
		/// @param len			Length of buffer
		/// @return				true if operation completed succesfully
		/// 
		bool GetManufacturer(char* manufacturer, uint8_t len) const
		{
			return GetString("GDN", manufacturer, len);
		}

		/// 
		/// This command sets the device name, where <string> is up to 20 alphanumeric
		/// characters.
		///
		/// @param name		Device name to set
		/// @return			true if operation completed succesfully			
		/// 
		bool SetName(const char* name) const override
		{
			return Set("SN", name);
		}

		/// 
		/// 
		///
		/// @param name		Current device name
		/// @param len		Length of buffer
		/// @return			true if operation completed succesfully
		///
		bool GetName(char* name, uint8_t len) const override
		{
			return GetString("GN", name, len);
		}

		/// 
		/// This command sets the serialized Bluetooth-friendly name of the device, where
		/// <string> is up to 15 alphanumeric characters.This command automatically appends
		///	the last 2 bytes of the Bluetooth MAC address to the name, which is useful for
		///	generating a custom name with unique numbering
		///
		/// @param name		Bluetooth-friendly name
		/// @return			true if operation completed succesfully
		/// 
		bool SetSerializedName(const char* name) const
		{
			return Set("S-", name);
		}

		/// 
		/// This command gets the serialized Bluetooth-friendly name of the device.
		///
		/// @param name		Bluetooth-friendly name
		/// @param len		Length of buffer
		/// @return			true if operation completed succesfully
		/// 
		bool GetSerializedName(char* name, uint8_t len) const
		{
			return GetString("G-", name, len);
		}

		/// 
		/// This command sets the value of the software revision characteristics in the Device
		///	Information Service.
		///
		/// @param revision		Revision to set
		/// @return				true if operation completed succesfully
		/// 
		bool SetSoftwareRevision(const char* revision) const
		{
			return Set("SDR", revision);
		}

		/// 
		/// This command gets the current software revision.
		///
		/// @param revision		Current revision
		/// @param len			Length of buffer
		/// @return				true if operation completed succesfully
		/// 
		bool GetSoftwareRevision(char* revision, uint8_t len) const
		{
			return GetString("GDR", revision, len);
		}

		/// 
		/// This command sets the value of the serial number characteristics in the Device
		/// Information Service.
		///
		/// @param serial		Serial to set
		/// @return				true if operation completed succesfully
		/// 
		bool SetSerialNumber(const char* serial) const
		{
			return Set("SDS", serial);
		}

		/// 
		/// This command gets the current serial number.
		///
		/// @param serial		Current serial
		/// @param len			Length of buffer
		/// @return				true if operation completed succesfully
		/// 
		bool GetSerialNumber(char* serial, uint8_t len) const
		{
			return GetString("GDS", serial, len);
		}

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
		/// @return				true if operation completed succesfully				
		/// 
		bool SetTiming(uint16_t interval, uint16_t latency, uint16_t timeout) const
		{
			char buf[15] = { 0 };
			snprintf(buf, 14, "%04X,%04X,%04X", interval, latency, timeout);

			return Set("ST", buf);
		}

		/// 
		///	Returns the desirable connection parameters	set by the SetTiming command when a connection 
		/// is not established. Once a connection is established, the actual connection parameters 
		/// will be displayed in response to the command.
		///
		/// @param interval		Current interval
		/// @param latency		Current latency
		/// @param timeout		Current timeout
		/// @return				true if operation completed succesfully					
		/// 
		bool GetTiming(uint16_t* interval, uint16_t* latency, uint16_t* timeout) const
		{
			char buf[17] = { 0 };
			if (!GetString("GT", buf, sizeof(buf) - 1))
				return false;

			char* end;

#if ULONG_MAX >= 0xFFFFU
			unsigned long val = strtoul(buf, &end, 16);
			*interval = static_cast<uint16_t>(val);
			val = strtoul(end + 1, &end, 16);
			*latency = static_cast<uint16_t>(val);
			val = strtoul(end + 1, NULL, 16);
			*timeout = static_cast<uint16_t>(val);
#elif ULLONG_MAX >= 0xFFFFU
			unsigned long long val = strtoull(buf, &end, 16);
			*interval = static_cast<uint16_t>(val);
			val = strtoull(end + 1, &end, 16);
			*latency = static_cast<uint16_t>(val);
			val = strtoull(end + 1, NULL, 16);
			*timeout = static_cast<uint16_t>(val);
#else
#error "unable to convert hex16 string to the largest integer (unsigned long long) type using std library (strtoull)"
#endif

			return true;
		}

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
		/// @return				true if operation completed succesfully
		/// 
		bool SetServerServices(Services services) const
		{
			return SetHex32("SS", static_cast<uint32_t>(services));
		}

		/// 
		/// This command gets the current Server Services
		///
		/// @param services		Current Server Services
		/// @return				true if operation completed succesfully
		/// 
		bool GetServerServices(Services* services) const
		{
			return GetHex32("GS", reinterpret_cast<uint32_t*>(services));
		}


		/// 
		/// This command resets the configurations to the factory default at the next reboot. The
		/// parameters for this command can be either ‘1’ and ‘2’.\n
		///	When the input parameter is ‘1’, a majority of the settings will be restored to the
		///	factory default, but some settings, such as device name, device info, script and
		///	private services, stay the same. When the input parameter is ‘2’, all parameters are
		///	restored to factory default.
		///
		/// @param fullReset	if true, parameter is ‘2’
		/// @return				true if operation completed succesfully
		/// 
		bool ResetDefaults(bool fullReset = false) const
		{
			char buf[] = {(fullReset ? '2' : '1'), '\0'};
			return Set("SF", buf);
		}

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

		enum Services
		{
			SERVICE_DEVICE_INFORMATION = 0x80000000,
			SERVICE_BATTYER = 0x40000000,
			SERVICE_HEART_RATE = 0x20000000,
			SERVICE_HEALTH_THERMOMETER = 0x10000000,
			SERVICE_GLUCOSE = 0x08000000,
			SERVICE_BLOOD_PRESSURE = 0x04000000,
			SERVICE_RUNNING_SPEED_CADENCE = 0x02000000,
			SERVICE_CYCLING_SPEED_CADENCE = 0x01000000,
			SERVICE_CURRENT_TIME = 0x00800000,
			SERVICE_NEXT_DST_CHANGE = 0x00400000,
			SERVICE_REFERENCE_TIME_UPDATE = 0x00200000,
			SERVICE_LINK_LOSS = 0x00100000,
			SERVICE_IMMEDIATE_ALERT = 0x00080000,
			SERVICE_TX_POWER = 0x00040000,
			SERVICE_ALERT_NOTIFICATION = 0x00020000,
			SERVICE_PHONE_ALERT_STATUS = 0x00010000,
			SERVICE_SCAN_PARAMETERS = 0x00004000,
			SERVICE_USER_DEFINED = 0x00000001
		};

	private:
		bool Set(const char* command, const char* param) const;
		bool SetHex32(const char* command, uint32_t value) const;

		bool Get(const char* command, char* buf, uint8_t len, uint8_t* received) const;
		bool GetHex32(const char* command, uint32_t* value) const;
		bool GetString(const char* command, char* buf, uint8_t len, bool stripNewLine = true) const;
	};
}

#endif // !RN4020_H_
