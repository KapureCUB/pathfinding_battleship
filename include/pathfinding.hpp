#ifndef _PATHFINDING_
#define _PATHFINDING_

#include "definitions.hpp"

typedef struct POINTS {
    int x; 
    int y;
} _points;

/**
 * @brief Function to find the vaild path from start to target
 *        It uses A* method on the precalculated costs for each nodes
 *        and uses the state machine to iterate through the probable 
 *        path
 * @param bu pointer the the battleship class
 * @return return 1 if a valid path is found. 0 if no path
 * 
 */
int find_path(battleship *bu, vector<_points*> *sol);


#endif //_PATHFINDING_