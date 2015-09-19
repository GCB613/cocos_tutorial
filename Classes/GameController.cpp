#include "GameController.h"

USING_NS_CC;

Scene* GameController::createScene()
{
  // 'scene' is an autorelease object
  auto scene = Scene::create();
  
  // 'layer' is an autorelease object
  auto layer = GameController::create();
  
  // add layer as a child to scene
  scene->addChild(layer);
  
  // return the scene
  return scene;
}

// on "init" you need to initialize your instance
bool GameController::init()
{
  if ( !Layer::init() )
  {
    return false;
  }
  
  return true;
}
