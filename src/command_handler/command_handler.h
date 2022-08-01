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

    void add_task();

public:
    std::vector<std::string> command_argument;

    /**
     * @brief This function waits for a new command to be entered in the console and sets it to command_argument
     *
     */
    void handle_new_command();

    /**
     * @brief This function search task files in the alctive folder and convert file name in (name, tag, date, is commpleted), using splite.
     * Also reads contents this file and writes it file in to description
     * Then writes all the data (name, tag, date, description and ends) in new task_construct and adds it to the task_list array.
     *
     */
    void search_all_task();

    /**
     * @brief This function create a new task file and writes task description in to file content
     *
     * @param name This is a task name
     * @param tag  This is a task tag
     * @param description  This is a task description
     */
    void create_new_task_file(std::string name, std::string tag, std::string description);

    command_handler(/* args */) {}
};
