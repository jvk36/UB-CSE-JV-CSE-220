#include <stdio.h> 
  
int main() 
{ 
  
    // Pointer to an array of five numbers 
    int (*a)[5];
//    int *a;
  
    int b[5] = { 1, 2, 3, 4, 5 }; 
  
    int i = 0; 
  
    // Points to the whole array b 
    a = &b; // if a were of type 'int *', then a = b would make a point to b[0].
  
    for (i = 0; i < 5; i++)   
        printf("%d\n", *(*a + i));

    // array of pointers to integers
    int *c[5];
    for (i = 0; i<5; i++){
        c[i] = b+i;
    }
        
    for (i = 0; i < 5; i++)   
        printf("%d\n", *c[i]); /* c[i] dereferences the value at address c+i which is a pointer
                                  to an integer and so *c[i] is the integer. But, *(c+i) is the 
                                  address at c+i and so *(c+i)is the pointer
                                  stored at that address. As such *(c+i) and *c[i] are not the 
                                  same. *c[i] is synonymous to **(c+i) 
                               */
    
      
    return 0; 
}

