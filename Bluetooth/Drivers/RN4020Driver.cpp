﻿#include "RN4020Driver.h"

// std libraries
#include <string.h>
#include "../../Util.h"


// RN4020Driver Constants
#define MAX_SERIALIZED_NAME 15
#define MAX_NAME_LEN 20

namespace
{
	void stripNewLines(char* str)
	{
		char* p = str;
		while (*str)
		{
			if (*p != '\r' && *p != '\n')
				*p++ = *str++;
			else
				++str;
		}

		*p = '\0';
	}
}

namespace Bluetooth
{
	namespace Drivers
	{
		RN4020Driver::RN4020Driver(const Serial::ISerial& serial): m_Serial(serial)
		{
		}

		bool RN4020Driver::SetBaudRate(BaudRate baud) const
		{
			char buf[] = {static_cast<char>(baud + '0'), '\0'};
			return Set("SB", buf);
		}

		bool RN4020Driver::GetBaudRate(BaudRate* baud) const
		{
			// 1 for result; 2 for \r\n
			char buf[3];
			if (!Get("GB", buf, sizeof(buf), NULL))
				return false;

			*baud = static_cast<BaudRate>(buf[0] - '0');
			return true;
		}

		bool RN4020Driver::SetFeatures(Features features) const
		{
			return SetHex32("SR", static_cast<uint32_t>(features));
		}

		bool RN4020Driver::GetFeatures(Features* features) const
		{
			return GetHex32("GR", reinterpret_cast<uint32_t*>(features));
		}

		bool RN4020Driver::SetFirmwareVersion(const char* version) const
		{
			return Set("SDF", version);
		}

		bool RN4020Driver::GetFirmwareVersion(char* version, uint8_t len) const
		{
			return GetString("GDF", version, len);
		}

		bool RN4020Driver::SetHardwareVersion(const char* version) const
		{
			return Set("SDH", version);
		}

		bool RN4020Driver::GetHardwareVersion(char* version, uint8_t len) const
		{
			return GetString("SDH", version, len);
		}

		bool RN4020Driver::SetModel(const char* model) const
		{
			return Set("SDM", model);
		}

		bool RN4020Driver::GetModel(char* version, uint8_t len) const
		{
			return GetString("GDM", version, len);
		}

		bool RN4020Driver::SetManufacturer(const char* manufacturer) const
		{
			return Set("SDN", manufacturer);
		}

		bool RN4020Driver::GetManufacturer(char* manufacturer, uint8_t len) const
		{
			return GetString("GDN", manufacturer, len);
		}

		bool RN4020Driver::SetName(const char* name) const
		{
			return Set("SN", name);
		}

		bool RN4020Driver::GetName(char* name, uint8_t len) const
		{
			return GetString("GN", name, len);
		}

		bool RN4020Driver::SetSerializedName(const char* name) const
		{
			return Set("S-", name);
		}

		bool RN4020Driver::GetSerializedName(char* name, uint8_t len) const
		{
			return GetString("G-", name, len);
		}

		bool RN4020Driver::SetSoftwareRevision(const char* revision) const
		{
			return Set("SDR", revision);
		}

		bool RN4020Driver::GetSoftwareRevision(char* revision, uint8_t len) const
		{
			return GetString("GDR", revision, len);
		}

		bool RN4020Driver::SetSerialNumber(const char* serial) const
		{
			return Set("SDS", serial);
		}

		bool RN4020Driver::GetSerialNumber(char* serial, uint8_t len) const
		{
			return GetString("GDS", serial, len);
		}

		bool RN4020Driver::SetTiming(uint16_t interval, uint16_t latency, uint16_t timeout) const
		{
			char buf[16] = {0};
			snprintf(buf, 15, "%04X,%04X,%04X", interval, latency, timeout);

			return Set("ST", buf);
		}

