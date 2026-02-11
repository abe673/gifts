#include "Property.h"
#include "../asset/AssetRegistry.h"
#include "../window/WindowManager.h"
#include "Item.h"
#include <iostream>

ItemData *Property::getSelected() {
  if (selected < 0 || selected > items.size() - 1) return nullptr;
  return items[selected].get();
}

Property::Property() {
  items.reserve(20);
}

void Property::AddImage(std::string path) {
  AssetID mt = GetAsset().RegisterTexture(path);
  items.push_back({std::make_unique<DataTexture>(mt)});
  selected = items.size() - 1;
}
void Property::AddText(std::string path) {
  AssetID mf = GetAsset().RegisterFont(path, 50);
  items.push_back({std::make_unique<DataText>(mf)});
  selected = items.size() - 1;
}

bool Property::UpdateInput(Vector2 mouse) {
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    for (int i = 0; i < items.size(); i++) {
      if (CheckCollisionPointRec(mouse, items[i]->rect)) {
        dragOffset = {mouse.x - items[i]->rect.x, mouse.y - items[i]->rect.y};
        std::cout << "hit\n";
        selected = i;
        dragging = true;
      }
    }
  }
  // drag
  if (dragging && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
    if (auto *it = getSelected()) {
      Rectangle *r = &it->rect;
      r->x = mouse.x - dragOffset.x;
      r->y = mouse.y - dragOffset.y;
    }
  }
  // lepas
  bool changed = false;
  if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
    if (dragging) {
      dragging = false;
      changed = true; // drag selesai, anggap perubahan
    }
  }
  return changed;
}

void Property::Draw(int id, const DrawContext &ctx) {
  Window *win = GetWindowManager().GetWindow((WinID)id);

  for (int i = 0; i < items.size(); i++) {
    switch (items[i]->type) {

    case ItemType::Text: {
      auto *item = static_cast<DataText *>(items[i].get());

      Vector2 pos = {item->rect.x * ctx.scale + ctx.offset.x, item->rect.y * ctx.scale + ctx.offset.y};

      DrawTextEx(win->gpu.GetFont(item->assetId), item->text, pos, item->fontsize * ctx.scale, 1 * ctx.scale, BLACK);
    } break;

    case ItemType::Texture: {
      auto *item = static_cast<DataTexture *>(items[i].get());

      Texture2D &tex = win->gpu.GetTexture(item->assetId);

      Rectangle dst = {item->rect.x * ctx.scale + ctx.offset.x, item->rect.y * ctx.scale + ctx.offset.y, item->rect.width * ctx.scale, item->rect.height * ctx.scale};

      Rectangle src = {0, 0, (float)tex.width, (float)tex.height};

      DrawTexturePro(tex, src, dst, {0, 0}, 0.0f, WHITE);
    } break;
    }
  }
}

void Property::MoveForward() {
  if (selected < 0) return;
  if (selected >= items.size() - 1) return;

  std::swap(items[selected], items[selected + 1]);
  selected++;
}

void Property::MoveBackward() {
  if (selected <= 0) return;

  std::swap(items[selected], items[selected - 1]);
  selected--;
}
