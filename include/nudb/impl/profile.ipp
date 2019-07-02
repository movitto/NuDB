//
// Copyright (c) 2019 Mo Morsi (mo at devnull dot network)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef NUDB_IMPL_PROFILE_IPP
#define NUDB_IMPL_PROFILE_IPP

#include <numeric>

namespace nudb {
   static const int PROFILE_SIZE = (int)profile_op::last * PROFILE_SAMPLES;

   template<class _>
   void profile_t<_>::
   reset(){
      detail::unique_lock_type m{m_};
      start_ = std::chrono::steady_clock::now();
      for(int i = 0; i < (int)profile_op::last; ++i){
        index_[(profile_op)i] = 0;
        samples_[(profile_op)i].reserve(PROFILE_SIZE);
        for(int j = 0; j < PROFILE_SIZE; ++j)
          samples_[(profile_op)i].push_back(0);
      }
    }

   template<class _>
   void profile_t<_>::
   sample(profile_op op){
      detail::unique_lock_type m{m_};
      std::chrono::time_point<std::chrono::steady_clock> now =
        std::chrono::steady_clock::now();
      auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_);
      samples_[op][index_[op]++] = dur.count();
      start_ = now;

      if(index_[op] >= PROFILE_SIZE) index_[op] = 0;
    }

   template<class _>
   double profile_t<_>::
   avg(profile_op op) {
      detail::shared_lock_type m{m_};
      auto samples = samples_[op];
      return std::accumulate(samples.begin(), samples.end(), 0.0) / samples.size();
   }
} // nudb

#endif
