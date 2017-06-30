#!/usr/bin/perl

#
# Modified Thompson tau method library for removing outlier 2017-06-30.13
# https://github.com/trueroad/modified_thompson_tau/
#
# Tau table formatter
#
# Copyright (C) 2017 Masamichi Hosoda. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY AUTHOR AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#

print <<EOS;
namespace
{
  const std::map<std::size_t, double> modified_tau_table
  {
EOS

while ($line = <>)
{
    chomp ($line);
    if ($line =~ /^([0-9]+),([0-9]+\.[0-9]+)/)
    {
        $n = $1;
        $tau = $2;
        print ("    { $n, $tau },\n");
    }
    elsif ($line =~ /^[0-9]+\.?[0-9]*[eE]\+[0-9]+,([0-9]+\.[0-9]+)/)
    {
        $inf = $1;
    }
}

print <<"EOS"
  };

  const double inf_tau {$inf};
}
EOS
