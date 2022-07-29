#include <vector>
#include <map>
#include <string>

class command_handler
{
private:
    std::string file_format = ".task";
    std::string save_in_folder = "task_list";

public:
    std::vector<std::string> command_argument;

    void handle_new_command();

    void search_all_task();

    void create_new_task(std::string name, std::string tag, std::string description);

    command_handler(/* args */) {}
};
