//PROJECT TITLE


//StatMate: Modular Statistical Analyzer in C

// Description of the project

/*StatMate is a modular, menu-driven C program that performs fundamental statistical operations on integer arrays. 
Designed with clarity and educational value in mind, this tool allows users to calculate sum, average, maximum, 
minimum, mode, median, range, product, frequency, search results, variance,
and standard deviation—all implemented manually without using built-in libraries.*/

#include <stdio.h>

// Function Declarations
void arr_read(int *, int);
int arr_sum(int *, int);
float arr_avg(int, int);
int arr_max(int *, int);
int arr_min(int *, int);
void arr_mode(int *, int);
float arr_median(int *, int);
int arr_range(int, int);
long long arr_pro(int *, int);
void sort_array(int *, int);
void arr_frequency(int *, int);
void arr_search(int *, int, int);
float arr_variance(int *, int, float);
float arr_stddev(int *, int, float);
float arr_sqrt(float);


// Main function
int main() 
{
    int n;
    char cont;

    // Display a header with a unique style
    printf("\n***************************************************************\n");
    printf("*                                                             *\n");
    printf("*        🔢 SmartStat: Modular Statistical Analyzer in C      *\n");
    printf("*                                                             *\n");
    printf("***************************************************************\n\n");

    // Input array size
    printf("👉 Please enter the size of the array: ");
    scanf("%d", &n);
    if (n <= 0) 
    {
        printf("❌ Invalid size! Please run the program with a positive integer.\n");
        return 1;
    }

    int arr[n], sorted[n];
    printf("👉 Enter %d integer element(s) separated by space: ", n);
    arr_read(arr, n);

    // Pre-computations
    int sum = arr_sum(arr, n);
    int max = arr_max(arr, n);
    int min = arr_min(arr, n);
    long long product = arr_pro(arr, n);

    // Copy original array for sorting
    for (int i = 0; i < n; i++)
        sorted[i] = arr[i];
    sort_array(sorted, n);

    float average = arr_avg(sum, n);
    float variance = arr_variance(arr, n, average);
    float stddev = arr_stddev(arr, n, average);

    // Main Operation Loop
    do 
    {
        int option;
        printf("\n========================================================\n");
        printf("              ▶ SELECT OPERATION ◀\n");
        printf("========================================================\n");
        printf("  1. Sum\n");
        printf("  2. Average\n");
        printf("  3. Maximum\n");
        printf("  4. Minimum\n");
        printf("  5. Mode\n");
        printf("  6. Median\n");
        printf("  7. Range\n");
        printf("  8. Product\n");
        printf("  9. Frequency Table\n");
        printf(" 10. Search Value\n");
        printf(" 11. Variance\n");
        printf(" 12. Standard Deviation\n");
        printf("--------------------------------------------------------\n");
        printf("👉 Enter your option (1-12): ");
        scanf("%d", &option);

        // Process chosen option
        switch (option) {
            case 1:
                printf("\n🧮 Sum of elements: %d\n", sum);
                break;
            case 2:
                printf("\n📊 Average of elements: %.2f\n", average);
                break;
            case 3:
                printf("\n🔼 Maximum value: %d\n", max);
                break;
            case 4:
                printf("\n🔽 Minimum value: %d\n", min);
                break;
            case 5:
                printf("\n🎯 Mode(s): ");
                arr_mode(arr, n);
                break;
            case 6:
                printf("\n📈 Median value: %.2f\n", arr_median(sorted, n));
                break;
            case 7:
                printf("\n🔄 Range (Max - Min): %d\n", arr_range(max, min));
                break;
            case 8:
                printf("\n✖️ Product of elements: %lld\n", product);
                break;
            case 9:
                printf("\n📋 Frequency Table:\n");
                arr_frequency(arr, n);
                break;
            case 10: 
            {
                int val;
                printf("\n👉 Enter value to search: ");
                scanf("%d", &val);
                arr_search(arr, n, val);
                break;
            }
            case 11:
                printf("\n📉 Variance: %.4f\n", variance);
                break;
            case 12:
                printf("\n📐 Standard Deviation: %.4f\n", stddev);
                break;
            default:
                printf("\n❌ Invalid option! Please choose a number between 1 and 12.\n");
        }

        // Validate response for repeating operation
        do {
            printf("\n🔄 Do you want to perform another operation? (y/n): ");
            scanf(" %c", &cont);
            if (cont != 'y' && cont != 'Y' && cont != 'n' && cont != 'N') 
            {
                printf("❌ Invalid input! Please enter 'y' or 'n'.\n");
            }
        } while (cont != 'y' && cont != 'Y' && cont != 'n' && cont != 'N');

    } while (cont == 'y' || cont == 'Y');

    printf("\n✅ Thank you for using SmartStat! Stay curious & keep analyzing! 📊\n");
    printf("***************************************************************\n");
    return 0;
}

