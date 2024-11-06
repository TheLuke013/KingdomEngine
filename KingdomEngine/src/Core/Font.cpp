#include "KingdomEngine/Core/Font.h"

namespace KE
{
	Font::Font(const std::string& name, const std::string& path, float size)
	{
		properties.name = name;
		properties.filePath = path;
		properties.size = size;
	}

	void Font::Load()
	{
	}

	void Font::SetSize(float size)
	{
		properties.size = size;
	}

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