#include "camera.h"

void CameraSystem::update(float dt) {
  auto entities = manager->getAllEntitiesWithComponent<CenteredCameraComponent>();
  for (auto& ref : entities) {
    EID entity = ref.first;

    auto camera = manager->getComponent<CenteredCameraComponent>(entity);
    auto position = manager->getComponent<PositionComponent>(entity);
    auto dimension = manager->getComponent<DimensionComponent>(entity);

    auto centerPosition = manager->getComponent<PositionComponent>(camera->entity);
    auto centerDimension = manager->getComponent<DimensionComponent>(camera->entity);

    int width = game->grid.columns * game->grid.tile_w;
    int height = game->grid.rows * game->grid.tile_h;

    if (width <= dimension->w) {
      position->x = -(dimension->w - width) / 2;
    }
    else {
      position->x = max(centerPosition->x + centerDimension->w / 2 - dimension->w / 2, 0);
      position->x = min(position->x, game->grid.columns * game->grid.tile_w - dimension->w);
    }

    if (height <= dimension->h) {
      position->y = -(dimension->h - height) / 2;
    }
    else {
      position->y = max(centerPosition->y + centerDimension->h / 2 - dimension->h / 2, 0);
      position->y = min(position->y, game->grid.rows * game->grid.tile_h - dimension->h);
    }
  }
};

