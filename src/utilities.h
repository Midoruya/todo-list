#include <vector>
#include <sstream>
#include <string>

namespace utilities
{
    /**
     * @brief function for splitting a string and return word array
     *
     * @param str string for splite
     * @return std::vector<std::string> word array after splitting
     */
    inline std::vector<std::string> splite_string(std::string str)
    {
        std::vector<std::string> result;
        std::stringstream line_stream(str);
        std::string word;
        while (line_stream >> word)
            result.push_back(word);
        return result;
    }
}