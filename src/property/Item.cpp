#include "Item.h"
#include "../window/WindowManager.h"

ItemData::ItemData(ItemType t, AssetID id) : type(t), assetId(id) {};

DataText::DataText(AssetID fontId) : ItemData(ItemType::Text, fontId) {
  CalculateRect();
};
void DataText::CalculateRect() {
  Font &f = GetWindowManager().GetWindow(WinID::Editor)->gpu.GetFont(assetId);
  Vector2 s = MeasureTextEx(f, text, fontsize, 1);
  rect.width = s.x;
  rect.height = s.y;
};

DataTexture::DataTexture(AssetID texId) : ItemData(ItemType::Texture, texId) {
  CalculateRect();
};

void DataTexture::CalculateRect() {
  Texture2D &t = GetWindowManager().GetWindow(WinID::Editor)->gpu.GetTexture(assetId);
  baseSize = {(float)t.width, (float)t.height};
  rect.width = baseSize.x * scale;
  rect.height = baseSize.y * scale;
};
