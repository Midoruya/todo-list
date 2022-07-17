#include <Windows.h>
#include "structure_TODO/structure_TODO.h"
#include "other.h"
#include "coman_handler/command_handle.h"

int main()
{
	while (true)
	{
		command_handle command_manager = command_handle();
		command_manager.search_all_task();
		printf("all task\n");
		printf("Command list :\nadd : add new task to the list\nupdate {name_todo} : update description for current task\ndelete {name_todo} : delete all info about current task\n");
		printf("Please inter you command: \n");
		command_manager.handle_new_command();
		command_manager.handling_command_add();
		command_manager.handling_command_update();
		command_manager.handling_command_delete();
		command_manager.handling_command_select();
		command_manager.handling_command_done();

		system("pause");
		system("cls");
	}
}
