#include <iostream>
#include <omp.h>
#include <climits>

using namespace std;

void min_reduction(int arr[], int n)
{
    int min_value = INT_MAX;

#pragma omp parallel for reduction(min : min_value)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < min_value)
            min_value = arr[i];
    }

    cout << "Minimum value: " << min_value << endl;
}

void max_reduction(int arr[], int n)
{
    int max_value = INT_MIN;

#pragma omp parallel for reduction(max : max_value)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max_value)
            max_value = arr[i];
    }

    cout << "Maximum value: " << max_value << endl;
}

void sum_reduction(int arr[], int n)
{
    int sum = 0;

#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }

    cout << "Sum: " << sum << endl;
}

void avg_reduction(int arr[], int n)
{
    int sum = 0;

#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }

    cout << "Average: " << (double)sum / n << endl;
}

int main()
{
    int n = 0;

    cout << "\nEnter number of elements: ";
    cin >> n;

    int arr[n];

    cout << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "Element " << i + 1 << ": ";
        cin >> arr[i];
    }

    cout << endl;

    min_reduction(arr, n);
    max_reduction(arr, n);
    sum_reduction(arr, n);
    avg_reduction(arr, n);

    return 0;
}
