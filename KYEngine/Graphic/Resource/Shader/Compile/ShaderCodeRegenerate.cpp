#include "stdafx.h"
#include "ShaderCodeRegenerate.h"
#include "Common/FileSystem/FileSystem.h"
#include "DebugUtils/TraceUtils.h"

namespace KY
{

	void ShaderCodeRegenerate::AddDefineMacros(std::string &content)
	{
		for (auto &macro : mMacros)
		{
			std::string def = "#define " + macro.name;
			
			if (macro.defValue != -1)
			{
				def += std::to_string(macro.defValue);
			}

			def += "\n";

			content += def;
		}
	}

	int32 ShaderCodeRegenerate::RecurseFindIncludeFile(std::string &content)
	{
		std::vector<std::string>	codeLines;
		std::istringstream iss(content);		
		for (std::string line; (std::getline(iss, line)); codeLines.push_back(line));
	
		const std::string includePrefix = "#include";
		int32 includeCodeLines = 0;
		const std::string commonLine = "////////////////////////////////////////////////////////////////////\n";
		std::string newContent;
		for (auto &line : codeLines)
		{
			auto foundPos = line.find(includePrefix);
			if (foundPos != std::string::npos && foundPos == 0)
			{
				auto namePrefixPos = line.find('"', foundPos);
				if (namePrefixPos == std::string::npos)
				{
					DebugOutline("#include synatx is not correct, line is : ", line);
					return -1;
				}

				auto nameSuffixPos = line.find('"', namePrefixPos + 1);
				if (nameSuffixPos == std::string::npos)
				{
					DebugOutline("#include synatx is not correct, line is : ", line);
					return -1;
				}
					
				std::string includeFileName = line.substr(namePrefixPos + 1, nameSuffixPos - namePrefixPos - 1);
				auto shdrPath = FileSystem::Inst()->FindFromSubPath("shader");
				fs::path includeFullFilePath = shdrPath / includeFileName;
				if (!fs::exists(includeFullFilePath))
				{
					DebugOutline("try to get include file, failed, file name is : ", includeFileName);
					return -1;
				}
					

				auto itFoundInclude = msIncludes.find(includeFileName);
				if (itFoundInclude == msIncludes.end())
				{
					std::string includeContent;
					FileSystem::Inst()->ReadFileContent(includeFullFilePath, includeContent);
					includeContent = includeContent.c_str();	// cut off to 0
					RecurseFindIncludeFile(includeContent);
					
					itFoundInclude = msIncludes.insert(std::make_pair(includeFileName, includeContent)).first;
				}

				newContent += commonLine + "//" + includeFileName + "\n";
				newContent += itFoundInclude->second;
				newContent += commonLine;

				++includeCodeLines;
			}
			else
			{
				newContent += line + "\n";
			}
		}

		content = newContent;

		return includeCodeLines;
	}

	ShaderCodeRegenerate::IncludeFileMap ShaderCodeRegenerate::msIncludes;

	std::string ShaderCodeRegenerate::Regenerate(const fs::path &filePath)
	{
		std::string content;
		if (FileSystem::ReadFileResult::RFR_Success != FileSystem::Inst()->ReadFileContent(filePath, content))
			return std::string();

		std::string macroLines;
		AddDefineMacros(macroLines);

		RecurseFindIncludeFile(content);

		return content;
	}
}