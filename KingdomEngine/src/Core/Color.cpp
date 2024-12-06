#include "KingdomEngine/Core/Color.h"
#include "KingdomEngine/Core/Log.h"

#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <cctype>

namespace KE
{
    Color::Color()
        : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}

    Color::Color(const Color& color, float a)
        : r(color.r), g(color.g), b(color.b), a(a) {}

    Color::Color(const Color& color)
        : r(color.r), g(color.g), b(color.b), a(color.a) {}

    Color::Color(float r, float g, float b)
        : r(r), g(g), b(b), a(1.0f) {}

    Color::Color(float r, float g, float b, float a)
        : r(r), g(g), b(b), a(a) {}

    std::string Color::GetHex() const
    {
        int red = static_cast<int>(r * 255.0f);
        int green = static_cast<int>(g * 255.0f);
        int blue = static_cast<int>(b * 255.0f);

        std::ostringstream oss;
        oss << "#"
            << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << red
            << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << green
            << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << blue;

        return oss.str();
    }

    void Color::FromHex(const std::string& hex)
    {
        std::string cleanHex = hex;
        cleanHex.erase(std::remove_if(cleanHex.begin(), cleanHex.end(), ::isspace), cleanHex.end());

        if (cleanHex.empty() || cleanHex[0] != '#' || (cleanHex.length() != 7 && cleanHex.length() != 9))
        {
            LOG_ERROR("Invalid hex color format. Expected #RRGGBB or #RRGGBBAA.");
        }

        try
        {
            int red = std::stoi(hex.substr(1, 2), nullptr, 16);
            int green = std::stoi(hex.substr(3, 2), nullptr, 16);
            int blue = std::stoi(hex.substr(5, 2), nullptr, 16);

            int alpha = 255;
            if (hex.length() == 9)
            {
                alpha = std::stoi(hex.substr(7, 2), nullptr, 16);
            }

            r = red / 255.0f;
            g = green / 255.0f;
            b = blue / 255.0f;
            a = alpha / 255.0f;
        }
        catch (const std::exception& e)
        {
            LOG_ERROR("Invalid hex color format. Unable to parse components: " + std::string(e.what()));
        }
    }

    const Color Color::AQUA = Color(0.0f, 1.0f, 1.0f, 1.0f);
    const Color Color::AQUAMARINE = Color(0.498039f, 1.0f, 0.831373f, 1.0f);
    const Color Color::AZURE = Color(0.941176f, 1.0f, 1.0f, 1.0f);
    const Color Color::BEIGE = Color(0.960784f, 0.960784f, 0.862745f, 1.0f);
    const Color Color::BISQUE = Color(1.0f, 0.894118f, 0.768627f, 1.0f);
    const Color Color::BLACK = Color(0.0f, 0.0f, 0.0f, 1.0f);
    const Color Color::BLANCHED_ALMOND = Color(1.0f, 0.921569f, 0.803922f, 1.0f);
    const Color Color::BLUE = Color(0.0f, 0.0f, 1.0f, 1.0f);
    const Color Color::BLUE_VIOLET = Color(0.541176f, 0.168627f, 0.886275f, 1.0f);
    const Color Color::BROWN = Color(0.647059f, 0.164706f, 0.164706f, 1.0f);
    const Color Color::BURLYWOOD = Color(0.870588f, 0.721569f, 0.529412f, 1.0f);
    const Color Color::CADET_BLUE = Color(0.372549f, 0.619608f, 0.627451f, 1.0f);
    const Color Color::CHARTREUSE = Color(0.498039f, 1.0f, 0.0f, 1.0f);
    const Color Color::CHOCOLATE = Color(0.823529f, 0.411765f, 0.117647f, 1.0f);
    const Color Color::CORAL = Color(1.0f, 0.498039f, 0.313726f, 1.0f);
    const Color Color::CORNFLOWER_BLUE = Color(0.392157f, 0.584314f, 0.929412f, 1.0f);
    const Color Color::CORNSILK = Color(1.0f, 0.972549f, 0.862745f, 1.0f);
    const Color Color::CRIMSON = Color(0.862745f, 0.0784314f, 0.235294f, 1.0f);
    const Color Color::CYAN = Color(0.0f, 1.0f, 1.0f, 1.0f);
    const Color Color::DARK_BLUE = Color(0.0f, 0.0f, 0.545098f, 1.0f);
    const Color Color::DARK_CYAN = Color(0.0f, 0.545098f, 0.545098f, 1.0f);
    const Color Color::DARK_GOLDENROD = Color(0.721569f, 0.52549f, 0.0431373f, 1.0f);
    const Color Color::DARK_GRAY = Color(0.662745f, 0.662745f, 0.662745f, 1.0f);
    const Color Color::DARK_GREEN = Color(0.0f, 0.392157f, 0.0f, 1.0f);
    const Color Color::DARK_KHAKI = Color(0.741176f, 0.717647f, 0.419608f, 1.0f);
    const Color Color::DARK_MAGENTA = Color(0.545098f, 0.0f, 0.545098f, 1.0f);
    const Color Color::DARK_OLIVE_GREEN = Color(0.333333f, 0.419608f, 0.184314f, 1.0f);
    const Color Color::DARK_ORANGE = Color(1.0f, 0.54902f, 0.0f, 1.0f);
    const Color Color::DARK_ORCHID = Color(0.6f, 0.196078f, 0.8f, 1.0f);
    const Color Color::DARK_RED = Color(0.545098f, 0.0f, 0.0f, 1.0f);
    const Color Color::DARK_SALMON = Color(0.913725f, 0.588235f, 0.478431f, 1.0f);
    const Color Color::DARK_SEA_GREEN = Color(0.560784f, 0.737255f, 0.560784f, 1.0f);
    const Color Color::DARK_SLATE_BLUE = Color(0.282353f, 0.239216f, 0.545098f, 1.0f);
    const Color Color::DARK_SLATE_GRAY = Color(0.184314f, 0.309804f, 0.309804f, 1.0f);
    const Color Color::DARK_TURQUOISE = Color(0.0f, 0.807843f, 0.819608f, 1.0f);
    const Color Color::DARK_VIOLET = Color(0.580392f, 0.0f, 0.827451f, 1.0f);
    const Color Color::DEEP_PINK = Color(1.0f, 0.0784314f, 0.576471f, 1.0f);
    const Color Color::DEEP_SKY_BLUE = Color(0.0f, 0.74902f, 1.0f, 1.0f);
    const Color Color::DIM_GRAY = Color(0.411765f, 0.411765f, 0.411765f, 1.0f);
    const Color Color::DODGER_BLUE = Color(0.117647f, 0.564706f, 1.0f, 1.0f);
    const Color Color::FIREBRICK = Color(0.698039f, 0.133333f, 0.133333f, 1.0f);
    const Color Color::FLORAL_WHITE = Color(1.0f, 0.980392f, 0.941176f, 1.0f);
    const Color Color::FOREST_GREEN = Color(0.133333f, 0.545098f, 0.133333f, 1.0f);
    const Color Color::FUCHSIA = Color(1.0f, 0.0f, 1.0f, 1.0f);
    const Color Color::GAINSBORO = Color(0.862745f, 0.862745f, 0.862745f, 1.0f);
    const Color Color::GHOST_WHITE = Color(0.972549f, 0.972549f, 1.0f, 1.0f);
    const Color Color::GOLD = Color(1.0f, 0.843137f, 0.0f, 1.0f);
    const Color Color::GOLDENROD = Color(0.854902f, 0.647059f, 0.12549f, 1.0f);
    const Color Color::GRAY = Color(0.501961f, 0.501961f, 0.501961f, 1.0f);
    const Color Color::GREEN = Color(0.0f, 0.501961f, 0.0f, 1.0f);
    const Color Color::GREEN_YELLOW = Color(0.678431f, 1.0f, 0.184314f, 1.0f);
    const Color Color::HONEYDEW = Color(0.941176f, 1.0f, 0.941176f, 1.0f);
    const Color Color::HOT_PINK = Color(1.0f, 0.411765f, 0.705882f, 1.0f);
    const Color Color::INDIAN_RED = Color(0.803922f, 0.360784f, 0.360784f, 1.0f);
    const Color Color::INDIGO = Color(0.294118f, 0.0f, 0.509804f, 1.0f);
    const Color Color::IVORY = Color(1.0f, 1.0f, 0.941176f, 1.0f);
    const Color Color::KHAKI = Color(0.941176f, 0.901961f, 0.54902f, 1.0f);
    const Color Color::LAVENDER = Color(0.901961f, 0.901961f, 0.980392f, 1.0f);
    const Color Color::LAVENDER_BLUSH = Color(1.0f, 0.941176f, 0.960784f, 1.0f);
    const Color Color::LAWN_GREEN = Color(0.486275f, 0.988235f, 0.0f, 1.0f);
    const Color Color::LEMON_CHIFFON = Color(1.0f, 0.980392f, 0.803922f, 1.0f);
    const Color Color::LIGHT_BLUE = Color(0.678431f, 0.847059f, 0.901961f, 1.0f);
    const Color Color::LIGHT_CORAL = Color(0.941176f, 0.501961f, 0.501961f, 1.0f);
    const Color Color::LIGHT_CYAN = Color(0.878431f, 1.0f, 1.0f, 1.0f);
    const Color Color::LIGHT_GOLDENROD_YELLOW = Color(0.980392f, 0.980392f, 0.823529f, 1.0f);
    const Color Color::LIGHT_GRAY = Color(0.827451f, 0.827451f, 0.827451f, 1.0f);
    const Color Color::LIGHT_GREEN = Color(0.564706f, 0.933333f, 0.564706f, 1.0f);
    const Color Color::LIGHT_PINK = Color(1.0f, 0.713725f, 0.756863f, 1.0f);
    const Color Color::LIGHT_SALMON = Color(1.0f, 0.627451f, 0.478431f, 1.0f);
    const Color Color::LIGHT_SEA_GREEN = Color(0.12549f, 0.698039f, 0.666667f, 1.0f);
    const Color Color::LIGHT_SKY_BLUE = Color(0.529412f, 0.807843f, 0.980392f, 1.0f);
    const Color Color::LIGHT_SLATE_GRAY = Color(0.466667f, 0.533333f, 0.6f, 1.0f);
    const Color Color::LIGHT_STEEL_BLUE = Color(0.690196f, 0.768627f, 0.870588f, 1.0f);
    const Color Color::LIGHT_YELLOW = Color(1.0f, 1.0f, 0.878431f, 1.0f);
    const Color Color::LIME = Color(0.0f, 1.0f, 0.0f, 1.0f);
    const Color Color::LIME_GREEN = Color(0.196078f, 0.803922f, 0.196078f, 1.0f);
    const Color Color::LINEN = Color(0.980392f, 0.941176f, 0.901961f, 1.0f);
    const Color Color::MAGENTA = Color(1.0f, 0.0f, 1.0f, 1.0f);
    const Color Color::MAROON = Color(0.501961f, 0.0f, 0.0f, 1.0f);
    const Color Color::MEDIUM_AQUAMARINE = Color(0.4f, 0.803922f, 0.666667f, 1.0f);
    const Color Color::MEDIUM_BLUE = Color(0.0f, 0.0f, 0.803922f, 1.0f);
    const Color Color::MEDIUM_ORCHID = Color(0.729412f, 0.333333f, 0.827451f, 1.0f);
    const Color Color::MEDIUM_PURPLE = Color(0.576471f, 0.439216f, 0.858824f, 1.0f);
    const Color Color::MEDIUM_SEA_GREEN = Color(0.235294f, 0.701961f, 0.443137f, 1.0f);
    const Color Color::MEDIUM_SLATE_BLUE = Color(0.482353f, 0.407843f, 0.933333f, 1.0f);
    const Color Color::MEDIUM_SPRING_GREEN = Color(0.0f, 0.980392f, 0.603922f, 1.0f);
    const Color Color::MEDIUM_TURQUOISE = Color(0.282353f, 0.819608f, 0.8f, 1.0f);
    const Color Color::MEDIUM_VIOLET_RED = Color(0.780392f, 0.0823529f, 0.521569f, 1.0f);
    const Color Color::MIDNIGHT_BLUE = Color(0.0980392f, 0.0980392f, 0.439216f, 1.0f);
    const Color Color::MINT_CREAM = Color(0.960784f, 1.0f, 0.980392f, 1.0f);
    const Color Color::MISTY_ROSE = Color(1.0f, 0.894118f, 0.882353f, 1.0f);
    const Color Color::MOCCASIN = Color(1.0f, 0.894118f, 0.709804f, 1.0f);
    const Color Color::NAVAJO_WHITE = Color(1.0f, 0.870588f, 0.678431f, 1.0f);
    const Color Color::NAVY = Color(0.0f, 0.0f, 0.501961f, 1.0f);
    const Color Color::OLD_LACE = Color(0.992157f, 0.960784f, 0.901961f, 1.0f);
    const Color Color::OLIVE = Color(0.501961f, 0.501961f, 0.0f, 1.0f);
    const Color Color::OLIVE_DRAB = Color(0.419608f, 0.556863f, 0.137255f, 1.0f);
    const Color Color::ORANGE = Color(1.0f, 0.647059f, 0.0f, 1.0f);
    const Color Color::ORANGE_RED = Color(1.0f, 0.270588f, 0.0f, 1.0f);
    const Color Color::ORCHID = Color(0.854902f, 0.439216f, 0.839216f, 1.0f);
    const Color Color::PALE_GOLDENROD = Color(0.933333f, 0.909804f, 0.666667f, 1.0f);
    const Color Color::PALE_GREEN = Color(0.596078f, 0.984314f, 0.596078f, 1.0f);
    const Color Color::PALE_TURQUOISE = Color(0.686275f, 0.933333f, 0.933333f, 1.0f);
    const Color Color::PALE_VIOLET_RED = Color(0.858824f, 0.439216f, 0.576471f, 1.0f);
    const Color Color::PAPAYA_WHIP = Color(1.0f, 0.937255f, 0.835294f, 1.0f);
    const Color Color::PEACH_PUFF = Color(1.0f, 0.854902f, 0.72549f, 1.0f);
    const Color Color::PERU = Color(0.803922f, 0.521569f, 0.247059f, 1.0f);
    const Color Color::PINK = Color(1.0f, 0.752941f, 0.796078f, 1.0f);
    const Color Color::PLUM = Color(0.866667f, 0.627451f, 0.866667f, 1.0f);
    const Color Color::POWDER_BLUE = Color(0.690196f, 0.878431f, 0.901961f, 1.0f);
    const Color Color::PURPLE = Color(0.501961f, 0.0f, 0.501961f, 1.0f);
    const Color Color::RED = Color(1.0f, 0.0f, 0.0f, 1.0f);
    const Color Color::ROSY_BROWN = Color(0.737255f, 0.560784f, 0.560784f, 1.0f);
    const Color Color::ROYAL_BLUE = Color(0.254902f, 0.411765f, 0.882353f, 1.0f);
    const Color Color::SADDLE_BROWN = Color(0.545098f, 0.270588f, 0.0745098f, 1.0f);
    const Color Color::SALMON = Color(0.980392f, 0.501961f, 0.447059f, 1.0f);
    const Color Color::SANDY_BROWN = Color(0.956863f, 0.643137f, 0.376471f, 1.0f);
    const Color Color::SEA_GREEN = Color(0.180392f, 0.545098f, 0.341176f, 1.0f);
    const Color Color::SEA_SHELL = Color(1.0f, 0.960784f, 0.933333f, 1.0f);
    const Color Color::SIENNA = Color(0.627451f, 0.321569f, 0.176471f, 1.0f);
    const Color Color::SILVER = Color(0.752941f, 0.752941f, 0.752941f, 1.0f);
    const Color Color::SKY_BLUE = Color(0.529412f, 0.807843f, 0.921569f, 1.0f);
    const Color Color::SLATE_BLUE = Color(0.415686f, 0.352941f, 0.803922f, 1.0f);
    const Color Color::SLATE_GRAY = Color(0.439216f, 0.501961f, 0.564706f, 1.0f);
    const Color Color::SNOW = Color(1.0f, 0.980392f, 0.980392f, 1.0f);
    const Color Color::SPRING_GREEN = Color(0.0f, 1.0f, 0.498039f, 1.0f);
    const Color Color::STEEL_BLUE = Color(0.27451f, 0.509804f, 0.705882f, 1.0f);
    const Color Color::TAN = Color(0.823529f, 0.705882f, 0.54902f, 1.0f);
    const Color Color::TEAL = Color(0.0f, 0.501961f, 0.501961f, 1.0f);
    const Color Color::THISTLE = Color(0.847059f, 0.74902f, 0.847059f, 1.0f);
    const Color Color::TOMATO = Color(1.0f, 0.388235f, 0.278431f, 1.0f);
    const Color Color::TURQUOISE = Color(0.25098f, 0.878431f, 0.815686f, 1.0f);
    const Color Color::VIOLET = Color(0.933333f, 0.509804f, 0.933333f, 1.0f);
    const Color Color::WHEAT = Color(0.960784f, 0.870588f, 0.701961f, 1.0f);
    const Color Color::WHITE = Color(1.0f, 1.0f, 1.0f, 1.0f);
    const Color Color::WHITE_SMOKE = Color(0.960784f, 0.960784f, 0.960784f, 1.0f);
    const Color Color::YELLOW = Color(1.0f, 1.0f, 0.0f, 1.0f);
    const Color Color::YELLOW_GREEN = Color(0.603922f, 0.803922f, 0.196078f, 1.0f);
}
