#ifndef JSON_H
#define JSON_H

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <string>

namespace KE
{
    class JSON
    {
    public:
        JSON();
        ~JSON();

        void Parse(const std::string& jsonText, bool keepText = false);
        void ParseString(const std::string& jsonSting);
        std::string Stringify() const;
        const std::string& GetParsedJson() const;

        rapidjson::Document& GetData() { return data; }

    private:
        rapidjson::Document data;
        std::string originalJsonText;

    };
}

#endif
