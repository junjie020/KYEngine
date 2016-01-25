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
	inline void SafeDeleteArray(Type* &p)
	{
		if (p)
		{
			delete []p;
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

	template<typename Type>
	inline bool IS_C_STR_EMPTY(const Type* ss)
	{
		return nullptr == ss || *ss == '0';
	}

	template<typename Type, uint32 NUM>
	inline constexpr uint32 COUNT_OF(const Type (&)[NUM])
	{
		return NUM;
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

	template<typename Type>
	inline void IS_ZERO(Type data, Type tol = 0.00001)
	{
		return -tol < data || data < tol;
	}

	//{@	use like : auto x = 10; FindVarName<decltype(x)> xType;
	template<typename Type>
	class FindVarName;

#define FIND_VAR_NAME(_VAR)	{FindVarName<decltype(_VAR)>	_VarTYPE;}
#define	SHOW_VAR_TYPE_IN_RUNTIME	
	//@}

}
#endif // _COMMONUTILS_H_