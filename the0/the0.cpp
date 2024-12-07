#include "the0.h"


void insertionSort(int* arr, long &comparison, long &swap, int size) {


    int i = 1; // i'yi 1 olarak başlat

    while (i < size) { // i, dizi uzunluğundan küçük olduğu sürece
        int x = arr[i]; // x'e A[i] değerini ata
        int j = i - 1; // j'yi i-1 olarak ayarla
        // İçteki döngü
        while (j >= 0) { // j sıfırdan büyük veya eşit olduğu sürece
            comparison++; // j >= 0 kontrolü için karşılaştırma sayısını artır
            if (arr[j] > x) { // A[j] > x karşılaştırmasını yap
                arr[j + 1] = arr[j]; // A[j]'yi A[j+1]'e kopyala
                j--; // j'yi bir azalt
                swap++; // Takas sayısını artır (eleman kaydırdığımız için)
            } else {
                break; // Eğer A[j] <= x ise döngüden çık
            }
        }
        
        arr[j + 1] = x; // x'i doğru yere yerleştir
        
        i++; // i'yi artır
        
    }
    
    
    comparison++;

}

