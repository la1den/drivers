#include <stdio.h>

struct t {
    int a;
    double b;
    int *ap;
    
};
int main() {
    
    int i;
    struct t tt;
    printf("i= %d\n", i);
    printf("t.a = %d\n", tt.a);
    printf("t.b = %f\n", tt.b);
    printf("t.ap = %d\n", tt.ap);
    printf("t->ap = %d\n", *tt.ap);
    return 0;
}
