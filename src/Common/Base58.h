// Copyright (c) 2011-2017 The Cryptonote developers
// Copyright (c) 2014-2017 XDN developers
// Copyright (c) 2016-2017 BXC developers
// Copyright (c) 2017 Royalties developers
// Copyright (c) 2018 [ ] developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <cstdint>
#include <string>

namespace Tools
{
  namespace Base58
  {
    std::string encode(const std::string& data);
    bool decode(const std::string& enc, std::string& data);

    std::string encode_addr(uint64_t tag, const std::string& data);
    bool decode_addr(std::string addr, uint64_t& tag, std::string& data);
  }
}
