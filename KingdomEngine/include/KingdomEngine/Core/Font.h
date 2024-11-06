#ifndef FONT_H
#define FONT_H

#include <string>

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
}

#endif
