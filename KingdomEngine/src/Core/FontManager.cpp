#include "KingdomEngine/Core/FontManager.h"

namespace KE
{
	FontManager& FontManager::Get()
	{
		static FontManager* instance = new FontManager();
		return *instance;
	}

	void FontManager::AddFont(Font* font)
	{
		fonts.push_back(font);
		fontsMap[font->properties.name] = font;
	}

	void FontManager::FindFonts()
	{
	}
}