#ifndef WITCHBALL_COLLISIONPLAYER_H_
#define WITCHBALL_COLLISIONPLAYER_H_

#include <Box2D/Box2D.h>
#include <list>

#include "constants.h"
#include "ofMain.h"

class CollisionPlayer : public b2ContactListener {
public:
  CollisionPlayer();
  
  virtual ~CollisionPlayer() {}
  
  virtual void BeginContact(b2Contact *contact);
  
private:
  ofSoundPlayer sound_wallbounce[kConcurrentSounds];
  int play_next_index;
};

#endif  // WITCHBALL_COLLISIONPLAYER_H_
