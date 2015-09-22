//
//  air_craft.h
//  MyGameGarrett
//
//  Created by Garrett Bodily on 9/17/15.
//
//

#pragma once

#include <stdio.h>
#include "cocos2d.h"
#include "2d/CCDrawNode.h"

using namespace cocos2d;

class AirCraft : public Node {
public:
  CREATE_FUNC(AirCraft);
  bool init();
  void set_initial_position(Vec2 position);
  void set_initial_velocity(Vec2 velocity);
  void update_aircraft(float time_delta);
  void check_boundaries(Rect box);
  void collide(AirCraft* other);
  void reset_status();
  
protected:
  float m_speed = 80.0;
  Vec2 m_actual_velocity = Vec2(1.0f, 0.0f);
  Vec2 m_desired_velocity = Vec2(1.0f, 0.0f);
  DrawNode* _warning_circle = nullptr;
};
