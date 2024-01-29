#include <iostream>
using namespace std;

void MaxHeapify(int a[], int i, int n)
{
    int j, temp;
    temp = a[i];
    j = 2 * i;
    while (j <= n)
    {
        if (j < n && a[j + 1] > a[j])
            j = j + 1;
        if (temp > a[j])
            break;
        else if (temp <= a[j])
        {
            a[j / 2] = a[j];
            j = 2 * j;
        }
    }
    a[j / 2] = temp;
}

void MinHeapify(int a[], int i, int n)
{
    int j, temp;
    temp = a[i];
    j = 2 * i;
    while (j <= n)
    {
        if (j < n && a[j + 1] < a[j])
            j = j + 1;
        if (temp < a[j])
            break;
        else if (temp >= a[j])
        {
            a[j / 2] = a[j];
            j = 2 * j;
        }
    }
    a[j / 2] = temp;
}

void MaxHeapSort(int a[], int n)
{
    int i, temp;
    for (i = n; i >= 2; i--)
    {
        temp = a[i];
        a[i] = a[1];
        a[1] = temp;
        MaxHeapify(a, 1, i - 1);
    }
}

void MinHeapSort(int a[], int n)
{
    int i, temp;
    for (i = n; i >= 2; i--)
    {
        temp = a[i];
        a[i] = a[1];
        a[1] = temp;
        MinHeapify(a, 1, i - 1);
    }
}

void Build_MaxHeap(int a[], int n)
{
    int i;
    for (i = n / 2; i >= 1; i--)
        MaxHeapify(a, i, n);
}

void Build_MinHeap(int a[], int n)
{
    int i;
    for (i = n / 2; i >= 1; i--)
        MinHeapify(a, i, n);
}

int main()
{
    int n, i;
    cout << "\nEnter number of subjects of second year: ";
    cin >> n;
    n++;
    int arr[n];

    // Take input marks for all subjects
    for (i = 1; i < n; i++)
    {
        cout << "Enter the marks " << i << ": ";
        cin >> arr[i];
    }

    Build_MaxHeap(arr, n - 1); // build maximum heap
    cout << "\nPrint array after building MaxHeap :: ";
    for (i = 1; i < n; i++)
        cout << " " << arr[i];

    MaxHeapSort(arr, n - 1); // Apply max heap sort
    int max, min;
    cout << "\n\nSorted Data : ASCENDING : ";
    for (i = 1; i < n; i++) // Print the array
        cout << " " << arr[i];
    min = arr[1];

    Build_MinHeap(arr, n - 1); // build minimum heap
    cout << "\n\nPrint array after building MinHeap :: ";
    for (i = 1; i < n; i++)
        cout << " " << arr[i];

    MinHeapSort(arr, n - 1); // apply min heap sort
    cout << "\n\nSorted Data : DESCENDING: ";
    max = arr[1];
    for (i = 1; i < n; i++) // Print the array
        cout << " " << arr[i];

    cout << "\n\nMaximum Marks : " << max << "\nMinimum marks : " << min;

    return 0;
}
