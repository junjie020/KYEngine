#ifndef _TRACEUTILS_H_
#define _TRACEUTILS_H_

namespace KY
{
	//void DebugOutline(const std::string &info);

	template<typename T0, typename ...Tn>
	void DebugOutline(const T0 &t0, Tn ...tn);

	template<typename T0>
	void DebugOutline(const T0 &t0)
	{
#ifdef WIN32
		std::ostringstream oss;
		oss << t0 << std::endl;
		OutputDebugStringA(oss.str().c_str());
#else //!_WIN32
		std::cout << t0 << std::endl;
#endif // WIN32		
	}

	template<typename T0, typename ...Tn>
	void DebugOutline(const T0 & t0, Tn ...tn)
	{
#ifdef _WIN32
		std::ostringstream oss;
		oss << t0 << ", ";
		OutputDebugStringA(oss.str().c_str());
#else //!_WIN32
		std::cout << t0 << ",";
#endif // _WIN32

		DebugOutline(tn...);
	}

}
#endif // _TRACEUTILS_H_