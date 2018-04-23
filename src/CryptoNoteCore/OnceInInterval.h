// Copyright (c) 2011-2017 The Cryptonote developers
// Copyright (c) 2014-2017 XDN developers
// Copyright (c) 2016-2017 BXC developers
// Copyright (c) 2017 Royalties developers
// Copyright (c) 2018 [ ] developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <time.h>

namespace CryptoNote
{

class OnceInInterval {
public:

  OnceInInterval(unsigned interval, bool startNow = true) 
    : m_interval(interval), m_lastCalled(startNow ? 0 : time(nullptr)) {}

  template<class F>
  bool call(F func) {
    time_t currentTime = time(nullptr);

    if (currentTime - m_lastCalled > m_interval) {
      bool res = func();
      time(&m_lastCalled);
      return res;
    }

    return true;
  }

private:
  time_t m_lastCalled;
  time_t m_interval;
};

}
