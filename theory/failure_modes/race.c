#include <omp.h>
#include <stdio.h>

int main(int argc, char** argv) {
    size_t T=8;
    int t_hello[T];
    int i=0;
    for(i=0;i<T;i++) {
        t_hello[i]=-1;
    }
    #pragma omp parallel for
    for(int i=0;i<T;i++) {
        t_hello[i]=omp_get_thread_num();
    }

    for(i=0;i<T;i++) {
        printf("Hello from %d\n",t_hello[i]);
    }

    return 0;
}
    