		bool RN4020Driver::GetTiming(uint16_t* interval, uint16_t* latency, uint16_t* timeout) const
		{
			char buf[17] = {0};
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

		bool RN4020Driver::SetServerServices(Services services) const
		{
			return SetHex32("SS", services);
		}

		bool RN4020Driver::GetServerServices(Services* services) const
		{
			return GetHex32("GS", reinterpret_cast<uint32_t*>(services));
		}

		bool RN4020Driver::ResetDefaults(bool fullReset) const
		{
			char buf[] = {(fullReset ? '2' : '1'), '\0'};
			return Set("SF", buf);
		}

		bool RN4020Driver::Advertise(uint16_t interval, uint16_t window) const
		{
			if (interval == 0 && window == 0)
				return Set("A", NULL);

			char buf[11] = {0};
			snprintf(buf, 10, "%04X,%04X", interval, window);

			return Set("A", buf);
		}

		bool RN4020Driver::Bond(bool enable) const
		{
			char buf[] = {(enable ? '1' : '0'), '\0'};
			return Set("B", buf);
		}

		bool RN4020Driver::Establish(bool usePublicAddress, uint8_t macAddress[6]) const
		{
			char buf[9] = {(usePublicAddress ? '0' : '1'), ','};
			memcpy(buf + 2, macAddress, 6);

			return Set("E", buf);
		}

		bool RN4020Driver::Find(uint16_t interval, uint16_t window) const
		{
			if (interval == 0 && window == 0)
				return Set("F", NULL);

			char buf[11] = {0};
			snprintf(buf, 10, "%04X,%04X", interval, window);

			return Set("F", buf);
		}

		bool RN4020Driver::Observer(bool enable) const
		{
			char buf[] = {(enable ? '1' : '0'), '\0'};
			return Set("J", buf);
		}

		bool RN4020Driver::Kill() const
		{
			return Set("K", NULL);
		}

		int8_t RN4020Driver::SignalStrength() const
		{
			char buf[16] = {0}; // No Connection + \r\n

			if (!GetString("M", buf, sizeof(buf)))
				return 0;

			if (strcmp(buf, "No Connection") == 0)
				return 0;

			long rssi = strtol(buf, NULL, 16);
			return static_cast<int8_t>(rssi);
		}

		bool RN4020Driver::Broadcast(uint8_t data[25], uint8_t len) const
		{
			char buf[51] = {0};
			for (uint8_t i = 0; i < len; ++i)
				snprintf(buf + 2, 3, "%02X", data[i]);

			return Set("N", buf);
		}

		void RN4020Driver::Dormant() const
		{
			Set("O", NULL);
		}

		bool RN4020Driver::Dump(char* buf, uint8_t len) const
		{
			if (!GetString("D", buf, len, false))
				return false;

			m_Serial.Flush();
			return true;
		}

		bool RN4020Driver::Reboot() const
		{
			char buf[9] = {0}; // Reboot + \r\n

			// use Get to flush the incomming Reboot text
			if (!Get("R,1", buf, sizeof(buf), NULL))
				return false;

			// when it is booted it puts out CMD
			return WaitAnything();
		}

		bool RN4020Driver::UpdateTimings(uint16_t interval, uint16_t latency, uint16_t timeout) const
		{
			char buf[16] = {0};
			snprintf(buf, 15, "%04X,%04X,%04X", interval, latency, timeout);

			return Set("T", buf);
		}

		bool RN4020Driver::Unbond() const
		{
			return Set("U", NULL);
		}

		bool RN4020Driver::FirmwareVersion(char* buf, uint8_t len) const
		{
			return GetString("V", buf, len);
		}

		bool RN4020Driver::StopScan() const
		{
			return Set("X", NULL);
		}

		bool RN4020Driver::StopAdvertisement() const
		{
			return Set("Y", NULL);
		}

		bool RN4020Driver::StopConnecting() const
		{
			return Set("Z", NULL);
		}

		bool RN4020Driver::ReadScan(DiscoveredDevice* devices, uint8_t len) const
		{
			char buf[64];
			bool foundADevice = false;

			int32_t received;
			uint8_t index = 0;
			while (index < len && WaitAnything(buf, sizeof(buf), &received, 10))
			{
				foundADevice = true;
				devices[index] = DiscoveredDevice(buf);
			}

			return foundADevice;
		}

		RN4020Driver::DiscoveredDevice::DiscoveredDevice(const char* line)
		{
			const char* ptr = line;
			Util::Parse6ByteMACAddressFromString(ptr, m_MACAddress);
			ptr += 13; // skip the MACAddress + ','

			m_RandomAddress = *ptr == 0;
			ptr += 2; // skip the randomAddress + ','

			memset(m_Name, 0, sizeof(m_Name));

			size_t nameLength = strchr(ptr, ',') - ptr;
			if (nameLength > 20) // make sure that we can't overflow
				nameLength = 20;

			memcpy(m_Name, ptr, nameLength);
			ptr += nameLength + 1; // skip the name + ','

			// todo primary service
			ptr += 1;

			long rssi = strtol(ptr, NULL, 16);
			m_RSSI = static_cast<int8_t>(rssi);
		}

		bool RN4020Driver::Set(const char* command, const char* param) const
		{
			if (m_Serial.Send(command, strlen(command)) == -1)
				return false;

			if (param)
			{
				if (m_Serial.Send(",", 1) == -1)
					return false;
				if (m_Serial.Send(param, strlen(param)) == -1)
					return false;
			}

			if (m_Serial.Send("\r\n", 2) == -1)
				return false;

			// RN4020Driver returns AOK of ERR for set commands
			// (don't forget the trailling \r\n)
			char buf[5] = {0};
			int32_t received = m_Serial.Receive(buf, sizeof(buf));
			if (received == -1)
				return false;

			return strncmp(buf, "AOK", 3) == 0;
		}

		bool RN4020Driver::SetHex32(const char* command, uint32_t value) const
		{
			char buf[10] = {0};
			snprintf(buf, 9, "%08X", value);

			return Set(command, buf);
		}

		bool RN4020Driver::Get(const char* command, char* buf, uint8_t len, uint8_t* received) const
		{
			if (m_Serial.Send(command, strlen(command)) == -1)
				return false;
			if (m_Serial.Send("\r\n", 2) == -1)
				return false;

			int32_t tmp = m_Serial.Receive(buf, len);
			if (received)
				*received = tmp;

			return tmp != -1;
		}

		bool RN4020Driver::GetHex32(const char* command, uint32_t* value) const
		{
			char buf[11] = {0};
			if (!GetString("GS", buf, sizeof(buf) - 1))
				return false;

#if ULONG_MAX >= 0xFFFFFFFFU
			unsigned long val = strtoul(buf, NULL, 16);
#elif ULLONG_MAX >= 0xFFFFFFFFU
			unsigned long long val = strtoull(buf, NULL, 16);
#else
#error "unable to convert hex32 string to the largest integer (unsigned long long) type using std library (strtoull)"
#endif

			*value = static_cast<uint32_t>(val);
			return true;
		}

		bool RN4020Driver::GetString(const char* command, char* buf, uint8_t len, bool stripNewLine) const
		{
			uint8_t received;
			if (!Get(command, buf, len, &received))
				return false;

			buf[received] = '\0';
			if (stripNewLine)
				stripNewLines(buf);

			return true;
		}

		bool RN4020Driver::WaitAnything(uint8_t timeout) const
		{
			char buf[64];
			return WaitAnything(buf, sizeof(buf), NULL, timeout);
		}

		bool RN4020Driver::WaitAnything(char* buf, uint32_t len, int32_t* received, uint8_t timeout) const
		{
			for (uint8_t i = 0; i < timeout; ++i)
			{
				int32_t tmp = m_Serial.Receive(buf, len);
				if (received)
					*received = tmp;

				if (tmp > 0)
					return true;
			}

			return false;
		}
	}
}
