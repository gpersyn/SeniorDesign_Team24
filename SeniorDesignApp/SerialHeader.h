#pragma once
//Serial Port Variables
#include<iostream>
using namespace std;
#include<string>
#include<stdlib.h>
#include"SerialPort.h"

const int DataWidth = 15; //MAX_DATA_LENGTH
char output[DataWidth];
char incomingData[DataWidth];
char *port = "\\\\.\\COM4";