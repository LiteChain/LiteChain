// Copyright (c) 2011-2017 The Cryptonote developers
// Copyright (c) 2014-2017 XDN developers
// Copyright (c) 2016-2017 BXC developers
// Copyright (c) 2017 Royalties developers
// Copyright (c) 2018 [ ] developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <fstream>
#include "StreamLogger.h"

namespace Logging {

class FileLogger : public StreamLogger {
public:
  FileLogger(Level level = DEBUGGING);
  void init(const std::string& filename);

private:
  std::ofstream fileStream;
};

}
