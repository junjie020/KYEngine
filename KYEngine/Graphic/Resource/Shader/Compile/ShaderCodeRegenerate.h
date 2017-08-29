#pragma once

namespace KY
{
	struct MacroDef
	{
		MacroDef(const std::string &n, int32 v = -1) : name(n), defValue(v) {}
		std::string name;
		int32 defValue;
	};

	using MacroArray = std::vector<MacroDef>;

	class ShaderCodeRegenerate
	{
	public:
		void SetMacros(const MacroArray &macros)
		{
			mMacros = macros;
		}

		void SetMacros(MacroArray &&macro)
		{
			mMacros = std::forward<MacroArray&&>(macro);
		}
		std::string Regenerate(const fs::path &filePath);

	private:
		void AddDefineMacros(std::string &content);

		int32 RecurseFindIncludeFile(std::string &content);

	private:

		MacroArray mMacros;
	private:
		using IncludeFileMap = std::map<std::string, std::string>;
		static IncludeFileMap msIncludes;
	};
}

