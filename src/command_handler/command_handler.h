#include <vector>
#include <map>
#include <string>

class command_handler
{
private:
    /* data */
public:
    std::vector<std::string> command_argument;

    void handle_new_command();

    command_handler(/* args */) {}
};
