#include "KingdomEngine/Core/JSON.h"
#include "KingdomEngine/Core/Log.h"

namespace KE
{
    JSON::JSON()
    {
        data.SetObject();
    }

    JSON::~JSON()
    {

    }

    void JSON::Parse(const std::string& jsonText, bool keepText)
    {
        if (keepText)
            originalJsonText = jsonText;

        if (data.Parse(jsonText.c_str()).HasParseError())
        {
            LOG_ERROR("Failed to parse JSON");
        }
    }

    std::string JSON::Stringify() const
    {
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        data.Accept(writer);
        return buffer.GetString();
    }

    const std::string& JSON::GetParsedJson() const
    {
        return originalJsonText;
    }
}
