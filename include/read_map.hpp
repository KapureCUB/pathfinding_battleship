#ifndef _READ_MAP_
#define _READ_MAP_

#include "rapidjson/document.h"

using namespace rapidjson;

/**
 * @brief Function to read JSON file passed in as agrument. It reads and 
 *        stores the json formatted data to the doc object and closes the 
 *        file. 
 *        Refernces - https://www.geeksforgeeks.org/cpp/rapidjson-file-read-write-in-cpp/
 *                    https://github.com/Tencent/rapidjson
 * @param doc object pointer to store file info
 * @param f_name string containing map file path
 * @returns 1 if succeeded, 0 if failed 
 */
int read_file(Document *doc, string f_name);

/**
 * @brief Function to mark and print the map on the console. It reads and the 
 *        json formatted data, marks the start and target positions and prints
 *        the map on the console 
 *
 * @param buff pointer to buffer containing map data
 * @param start pointer to start position
 * @param target pointer to target position
 * @param y_max maximum size of a row in the map 
 */
void print_map_and_mark(const Value *buff, _field *start, _field *target, int y_max);

#endif // _READ_MAP_