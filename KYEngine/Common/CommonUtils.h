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

	template<typename Type, uint32 NUM>
	inline uint32 COUNT_OF(const Type (&arr)[NUM])
	{
		return sizeof(arr) / sizeof(arr[0]);
	}

	template<typename Type, uint32 NUM>
	inline void ZERO_MEMORY(Type (&arr)[NUM])
	{
		::memset(arr, 0, sizeof(arr));
	}

	template<typename Type>
	inline void ZERO_MEMORY(Type &t)
	{
		::memset(&t, 0, sizeof(t));
	}

}
#endif // _COMMONUTILS_H_