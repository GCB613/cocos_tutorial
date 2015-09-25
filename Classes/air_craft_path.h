//
//  air_craft_path.h
//  AirTrafficController
//
//  Created by Garrett Bodily on 9/25/15.
//
//

#pragma once

#include <stdio.h>
#include "cocos2d.h"
#include "ui/UILayout.h"
#include "2d/CCDrawNode.h"

using namespace cocos2d;

class AirCraftPath : public DrawNode {
public:
  CREATE_FUNC(AirCraftPath);
  virtual bool init() override;
  void reset_path(Vec2 first_point);
  void pop_first_point();
  void add_point(Vec2 new_point);
  Vec2 get_heading(Vec2 current_position, Vec2 current_heading);
  
protected:
  AirCraftPath() {}
  void redraw();
  
protected:
  std::vector<Vec2> _way_points;
};