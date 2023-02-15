#include <stdio.h>
#include <stdlib.h>

int main()
{
    long int fact(int*);
    int *n;
    long int f;

    n = (int*) malloc(sizeof(int)); // Tambah malloc
    printf("Enter a number: "); // cout dalam c
    scanf("%d", n); // cin dalam c
    f = fact(n);
    printf("Factorial is %ld\n", f); // cout dalam c
    free(n); // free memory yang dialokasi secara dinamis
    return 0;
}

long int fact(int* p)
{
    int i;
    long int f = 1;
    for(i = 1; i <= *p; i++)
        f *= i;
    return (f);
}