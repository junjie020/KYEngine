#ifndef _COMMONUTILS_H_
#define _COMMONUTILS_H_

namespace KY
{
	template<typename Type>
	inline void SafeDelete(Type* &p)
	{
		if (p)
		{
			delete p;
			p = nullptr;
		}
	}

	template<typename Type>
	inline void SafeRelease(Type* &p)
	{
		if (p)
		{ 
			p->Release();
			p = nullptr;
		}
	}

	template<typename BitType, typename Value>
	inline bool QueryBit(BitType bit, const Value &v)
	{
		return bit == (bit & v);
	}
}
#endif // _COMMONUTILS_H_