#include "stdafx.h"

namespace KY
{


	namespace StringUtils
	{
		using UTF8_UTF16_CVT = std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>;// utf16conv;

		std::wstring utf8_to_utf16(const std::string& str)
		{
			using convert_typeX = std::codecvt_utf8<wchar_t>;
			std::wstring_convert<convert_typeX, wchar_t> converterX;

			return converterX.from_bytes(str);
		}

		std::string utf16_to_utf8(const std::wstring& wstr)
		{
			using convert_typeX = std::codecvt_utf8<wchar_t>;
			std::wstring_convert<convert_typeX, wchar_t> converterX;

			return converterX.to_bytes(wstr);
		}

		static const char* GBK_LOCALE_NAME = ".936";
		using UTF16_GBK_NAME = std::codecvt_byname<wchar_t, char, mbstate_t>;
		using GBK_UTF16_CVT = std::wstring_convert<UTF16_GBK_NAME>;

		std::wstring gbk_to_utf16(const std::string &gbk)
		{
			GBK_UTF16_CVT gbkCVT(new UTF16_GBK_NAME(GBK_LOCALE_NAME));

			return gbkCVT.from_bytes(gbk);
		}

		std::string utf16_to_gbk(const std::wstring &utf16)
		{
			GBK_UTF16_CVT gbkCVT(new UTF16_GBK_NAME(GBK_LOCALE_NAME));

			return gbkCVT.to_bytes(utf16);
		}

		std::string utf8_to_gbk(const std::string &utf8)
		{
			return utf16_to_gbk(utf8_to_utf16(utf8));
		}

		std::string gbk_to_utf8(const std::string &gbk)
		{
			return utf16_to_utf8(gbk_to_utf16(gbk));
		}


		bool is_white_space(int32 c)
		{
			const char whitespace[] = { ' ', '\t', '\r', '\n' };

			for (auto &ws : whitespace)
			{
				if (ws == c)
					return true;
			}

			return false;
		}
	}
}