#include "the3.h"

// DO NOT CHANGE ABOVE THIS LINE!
// you may implement helper functions below

int find_min_cost(const std::vector<std::vector<int>>& costs, int N) {
    const int num_spots = N - 1;
    if (num_spots == 0) return 0;
    
    // We only need to keep track of previous state
    // Each state represents: [flower1, flower2, bush1, bush2, tree1, tree2]
    std::vector<int> prev(6, 1e9);
    std::vector<int> curr(6, 1e9);
    
    // Initialize first position
    for (int j = 0; j < 6; ++j) {
        prev[j] = costs[0][j];
    }
    
    // Process each position
    for (int i = 1; i < num_spots; ++i) {
        // For each current plant type
        for (int curr_plant = 0; curr_plant < 6; ++curr_plant) {
            curr[curr_plant] = 1e9;
            // Check against each previous plant type
            for (int prev_plant = 0; prev_plant < 6; ++prev_plant) {
                // Skip invalid combinations
                
                // Cannot have consecutive bushes (2,3)
                if (curr_plant >= 2 && curr_plant <= 3 && 
                    prev_plant >= 2 && prev_plant <= 3) {
                    continue;
                }
                
                // Cannot have consecutive trees (4,5)
                if (curr_plant >= 4 && curr_plant <= 5 && 
                    prev_plant >= 4 && prev_plant <= 5) {
                    continue;
                }
                
                // Consecutive flowers must be same species
                if (prev_plant <= 1 && curr_plant <= 1 && 
                    prev_plant != curr_plant) {
                    continue;
                }
                
                // Update minimum cost
                if (prev[prev_plant] + costs[i][curr_plant] < curr[curr_plant]) {
                    curr[curr_plant] = prev[prev_plant] + costs[i][curr_plant];
                }
            }
        }
        
        // Swap current and previous arrays
        prev.swap(curr);
    }
    
    // Find minimum in the last position without std::min_element
    int min_cost = prev[0];
    for (int j = 1; j < 6; ++j) {
        if (prev[j] < min_cost) {
            min_cost = prev[j];
        }
    }
    
    return min_cost;
}