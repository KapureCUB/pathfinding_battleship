#ifndef _DEFINITIONS_
#define _DEFINITIONS_

#include <fstream>
#include <iostream>
#include <vector>
#include "rapidjson/document.h"

using namespace std;
using namespace rapidjson;

enum VISITED_STAT {
    NOT_VISITED=0,
    DEAD_END=-1
};

typedef enum F_TYPE {
    GROUND_TERRAIN = -1,
    BU_TARGET = 0,
    ELEVATED_TERRAIN = 3,
    BU_START = 8
} _f_type; 

typedef struct FIELD {
    int x_pos;              
    int y_pos;
    _f_type field_stat;
    int cost_to_dest;
    int cost_from_src;
    int visited;
    bool marked_path;       
} _field;


class battleship {
    private:
        int bu_num;
        int x_max;
        int y_max;
        _field bu_start;
        _field bu_target;  
        _field curr_pos;        // TO DO: For multiple battleships  
        vector<vector<_field*>> array;
    public:
        battleship(int bu, int x, int y, _field *s, _field *t) {
            bu_num = bu;
            x_max = x; y_max = y;
            array.resize(x_max, std::vector<_field*>(y_max, nullptr));
            bu_start.x_pos = s->x_pos;
            bu_start.y_pos = s->y_pos;
            
            bu_target.x_pos = t->x_pos;
            bu_target.y_pos = t->y_pos;
        }

        int insert_nodes(const Value *buff) {
            int temp_x=0, temp_y=0, ret = 1;
            for (SizeType i=0; i < buff->Size(); ++i) {
                double dot = (*buff)[i].GetDouble();
                _field *node = new _field;
                if(node) {
                    node->x_pos = temp_x;
                    node->y_pos = temp_y;
                    node->field_stat = (_f_type)(dot);
                    if(node->field_stat != ELEVATED_TERRAIN) {
                        node->cost_from_src = abs(bu_start.x_pos - temp_x) + abs(bu_start.y_pos - temp_y); 
                        node->cost_to_dest = abs(bu_target.x_pos - temp_x) + abs(bu_target.y_pos - temp_y);
                    } else {
                        node->cost_from_src = 0; 
                        node->cost_to_dest = 0;
                    }
                    node->visited = NOT_VISITED;
                    node->marked_path = false;  
                    array[temp_x][temp_y] = node;
                    
                    //check for temps
                    temp_x = (temp_y==(y_max - 1)) ? (temp_x+1) : (temp_x);
                    temp_y = (temp_y==(y_max - 1)) ? (0) : (temp_y+1);
                } else {
                    ret = 0;
                    break;
                }
            }
            return ret;
        }

        void print_nodes() {   
            cout << "Reading array.." << endl;
            for (int i=0; i < x_max; ++i) {
                for(int j=0; j < y_max; ++j) {
                    _field *dot = array[i][j];
                    if(dot->field_stat == GROUND_TERRAIN) {
                        cout << "-" << " ";
                    } else if(dot->field_stat == ELEVATED_TERRAIN) {
                        cout << "8" << " ";
                    } else if(dot->field_stat == BU_START) {
                        cout << "@" << " ";
                    } else {
                        cout << "*" << " ";
                    }
                }
                cout << "\n";
            }
        }

        void print_path() {   
            cout << "Printing path.." << endl;
            for (int i=0; i < x_max; ++i) {
                for(int j=0; j < y_max; ++j) {
                    _field *dot = array[i][j];
                    if(dot->field_stat == GROUND_TERRAIN) {
                        if(dot->marked_path) {
                            cout << "@" << " ";
                        } else {
                            cout << "-" << " ";
                        }
                    } else if(dot->field_stat == ELEVATED_TERRAIN) {
                        cout << "8" << " ";
                    } else if(dot->field_stat == BU_START) {
                        cout << "@" << " ";
                    } else {
                        cout << "*" << " ";
                    }
                }
                cout << "\n";
            }
        }

        _field *get_start(void) { return array[bu_start.x_pos][bu_start.y_pos]; }
        _field *get_target(void) { return array[bu_target.x_pos][bu_target.y_pos]; }
        int get_max_cost(void) { return (x_max+y_max); }
        int get_bu_num(void) { return bu_num; }

        void get_valid_neighbours(vector<_field*> *neighbours, _field *node) {
            _field *temp;
            if((node->x_pos - 1) >= 0) {
                temp = array[node->x_pos - 1][node->y_pos];
                if((temp->field_stat != ELEVATED_TERRAIN) && (temp->visited != DEAD_END)) {
                    neighbours->push_back(temp);    
                }
            }
            if((node->x_pos + 1) < x_max) {
                temp = array[node->x_pos + 1][node->y_pos];
                if((temp->field_stat != ELEVATED_TERRAIN) && (temp->visited != DEAD_END)) {
                    neighbours->push_back(temp);
                }
            }
            if((node->y_pos - 1) >= 0) {
                temp = array[node->x_pos][node->y_pos - 1];
                if((temp->field_stat != ELEVATED_TERRAIN) && (temp->visited != DEAD_END)) {
                    neighbours->push_back(temp);
                }
            }
            if((node->y_pos + 1) < y_max) {
                temp = array[node->x_pos][node->y_pos + 1];
                if((temp->field_stat != ELEVATED_TERRAIN) && (temp->visited != DEAD_END)) {
                    neighbours->push_back(temp);
                }
            }
        }

};
#endif //_DEFINITIONS_