/*******************************************************************************
* Copyright 2018 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#ifndef MKLDNN_THREAD_PARALLEL_ND_HPP
#define MKLDNN_THREAD_PARALLEL_ND_HPP

/* This header must be included by mkldnn_thread.hpp only */

/* Functions:
 *  - parallel(nthr, f)              - executes f in parallel using at most
 *                                     nthr threads. If nthr equals 0
 *                                     mkldnn_get_max_threads() threads is
 *                                     used
 *  - for_nd(ithr, nthr, dims..., f) - multidimensional for loop for already
 *                                     created threads
 *  - parallel_nd(dims..., f)        - creates a parallel section and then
 *                                     calls for_nd
 *  - parallel_nd_in_omp(dims..., f) - queries current nthr and ithr and then
 *                                     calls for_nd (mostly for convenience)
 */

namespace mkldnn {
namespace impl {

/* general parallelization */
void parallel(int nthr, size_t work_amount, const std::function<void(size_t, size_t)>& f);

void parallel(int nthr, const std::function<void(size_t, size_t)>& f);

/* for_nd section */

template <typename T0>
void for_nd(const int ithr, const int nthr, const T0 &D0, const std::function<void(size_t)>& f) {
    T0 start{0}, end{0};
    balance211(D0, nthr, ithr, start, end);
    for (T0 d0 = start; d0 < end; ++d0) f(d0);
}

template <typename T0, typename T1>
void for_nd(const int ithr, const int nthr, const T0 &D0, const T1 &D1, const std::function<void(size_t, size_t)>& f) {
    const size_t work_amount = (size_t)D0 * D1;
    if (work_amount == 0) return;
    size_t start{0}, end{0};
    balance211(work_amount, nthr, ithr, start, end);

    T0 d0{0}; T1 d1{0};
    utils::nd_iterator_init(start, d0, D0, d1, D1);
    for (size_t iwork = start; iwork < end; ++iwork) {
        f(d0, d1);
        utils::nd_iterator_step(d0, D0, d1, D1);
    }
}

template <typename T0, typename T1, typename T2>
void for_nd(const int ithr, const int nthr, const T0 &D0, const T1 &D1,
        const T2 &D2, const std::function<void(size_t, size_t, size_t)>& f) {
    const size_t work_amount = (size_t)D0 * D1 * D2;
    if (work_amount == 0) return;
    size_t start{0}, end{0};
    balance211(work_amount, nthr, ithr, start, end);

    T0 d0{0}; T1 d1{0}; T2 d2{0};
    utils::nd_iterator_init(start, d0, D0, d1, D1, d2, D2);
    for (size_t iwork = start; iwork < end; ++iwork) {
        f(d0, d1, d2);
        utils::nd_iterator_step(d0, D0, d1, D1, d2, D2);
    }
}

template <typename T0, typename T1, typename T2, typename T3>
void for_nd(const int ithr, const int nthr, const T0 &D0, const T1 &D1,
        const T2 &D2, const T3 &D3, const std::function<void(size_t, size_t, size_t, size_t)>& f) {
    const size_t work_amount = (size_t)D0 * D1 * D2 * D3;
    if (work_amount == 0) return;
    size_t start{0}, end{0};
    balance211(work_amount, nthr, ithr, start, end);

    T0 d0{0}; T1 d1{0}; T2 d2{0}; T3 d3{0};
    utils::nd_iterator_init(start, d0, D0, d1, D1, d2, D2, d3, D3);
    for (size_t iwork = start; iwork < end; ++iwork) {
        f(d0, d1, d2, d3);
        utils::nd_iterator_step(d0, D0, d1, D1, d2, D2, d3, D3);
    }
}

template <typename T0, typename T1, typename T2, typename T3, typename T4>
void for_nd(const int ithr, const int nthr, const T0 &D0, const T1 &D1,
        const T2 &D2, const T3 &D3, const T4 &D4, const std::function<void(size_t, size_t, size_t, size_t, size_t)>& f) {
    const size_t work_amount = (size_t)D0 * D1 * D2 * D3 * D4;
    if (work_amount == 0) return;
    size_t start{0}, end{0};
    balance211(work_amount, nthr, ithr, start, end);

    T0 d0{0}; T1 d1{0}; T2 d2{0}; T3 d3{0}; T4 d4{0};
    utils::nd_iterator_init(start, d0, D0, d1, D1, d2, D2, d3, D3, d4, D4);
    for (size_t iwork = start; iwork < end; ++iwork) {
        f(d0, d1, d2, d3, d4);
        utils::nd_iterator_step(d0, D0, d1, D1, d2, D2, d3, D3, d4, D4);
    }
}

template <typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5>
void for_nd(const int ithr, const int nthr, const T0 &D0, const T1 &D1,
        const T2 &D2, const T3 &D3, const T4 &D4, const T5 &D5, const std::function<void(size_t, size_t, size_t, size_t, size_t, size_t)>& f) {
    const size_t work_amount = (size_t)D0 * D1 * D2 * D3 * D4 * D5;
    if (work_amount == 0) return;
    size_t start{0}, end{0};
    balance211(work_amount, nthr, ithr, start, end);

    T0 d0{0}; T1 d1{0}; T2 d2{0}; T3 d3{0}; T4 d4{0}; T5 d5{0};
    utils::nd_iterator_init(start, d0, D0, d1, D1, d2, D2, d3, D3, d4, D4,
            d5, D5);
    for (size_t iwork = start; iwork < end; ++iwork) {
        f(d0, d1, d2, d3, d4, d5);
        utils::nd_iterator_step(d0, D0, d1, D1, d2, D2, d3, D3, d4, D4, d5, D5);
    }
}

// Skip a lambda function in the parameter pack.
template <typename T>
constexpr size_t get_work_amount(const T &v) { return 1; }
template <typename T, typename ...Args>
constexpr size_t get_work_amount(const T &v, Args &&...args)
{ return (size_t)v * get_work_amount(utils::forward<Args>(args)...); }

/* parallel_nd and parallel_nd_in_omp section */

#if (MKLDNN_THR != MKLDNN_THR_TBB && MKLDNN_THR != MKLDNN_THR_TBB_AUTO)
template <typename ...Args>
void parallel_nd(Args &&...args) {
#if MKLDNN_THR == MKLDNN_THR_SEQ
    for_nd(0, 1, utils::forward<Args>(args)...);
#elif MKLDNN_THR == MKLDNN_THR_OMP
    const bool do_parallel = get_work_amount(utils::forward<Args>(args)...) > 1;
#   pragma omp parallel if (do_parallel)
    {
        const int nthr = !do_parallel ? 1 : mkldnn_get_num_threads();
        const int ithr = !do_parallel ? 0 : mkldnn_get_thread_num();
        for_nd(ithr, nthr, utils::forward<Args>(args)...);
    }
#endif
}
#else // MKLDNN_THR != MKLDNN_THR_TBB && MKLDNN_THR != MKLDNN_THR_TBB_AUTO

// gcc 4.8 has a bug with passing parameter pack to lambdas.
// So have to explicitly instantiate all the cases.

template <typename T0>
void parallel_nd(const T0 &D0, const std::function<void(size_t)>& f) {
#if MKLDNN_THR == MKLDNN_THR_TBB
    int nthr = mkldnn_get_max_threads();
    size_t work_amount = D0;
    if (work_amount < (size_t)nthr)
        nthr = (int)work_amount;
    if (nthr == 1) {
        for_nd(0, 1, D0, f);
    } else {
        tbb::parallel_for(0, nthr, [&](int ithr) {
            for_nd(ithr, nthr, D0, f);
        }, tbb::static_partitioner());
    }
#elif MKLDNN_THR == MKLDNN_THR_TBB_AUTO
    const int nthr = mkldnn_get_max_threads();
    tbb::parallel_for(0, nthr, [&](int ithr) {
        for_nd(ithr, nthr, D0, f);
    });
#endif
}

template <typename T0, typename T1>
void parallel_nd(const T0 &D0, const T1 &D1, const std::function<void(size_t, size_t)>& f) {
#if MKLDNN_THR == MKLDNN_THR_TBB
    int nthr = mkldnn_get_max_threads();
    size_t work_amount = D0 * D1;
    if (work_amount < (size_t)nthr)
        nthr = (int)work_amount;
    if (nthr == 1) {
        for_nd(0, 1, D0, D1, f);
    } else {
        tbb::parallel_for(0, nthr, [&](int ithr) {
            for_nd(ithr, nthr, D0, D1, f);
        }, tbb::static_partitioner());
    }
#elif MKLDNN_THR == MKLDNN_THR_TBB_AUTO
    const int nthr = mkldnn_get_max_threads();
    tbb::parallel_for(0, nthr, [&](int ithr) {
        for_nd(ithr, nthr, D0, D1, f);
    });
#endif
}

template <typename T0, typename T1, typename T2>
void parallel_nd(const T0 &D0, const T1 &D1, const T2 &D2, const std::function<void(size_t, size_t, size_t)>& f) {
#if MKLDNN_THR == MKLDNN_THR_TBB
    int nthr = mkldnn_get_max_threads();
    size_t work_amount = D0 * D1 * D2;
    if (work_amount < (size_t)nthr)
        nthr = (int)work_amount;
    if (nthr == 1) {
        for_nd(0, 1, D0, D1, D2, f);
    } else {
        tbb::parallel_for(0, nthr, [&](int ithr) {
            for_nd(ithr, nthr, D0, D1, D2, f);
        }, tbb::static_partitioner());
    }
#elif MKLDNN_THR == MKLDNN_THR_TBB_AUTO
    const int nthr = mkldnn_get_max_threads();
    tbb::parallel_for(0, nthr, [&](int ithr) {
        for_nd(ithr, nthr, D0, D1, D2, f);
    });
#endif
}

template <typename T0, typename T1, typename T2, typename T3>
void parallel_nd(const T0 &D0, const T1 &D1, const T2 &D2, const T3 &D3, const std::function<void(size_t, size_t, size_t, size_t)>& f) {
#if MKLDNN_THR == MKLDNN_THR_TBB
    int nthr = mkldnn_get_max_threads();
    size_t work_amount = D0 * D1 * D2 * D3;
    if (work_amount < (size_t)nthr)
        nthr = (int)work_amount;
    if (nthr == 1) {
        for_nd(0, 1, D0, D1, D2, D3, f);
    } else {
        tbb::parallel_for(0, nthr, [&](int ithr) {
            for_nd(ithr, nthr, D0, D1, D2, D3, f);
        }, tbb::static_partitioner());
    }
#elif MKLDNN_THR == MKLDNN_THR_TBB_AUTO
    const int nthr = mkldnn_get_max_threads();
    tbb::parallel_for(0, nthr, [&](int ithr) {
        for_nd(ithr, nthr, D0, D1, D2, D3, f);
    });
#endif
}

template <typename T0, typename T1, typename T2, typename T3, typename T4>
void parallel_nd(const T0 &D0, const T1 &D1, const T2 &D2, const T3 &D3,
        const T4 &D4, const std::function<void(size_t, size_t, size_t, size_t, size_t)>& f) {
#if MKLDNN_THR == MKLDNN_THR_TBB
    int nthr = mkldnn_get_max_threads();
    size_t work_amount = D0 * D1 * D2 * D3 * D4;
    if (work_amount < (size_t)nthr)
        nthr = (int)work_amount;
    if (nthr == 1) {
        for_nd(0, 1, D0, D1, D2, D3, D4, f);
    } else {
        tbb::parallel_for(0, nthr, [&](int ithr) {
            for_nd(ithr, nthr, D0, D1, D2, D3, D4, f);
        }, tbb::static_partitioner());
    }
#elif MKLDNN_THR == MKLDNN_THR_TBB_AUTO
    const int nthr = mkldnn_get_max_threads();
    tbb::parallel_for(0, nthr, [&](int ithr) {
        for_nd(ithr, nthr, D0, D1, D2, D3, D4, f);
    });
#endif
}

template <typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5>
void parallel_nd(const T0 &D0, const T1 &D1, const T2 &D2, const T3 &D3,
        const T4 &D4, const T5 &D5, const std::function<void(size_t, size_t, size_t, size_t, size_t, size_t)>& f) {
#if MKLDNN_THR == MKLDNN_THR_TBB
    int nthr = mkldnn_get_max_threads();
    size_t work_amount = D0 * D1 * D2 * D3 * D4 * D5;
    if (work_amount < (size_t)nthr)
        nthr = (int)work_amount;
    if (nthr == 1) {
        for_nd(0, 1, D0, D1, D2, D3, D4, D5, f);
    } else {
        tbb::parallel_for(0, nthr, [&](int ithr) {
            for_nd(ithr, nthr, D0, D1, D2, D3, D4, D5, f);
        }, tbb::static_partitioner());
    }
#elif MKLDNN_THR == MKLDNN_THR_TBB_AUTO
    const int nthr = mkldnn_get_max_threads();
    tbb::parallel_for(0, nthr, [&](int ithr) {
        for_nd(ithr, nthr, D0, D1, D2, D3, D4, D5, f);
    });
#endif
}
#endif

template <typename ...Args>
void parallel_nd_in_omp(Args &&...args) {
#if MKLDNN_THR == MKLDNN_THR_SEQ
    for_nd(0, 1, utils::forward<Args>(args)...);
#elif MKLDNN_THR == MKLDNN_THR_OMP
    for_nd(mkldnn_get_thread_num(), mkldnn_get_num_threads(),
            utils::forward<Args>(args)...);
#elif (MKLDNN_THR == MKLDNN_THR_TBB || MKLDNN_THR == MKLDNN_THR_TBB_AUTO)
    assert(!"unsupported parallel_nd_in_omp()");
#endif
}

} // namespace impl
} // namespace mkldnn

#endif