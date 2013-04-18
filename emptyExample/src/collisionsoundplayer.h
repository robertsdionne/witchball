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
  void PlaySound(const b2Body *body, ofSoundPlayer *sound, int &next_index);
  
private:
  ofSoundPlayer sound_wallbounce[10];
  ofSoundPlayer sound_hit1[10];
  int play_next_index_wallbounce;
  int play_next_index_hit1;
};

#endif  // WITCHBALL_COLLISIONSOUNDPLAYER_H_
