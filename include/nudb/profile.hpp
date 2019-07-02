//
// Copyright (c) 2015-2016 Vinnie Falco (vinnie dot falco at gmail dot com)
//               2019 Mo Morsi (mo at devnull dot network)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef NUDB_PROFILE_RUNTIME
#define NUDB_PROFILE_RUNTIME 1
#endif

#if NUDB_PROFILE_RUNTIME

#ifndef NUDB_PROFILE_HPP
#define NUDB_PROFILE_HPP

#include <nudb/detail/mutex.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace nudb {
    const int PROFILE_SAMPLES = 5000;

    enum class profile_op
    {
        insert,
        fetch,
        last
    };

    template<class = void>
    class profile_t {
      public:

        using samples_t = std::map<profile_op, std::vector<int>>;
        using index_t = std::map<profile_op, int>;

        void reset();

        void sample(profile_op);

        double avg(profile_op);

      private:
        boost::shared_mutex m_;

        std::chrono::time_point<std::chrono::steady_clock> start_;
        samples_t samples_;
        index_t index_;
    };

    using profile = profile_t<>;
} // nudb

#include <nudb/impl/profile.ipp>

#endif
#endif
