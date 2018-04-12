#ifndef SERIALPORT_H
#define SERIALPORT_H

#define ARDUINO_WAIT_TIME 2000
#define MAX_DATA_LENGTH 255

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

class SerialPort
{
private:
	HANDLE handler;
	bool connected;
	COMSTAT status;
	DWORD errors;
public:
	SerialPort(const char *portName); //all of this was just char *
	~SerialPort();

	int readSerialPort(char *buffer, unsigned int buf_size);
	bool writeSerialPort(const char *buffer, unsigned int buf_size);
	bool isConnected();
};

#endif // SERIALPORT_H

