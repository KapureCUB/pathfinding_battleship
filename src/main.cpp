#include "definitions.hpp"
#include "read_map.hpp"
#include "pathfinding.hpp"

int main(int argc, char *argv[]) {
    
    // Input parsing
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <map_file> <x_max> <y_max>\n";
        return -1;
    }

    string map_file = argv[1];
    int x_max = stoi(argv[2]);
    int y_max = stoi(argv[3]);

    // Print input
    cout << "Map file: " << map_file << "\n";
    cout << "x_max: " << x_max << "\n";
    cout << "y_max: " << y_max << "\n";


    // Shared data structures
    Document doc;                           // JSON file object
    const Value* buff = NULL;               // pointer to store world map points
    _field bu_start, bu_target;             // pointers to store start and end, TO DO: declare to a vector for multiple ships

    if(read_file(&doc, map_file)) {
        cout << "File object created" << endl;
        if(doc.HasMember("layers")) {                              // check if file has "layers" field
            const auto& layers = doc["layers"];
            for (auto& layer : layers.GetArray()) {
                if (string(layer["name"].GetString()) == "world") {   // go to "world" section
                    buff = &layer["data"];                             // assign to buffer ptr
                    break;
                }
            }
        }
    }

    print_map_and_mark(buff, &bu_start, &bu_target, y_max);

    // Battelship objects
    battleship bu1(1, x_max, y_max, &bu_start, &bu_target);

    if(buff) {
        if(buff->Size() != (SizeType)(x_max * y_max)) {
            cerr << "Input size does not match map file data dimensions!" << endl;
            return -1;
        }
        // Insert to array
        bu1.insert_nodes(buff);
        cout << "Running path finding.." << endl;
        if(find_path(&bu1)) {
            cout << "Found a path!" << endl;
            bu1.print_path();
        } else {
            cout << "No valid path found!" << endl;
        }
    }

    return 0;
}