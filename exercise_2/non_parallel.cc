#include <iostream>
#include <array>
#include <numeric>
#include <omp.h>

int
main(void)
{
  constexpr uint64_t num_steps = 100'000'000;
  constexpr uint8_t NUM_OF_THREADS = 4;
  constexpr double step = 1.0 / num_steps;

  const double start = omp_get_wtime();

  omp_set_num_threads(NUM_OF_THREADS);
  double sums[NUM_OF_THREADS] = {0.0};
  #pragma omp parallel
  {
    const uint64_t id = omp_get_thread_num();
    for (uint64_t i = id; i < num_steps; i += NUM_OF_THREADS) {
      const double x = (i + 0.5) * step;
      sums[id] += 4.0 / (1.0 + x * x);
    }
  }

  double sum = 0.0;
  for (int i = 0; i < NUM_OF_THREADS; ++i)
    sum += sums[i];

  const double pi = step * sum;
  const double total_time = omp_get_wtime() - start;
  std::cout << pi << "\ntime: " << total_time << '\n';
  return EXIT_SUCCESS;
}
