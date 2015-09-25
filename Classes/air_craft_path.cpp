//
//  air_craft_path.cpp
//  AirTrafficController
//
//  Created by Garrett Bodily on 9/25/15.
//
//

#include "air_craft_path.h"

using namespace cocos2d;

bool AirCraftPath::init() {
  if (!DrawNode::init()) {
    return false;
  }
  setPosition(Vec2::ZERO);
  clear();
  return true;
}

void AirCraftPath::reset_path(Vec2 first_point) {
  _way_points.resize(1);
  _way_points.back() = first_point;
  redraw();
}

void AirCraftPath::pop_first_point() {
  if (!_way_points.empty()) {
    _way_points.erase(_way_points.begin());
  }
  redraw();
}

void AirCraftPath::add_point(Vec2 new_point) {
  _way_points.push_back(new_point);
  redraw();
}

Vec2 AirCraftPath::get_heading(Vec2 current_position, Vec2 current_heading) {
  if (_way_points.empty()) return current_heading;

  // check if we are too close to the first path point.
  float dist_to_front = current_position.distanceSquared(_way_points.front());
  if (dist_to_front < 5.0f * 5.0f) {
    pop_first_point();
  }
  
  if (_way_points.empty()) return current_heading;
  
  Vec2 new_heading = _way_points.front() - current_position;
  new_heading.normalize();
  return new_heading;
}

void AirCraftPath::redraw() {
  clear();
  bool is_first = true;
  Vec2 previous_point(0.0f, 0.0f);
  for (auto& point : _way_points) {
    if (is_first) {
      is_first = false;
      previous_point = point;
    } else {
      drawLine(previous_point, point, cocos2d::Color4F::WHITE);
      previous_point = point;
    }
  }
}
