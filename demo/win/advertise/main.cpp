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


using namespace std;
using namespace Serial;
using namespace Serial::Windows;
using namespace Bluetooth;

const char* const COM_PORT = "\\\\.\\COM15";

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
	Services services = static_cast<Services>(SERVICE_DEVICE_INFORMATION | SERVICE_BATTERY);

	cout << "Name set: " << device.SetName("MyClient") << endl;
	cout << "Services set: " << device.SetServices(services) << endl;
	cout << "Advertising: " << device.StartAdvertise(true) << endl;

	cout << "Advertising!" << endl;

	Drivers::RN4020Driver driver = device.GetDriver();
	driver.SetPower(0);

	while (true)
	{
		for (uint8_t i = 0; i < 100; ++i)
		{
			driver.WriteServerIntegerByHandle(0x001B, i);
			Sleep(100);
		}
	}

	return 0;
}
