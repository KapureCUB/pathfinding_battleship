#include <fstream>
#include "definitions.hpp"
#include "read_map.hpp"

/**
 * Refernces - https://www.geeksforgeeks.org/cpp/rapidjson-file-read-write-in-cpp/
 *             https://github.com/Tencent/rapidjson
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

    // Parse the JSON data
    doc->Parse(json.c_str());
    if (doc->HasParseError()) {
        cerr << "Error parsing JSON: "<< doc->GetParseError() << endl;
        ret = 0;   // TO DO: Add error here
    }

    return ret;
}

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
            if ((i + 1) % 32 == 0) cout << "\n";
        }
        cout << "Start at (" << start->x_pos << "," << start->y_pos << ")" << endl;
        cout << "Target at (" << target->x_pos << "," << target->y_pos << ")" << endl;
    }
}
