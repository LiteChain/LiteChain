// Copyright (c) 2011-2017 The Cryptonote developers
// Copyright (c) 2014-2017 XDN developers
// Copyright (c) 2016-2017 BXC developers
// Copyright (c) 2017 Royalties developers
// Copyright (c) 2018 [ ] developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <algorithm>
#include <vector>

namespace Common {

template <class T>
T medianValue(std::vector<T> &v) {
  if (v.empty())
    return T();

  if (v.size() == 1)
    return v[0];

  auto n = (v.size()) / 2;
  std::sort(v.begin(), v.end());
  //nth_element(v.begin(), v.begin()+n-1, v.end());
  if (v.size() % 2) { //1, 3, 5...
    return v[n];
  } else { //2, 4, 6...
    return (v[n - 1] + v[n]) / 2;
  }
}

}
