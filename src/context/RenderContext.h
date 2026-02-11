#pragma once
#include "../asset/AssetRegistry.h"
#include "raylib.h"
#include <unordered_map>

class RenderContext {
public:
  RenderContext();
  Texture2D &GetTexture(AssetID id);
  Font &GetFont(AssetID id);
  void DestroyAll();

private:
  AssetRegistry &registry;
  std::unordered_map<AssetID, Texture2D> textures;
  std::unordered_map<AssetID, Font> fonts;
};
