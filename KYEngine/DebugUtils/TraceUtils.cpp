#include "stdafx.h"
#include "TraceUtils.h"

#include <iostream>
namespace KY
{
	

	void DebugOutline(const std::string &info)
	{
#ifdef WIN32
		OutputDebugStringA(info.c_str());
#else //!_WIN32
		std::cout << info << std::endl;
#endif // WIN32		
	}

}