#pragma once

#include "cocos2d.h"
#include "air_craft.h"

using namespace cocos2d;

class GameController : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameController);

protected:
  void setup_game();
  virtual void update(float dt) override;
  Vec2 random_position();
  Vec2 random_direction();
  void setup_touch_events();
  
protected:
  std::vector<AirCraft*> _air_craft;
  float _generator_timer = 0.0f;
  int score = 0;
  
  Vec2 _previous_point;
  AirCraft* _selected_craft = nullptr;
  DrawNode* _drawing_node = nullptr;
};
