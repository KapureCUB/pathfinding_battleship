#ifndef _READ_MAP_
#define _READ_MAP_

#include "rapidjson/document.h"

using namespace rapidjson;


int read_file(Document *doc, string f_name);
void print_map_and_mark(const Value *buff, _field *start, _field *target, int y_max);

#endif // _READ_MAP_