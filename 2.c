#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int** num, int size);
int main(void) {
    FILE* file1;
    FILE* file2;

    file1 = fopen("graph1.dot", "w");
    file2 = fopen("graph2.dot", "w");
    fprintf(file1, "graph g {\n");
    fprintf(file2, "graph g {\n");

    int v_count = 0;
    printf("Enter the number of vertices in the graph: ");
    scanf_s("%d", &v_count);
    for (int i = 0; i < v_count; ++i) {
        fprintf(file1, "%d;\n", i + 1);
        fprintf(file2, "%d;\n", i + 1);
    }

    printf("Enter the adjacency matrix of a %d by %d graph:\n", v_count, v_count);
    int** v_arr = (int**)malloc(v_count * sizeof(int*));
    for (int i = 0; i < v_count; ++i) {
        v_arr[i] = (int*)malloc(v_count * sizeof(int));
        for (int j = 0; j < v_count; ++j) {
            scanf_s("%d", &v_arr[i][j]);
            if (j >= i) {
                int sup = v_arr[i][j];
                while (sup > 0) {
                    fprintf(file1, "%d -- %d;\n", i + 1, j + 1);
                    sup--;
                }
            }
        }
    }

    fprintf(file1, "}\n");

    int v1 = 0, v2 = 0;

    printf("Enter the edge you want to delete:");

    scanf_s("%d%d", &v1, &v2);
    v1--;
    v2--;
    v_arr[v1][v2]--;
    v_arr[v2][v1]--;

    for (int i = 0; i < v_count; ++i) {

        for (int j = i; j < v_count; ++j) {

            int sup = v_arr[i][j];
            while (sup > 0) {
                fprintf(file2, "%d -- %d;\n", i + 1, j + 1);
                sup--;
            }
        }
    }

    fprintf(file2, "}\n");

    int** degree_ed_arr = (int**)malloc(v_count * sizeof(int*));

    for (int i = 0; i < v_count; ++i) {
        degree_ed_arr[i] = malloc(sizeof(int) * 2);
        degree_ed_arr[i][1] = i;
    }

    for (int i = 0; i < v_count; ++i) {

        degree_ed_arr[i][0] = 0;

        for (int j = 0; j < v_count; ++j) {

            degree_ed_arr[i][0] += v_arr[i][j];
        }
    }

    bubbleSort(degree_ed_arr, 8);

    for (int i = 0; i < v_count; ++i) {

        printf("Vertex number %d has degree %d\n", degree_ed_arr[i][1] + 1, degree_ed_arr[i][0]);

    }

    for (int i = 0; i < v_count; ++i) {

        free(v_arr[i]);
    }

    fclose(file1);
    fclose(file2);
    system("dot -Tpng graph1.dot -o graph1.png");
    system("graph1.png");
    system("dot -Tpng graph2.dot -o graph2.png");
    system("graph2.png");

    return 0;
}

void swap(int* val1, int* val2) {
    int tmp;
    tmp = *val1;
    *val1 = *val2;
    *val2 = tmp;
}

void bubbleSort(int** num, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = (size - 1); j > i; j--)
        {
            if (num[j][0] < num[j - 1][0])
            {
                swap(&num[j - 1][0], &num[j][0]);
                swap(&num[j - 1][1], &num[j][1]);
                /*int temp1 = num[j - 1][0];
                int temp2 = num[j - 1][1];
                num[j - 1][0] = num[j][0];
                num[j - 1][1] = num[j][1];
                num[j][0] = temp1;
                num[j][1] = temp2;*/
            }
        }
    }
}