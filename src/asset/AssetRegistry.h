#pragma once
#include "Asset.h"
#include <unordered_map>

class AssetRegistry {
public:
  AssetID RegisterTexture(const std::string &path);
  AssetID RegisterFont(const std::string &path, int size);
  const AssetDesc *Get(AssetID id) const;

private:
  AssetID lastId = 0;

  // pathToId : path → ID      (lookup cepat)
  // assets   : ID   → desc   (data utama)
  std::unordered_map<AssetID, AssetDesc> assets;
  std::unordered_map<std::string, AssetID> pathToId;
};

inline AssetRegistry &GetAsset() {
  static AssetRegistry ar;
  return ar;
}
