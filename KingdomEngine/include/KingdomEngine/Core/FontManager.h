#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include <string>
#include <vector>
#include <unordered_map>

#include "KingdomEngine/Core/Font.h"

namespace KE
{
	class FontManager
	{
	public:
		static FontManager& Get();

		void AddFont(Font* font);
		void FindFonts(const std::string& directoryPath, const std::string& fontType);

		std::vector<Font*> GetFonts() { return fonts; }

	private:
		FontManager() {}

		std::vector<Font*> fonts;
		std::unordered_map<std::string, Font*> fontsMap;
	};
}

#define GET_FONTS() KE::FontManager::Get().GetFonts();
#define ADD_FONT(font) KE::FontManager::Get().AddFont(font);

#endif
