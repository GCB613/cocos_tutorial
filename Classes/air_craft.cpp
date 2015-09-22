#include "air_craft.h"

using namespace cocos2d;

bool AirCraft::init() {
  if (!Node::init()) {
    return false;
  }
  
  setAnchorPoint(Vec2::ANCHOR_MIDDLE);
  
  // Draw the plane.
  auto shape = DrawNode::create();
  shape->setPosition(Vec2::ZERO);
  shape->clear();
  shape->drawLine(Vec2(-20.0f, 0.0f), Vec2(20.0f, 0.0f), Color4F::GREEN);
  shape->drawLine(Vec2(10.0f, -15.0f), Vec2(10.0f, 15.0f), Color4F::GREEN);
  shape->drawLine(Vec2(-18.0f, -8.0f), Vec2(-18.0f, 8.0f), Color4F::GREEN);
  addChild(shape);
  
  _warning_circle = DrawNode::create();
  _warning_circle->setPosition(Vec2::ZERO);
  _warning_circle->clear();
  _warning_circle->drawCircle(Vec2::ZERO, 25.0f, 360.0f, 25, false, Color4F::RED);
  _warning_circle->setVisible(false);
  addChild(_warning_circle);
  
  return true;
}

void AirCraft::set_initial_position(Vec2 position) {
  setPosition(position);
}

void AirCraft::set_initial_velocity(Vec2 velocity) {
  m_actual_velocity = velocity;
  m_desired_velocity = velocity;
  m_actual_velocity.normalize();
  m_desired_velocity.normalize();
}

void AirCraft::update_aircraft(float time_delta) {
  m_desired_velocity.normalize();
  m_actual_velocity.normalize();
  
  Vec2 steering = m_desired_velocity - m_actual_velocity;
  if (Vec2::angle(m_desired_velocity, m_actual_velocity) * 180.0f > 179.0 * 3.1415926f) {
    steering.x = m_actual_velocity.y;
    steering.y = -m_actual_velocity.x;
  }
  steering *= 0.15f;

  m_actual_velocity = m_actual_velocity + steering;
  m_actual_velocity.normalize();
  
  Vec2 old_pos = getPosition();
  Vec2 new_pos = old_pos + m_actual_velocity * m_speed * time_delta;
  setPosition(new_pos);

  Vec2 x_axis(1.0f, 0.0f);
  float theta = Vec2::angle(m_actual_velocity, x_axis) * 180.0f / 3.1415926f;
  if (m_actual_velocity.y < 0.0) {
    theta *= -1.0;
  }
  setRotation(-theta);
}

void AirCraft::check_boundaries(Rect box) {
  auto pos = getPosition();
  if (pos.x < box.getMinX()) {
    m_desired_velocity.x = fabsf(m_desired_velocity.x);
  }
  if (pos.x > box.getMaxX()) {
    m_desired_velocity.x = -fabsf(m_desired_velocity.x);
  }
  if (pos.y < box.getMinY()) {
    m_desired_velocity.y = fabs(m_desired_velocity.y);
  }
  if (pos.y > box.getMaxY()) {
    m_desired_velocity.y = -fabs(m_desired_velocity.y);
  }
}

void AirCraft::collide(AirCraft* other) {
  Vec2 pos1 = getPosition();
  Vec2 pos2 = other->getPosition();
  float dx = pos1.x - pos2.x;
  float dy = pos1.y - pos2.y;
  float distance_squared = dx * dx + dy * dy;
  if (distance_squared < 50.0 * 50.0) {
    _warning_circle->setVisible(true);
    other->_warning_circle->setVisible(true);
  }
}

void AirCraft::reset_status() {
  if (_warning_circle) {
    _warning_circle->setVisible(false);
  }
}



/*
 bool AirCraft::init() {
 if (!Node::init()) {
 return false;
 }
 
 setAnchorPoint(Vec2::ANCHOR_MIDDLE);
 
 // Draw the plane.
 auto shape = DrawNode::create();
 shape->setPosition(Vec2::ZERO);
 shape->clear();
 shape->drawLine(Vec2(-20.0f, 0.0f), Vec2(20.0f, 0.0f), Color4F::GREEN);
 shape->drawLine(Vec2(10.0f, -15.0f), Vec2(10.0f, 15.0f), Color4F::GREEN);
 shape->drawLine(Vec2(-18.0f, -8.0f), Vec2(-18.0f, 8.0f), Color4F::GREEN);
 addChild(shape);
 
 return true;
 }
 
 void AirCraft::set_initial_position(Vec2 position) {
 setPosition(position);
 }
 
 void AirCraft::set_initial_velocity(Vec2 velocity) {
 m_actual_velocity = velocity;
 m_desired_velocity = velocity;
 m_actual_velocity.normalize();
 m_desired_velocity.normalize();
 }
 
 void AirCraft::update_aircraft(float time_delta) {
 m_desired_velocity.normalize();
 m_actual_velocity.normalize();
 Vec2 steering = m_desired_velocity - m_actual_velocity;
 steering *= 0.15f;
 
 m_actual_velocity = m_actual_velocity + steering;
 m_actual_velocity.normalize();
 
 Vec2 old_pos = getPosition();
 Vec2 new_pos = old_pos + m_actual_velocity * m_speed * time_delta;
 setPosition(new_pos);
 
 Vec2 x_axis(1.0f, 0.0f);
 float theta = Vec2::angle(m_actual_velocity, x_axis) * 180.0f / 3.1415926f;
 if (m_actual_velocity.y < 0.0) {
 theta *= -1.0;
 }
 setRotation(-theta);
 }
 
 void AirCraft::check_boundaries(Rect box) {
 auto pos = getPosition();
 if (pos.x < box.getMinX()) {
 m_desired_velocity.x = fabsf(m_desired_velocity.x);
 }
 if (pos.x > box.getMaxX()) {
 m_desired_velocity.x = -fabsf(m_desired_velocity.x);
 }
 if (pos.y < box.getMinY()) {
 m_desired_velocity.y = fabs(m_desired_velocity.y);
 }
 if (pos.y > box.getMaxY()) {
 m_desired_velocity.y = -fabs(m_desired_velocity.y);
 }
 }
*/