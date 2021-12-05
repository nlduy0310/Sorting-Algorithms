#include "sort.h"

void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void print(int array[], int size)
{
    for (int i = 0; i < size; i++)
        cout << array[i] << ' ';

    cout << endl;
}

// Reference: https://www.programiz.com/dsa/selection-sort
//
void SelectionSort(int array[], int size, unsigned long long &comparisions_count)
{
    for (int step = 0; ++comparisions_count && step < size - 1; step++)
    {
        int min_idx = step;
        for (int i = step + 1; ++comparisions_count && i < size; i++)
            if (++comparisions_count && array[i] < array[min_idx])
                min_idx = i;

        swap(array[min_idx], array[step]);
    }
}

// Reference: https://www.programiz.com/dsa/insertion-sort
//
void InsertionSort(int array[], int size, unsigned long long &comparisions_count)
{
    for (int step = 1; ++comparisions_count && step < size; step++)
    {
        int key = array[step];
        int j = step - 1;

        while ((++comparisions_count && key < array[j]) && (++comparisions_count && j >= 0))
        {
            array[j + 1] = array[j];
            --j;
        }

        array[j + 1] = key;
    }
}

// Reference: https://www.tutorialspoint.com/cplusplus-program-to-implement-bubble-sort
// Improved version of bubble sort, with swap flag
//
void BubbleSort(int array[], int size, unsigned long long &comparisions_count)
{
    for (int i = 0; ++comparisions_count && i < size; i++)
    {
        bool swapped = false;
        for (int j = 0; ++comparisions_count && (j < size - i - 1); j++)
        {
            if (++comparisions_count && array[j] > array[j + 1])
            {
                swap(array[j], array[j + 1]);
                swapped = true;
            }
        }
        if (++comparisions_count && !swapped)
            break;
    }
}

// Reference: https://www.sanfoundry.com/cplusplus-program-perform-shaker-sort/
//
void ShakerSort(int array[], int size, unsigned long long &comparisions_count)
{
    int i, j, k;
    for (i = 0; ++comparisions_count && i < size;)
    {
        for (j = i + 1; ++comparisions_count && j < size; j++)
        {
            if (++comparisions_count && array[j] < array[j - 1])
                swap(array[j], array[j - 1]);
        }

        size--;

        for (k = size - 1; ++comparisions_count && k > i; k--)
        {
            if (++comparisions_count && array[k] < array[k - 1])
                swap(array[k], array[k - 1]);
        }

        i++;
    }
}

// Reference: https://www.programiz.com/dsa/shell-sort
//
void ShellSort(int array[], int size, unsigned long long &comparisions_count)
{
    for (int interval = size / 2; ++comparisions_count && interval > 0; interval /= 2)
    {
        for (int i = interval; ++comparisions_count && i < size; i += 1)
        {
            int temp = array[i];
            int j;
            for (j = i; (++comparisions_count && j >= interval) && (++comparisions_count && array[j - interval] > temp); j -= interval)
            {
                array[j] = array[j - interval];
            }
            array[j] = temp;
        }
    }
}

// Reference: https://www.programiz.com/dsa/heap-sort
//
void heapify(int array[], int size, int i, unsigned long long &comparisions_count)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if ((++comparisions_count && left < size) && (++comparisions_count && array[left] > array[largest]))
        largest = left;

    if ((++comparisions_count && right < size) && (++comparisions_count && array[right] > array[largest]))
        largest = right;

    if (++comparisions_count && largest != i)
    {
        swap(array[i], array[largest]);
        heapify(array, size, largest, comparisions_count);
    }
}

void HeapSort(int array[], int size, unsigned long long &comparisions_count)
{
    for (int i = size / 2 - 1; ++comparisions_count && i >= 0; i--)
        heapify(array, size, i, comparisions_count);

    for (int i = size - 1; ++comparisions_count && i >= 0; i--)
    {
        swap(array[0], array[i]);
        heapify(array, i, 0, comparisions_count);
    }
}

// Reference: https://www.programiz.com/dsa/merge-sort
//
void merge(int array[], int p, int q, int r, unsigned long long &comparisions_count)
{
    int n1 = q - p + 1;
    int n2 = r - q;

    int L[n1], M[n2];

    for (int i = 0; ++comparisions_count && i < n1; i++)
        L[i] = array[p + i];
    for (int j = 0; ++comparisions_count && j < n2; j++)
        M[j] = array[q + 1 + j];

    int i, j, k;
    i = 0;
    j = 0;
    k = p;

    while ((++comparisions_count && i < n1) && (++comparisions_count && j < n2))
    {
        if (++comparisions_count && L[i] <= M[j])
        {
            array[k] = L[i];
            i++;
        }
        else
        {
            array[k] = M[j];
            j++;
        }
        k++;
    }

    while (++comparisions_count && i < n1)
    {
        array[k] = L[i];
        i++;
        k++;
    }

    while (++comparisions_count && j < n2)
    {
        array[k] = M[j];
        j++;
        k++;
    }
}

