// Copyright (c) 2011-2017 The Cryptonote developers
// Copyright (c) 2014-2017 XDN developers
// Copyright (c) 2016-2017 BXC developers
// Copyright (c) 2017 Royalties developers
// Copyright (c) 2018 [ ] developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <array>
#include <cstdint>
#include <streambuf>

namespace System {

class TcpConnection;

class TcpStreambuf : public std::streambuf {
public:
  explicit TcpStreambuf(TcpConnection& connection);
  TcpStreambuf(const TcpStreambuf&) = delete;
  ~TcpStreambuf();
  TcpStreambuf& operator=(const TcpStreambuf&) = delete;

private:
  TcpConnection& connection;
  std::array<char, 4096> readBuf;
  std::array<uint8_t, 1024> writeBuf;

  std::streambuf::int_type overflow(std::streambuf::int_type ch) override;
  int sync() override;
  std::streambuf::int_type underflow() override;
  bool dumpBuffer(bool finalize);
};

}
