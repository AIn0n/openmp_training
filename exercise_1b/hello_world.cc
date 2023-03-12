#include <iostream>
#include <omp.h>

int main(void)
{
  #pragma omp parallel
  {
    int ID = 0;
    std::cout << "hello " << ID << '\n';
  }
}