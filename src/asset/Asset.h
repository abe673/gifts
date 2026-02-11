#pragma once
#include <cstdint>
#include <string>

using AssetID = uint16_t;
constexpr AssetID InvalidAsset = 0;

enum class AssetType { Texture, Font };

struct AssetDesc {
  AssetType type;
  std::string path;
  int fontSize = 0; // hanya dipakai font
};