// ---------- Function Definitions ----------

void arr_read(int *arr, int n) 
{
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
}

int arr_sum(int *arr, int n) 
{
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    return sum;
}

float arr_avg(int sum, int n) 
{
    return (float)sum / n;
}

int arr_max(int *arr, int n) 
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

int arr_min(int *arr, int n) 
{
    int min = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] < min)
            min = arr[i];
    return min;
}

void arr_mode(int *arr, int n) 
{
    if (n == 0) 
    {
        printf("❌ Array is empty. Mode cannot be determined.\n");
        return;
    }

    int freq[n], printed[n];
    for (int i = 0; i < n; i++) 
    {
        freq[i] = 1;
        printed[i] = 0;
    }

    // Calculate frequency for each element
    for (int i = 0; i < n; i++) 
    {
        if (!printed[i]) 
        {
            for (int j = i + 1; j < n; j++) 
            {
                if (arr[i] == arr[j]) 
                {
                    freq[i]++;
                    printed[j] = 1;
                }
            }
        }
    }

    int max_count = 0;
    for (int i = 0; i < n; i++)
        if (!printed[i] && freq[i] > max_count)
            max_count = freq[i];

    // Output mode(s)
    for (int i = 0; i < n; i++) 
    {
        if (!printed[i] && freq[i] == max_count) 
        {
            printf("%d ", arr[i]);
            printed[i] = 1;
        }
    }
    printf("\n");
}

float arr_median(int *sorted, int n) 
{
    if (n % 2 == 1)
        return sorted[n / 2];
    else
        return (sorted[n / 2] + sorted[n / 2 - 1]) / 2.0;
}

int arr_range(int max, int min) 
{
    return max - min;
}

long long arr_pro(int *arr, int n) 
{
    long long pro = 1;
    for (int i = 0; i < n; i++)
        pro *= arr[i];
    return pro;
}

void sort_array(int *arr, int n) 
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) 
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

void arr_frequency(int *arr, int n) 
{
    int printed[n];
    for (int i = 0; i < n; i++)
        printed[i] = 0;

    for (int i = 0; i < n; i++) 
    {
        if (!printed[i]) 
        {
            int count = 1;
            for (int j = i + 1; j < n; j++) 
            {
                if (arr[i] == arr[j]) 
                {
                    count++;
                    printed[j] = 1;
                }
            }
            printf("   ➤ Value %d appears %d time(s).\n", arr[i], count);
        }
    }
}

void arr_search(int *arr, int n, int target) 
{
    int found = 0;
    printf("🔍 Positions of %d: ", target);
    for (int i = 0; i < n; i++) 
    {
        if (arr[i] == target) 
        {
            printf("%d ", i);
            found = 1;
        }
    }
    if (!found)
        printf("Not found.");
    printf("\n");
}

float arr_variance(int *arr, int n, float avg) 
{
    float var = 0;
    for (int i = 0; i < n; i++)
        var += (arr[i] - avg) * (arr[i] - avg);
    return var / n;
}

float arr_stddev(int *arr, int n, float avg) 
{

    float var = arr_variance(arr, n, avg);
    return arr_sqrt(var);
}

float arr_sqrt(float x) 
{
    if (x <= 0)
        return 0;
    float guess = x / 2.0;
    for (int i = 0; i < 10; i++)
        guess = (guess + x / guess) / 2.0;
    return guess;
}
