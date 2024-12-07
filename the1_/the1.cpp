#include "the1.h"

std::pair<int, int> partition3(unsigned short *arr, unsigned int size, long &swap) {
    
    int i = 1;
    int j = 1;
    int k = size - 1;
    unsigned short pivot = arr[0];
    
    while (k >= j) {
        
        if (arr[j] == pivot) {
            j++;
        }
        
        else if (pivot > arr[j]) {
            unsigned short temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            swap++;
            i++;
            j++;
        }
        
        else if(arr[j] > pivot) {
            unsigned short temp = arr[k];
            arr[k] = arr[j];
            arr[j] = temp;
            swap++;
            k--;
        }
        
        
    }
    
    unsigned short temp = arr[i - 1];
    arr[i - 1] = arr[0];
    arr[0] = temp;
    swap++;
    
    return std::make_pair(i-1, j);
    
}





unsigned int quicksort3_helper(unsigned short *arr, unsigned int size, long &swap) {
    
    if (size <= 1) return 0; 
    
    int call_count = 1;  
    
    std::pair<int, int> bounds = partition3(arr, size, swap);
    int left = bounds.first;
    int right = bounds.second;
    
    if (left > 0) {
        call_count += quicksort3_helper(arr, left, swap);
    }
    
    if (right < size) {
        call_count += quicksort3_helper(arr + right, size - right, swap);
    }
    
    return call_count;
    
}





std::pair<unsigned short, unsigned int> select_k_with_quick_sort3(unsigned short *arr, unsigned int size, unsigned int index, long &swap) {
    
    int call_count = quicksort3_helper(arr, size, swap);
    
    return std::make_pair(arr[index], call_count);
    
}





unsigned int quickselect3_helper(unsigned short *arr, unsigned int size, unsigned int k, unsigned short &result, long &swap) {
    
    if (size <= 1) {
        result = arr[0];
        return 0;  
    }
    
    int call_count = 1;  
    
    std::pair<int, int> bounds = partition3(arr, size, swap);
    int left = bounds.first;
    int right = bounds.second;
    
    if (left > k) {
        call_count += quickselect3_helper(arr, left, k, result, swap);
    }
    
    else if (right > k) {
        result = arr[left];
    }
    
    else {
        call_count += quickselect3_helper(arr + right, size - right, k - right, result, swap);
    }
    
    return call_count;
    
}




std::pair<unsigned short, unsigned int> quick_select3(unsigned short *arr, unsigned int size, unsigned int index, long &swap) {
    
    unsigned short result;
    
    int call_count = quickselect3_helper(arr, size, index, result, swap);
    
    return std::make_pair(result, call_count);
    
}