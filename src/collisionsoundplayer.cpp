#include <Box2D/Box2D.h>
#include <algorithm>
#include <list>

#include "collisionsoundplayer.h"
#include "constants.h"
#include "model.h"
#include "ofMain.h"

CollisionSoundPlayer::CollisionSoundPlayer()
: sound_wallbounce(), sound_hit1(), play_next_index_wallbounce(0), play_next_index_hit1(0) {
  /*
	for (int i = 0; i < kConcurrentSounds; ++i) {
    sound_wallbounce[i].loadSound(kWallBounceFilename);
    sound_wallbounce[i].setMultiPlay(true);
  }
  for (int i = 0; i < kConcurrentSounds; ++i) {
    sound_hit1[i].loadSound(kHit1);
    sound_hit1[i].setMultiPlay(true);
  }
	 */
}

void CollisionSoundPlayer::BeginContact(b2Contact *contact) {
  const b2Body *const bodyA = contact->GetFixtureA()->GetBody();
  const b2Body *const bodyB = contact->GetFixtureB()->GetBody();
  const b2Body *const body = bodyA->GetType() == b2_dynamicBody ? bodyA : bodyB;
  const b2Body *const other = body == bodyA ? bodyB : bodyA;
  void *body_user_data = body->GetUserData();
  if (body_user_data) {
    Model *model = static_cast<Model *>(body_user_data);
    if (other == model->player1_top || other == model->player1_bottom ||
        other == model->player2_top || other == model->player2_bottom) {
      PlaySound(body, sound_hit1, play_next_index_hit1);
    } else {
      PlaySound(body, sound_wallbounce, play_next_index_wallbounce);
    }
  }
}

void CollisionSoundPlayer::PlaySound(const b2Body *body, ofSoundPlayer *sound, int &next_index) {
  const float speed = ofClamp(body->GetLinearVelocity().Length() / 10.0, 0.1f, 2.0f);
  const float volume = ofClamp(body->GetLinearVelocity().Length() / 10.0, 0.1f, 1.0f);
  sound[next_index].setSpeed(speed + 0.1 * ofRandomf());
  sound[next_index].setVolume(volume);
  sound[next_index].setPan(body->GetPosition().x / kHalfCourtWidth);
  sound[next_index].play();
  next_index = (next_index + 1) % kConcurrentSounds;
}
