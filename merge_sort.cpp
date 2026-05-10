#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

long long comparisons = 0, swaps = 0;

// Merge helper - merges two sorted halves into one sorted array
// Uses temporary arrays so it needs O(n) extra space
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2); // temporary arrays

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Merge Sort - O(n log n) time in all cases, O(n) auxiliary space for temp arrays
// Divide and conquer: split in half, sort each half, merge them back together
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Runs sort 3 times on a copy and returns the average time in microseconds
double timeSort(vector<int> original) {
    double total = 0;
    for (int run = 0; run < 3; run++) {
        vector<int> arr = original;
        comparisons = swaps = 0;
        auto start = high_resolution_clock::now();
        mergeSort(arr, 0, arr.size() - 1);
        auto end = high_resolution_clock::now();
        total += duration<double, micro>(end - start).count();
    }
    return total / 3.0;
}

int main() {
    // n=5 sorted
    vector<int> s5 = {1, 2, 3, 4, 5};
    comparisons = swaps = 0;
    double t1 = timeSort(s5);
    vector<int> tmp = s5; mergeSort(tmp, 0, tmp.size() - 1);
    cout << "n=5, Sorted     | Time: " << t1 << " us | Comparisons: " << comparisons << " | Swaps: " << swaps << endl;

    // n=5 reversed
    vector<int> r5 = {5, 4, 3, 2, 1};
    comparisons = swaps = 0;
    double t2 = timeSort(r5);
    tmp = r5; mergeSort(tmp, 0, tmp.size() - 1);
    cout << "n=5, Reversed   | Time: " << t2 << " us | Comparisons: " << comparisons << " | Swaps: " << swaps << endl;

    // n=100 sorted and reversed
    vector<int> s100(100), r100(100);
    for (int i = 0; i < 100; i++) { s100[i] = i + 1; r100[i] = 100 - i; }

    comparisons = swaps = 0;
    double t3 = timeSort(s100);
    tmp = s100; mergeSort(tmp, 0, tmp.size() - 1);
    cout << "n=100, Sorted   | Time: " << t3 << " us | Comparisons: " << comparisons << " | Swaps: " << swaps << endl;

    comparisons = swaps = 0;
    double t4 = timeSort(r100);
    tmp = r100; mergeSort(tmp, 0, tmp.size() - 1);
    cout << "n=100, Reversed | Time: " << t4 << " us | Comparisons: " << comparisons << " | Swaps: " << swaps << endl;

    return 0;
}
