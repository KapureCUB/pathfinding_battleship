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
int find_path(battleship *bu) {
    int ret = 0;
    vector<_field*> neighbours;
    _field *next_node = bu->get_start();
    _field *prev_node = NULL, *curr_node=NULL;

    // loop till destination not found
    while((next_node != bu->get_target()) && (next_node != NULL)) {
        curr_node = next_node;                                      // reset locals
        neighbours.clear();                                         
        bu->get_valid_neighbours(&neighbours, next_node);           // get neighbourhood nodes
        for(_field *ptr: neighbours) {
            if((curr_node == next_node) && (ptr != prev_node)) {    // read one entry from valid neighbours to start comparisons
                curr_node = ptr;
            } else if(ptr != prev_node) {
                update_state_machine(&curr_node, &ptr);             // run thorugh state machine to check priority sequence
            }
        }   
        if(curr_node == next_node) {                                // we hit dead end
            curr_node->visited = DEAD_END;
            next_node = prev_node;                                  // go back to previous node
            prev_node = NULL;
        } else {
            (curr_node->marked_path)=1;                             // toggle marked state
            curr_node->visited = bu->get_bu_num();     
            prev_node = next_node;                                  // update prev_node
            next_node = curr_node;                                  // update next_node
        }
    }

    if(next_node == bu->get_target()) {
        ret = 1;                                                    // set the return variable to notify caller
    }
    
    // clear before exit
    neighbours.clear();

    return ret;
}
