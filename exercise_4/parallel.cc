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
  #pragma omp parallel for reduction(+:sum)
  for (uint64_t i = 0; i < num_steps; ++i) {
    const double x = (i + 0.5) * step;
    sum += 4.0 / (1.0 + x * x);
  }

  const double pi = step * sum;
  const double total_time = omp_get_wtime() - start;
  std::cout << pi << "\ntime: " << total_time << '\n';
  return EXIT_SUCCESS;
}
