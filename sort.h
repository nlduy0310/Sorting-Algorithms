#ifndef SORT_H_
#define SORT_H_

#include <iostream>
#include <cstring>

using namespace std;

void swap(int &a, int &b);
void print(int array[], int size);

void SelectionSort(int array[], int size, unsigned long long &);

void InsertionSort(int array[], int size, unsigned long long &);

void BubbleSort(int array[], int size, unsigned long long &);

void ShakerSort(int array[], int size, unsigned long long &);

void ShellSort(int array[], int size, unsigned long long &);

void heapify(int array[], int size, int i, unsigned long long &);
void HeapSort(int array[], int size, unsigned long long &);

void merge(int array[], int p, int q, int r, unsigned long long &);
void mergeSort(int array[], int left, int right, unsigned long long &);
void MergeSort(int array[], int size, unsigned long long &);

void quickSort(int array[], int left, int right, unsigned long long &);
void QuickSort(int array[], int size, unsigned long long &);

void CountingSort(int array[], int size, unsigned long long &);

void RadixSort(int array[], int size, unsigned long long &);

void FlashSort(int array[], int size, unsigned long long &);

#endif