#include <omp.h>

#include "helper.h"
#include "homework/trap_integral.h"

// #ifdef _OPENMP
// #include <omp.h>
// #endif

namespace homework::trap_integral {

TrapIntegralDataTypeImp ompImp(int num_threads,
                               const TrapIntegralTaskImp &task) {
  // #ifndef _OPENMP
  //   std::cout << "Warning: OpenMP is not enabled\n";
  // #endif

  using DataType = TrapIntegralDataTypeImp;
  using TaskType = TrapIntegralTaskImp;
  using ResultType = TrapIntegralResultImp;

  DataType res = 0;

#pragma omp parallel num_threads(num_threads)
  {
    // #ifdef _OPENMP
    //     int my_rank = omp_get_thread_num();
    // #else
    //     int my_rank = 0;
    // #endif

    int my_rank = omp_get_thread_num();
    auto h = (task.r() - task.l()) / task.n();
    std::size_t local_l;
    std::size_t local_r;
    auto n = task.n();
    distributeTask(my_rank, num_threads, n, &local_l, &local_r);
    auto local_res = serialImp(
        task.l() + local_l * h, task.l() + local_r * h, local_r - local_l,
        [](DataType x) { return givenFuncDerivative(x); });

#pragma omp critical
    { res += local_res; }
  }

  return res;
}
}  // namespace homework::trap_integral
