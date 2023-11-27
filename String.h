#pragma once

class String
{
public:
	static void SplitString(std::vector < std::wstring > * result, std::wstring origin, std::wstring tok);
	static void SplitFilePath(std::wstring fullPath, std::wstring* filePath = NULL, std::wstring* fileName = NULL);

	static bool StartsWith(std::wstring str, std::wstring comp);

	static bool Contain(std::wstring str, std::wstring comp);
	static void Replace(std::wstring* str, std::wstring comp, std::wstring rep);

	static std::wstring StringToWString(std::string value);
	static std::string WStringToString(std::wstring value);
};