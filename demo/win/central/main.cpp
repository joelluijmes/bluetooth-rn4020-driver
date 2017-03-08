// user libraries
#include "LastError.h"
#include "WindowsSerialPort.h"

#include "UART/ParityBit.h"
#include "UART/BaudRate.h"
#include "UART/DataBit.h"
#include "UART/StopBit.h"

#include "BluetoothLEDevice.h"
#include "Drivers/RN4020Device.h"
#include "Drivers/RN4020Driver.h"

// std libraries
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Serial/DelimiterSerial.h"

using namespace std;
using namespace Serial;
using namespace Serial::Windows;
using namespace Bluetooth;

const char* const COM_PORT = "\\\\.\\COM16";

int main()
{
	WindowsSerialPort serialPort(COM_PORT, BAUDRATE_115200, DATABIT_8, PARITYBIT_NONE, STOPBIT_1);


	if (!serialPort.Open())
	{
		cout << "Failed to open " << COM_PORT << " " << GetLastErrorMessage() << endl;
		return 1;
	}
	
	cout << boolalpha << hex;
	cout << "Opened " << COM_PORT << endl;

	RN4020Device device(serialPort);
	Drivers::RN4020Driver driver = device.GetDriver();

	/*Services services = static_cast<Services>(SERVICE_DEVICE_INFORMATION);
	cout << "Name set: " << device.SetName("MyServer") << endl;
	cout << "Services set: " << device.SetServices(services) << endl;
	cout << "Scanning.." << endl;*/

	BluetoothLEPeripheral peripherals[16];
	uint8_t found = 0;
	cout << "Scanned: " << device.ScanPeripherals(peripherals, 16, &found) << endl;
	cout << " Found " << static_cast<int>(found) << " devices" << endl;
	if (found < 1)
		return 1;

	for (uint8_t i = 0; i < found; ++i)
	{
		char mac[32];
		peripherals[i].GetMACAddress().ToCharArray(mac, sizeof(mac));
		printf("%s (%s)\n", peripherals[i].GetName(), mac);
	}

	return 1;

	BluetoothLEPeripheral* peripheral = NULL;
	for (uint8_t i = 0; i < found; ++i)
	{
		if (strcmp(peripherals[i].GetName(), "MyClient") != 0)
			continue;

		peripheral = &peripherals[i];
		break;
	}

	if (peripheral == NULL)
		return 1;

	char buf[18];
	peripheral->GetMACAddress().ToCharArray(buf, sizeof(buf));
	cout << buf << endl;

	printf(" - %s\n", peripheral->GetName());

	if (!device.Connect(*peripheral))
		return 1;

	cout << "Connected: " << endl;	

	LongClientCharacteristic characteristics[20];
	uint8_t len;
	if (!driver.ListClientCharacteristics(Bluetooth::UUID(0x180F), characteristics, 20, &len))
		return 1;

	while (true)
	{
		for (uint8_t i = 0; i < len; ++i)
		{
			if (characteristics[i].GetCharacteristicProperty() == CHARACTERISTIC_PROPERTY_READ)
			{
				uint8_t val;
				if (driver.ReadClientIntegerByHandle(characteristics[i].GetHandle(), &val))
					printf(" %04X, %d\n", characteristics[i].GetHandle(), val);
			}
		}

		Sleep(100);
	}
	
	return 0;
}
