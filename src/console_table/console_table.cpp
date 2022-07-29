#include "console_table.h"
#include <vector>

console_table::console_table(std::vector<table_header> all_header)
{
    this->header_list = all_header;
}
