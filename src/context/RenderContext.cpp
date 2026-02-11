
#include "RenderContext.h"
#include "../asset/AssetRegistry.h"
#include "raylib.h"

RenderContext::RenderContext() : registry(GetAsset()) {
}

Texture2D &RenderContext::GetTexture(AssetID id) {

  auto [it, inserted] = textures.try_emplace(id, Texture2D{});
  auto &t = it->second;

  if (t.id == 0) {
    const AssetDesc *d = registry.Get(id);
    t = LoadTexture(d->path.c_str());
  }
  return t;
}

Font &RenderContext::GetFont(AssetID id) {
  auto [it, inserted] = fonts.try_emplace(id, Font{});
  auto &f = it->second;

  if (f.texture.id == 0) {
    const AssetDesc *d = registry.Get(id);
    f = LoadFontEx(d->path.c_str(), d->fontSize, nullptr, 0);
  }
  return f;
}

void RenderContext::DestroyAll() {
  for (auto &[_, t] : textures)
    if (t.id) UnloadTexture(t);

  for (auto &[_, f] : fonts)
    if (f.texture.id) UnloadFont(f);

  textures.clear();
  fonts.clear();
}
