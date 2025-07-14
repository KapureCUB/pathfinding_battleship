/**
 * @brief   Read JSON map file  
 * @details This file contains the functions to read the JSON file and store it to Document 
 *          object for parsing. It also had printing and marking functions for handling the
 *          Document object
 * 
 * @author  Deepak E Kapure
 * @date    07-13-2025 
 * 
 */
#include <fstream>
#include "definitions.hpp"
#include "read_map.hpp"

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
int read_file(Document *doc, string f_name) {
    int ret=1;
    ifstream file(f_name);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << f_name << endl;
        return 0;   // TO DO: Add error here
    }

    // Read the file into a string
    string json((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    
    // close file
    file.close();

    // Parse the JSON data
    doc->Parse(json.c_str());
    if (doc->HasParseError()) {
        cerr << "Error parsing JSON: "<< doc->GetParseError() << endl;
        ret = 0;   // TO DO: Add error here
    }

    return ret;
}

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
void print_map_and_mark(const Value *buff, _field *start, _field *target, int y_max) {
    if(buff) {
        cout << "Reading map.." << endl;
        for (SizeType i=0; i < buff->Size(); ++i) {
            double dot = (*buff)[i].GetDouble();
            if(dot == -1) {
                cout << "-" << " ";
            } else if(dot == 3) {
                cout << "8" << " ";
            } else if(dot >= 8) {
                start->x_pos = (i/y_max);       
                start->y_pos = (i%y_max);
                start->field_stat = BU_START;
                start->cost_from_src = 0;
                start->visited = 0;
                start->marked_path = 0;
                cout << "@" << " ";
            } else {
                target->x_pos = (i/y_max);       
                target->y_pos = (i%y_max);
                target->field_stat = BU_TARGET;
                target->cost_to_dest = 0;
                target->visited = 0;
                target->marked_path = 0;
                cout << "*" << " ";
            }
            if ((i + 1) % y_max == 0) cout << "\n";
        }
        cout << "Start at (" << start->x_pos << "," << start->y_pos << ")" << endl;
        cout << "Target at (" << target->x_pos << "," << target->y_pos << ")" << endl;
    }
}
