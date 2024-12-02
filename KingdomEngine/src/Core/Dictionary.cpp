#include "KingdomEngine/Core/Dictionary.h"
#include "KingdomEngine/Core/Log.h"

namespace KE
{
    Dictionary::Dictionary()
    {

    }

    Dictionary::~Dictionary()
    {

    }

    void Dictionary::Add(const std::string& key, const ValueType& value)
    {
        dict[key] = value;
    }

    Dictionary::ValueType Dictionary::Get(const std::string& key) const
    {
        if (dict.find(key) != dict.end())
        {
            return dict.at(key);
        }
        else
        {
            LOG_ERROR("Key Not Found");
        }
    }

    bool Dictionary::Contains(const std::string& key) const
    {
        return dict.find(key) != dict.end();
    }

    void Dictionary::Remove(const std::string& key)
    {
        dict.erase(key);
    }
}