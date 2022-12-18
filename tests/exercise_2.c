#include <stdio.h>
#include <stdlib.h>

typedef struct Complex_st {
    double real;
    double imag;
} Complex;

typedef struct Complex_Set_st {
    double num_points_in_set;
    Complex *points;
} ComplexSet;

ComplexSet *AllocSet(Complex c_arr[], int size) {
    ComplexSet *set = (ComplexSet *)malloc(sizeof(ComplexSet));
    set->points = (Complex *) malloc(sizeof(Complex)*size);
    set->num_points_in_set = size;
    for (int i=0; i<size; i++) {
        set->points[i].real = c_arr[i].real;
        set->points[i].imag = c_arr[i].imag;
    }
    return set;
}

void FreeSet(ComplexSet *set) {
    free(set->points);
    free(set);
}

int main(int argc, char *argv[]) {
    Complex a[] = {{1.0, 2.0}, {3.0, 4.5}, {5.0, 6.0}};
    ComplexSet *set = AllocSet(a, 3);
    for (int i=0; i<set->num_points_in_set; i++) {
        printf("Set Element %d: (%.2f, i%.2f)\n", i, set->points[i].real, set->points[i].imag);
    }
    FreeSet(set);
    return 0;
}
