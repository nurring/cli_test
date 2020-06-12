#include "pch.h"
#include <utility>
#include <limits.h>
#include "ClamirFunctions.h"
#define CLAMIRLIBRARY_API


int connection_result = 1;
const char* lIPAddress = "192.168.1.77";

int ClamirFunctions::Add(int a, int b)
{
	return a + b;
}

int ClamirFunctions::Subtract(int a, int b)
{
	return a - b;
}

float ClamirFunctions::Multiply(float a, float b)
{
	return a * b;
}

float ClamirFunctions::Divide(float a, float b)
{
	return a / b;
}

int ClamirFunctions::ConnectDevice()
{
	connection_result = ConnectCLAMIR((char*)lIPAddress);
	return connection_result;
}
int ClamirFunctions::DisconnectDevice()
{
	connection_result = DisconnectCLAMIR();
	return connection_result;
}
