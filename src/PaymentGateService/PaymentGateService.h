// Copyright (c) 2011-2017 The Cryptonote developers
// Copyright (c) 2014-2017 XDN developers
// Copyright (c) 2016-2017 BXC developers
// Copyright (c) 2017 Royalties developers
// Copyright (c) 2018 [ ] developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include "ConfigurationManager.h"
#include "PaymentServiceConfiguration.h"

#include "Logging/ConsoleLogger.h"
#include "Logging/LoggerGroup.h"
#include "Logging/StreamLogger.h"

#include "PaymentGate/NodeFactory.h"
#include "PaymentGate/WalletService.h"

class PaymentGateService {
public:

  PaymentGateService() : dispatcher(nullptr), stopEvent(nullptr), config(), service(nullptr), logger(), currencyBuilder(logger) {
  }

  bool init(int argc, char** argv);

  const PaymentService::ConfigurationManager& getConfig() const { return config; }
  PaymentService::WalletConfiguration getWalletConfig() const;
  const CryptoNote::Currency getCurrency();

  void run();
  void stop();
  
  Logging::ILogger& getLogger() { return logger; }

private:

  void runInProcess(Logging::LoggerRef& log);
  void runRpcProxy(Logging::LoggerRef& log);

  void runWalletService(const CryptoNote::Currency& currency, CryptoNote::INode& node);

  System::Dispatcher* dispatcher;
  System::Event* stopEvent;
  PaymentService::ConfigurationManager config;
  PaymentService::WalletService* service;
  CryptoNote::CurrencyBuilder currencyBuilder;
  
  Logging::LoggerGroup logger;
  std::ofstream fileStream;
  Logging::StreamLogger fileLogger;
  Logging::ConsoleLogger consoleLogger;
};
