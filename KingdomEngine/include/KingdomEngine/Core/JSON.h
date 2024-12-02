#ifndef JSON_H
#define JSON_H

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <string>

#include "KingdomEngine/Core/Dictionary.h"

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
        void AddDicionary(const std::string& name, Dictionary& dict);

        rapidjson::Document& GetData() { return data; }

    private:
        rapidjson::Document data;
        rapidjson::Document::AllocatorType& allocator;
        std::string originalJsonText;

    };
}

#endif
