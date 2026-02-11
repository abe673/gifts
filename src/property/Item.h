

#pragma once
#include "../asset/Asset.h"
#include "raylib.h"

enum class ItemType { Text, Texture };

struct ItemData {
  ItemType type;
  AssetID assetId;
  Rectangle rect{0, 0, 0, 0};
  ItemData(ItemType t, AssetID id);
  virtual ~ItemData() = default;
  virtual void CalculateRect() = 0;
  // virtual void DrawGui() = 0;
};

struct DataText final : ItemData {
  int fieldKey = 0;
  char text[128] = "sample";
  int fontsize = 30;
  DataText(AssetID fontId);
  void CalculateRect() override;
  // void DrawGui() override;
};

struct DataTexture final : ItemData {
  Vector2 baseSize{};
  float scale = 1.0f;

  DataTexture(AssetID texId);
  void CalculateRect() override;
  // void DrawGui() override;
};
