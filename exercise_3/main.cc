#include <iostream>
#include <array>
#include <numeric>
#include <omp.h>

int
main(void)
{
  constexpr uint64_t num_steps = 100'000'000;
  constexpr double step = 1.0 / num_steps;
  const int NUM_OF_THREADS = 4;

  const double start = omp_get_wtime();

  omp_set_num_threads(NUM_OF_THREADS);
  double sum = 0.0;
  #pragma omp parallel
  {
    const int id = omp_get_thread_num();
    for (uint64_t i = id; i < num_steps; i += NUM_OF_THREADS) {
      const double x = (i + 0.5) * step;
      const double res = 4.0 / (1.0 + x * x);
  #pragma omp atomic
      sum += res;
    }
  }

  const double pi = step * sum;
  const double total_time = omp_get_wtime() - start;
  std::cout << pi << "\ntime: " << total_time << '\n';
  return EXIT_SUCCESS;
}
