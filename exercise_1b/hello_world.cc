#include <iostream>
#include <omp.h>

int main(void)
{
  #pragma omp parallel
  {
    int ID = omp_get_thread_num();
    std::cout << "hello " << ID << '\n';
  }
}