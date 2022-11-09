#include "Utilities.h"
#include <algorithm> 
#include <cctype>
#include <string>

namespace neu
{
	std::string ToLower(const std::string& str)
	{
		std::string lower = str;
		std::transform(str.begin(), str.end(), lower.begin(), [](unsigned char c) { return std::tolower(c); });

		return lower;
	}

	std::string ToUpper(const std::string& str)
	{
		std::string upper = str;
		std::transform(str.begin(), str.end(), upper.begin(), [](unsigned char c) { return std::toupper(c); });

		return upper;
	}

	bool CompareIgnoreCase(const std::string& str1,const std::string& str2)
	{
		// if string lengths don't match return false 
		if (str1.length() != str2.length()) return false;
		const std::string lower1 = ToLower(str1);
		const std::string lower2 = ToLower(str2);
		for (size_t i = 0; i < str1.length(); i++)
		{
			if (lower1[i] != lower2[i])
			{
				return false;
			}
		}
		return true;

	}
	
}