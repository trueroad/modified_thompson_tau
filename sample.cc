//
// Modified Thompson tau method library for removing outlier 2017-06-30.13
// https://github.com/trueroad/modified_thompson_tau/
//
// Sample
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

#include <iostream>
#include <random>

#include "modified_thompson_tau.hh"

int main ()
{
  std::vector<double> v
  {
    12.55390,  5.97100,  6.20120,  7.53099, 15.14670, 40.12345,
     1.55136, 23.96700,  1.73521, 21.31010,  8.80132, 50.12345,
  };

  std::cout << "input data" << std::endl;
  for (auto e: v)
    std::cout << e << std::endl;

  modified_thompson_tau::remove_outliers (&v);

  std::cout << "removed outliers" << std::endl;
  for (auto e: v)
    std::cout << e << std::endl;
}
