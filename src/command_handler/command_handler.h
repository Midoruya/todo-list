#include <vector>
#include <map>
#include <string>

struct task_construct
{
    task_construct(std::string name, std::string description, std::string date, std::string tag, bool is_complete)
    {
        this->name = name;
        this->description = description;
        this->date = date;
        this->tag = tag;
        this->is_complete = is_complete;
    }

    bool is_complete;
    std::string name;
    std::string tag;
    std::string date;
    std::string description;
};

class command_handler
{
private:
    std::string file_format = ".task";
    std::string save_in_folder = "task_list";
    std::vector<task_construct> task_list;

public:
    std::vector<std::string> command_argument;

    void handle_new_command();

    void search_all_task();

    void create_new_task(std::string name, std::string tag, std::string description);

    command_handler(/* args */) {}
};
