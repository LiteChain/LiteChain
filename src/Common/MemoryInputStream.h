// Copyright (c) 2011-2017 The Cryptonote developers
// Copyright (c) 2014-2017 XDN developers
// Copyright (c) 2016-2017 BXC developers
// Copyright (c) 2017 Royalties developers
// Copyright (c) 2018 [ ] developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include "IInputStream.h"

namespace Common {

  class MemoryInputStream : public IInputStream {
  public:
    MemoryInputStream(const void* buffer, size_t bufferSize);
    size_t getPosition() const;
    bool endOfStream() const;
    
    // IInputStream
    virtual size_t readSome(void* data, size_t size) override;

  private:
    const char* buffer;
    size_t bufferSize;
    size_t position;
  };
}
