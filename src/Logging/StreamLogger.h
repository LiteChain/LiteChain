// Copyright (c) 2011-2017 The Cryptonote developers
// Copyright (c) 2014-2017 XDN developers
// Copyright (c) 2016-2017 BXC developers
// Copyright (c) 2017 Royalties developers
// Copyright (c) 2018 [ ] developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <mutex>
#include "CommonLogger.h"

namespace Logging {

class StreamLogger : public CommonLogger {
public:
  StreamLogger(Level level = DEBUGGING);
  StreamLogger(std::ostream& stream, Level level = DEBUGGING);
  void attachToStream(std::ostream& stream);

protected:
  virtual void doLogString(const std::string& message) override;

protected:
  std::ostream* stream;

private:
  std::mutex mutex;
};

}
