// Copyright (c) 2011-2017 The Cryptonote developers
// Copyright (c) 2014-2017 XDN developers
// Copyright (c) 2016-2017 BXC developers
// Copyright (c) 2017 Royalties developers
// Copyright (c) 2018 [ ] developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <cstdint>
#include <utility>

namespace CryptoNote {

class IFusionManager {
public:
  struct EstimateResult {
    size_t fusionReadyCount;
    size_t totalOutputCount;
  };

  virtual ~IFusionManager() {}

  virtual size_t createFusionTransaction(uint64_t threshold, uint64_t mixin) = 0;
  virtual bool isFusionTransaction(size_t transactionId) const = 0;
  virtual EstimateResult estimate(uint64_t threshold) const = 0;
};

}
