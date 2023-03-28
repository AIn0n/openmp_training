#include <iostream>
#include <array>
#include <numeric>
#include <omp.h>

constexpr uint64_t num_steps = 100'000'000;
constexpr uint8_t NUM_OF_THREADS = 4;
double step;

int
main(void)
{
  const double start = omp_get_wtime();
  omp_set_num_threads(NUM_OF_THREADS);
  
  double pi;
  std::array<double, NUM_OF_THREADS> sums = {0.0};

  step = 1.0 / num_steps;
  #pragma omp parallel
  {
    const int id = omp_get_thread_num();
    for (uint64_t i = id; i < num_steps; i = i + NUM_OF_THREADS) {
      const double x = (i + 0.5) * step;
      sums[id] += 4.0 / (1.0 + x * x);
    }
  }

  pi = step * std::reduce(sums.begin(), sums.end(), 0.0);
  std::cout << pi << "\ntime: " << omp_get_wtime() - start << '\n';
  return EXIT_SUCCESS;
}
