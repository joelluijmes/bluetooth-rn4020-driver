// user libraries
#include "Windows/WindowsSerialPort.h"
#include "Windows/LastError.h"

#include "Serial/ParityBit.h"
#include "Serial/BaudRate.h"
#include "Serial/DataBit.h"
#include "Serial/StopBit.h"

#include "Bluetooth/RN4020.h"

// std libraries
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


using namespace std;
using namespace Serial;
using namespace Bluetooth;

bool ReadWrite(const WindowsSerialPort& port, std::string message)
{
	if (port.Send(message.c_str(), message.length()) == -1)
	{
		cout << "Error occurred: " << GetLastErrorMessage() << endl;
		return false;
	}

	Sleep(100);

	char buf[64];
	int read = port.Receive(buf, sizeof(buf));
	if (read == -1)
	{
		cout << "Error occurred: " << GetLastErrorMessage() << endl;
		return false;
	}

	buf[read] = 0;
	cout << buf << endl;

	return true;
}

int main()
{
	WindowsSerialPort serialPort("\\\\.\\COM15", BAUDRATE_115200, DATABIT_8, PARITYBIT_NONE, STOPBIT_1);
	if (!serialPort.Open())
	{
		cout << "Failed to open COM15: " << GetLastErrorMessage() << endl;

		return 1;
	}

	cout << "Opened COM15" << endl;

	RN4020 bluetooth(serialPort);
	
	char buf[32];
	if (bluetooth.GetDisplayName(buf, 32))
		cout << "Name: " << buf << endl;
	else
		cout << "Failed to get name from device" << endl;

	/*string message;
	do
	{
		cout << "Enter command: ";
		
		getline(cin, message);
		message += "\r\n";
	} while (ReadWrite(serialPort, message));*/

	return 0;
}