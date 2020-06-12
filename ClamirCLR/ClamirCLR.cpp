#include "pch.h"

#include "ClamirCLR.h"

namespace ClamirCLR {
	ClamirCLR::ClamirCLR() : clamirfunc(new ClamirFunctions)
	{

	};

	ClamirCLR::~ClamirCLR() 
	{
		if (clamirfunc)
		{
			delete clamirfunc;
			clamirfunc = 0;
		}

	};
	//연습용 - 계산기
	int ClamirCLR::Add(int a, int b)
	{
		return (clamirfunc->Add(a, b));
	}
	int ClamirCLR::Subtract(int a, int b)
	{
		return (clamirfunc->Subtract(a, b));
	}
	float ClamirCLR::Multiply(float a, float b)
	{
		return (clamirfunc->Multiply(a, b));
	}
	float ClamirCLR::Divide(float a, float b)
	{
		return (clamirfunc->Divide(a, b));
	}
	//ClamIR
	int ClamirCLR::ConnectDevice()
	{
		int result = clamirfunc->ConnectDevice();
		return result;
	}
	int ClamirCLR::DisconnectDevice()
	{
		int result = clamirfunc->DisconnectDevice();
		return result;
	}

}
