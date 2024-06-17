class Solution {
public:
    bool less(int a, int b) {
        return a < b;
}

/*
Definitions:
--------------------------------------------------------
sort(low, high, a[], aux) --> given a[low...high] = aux[low...high], this function
                            sorts the a[low...high] (or, aux[low...high] as both equal)
                            and puts the sorted result in aux[low...high]. 
                            (And, a[low...high] might be shuffled)

merge(low, mid, high, a, aux) --> given sorted arrays a[low...mid] and a[mid+1 ... high]
                                this function merges these 2 parts and puts the result
                                into aux[low...high]

*/

    void merge(int low, int mid, int high, vector<int>  &a, vector<int> &aux) {
        //CHANGE: here merge(a, aux) merges 2 sorted halves of a[] into aux
        //so can not use this case to just return, we must copy the sorted array into aux[]
        // if (a[mid] <= a[mid + 1]) return;

        int i = low, j = mid + 1, k = low;
        while (i <= mid && j <= high) {
            if (less(a[i], a[j])) aux[k++] = a[i++]; 
            else aux[k++] = a[j++];
        }
        while (i <= mid) aux[k++] = a[i++];
        while (j <= high) aux[k++] = a[j++];

        //CHANGE: DONT COPY
        // for (int i = low; i <= high; ++i)
        //     a[i] = aux[i];
    }


    void mergeSort(int low, int high, vector<int> &a, vector<int> &aux) {
        if (low >= high) {
            // this copy is not needed, as it's given a[low...high] = aux[low...high]
            // if (low == high) aux[low] = a[low];
            return;
        }

        int mid = low + (high - low) / 2;
        //CHANGE: swap a[] and aux[] arguments 
        mergeSort(low, mid, aux, a);
        mergeSort(mid + 1, high, aux, a);
        //NO CHANGE:
        merge(low, mid, high, a, aux);
    }

    vector<int> sortArray(vector<int>& a) {
        //CHANGE: deepcopy a[] into aux[]
        vector<int> aux = a;
        mergeSort(0, a.size() - 1, a, aux);
        //CHANGE: mergeSort(0, n-1, a, aux) --> sorts the array and puts into aux
        //so return aux
        return aux;    
    }
};



// //If we want to cutoff to insertion sort for smaller arrays, then
// //we have to sort aux[low...high] instead of a[low...high], 
// //because, here mergeSort(low, high, a, aux) --> sorts and puts into aux[low...high]
// void mergeSort(int low, int high, vector<int> &a, vector<int> &aux) {
//     if (low >= high) return;
//     //CHANGE: insertionSort aux[]
//     if (high <= low - 1 + 7) {
//             insertionSort(low, high, aux);
//         return;
//     }
    
//     int mid = low + (high - low) / 2;
//     mergeSort(low, mid, aux, a);
//     mergeSort(mid + 1, high, aux, a);
//     merge(low, mid, high, a, aux);
// }
