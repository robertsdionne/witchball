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

  void PlayPlayer1Hit(const b2Body *ball);

  void PlayPlayer1Score(const b2Body *ball);

  void PlayPlayer1Win(const b2Body *ball);

  void PlayPlayer2Hit(const b2Body *ball);

  void PlayPlayer2Score(const b2Body *ball);

  void PlayPlayer2Win(const b2Body *ball);
  
private:
  void PlaySound(const b2Body *body, ofSoundPlayer *sound, int &next_index);

  void PlaySoundAt(const b2Body *body, ofSoundPlayer *sound);
  
private:
  static constexpr int kConcurrentSounds = 10;

  ofSoundPlayer sound_wallbounce[kConcurrentSounds];
  ofSoundPlayer hit[4], backhit[4];
  ofSoundPlayer player1_score, player1_score7, player1_winfade;
  ofSoundPlayer player2_score, player2_score7, player2_winfade;
  int play_next_index_wallbounce;
};

#endif  // WITCHBALL_COLLISIONSOUNDPLAYER_H_
