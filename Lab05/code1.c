#include <stdio.h>
#include <string.h>

const char *months[] = {
    "January", "February", "March", "April",
    "May", "June", "July", "August",
    "September", "October", "November", "December"
};

// Function to read monthly sales from an input file
void readSales(float sales[], int n, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the input file.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%f", &sales[i]);
    }

    fclose(file);
}

// Function to generate the sales report
void generateSalesReport(float sales[], int n) {
    printf("Monthly sales report for 2022:\n");
    printf("Month\tSales\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t$%.2f\n", months[i], sales[i]);
    }
}

// Function to generate sales summary
void generateSalesSummary(float sales[], int n) {
    float minSale = sales[0];
    float maxSale = sales[0];
    float totalSales = sales[0];
    int minIndex = 0;
    int maxIndex = 0;

    for (int i = 1; i < n; i++) {
        if (sales[i] < minSale) {
            minSale = sales[i];
            minIndex = i;
        }

        if (sales[i] > maxSale) {
            maxSale = sales[i];
            maxIndex = i;
        }

        totalSales += sales[i];
    }

    printf("Sales summary:\n");
    printf("Minimum sales: $%.2f (%s)\n", minSale, months[minIndex]);
    printf("Maximum sales: $%.2f (%s)\n", maxSale, months[maxIndex]);
    printf("Average sales: $%.2f\n", totalSales / n);
}

// Function to generate six-month moving averages
void generateSixMonthMovingAverage(float sales[], int n) {
    printf("Six-Month Moving Average Report:\n");
    for (int i = 6; i <= n; i++) {
        float sum = 0;
        for (int j = i - 6; j < i; j++) {
            sum += sales[j];
        }
        printf("%s - %s $%.2f\n", months[i - 6], months[i - 1], sum / 6);
    }
}

// Function to generate sales report sorted from highest to lowest
void generateSortedSalesReport(float sales[], int n) {
    // Create a copy of the sales array to sort while preserving the original order
    float sortedSales[n];
    int indices[n];
    memcpy(sortedSales, sales, sizeof(float) * n);

    // Sort the copy of the sales array in descending order and track indices
    for (int i = 0; i < n; i++) {
        indices[i] = i;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (sortedSales[j] > sortedSales[i]) {
                float temp = sortedSales[i];
                sortedSales[i] = sortedSales[j];
                sortedSales[j] = temp;
                int tempIndex = indices[i];
                indices[i] = indices[j];
                indices[j] = tempIndex;
            }
        }
    }

    printf("Sales Report (Highest to Lowest):\n");
    printf("Month\tSales\n");
    for (int i = 0; i < n; i++) {
        int originalIndex = indices[i];
        printf("%s\t$%.2f\n", months[originalIndex], sortedSales[i]);
    }
}

int main() {
    const int n = 12;
    float monthlySales[n];

    readSales(monthlySales, n, "monthly_sales.txt");  // Replace with your input file name

    generateSalesReport(monthlySales, n);
    generateSalesSummary(monthlySales, n);
    generateSixMonthMovingAverage(monthlySales, n);
    generateSortedSalesReport(monthlySales, n);

    return 0;
}