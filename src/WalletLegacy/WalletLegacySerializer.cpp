// Copyright (c) 2011-2017 The Cryptonote developers
// Copyright (c) 2014-2017 XDN developers
// Copyright (c) 2016-2017 BXC developers
// Copyright (c) 2017 Royalties developers
// Copyright (c) 2018 [ ] developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "WalletLegacySerializer.h"

#include <stdexcept>

#include "Common/MemoryInputStream.h"
#include "Common/StdInputStream.h"
#include "Common/StdOutputStream.h"
#include "Serialization/BinaryOutputStreamSerializer.h"
#include "Serialization/BinaryInputStreamSerializer.h"
#include "CryptoNoteCore/Account.h"
#include "CryptoNoteCore/CryptoNoteSerialization.h"
#include "WalletLegacy/WalletUserTransactionsCache.h"
#include "Wallet/WalletErrors.h"
#include "WalletLegacy/KeysStorage.h"

using namespace Common;

namespace {

const uint32_t WALLET_SERIALIZATION_VERSION = 2;

bool verifyKeys(const Crypto::SecretKey& sec, const Crypto::PublicKey& expected_pub) {
  Crypto::PublicKey pub;
  bool r = Crypto::secret_key_to_public_key(sec, pub);
  return r && expected_pub == pub;
}

void throwIfKeysMissmatch(const Crypto::SecretKey& sec, const Crypto::PublicKey& expected_pub) {
  if (!verifyKeys(sec, expected_pub))
    throw std::system_error(make_error_code(CryptoNote::error::WRONG_PASSWORD));
}

}

namespace CryptoNote {

WalletLegacySerializer::WalletLegacySerializer(CryptoNote::AccountBase& account, WalletUserTransactionsCache& transactionsCache) :
  account(account),
  transactionsCache(transactionsCache),
  walletSerializationVersion(WALLET_SERIALIZATION_VERSION)
{
}

void WalletLegacySerializer::serialize(std::ostream& stream, const std::string& password, bool saveDetailed, const std::string& cache) {
  std::stringstream plainArchive;
  StdOutputStream plainStream(plainArchive);
  CryptoNote::BinaryOutputStreamSerializer serializer(plainStream);
  saveKeys(serializer);

  serializer(saveDetailed, "has_details");

  if (saveDetailed) {
    serializer(transactionsCache, "details");
  }

  serializer.binary(const_cast<std::string&>(cache), "cache");

  std::string plain = plainArchive.str();
  std::string cipher;

  Crypto::chacha_iv iv = encrypt(plain, password, cipher);

  uint32_t version = walletSerializationVersion;
  StdOutputStream output(stream);
  CryptoNote::BinaryOutputStreamSerializer s(output);
  s.beginObject("wallet");
  s(version, "version");
  s(iv, "iv");
  s(cipher, "data");
  s.endObject();

  stream.flush();
}

void WalletLegacySerializer::saveKeys(CryptoNote::ISerializer& serializer) {
  CryptoNote::KeysStorage keys;
  CryptoNote::AccountKeys acc = account.getAccountKeys();

  keys.creationTimestamp = account.get_createtime();
  keys.spendPublicKey = acc.address.spendPublicKey;
  keys.spendSecretKey = acc.spendSecretKey;
  keys.viewPublicKey = acc.address.viewPublicKey;
  keys.viewSecretKey = acc.viewSecretKey;

  keys.serialize(serializer, "keys");
}

Crypto::chacha_iv WalletLegacySerializer::encrypt(const std::string& plain, const std::string& password, std::string& cipher) {
  Crypto::chacha_key key;
  Crypto::cn_context context;
  Crypto::generate_chacha8_key(context, password, key);

  cipher.resize(plain.size());

  Crypto::chacha_iv iv = Crypto::rand<Crypto::chacha_iv>();
  Crypto::chacha8(plain.data(), plain.size(), key, iv, &cipher[0]);

  return iv;
}


void WalletLegacySerializer::deserialize(std::istream& stream, const std::string& password, std::string& cache) {
  StdInputStream stdStream(stream);
  CryptoNote::BinaryInputStreamSerializer serializerEncrypted(stdStream);

  serializerEncrypted.beginObject("wallet");

  uint32_t version;
  serializerEncrypted(version, "version");

  Crypto::chacha_iv iv;
  serializerEncrypted(iv, "iv");

  std::string cipher;
  serializerEncrypted(cipher, "data");

  serializerEncrypted.endObject();

  std::string plain;
  decrypt(cipher, plain, iv, password);

  MemoryInputStream decryptedStream(plain.data(), plain.size()); 
  CryptoNote::BinaryInputStreamSerializer serializer(decryptedStream);

  loadKeys(serializer);
  throwIfKeysMissmatch(account.getAccountKeys().viewSecretKey, account.getAccountKeys().address.viewPublicKey);

  if (account.getAccountKeys().spendSecretKey != NULL_SECRET_KEY) {
    throwIfKeysMissmatch(account.getAccountKeys().spendSecretKey, account.getAccountKeys().address.spendPublicKey);
  } else {
    if (!Crypto::check_key(account.getAccountKeys().address.spendPublicKey)) {
      throw std::system_error(make_error_code(CryptoNote::error::WRONG_PASSWORD));
    }
  }

  bool detailsSaved;

  serializer(detailsSaved, "has_details");

  if (detailsSaved) {
    if (version == 1) {
      transactionsCache.deserializeLegacyV1(serializer);
    } else {
      serializer(transactionsCache, "details");
    }
  }

  serializer.binary(cache, "cache");
}

void WalletLegacySerializer::decrypt(const std::string& cipher, std::string& plain, Crypto::chacha_iv iv, const std::string& password) {
  Crypto::chacha_key key;
  Crypto::cn_context context;
  Crypto::generate_chacha8_key(context, password, key);

  plain.resize(cipher.size());

  Crypto::chacha8(cipher.data(), cipher.size(), key, iv, &plain[0]);
}

void WalletLegacySerializer::loadKeys(CryptoNote::ISerializer& serializer) {
  CryptoNote::KeysStorage keys;

  try {
    keys.serialize(serializer, "keys");
  } catch (const std::runtime_error&) {
    throw std::system_error(make_error_code(CryptoNote::error::WRONG_PASSWORD));
  }

  CryptoNote::AccountKeys acc;
  acc.address.spendPublicKey = keys.spendPublicKey;
  acc.spendSecretKey = keys.spendSecretKey;
  acc.address.viewPublicKey = keys.viewPublicKey;
  acc.viewSecretKey = keys.viewSecretKey;

  account.setAccountKeys(acc);
  account.set_createtime(keys.creationTimestamp);
}

}
