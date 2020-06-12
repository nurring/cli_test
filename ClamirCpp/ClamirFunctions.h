#pragma once

#include "CLAMIR_dll.h"
#include "CImg.h"

#ifdef CLAMIRLIBRARY_EXPORTS
#define CLAMIRLIBRARY_API __declspec(dllexport)
#else
#define CLAMIRLIBRARY_API __declspec(dllimport)
#endif


class CLAMIRLIBRARY_API ClamirFunctions
{
public:
	static int Add(int a, int b);
	static int Subtract(int a, int b);
	static float Multiply(float a, float b);
	static float Divide(float a, float b);

	static int ConnectDevice();
	static int DisconnectDevice();
};
