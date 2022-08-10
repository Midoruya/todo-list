#include <vector>
#include <map>
#include <string>

struct task_construct
{
    /**
     * @brief Construct a new task\
     *
     * @param name enter a task name
     * @param description  enter a task description
     * @param date enter a date
     * @param tag enter a task tag
     * @param is_complete
     */
    task_construct(std::string name, std::string description, std::string date, std::string tag, bool is_complete) : name(name), description(description), date(date), tag(tag), is_complete(is_complete) {}

    /**
     * @brief Get the full task filename
     *
     * @return std::string result full task filename
     */
    std::string get_file_name();

    std::string file_format = ".task";
    bool is_complete;
    std::string name;
    std::string tag;
    std::string date;
    std::string description;
};

class command_handler
{
private:
    std::string save_in_folder = "task_list";
    std::vector<task_construct> task_list;

    /**
     * @brief use this function to create a new task
     *
     */
    void add_task();

    /**
     * @brief use this function to delete a task
     *
     */
    void delete_task();

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
     * @brief use this function to create a new file task
     *
     * @param task task construcor which the have all info
     */
    void create_new_task_file(task_construct task);

    /**
     * @brief Get the work directory in which the lie all task file
     *
     * @return std::string return the work directory in which the lie all task file
     */
    std::string get_work_directory();

    command_handler(/* args */) {}
};
