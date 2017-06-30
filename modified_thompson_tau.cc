//
// Modified Thompson tau method library for removing outliers 2017-06-30.15
// https://github.com/trueroad/modified_thompson_tau/
//
// Copyright (C) 2017 Masamichi Hosoda. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY AUTHOR AND CONTRIBUTORS ``AS IS'' AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.
//

#include "modified_thompson_tau.hh"

#include<algorithm>
#include<iterator>
#include<limits>
#include<map>
#include<numeric>
#include<vector>

#ifdef DEBUG_MODIFIED_THOMPSON_TAU
#include<iostream>
#endif

#include<cmath>
#include<cstddef>

#include "tau_table/tau_table.hh"

namespace
{
  template <typename T>
  T square (T a)
  {
    return a * a;
  }

  inline std::size_t count (const std::vector<double> &v)
  {
    return std::count_if (v.begin (), v.end (),
                          [] (double x)
                          {
                            return !std::isnan (x);
                          });
  }

  inline double average (const std::vector<double> &v)
  {
    auto cnt {count (v)};

    return std::accumulate (v.begin (), v.end (), 0.0,
                            [cnt] (double a, double b)
                            {
                              return std::isnan (b) ?
                                a :
                                (a + b / cnt);
                            });
  }

  inline double variance (const std::vector<double> &v)
  {
    auto cnt {count (v)};
    auto ave {average (v)};

    return std::accumulate (v.begin (), v.end (), 0.0,
                            [cnt, ave] (double a, double b)
                            {
                              return std::isnan (b) ?
                                a :
                                a + (square (b - ave) / (cnt - 1));
                            });
  }

  inline double standard_deviation (const std::vector<double> &v)
  {
    return std::sqrt(variance (v));
  }

  inline double lookup_tau (std::size_t n)
  {
    if (n < 3)
      return 0.0;

    auto it {modified_tau_table.lower_bound (n)};

    if (it == modified_tau_table.end ())
      return inf_tau;

    return it->second;
  }
}

namespace modified_thompson_tau
{
  void remove_outliers (std::vector<double> *v)
  {
    if (v == nullptr)
      return;

#ifdef DEBUG_MODIFIED_THOMPSON_TAU
    std::cout << std::endl << "remove_outliers (): started." << std::endl;
#endif

    while (true)
      {
        auto n {count (*v)};

        if (n < 3)
          break;

        auto ave {average (*v)};
        auto sd {standard_deviation (*v)};

#ifdef DEBUG_MODIFIED_THOMPSON_TAU
        std::cout << std::endl
                  << "n   = " << n << std::endl
                  << "ave = " << ave << std::endl
                  << "sd  = " << sd << std::endl;
#endif

        std::vector<double> delta;
        std::transform (v->begin (), v->end (),
                        std::back_inserter (delta),
                        [ave] (double x)
                        {
                          return std::isnan (x) ?
                            std::numeric_limits<double>::quiet_NaN () :
                            std::abs (x - ave);
                        });

#ifdef DEBUG_MODIFIED_THOMPSON_TAU
        std::cout << "delta" << std::endl;
        for (auto d: delta)
          std::cout << d << std::endl;
#endif

        auto it {std::max_element (delta.begin (), delta.end ())};

#ifdef DEBUG_MODIFIED_THOMPSON_TAU
        std::cout << "max delta = " << *it << std::endl
                  << "tau       = " << lookup_tau (n) << std::endl
                  << "tau * S   = " << lookup_tau (n) * sd
                  << std::endl;
#endif

        if (*it <= (lookup_tau (n) * sd))
          break;

        v->at (std::distance (delta.begin (), it))
          = std::numeric_limits<double>::quiet_NaN ();

#ifdef DEBUG_MODIFIED_THOMPSON_TAU
        std::cout << "It's outlier. Removed." << std::endl
                  << "Continuing." << std::endl;
#endif
      }

#ifdef DEBUG_MODIFIED_THOMPSON_TAU
    std::cout << "It's not outlier." << std::endl << std::endl
              << "remove_outliers (): completed." << std::endl << std::endl;
#endif
  }
}
