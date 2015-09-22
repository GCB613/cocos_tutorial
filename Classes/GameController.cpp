#include "GameController.h"

using namespace cocos2d;

Scene* GameController::createScene() {
  auto scene = Scene::create();
  auto layer = GameController::create();
  scene->addChild(layer);
  return scene;
}

bool GameController::init() {
  if ( !Layer::init() ) {
    return false;
  }
  scheduleUpdate();
  return true;
}

void GameController::setup_game() {
  unsigned int seed = static_cast<unsigned int>(time(nullptr));
  srand(seed);
}

void GameController::update(float dt) {
  _generator_timer += dt;
  
  // At a certain time interval, generate an aircraft at a random location.
  if (_generator_timer >= 2.0f && _air_craft.size() < 10) {
    _generator_timer = 0.0f;
    auto new_air_craft = AirCraft::create();
    new_air_craft->set_initial_position(random_position());
    new_air_craft->set_initial_velocity(random_direction());
    addChild(new_air_craft);
    _air_craft.push_back(new_air_craft);
  }
  
  // update the position of the aircraft on the screen.
  // AND Check if aircraft need to be turned around by boundaries.
  float width = getContentSize().width - 30.0f;
  float height = getContentSize().height - 30.0f;
  Rect box(15.0f, 15.0f, width, height);
  
  for (auto& craft : _air_craft) {
    craft->update_aircraft(dt);
    craft->check_boundaries(box);
    craft->reset_status();
  }

  // Check for collisions between the aircraft.
  for (size_t i=0; i<_air_craft.size(); i++) {
    for (size_t j=i+1; j<_air_craft.size(); j++) {
      _air_craft[i]->collide(_air_craft[j]);
    }
  }
}

Vec2 GameController::random_position() {
  float x = getContentSize().width * 0.5f;
  float y = getContentSize().height * 0.5f;
  return Vec2(x, y);
}

Vec2 GameController::random_direction() {
   float degrees = float(rand() % 360);
   float radians = degrees * 3.1415926f / 180.0f;
   return Vec2(cos(radians), sin(radians));
}
