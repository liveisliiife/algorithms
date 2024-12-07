#include "the4.h"

// DO NOT CHANGE ABOVE THIS LINE!
// You may implement helper functions below




unsigned int wasted_cake_hesaplama(const int w, const int h, const std::vector<std::vector<bool>>& perfect_cuts, 
    std::vector<std::vector<unsigned int>>& wasted_cake) {
                                       
    unsigned int min_wasted = wasted_cake[w][h]; 

    int k = 1;
    while (k < w) {
        if (wasted_cake[w][h] > wasted_cake[k][h] + wasted_cake[w - k][h]) {
            wasted_cake[w][h] = wasted_cake[k][h] + wasted_cake[w - k][h];
        }
        ++k;
    }

    int l = 1;
    while (l < h) {
        if (wasted_cake[w][h] > wasted_cake[w][l] + wasted_cake[w][h - l]) {
            wasted_cake[w][h] = wasted_cake[w][l] + wasted_cake[w][h - l];
        }
        ++l;
    }

    return wasted_cake[w][h];  
    
}



void wasted_cake_baslat(const unsigned short width, const unsigned short height, const std::vector<std::vector<bool>>& perfect_cuts, 
    std::vector<std::vector<unsigned int>>& wasted_cake) {
                                
    for (int i = 0; i <= width; ++i) {
        for (int j = 0; j <= height; ++j) {
            if (perfect_cuts[i][j] == false) {
                wasted_cake[i][j] = i * j;
            } else {
                wasted_cake[i][j] = 0;
            }
        }
    }
    
}





unsigned int wasted_part(const unsigned short width, const unsigned short height, const std::vector<std::vector<bool>>& perfect_cuts, 
    std::vector<std::vector<unsigned int>>& wasted_cake) {


    wasted_cake_baslat(width, height, perfect_cuts, wasted_cake);

    for (int w = 1; w <= width; ++w) {
        for (int h = 1; h <= height; ++h) {
            wasted_cake[w][h] = wasted_cake_hesaplama(w, h, perfect_cuts, wasted_cake);
        }
    }

    return wasted_cake[width][height];
    
}







unsigned int alice_cutting_cake(const unsigned short cake_width,
                            const unsigned short cake_height,
                            bool **perfect_cuts) {
                                 
    std::vector<std::vector<bool>> perfect_cuts_check(cake_width + 1, std::vector<bool>(cake_height + 1, false));
   
    for (int i = 0; i <= cake_width; ++i) {
        for (int j = 0; j <= cake_height; ++j) {
            perfect_cuts_check[i][j] = perfect_cuts[i][j];
       }
   }
   
   std::vector<std::vector<unsigned int>> wasted_cake(cake_width + 1, std::vector<unsigned int>(cake_height + 1, UINT_MAX));
   
   return wasted_part(cake_width, cake_height, perfect_cuts_check, wasted_cake);
   
}