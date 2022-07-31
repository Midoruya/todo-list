#include <vector>
#include <sstream>
#include <string>

namespace utilities
{
    /**
     * @brief This function for splite string on the array words
     *
     * @param str This is a text for split
     * @param delimiter This is the letter by which the division will be
     * @return std::vector<std::string> This function returns separated words by an array
     */
    inline std::vector<std::string> splite_string(std::string str, std::string delimiter = " ")
    {
        std::vector<std::string> ret;
        size_t pos = 0;
        std::string token;
        while ((pos = str.find(delimiter)) != std::string::npos)
        {
            token = str.substr(0, pos);
            ret.emplace_back(std::move(token));
            str.erase(0, pos + delimiter.length());
        }
        ret.push_back(std::move(str));
        return ret;
    }
}