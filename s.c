#include<stdio.h>
#include<limits.h>

void northwestCornerMethod(int m, int n, int supply[], int demand[], int allocation[][100], int *numAllocations) {
    int i = 0, j = 0;
    *numAllocations = 0;
    while (i < m && j < n) {
        if (supply[i] < demand[j]) {
            allocation[i][j] = supply[i];
            demand[j] -= supply[i];
            supply[i] = 0;
            i++;
        } else {
            allocation[i][j] = demand[j];
            supply[i] -= demand[j];
            demand[j] = 0;
            j++;
        }
        (*numAllocations)++;
    }
}

void calculatePotentials(int m, int n, int cost[][100], int allocation[][100], int u[], int v[]) {
    for (int i = 0; i < m; i++) u[i] = INT_MIN;
    for (int j = 0; j < n; j++) v[j] = INT_MIN;

    u[0] = 0; // Start with u[0] = 0
    for (int k = 0; k < m + n - 1; k++) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (allocation[i][j] > 0) {
                    if (u[i] != INT_MIN && v[j] == INT_MIN) {
                        v[j] = cost[i][j] - u[i];
                    } else if (v[j] != INT_MIN && u[i] == INT_MIN) {
                        u[i] = cost[i][j] - v[j];
                    }
                }
            }
        }
    }
}

void calculateDeltas(int m, int n, int cost[][100], int allocation[][100], int u[], int v[], int delta[][100]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (allocation[i][j] == 0) { // Only calculate for unallocated cells
                delta[i][j] = cost[i][j] - (u[i] + v[j]);
            } else {
                delta[i][j] = INT_MAX; // Ignore allocated cells
            }
        }
    }
}

void findMinimumDelta(int m, int n, int delta[][100], int *minI, int *minJ) {
    int minDelta = INT_MAX;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (delta[i][j] < minDelta) {
                minDelta = delta[i][j];
                *minI = i;
                *minJ = j;
            }
        }
    }
}

void adjustAllocations(int m, int n, int allocation[][100], int i, int j) {
    // Implement the adjustment logic for stepping stone paths
    // (This part involves constructing a loop and redistributing allocations.)
}

int isOptimal(int m, int n, int delta[][100]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (delta[i][j] < 0) return 0; // Not optimal
        }
    }
    return 1; // Optimal
}

void printMatrix(int m, int n, int matrix[][100], const char *title) {
    printf("\n%s:\n", title);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%5d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int calculateTotalCost(int m, int n, int cost[][100], int allocation[][100]) {
    int totalCost = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (allocation[i][j] > 0) {
                totalCost += allocation[i][j] * cost[i][j];
            }
        }
    }
    return totalCost;
}

int main() {
    int m, n;
    printf("Enter the number of sources: ");
    scanf("%d", &m);
    printf("Enter the number of destinations: ");
    scanf("%d", &n);

    int cost[100][100], supply[100], demand[100];
    printf("Enter the cost matrix (%d x %d):\n", m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }
    printf("Enter the supply array (%d elements):\n", m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &supply[i]);
    }
    printf("Enter the demand array (%d elements):\n", n);
    for (int j = 0; j < n; j++) {
        scanf("%d", &demand[j]);
    }

    int allocation[100][100] = {0};
    int numAllocations = 0;
    northwestCornerMethod(m, n, supply, demand, allocation, &numAllocations);

    printMatrix(m, n, allocation, "Initial Allocation Matrix");
    int initialCost = calculateTotalCost(m, n, cost, allocation);
    printf("\nInitial Total Transportation Cost: %d\n", initialCost);

    int u[100], v[100], delta[100][100];
    while (1) {
        calculatePotentials(m, n, cost, allocation, u, v);
        calculateDeltas(m, n, cost, allocation, u, v, delta);
        if (isOptimal(m, n, delta)) break;

        int minI, minJ;
        findMinimumDelta(m, n, delta, &minI, &minJ);
        adjustAllocations(m, n, allocation, minI, minJ);
    }

    printMatrix(m, n, allocation, "Optimal Allocation Matrix");
    int finalCost = calculateTotalCost(m, n, cost, allocation);
    printf("\nFinal Total Transportation Cost: %d\n", finalCost);

    return 0;
}