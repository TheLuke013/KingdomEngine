#ifndef FONT_H
#define FONT_H

#include <string>
#include <vector>
#include <unordered_map>

namespace KE
{
	struct FontProperties
	{
		std::string name;
		std::string filePath;
		float size;
	};

	class Font
	{
	public:
		Font(const std::string& name, const std::string& path, float size);

		void Load();
		void SetSize(float size);

		FontProperties properties;
	};

	class FontManager
	{
	public:
		static FontManager& Get();

		void AddFont(Font* font);
		void FindFonts();

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
