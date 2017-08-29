#pragma once

namespace KY
{


	namespace StringUtils
	{
		std::wstring utf8_to_utf16(const std::string &wstr);
		std::string utf16_to_utf8(const std::wstring &str);

		std::wstring gbk_to_utf16(const std::string &gbk);
		std::string utf16_to_gbk(const std::wstring &utf16);

		std::string utf8_to_gbk(const std::string &utf8);
		std::string gbk_to_utf8(const std::string &gbk);

		bool is_white_space(int32 c);

		template<class StrType>
		void trim(StrType &str)
		{
			size_t leftIdx = 0;
			size_t rightIdx = str.length() - 1;
			for (auto &c : str)
			{
				if (!is_white_space(c))
					break;

				++leftIdx;
			}

			for (auto it = std::rbegin(str); it != std::rend(str); ++it)
			{
				if (!is_white_space(*it))
					break;

				--rightIdx;
			}

			if (leftIdx == 0 && rightIdx == str.length() - 1)
				return;

			str = str.substr(leftIdx, rightIdx + 1);
		}

		template<typename CharType>
		bool is_empty_c_str(const CharType *ch)
		{
			return ch == nullptr || *ch == '\0';
		}

		template<class StrType>
		StrType get_parent_path(const StrType &ss)
		{
			auto pos = ss.rfind('\\');
			if (pos == StrType::npos)
			{
				pos = ss.rfind('/');
			}

			if (pos == StrType::npos)
				return StrType();

			return ss.substr(0, pos);
		}

		template<class StrType>
		StrType join_path(const StrType &pp, const StrType &part, bool backSlash = false)
		{
			if (pp.back() != '/' && pp.back() != '\\')
			{
				StrType ss;
				ss.append(1, typename StrType::traits_type::char_type(backSlash ? '\\' : '/'));

				return pp + ss + part;
			}

			return pp + part;
		}

		template<class StrType, typename T>
		StrType join_path(const StrType &pp, const T* part, bool backSlash = false)
		{
			return join_path(pp, StrType(part), backSlash);
		}

		template<class StrType, typename T>
		StrType join_path(const T* pp, const StrType& part, bool backSlash = false)
		{
			return join_path(StrType(pp), part, backSlash);
		}
	}
}