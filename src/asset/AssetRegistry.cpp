
#include "AssetRegistry.h"
#include <iostream>
#include <limits>

AssetID AssetRegistry::RegisterTexture(const std::string &path) {
  if (auto it = pathToId.find(path); it != pathToId.end()) {
    std::cout << "reuse id path exist \n";
    return it->second;
  }

  if (lastId == std::numeric_limits<AssetID>::max()) return InvalidAsset;

  AssetID id = ++lastId;
  std::cout << "registered id" << id << " \n";

  assets.try_emplace(id, AssetDesc{AssetType::Texture, path});
  pathToId[path] = id;
  return id;
}

AssetID AssetRegistry::RegisterFont(const std::string &path, int size) {
  if (auto it = pathToId.find(path); it != pathToId.end()) return it->second;

  if (lastId == std::numeric_limits<AssetID>::max()) return InvalidAsset;

  AssetID id = ++lastId;
  assets.try_emplace(id, AssetDesc{AssetType::Font, path, size});
  pathToId[path] = id;
  return id;
}

const AssetDesc *AssetRegistry::Get(AssetID id) const {
  auto it = assets.find(id);
  return it == assets.end() ? nullptr : &it->second;
}
