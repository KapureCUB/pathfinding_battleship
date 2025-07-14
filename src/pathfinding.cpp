/**
 * @brief   Pathfinding file  
 * @details This file contains the function for A* based pathfinding functions for the pathfinding problem given by Globus Medical.
 *          The code uses a modified implementation of A* algorithm for path finding where only vertical and horizontal steps 
 *          are taken into account.
 * 
 * @author  Deepak E Kapure
 * @date    07-13-2025 
 * 
 */
#include "pathfinding.hpp"
#include "definitions.hpp"
#include <stack>

/**
 * @brief States for the state machine on checking evry new node
 * 
 */
enum STATES {
    NEW_NODE=0,
    CHECK_T_COST=1,
    CHECK_D_COST=2
};

/**
 * @brief Function to check the nature of the new neighbour node
 *        The State machine cycles through 3 states to determine
 *        if the new node should be replaced by the current node
 * @param c Address of current node pointer
 * @param n Address of next node pointer 
 * 
 */
void update_state_machine(_field **c, _field **n) {
    if(c && n) {
        _field *curr = *c;
        _field *node = *n;
        int state = NEW_NODE;
        
        if(state == NEW_NODE) {
            if((node->visited==NOT_VISITED) && (curr->visited > NOT_VISITED)) {      // new node is not visited
                *c = node;
                return;
            } else {
                state = CHECK_T_COST;
            }
        }
        if(state == CHECK_T_COST) {                                                 
            int curr_cost = curr->cost_from_src + curr->cost_to_dest;
            int node_cost = node->cost_from_src + node->cost_to_dest;
            if(node_cost < curr_cost) {                                              // new node has lower total cost 
                *c = node;
                return;
            } else {
                state = CHECK_D_COST;
            }
        }
        if(state == CHECK_D_COST) {                                                 // new node had lower destination cost
            if(node->cost_to_dest < curr->cost_to_dest) {
                *c = node;
            } 
            // else no change to curr
        }
    }
}

/**
 * @brief Function to find the vaild path from start to target
 *        It uses A* method on the precalculated costs for each nodes
 *        and uses the state machine to iterate through the probable 
 *        path
 * @param bu pointer the the battleship class
 * @return return 1 if a valid path is found. 0 if no path
 * 
 */
int find_path(battleship *bu, vector<_points*> *sol) {
    int ret = 0;
    vector<_field*> neighbours;
    stack<_field*> backtrack;
    _field *start = bu->get_start();
    _field *target = bu->get_target();

    _field *curr_node = start;                                  // start with current node 
    curr_node->visited = bu->get_bu_num();
    curr_node->marked_path = true;
    backtrack.push(curr_node);                                  // push it to back tracking stack

    while (!backtrack.empty()) {                                // iterate over the stack 
        curr_node = backtrack.top();                            
        if (curr_node == target) {                              // target is reached, exit
            ret = 1;
            break;
        }
        neighbours.clear();
        bu->get_valid_neighbours(&neighbours, curr_node);       // get neighbourhood nodes

        _field *next_node = NULL;
        for (_field *ptr : neighbours) {
            if (ptr->visited == NOT_VISITED) {                  // look for new nodes
                if(!next_node) {                                // read one entry from valid neighbours to start comparisons
                    next_node = ptr;
                } else { 
                    update_state_machine(&next_node, &ptr);     // look for valid neighbouring nodes
                }
            }
        }

        if(next_node) {                                         // found a new node, mark it
            next_node->visited = bu->get_bu_num();
            next_node->marked_path = true;
            backtrack.push(next_node);

            // Save path point
            _points *p = new _points;
            p->x = next_node->x_pos; 
            p->y = next_node->y_pos;
            sol->push_back(p);
        } else {                                                // no new valid node, backtrack
            curr_node->marked_path = false;
            curr_node->visited = DEAD_END;
            backtrack.pop();

            // Remove last added point from solution
            if (!sol->empty()) {
                delete sol->back();
                sol->pop_back();
            }
        }
    }

    if (ret) {
        target->marked_path = true;                             // mark target for solution entry

        _points *start_p = new _points;                         // put start in solution list
        start_p->x = start->x_pos;
        start_p->y = start->y_pos;
        sol->insert(sol->begin(), start_p);
    }

    return ret;

}

