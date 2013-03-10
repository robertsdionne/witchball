#include <Box2D/Box2D.h>
#include <algorithm>
#include <list>

#include "collisionplayer.h"
#include "constants.h"
#include "ofMain.h"

CollisionPlayer::CollisionPlayer()
: sound_wallbounce(), play_next_index(0) {
  for (int i = 0; i < kConcurrentSounds; ++i) {
    ofSoundPlayer bounce;
    bounce.loadSound(kWallBounceFilename);
    bounce.setMultiPlay(true);
    sound_wallbounce[i] = bounce;
  }
}

void CollisionPlayer::BeginContact(b2Contact *contact) {
  const b2Body *const body = contact->GetFixtureA()->GetBody()->GetType() == b2_dynamicBody ?
  contact->GetFixtureA()->GetBody() : contact->GetFixtureB()->GetBody();
  const float speed = ofClamp(body->GetLinearVelocity().Length() / 10.0, 0.1f, 2.0f);
  const float volume = ofClamp(body->GetLinearVelocity().Length() / 10.0, 0.1f, 1.0f);
  sound_wallbounce[play_next_index].setSpeed(speed + 0.1 * ofRandomf());
  sound_wallbounce[play_next_index].setVolume(volume);
  sound_wallbounce[play_next_index].setPan(body->GetPosition().x / kHalfCourtWidth);
  sound_wallbounce[play_next_index].play();
  play_next_index = (play_next_index + 1) % kConcurrentSounds;
}
