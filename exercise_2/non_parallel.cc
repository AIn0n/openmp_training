#include <iostream>
#include <array>
#include <numeric>
#include <omp.h>

double
run_for_id(
  const int id,
  const uint64_t num_steps,
  const int num_of_threads,
  const double step)
{
  double res = 0.0;
  for (uint64_t i = id; i < num_steps; i += num_of_threads) {
    const double x = (i + 0.5) * step;
    res += 4.0 / (1.0 + x * x);
  }
  return res;
}

int
main(void)
{
  constexpr uint64_t num_steps = 100'000'000;
  constexpr double step = 1.0 / num_steps;
  const int NUM_OF_THREADS = 4;

  const double start = omp_get_wtime();

  omp_set_num_threads(NUM_OF_THREADS);
  std::array<double, NUM_OF_THREADS> sums = {0.0};
  #pragma omp parallel
  {
    const int id = omp_get_thread_num();
    sums[id] = run_for_id(id, num_steps, NUM_OF_THREADS, step);
  }

  const double pi = step * std::reduce(sums.begin(), sums.end(), 0.0);;
  const double total_time = omp_get_wtime() - start;
  std::cout << pi << "\ntime: " << total_time << '\n';
  return EXIT_SUCCESS;
}
