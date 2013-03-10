#ifndef WITCHBALL_COLLISIONSOUNDPLAYER_H_
#define WITCHBALL_COLLISIONSOUNDPLAYER_H_

#include <Box2D/Box2D.h>
#include <list>

#include "constants.h"
#include "ofMain.h"

class CollisionSoundPlayer : public b2ContactListener {
public:
  CollisionSoundPlayer();
  
  virtual ~CollisionSoundPlayer() {}
  
  virtual void BeginContact(b2Contact *contact);
  
private:
  ofSoundPlayer sound_wallbounce[kConcurrentSounds];
  int play_next_index;
};

#endif  // WITCHBALL_COLLISIONSOUNDPLAYER_H_
