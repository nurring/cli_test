#pragma once
#include "ClamirFunctions.h"

using namespace System;

namespace ClamirCLR {
	public ref class ClamirCLR
	{
	protected:
		ClamirFunctions* clamirfunc;

	public:
		ClamirCLR();
		virtual ~ClamirCLR();

		int Add(int a, int b);
		int Subtract(int a, int b);
		float Multiply(float a, float b);
		float Divide(float a, float b);

		int ConnectDevice();
		int DisconnectDevice();
	};
}
