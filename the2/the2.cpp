#include "the2.h"

// DO NOT CHANGE ABOVE THIS LINE!
// you may implement helper functions below




int getGroupKey(const std::string& str, int startPos, int endPos) {
    int key = 0;
    for (int i = startPos; i <= endPos; i++) {
        key = key * 27 + (i < str.length() ? str[i] - 'A' + 1 : 0);
    }
    return key;
}

long countingSort(std::string* arr, int size, int startPos, int endPos, bool ascending) {
    long iterations = 0;

    int k = 1;
    for(int i = -1; i < endPos - startPos ; i++) {
        k *= 27;
    }

    std::vector<std::string> B(size);
    std::vector<int> C(k, 0);

    for(int i = 0; i < size; i++) {
        iterations++;
        int bucket = getGroupKey(arr[i], startPos, endPos);
        C[bucket]++;
        
    }

    if(ascending) {
        for(int i = 1; i < k; i++) {
            iterations++;
            C[i] += C[i - 1];
            
        }
    } else {
        for(int i = k - 2; i >= 0; i--) {
            iterations++;
            C[i] += C[i + 1];
            
        }
    }

    for(int i = size - 1; i >= 0; i--) {
        iterations++;
        int bucket = getGroupKey(arr[i], startPos, endPos);
        int idx = ascending ? C[bucket] - 1 : --C[bucket];
        B[idx] = arr[i];
        if (ascending){
            C[bucket]--;
        } 
        
    }

    for(int i = 0; i < size; i++) {
        iterations++;
        arr[i] = B[i];
        
    }

    return iterations;
}

long multi_digit_string_radix_sort(std::string* arr, const int size, const bool ascending, const int group_size) {
    if(size <= 1) return 0;

    int maxLen = 0;
    for(int i = 0; i < size; i++) {
        if(arr[i].length() > maxLen) {
            maxLen = arr[i].length();
        }
    }

    long total_iterations = 0;
    int numGroups = (maxLen + group_size - 1) / group_size;

    for(int group = 0; group < numGroups; group++) {
        int startPos = maxLen - (group + 1) * group_size;
        int endPos = startPos + group_size - 1;
        if (startPos < 0) {
            startPos = 0;
        }
        if (endPos >= maxLen) {
            endPos = maxLen - 1;
        }

        total_iterations = total_iterations + countingSort(arr, size, startPos, endPos, ascending);
    }

    return total_iterations;
}