void mergeSort(int array[], int left, int right, unsigned long long &comparisions_count)
{
    if (++comparisions_count && left < right)
    {
        int middle = left + (right - left) / 2;

        mergeSort(array, left, middle, comparisions_count);
        mergeSort(array, middle + 1, right, comparisions_count);

        merge(array, left, middle, right, comparisions_count);
    }
}

void MergeSort(int array[], int size, unsigned long long &comparisions_count)
{
    mergeSort(array, 0, size - 1, comparisions_count);
}

// Reference: https://www.algolist.net/Algorithms/Sorting/Quicksort
//
void quickSort(int array[], int left, int right, unsigned long long &comparisions_count)
{

    int i = left, j = right;
    int tmp;
    int pivot = array[(left + right) / 2];

    while (++comparisions_count && i <= j)
    {
        while (++comparisions_count && array[i] < pivot)
            i++;

        while (++comparisions_count && array[j] > pivot)
            j--;

        if (++comparisions_count && i <= j)
        {
            tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;

            i++;
            j--;
        }
    }

    if (++comparisions_count && left < j)
        quickSort(array, left, j, comparisions_count);

    if (++comparisions_count && i < right)
        quickSort(array, i, right, comparisions_count);
}

void QuickSort(int array[], int size, unsigned long long &comparisions_count)
{
    quickSort(array, 0, size - 1, comparisions_count);
}

// Reference: https://www.programiz.com/dsa/counting-sort
//
void CountingSort(int array[], int size, unsigned long long &comparisions_count)
{
    int max = array[0];

    int temp_array[size];

    for (int i = 1; ++comparisions_count && i < size; ++i)
        if (++comparisions_count && array[i] > max)
            max = array[i];

    if (++comparisions_count && max > 0)
    {
        int count[max + 1] = {0};

        for (int i = 0; ++comparisions_count && i < size; ++i)
            count[array[i]]++;

        for (int i = 1; ++comparisions_count && (i < max + 1); ++i)
            count[i] += count[i - 1];

        for (int i = size - 1; ++comparisions_count && i >= 0; --i)
        {
            temp_array[count[array[i]] - 1] = array[i];
            count[array[i]]--;
        }

        for (int i = 0; ++comparisions_count && i < size; ++i)
            array[i] = temp_array[i];
    }
}

// Reference: https://www.programiz.com/dsa/radix-sort
//
void RadixSort(int array[], int size, unsigned long long &comparisions_count)
{
    int max = array[0];

    for (int i = 1; ++comparisions_count && i < size; i++)
        if (++comparisions_count && array[i] > max)
            max = array[i];

    const int base = 10;

    for (int place = 1; ++comparisions_count && max / place > 0; place *= 10)
    {
        int output[size];
        int count[base] = {0};

        for (int i = 0; ++comparisions_count && i < size; i++)
            count[(array[i] / place) % 10]++;

        for (int i = 1; ++comparisions_count && i < base; i++)
            count[i] += count[i - 1];

        for (int i = size - 1; ++comparisions_count && i >= 0; i--)
        {
            output[count[(array[i] / place) % 10] - 1] = array[i];
            count[(array[i] / place) % 10]--;
        }

        for (int i = 0; ++comparisions_count && i < size; i++)
            array[i] = output[i];
    }
}

// Reference: https://github.com/leduythuccs/Sorting-Algorithms
//

void FlashSort(int array[], int size, unsigned long long &comparisions_count)
{
    if (++comparisions_count && size <= 1)
        return;
    int m = size * 0.43;
    if (++comparisions_count && m <= 2)
        m = 2;
    // int m = size;
    int __L[m] = {0};
    int Mx = array[0], Mn = array[0];
    for (int i = 1; ++comparisions_count && i < size; ++i)
    {
        if (++comparisions_count && Mx < array[i])
            Mx = array[i];
        if (++comparisions_count && Mn > array[i])
            Mn = array[i];
    }
    if (++comparisions_count && Mx == Mn)
        return;
#define getK(x) 1ll * (m - 1) * (x - Mn) / (Mx - Mn)
    for (int i = 0; ++comparisions_count && i < size; ++i)
        ++__L[getK(array[i])];
    for (int i = 1; ++comparisions_count && i < m; ++i)
        __L[i] += __L[i - 1];
    //step 2
    int count = 0;
    int i = 0;
    while (++comparisions_count && count < size)
    {
        int k = getK(array[i]);
        while (++comparisions_count && i >= __L[k])
            k = getK(array[++i]);
        int z = array[i];
        while (++comparisions_count && i != __L[k])
        {
            k = getK(z);
            int y = array[__L[k] - 1];
            array[--__L[k]] = z;
            z = y;
            ++count;
        }
    }
    //step 3
    for (int k = 1; ++comparisions_count && k < m; ++k)
    {
        for (int i = __L[k] - 2; ++comparisions_count && i >= __L[k - 1]; --i)
            if (++comparisions_count && array[i] > array[i + 1])
            {
                int t = array[i], j = i;
                while (++comparisions_count && t > array[j + 1])
                {
                    array[j] = array[j + 1];
                    ++j;
                }
                array[j] = t;
            }
    }
}