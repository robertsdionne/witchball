#include <Box2D/Box2D.h>
#include <algorithm>
#include <list>

#include "collisionsoundplayer.h"
#include "constants.h"
#include "model.h"
#include "ofMain.h"

CollisionSoundPlayer::CollisionSoundPlayer()
: sound_wallbounce(), hit(), backhit(), play_next_index_wallbounce(0) {
  for (int i = 0; i < kConcurrentSounds; ++i) {
    sound_wallbounce[i].loadSound("wallbounce.wav");
    sound_wallbounce[i].setMultiPlay(true);
  }
  for (int i = 0; i < 4; ++i) {
    std::stringstream hit_filename, backhit_filename;
    hit_filename << "hit" << (i + 1) << ".wav";
    hit[i].loadSound(hit_filename.str());
    backhit_filename << "backhit" << (i + 1) << ".wav";
    backhit[i].loadSound(backhit_filename.str());
  }
  player1_score.loadSound("p1 score new.wav");
  player1_score7.loadSound("p1 score7 new.wav");
  player1_winfade.loadSound("p1 winfade.wav");
  player2_score.loadSound("p2 score new.wav");
  player2_score7.loadSound("p2 score7 new.wav");
  player2_winfade.loadSound("p2 winfade.wav");
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
      // do nothing
    } else {
      PlaySound(body, sound_wallbounce, play_next_index_wallbounce);
    }
  }
}

void CollisionSoundPlayer::PlayPlayer1Hit(const b2Body *ball) {
  ofSoundPlayer *choice = &hit[static_cast<int>(ofRandom(0, 4))];
  PlaySoundAt(ball, choice);
}

void CollisionSoundPlayer::PlayPlayer1Score(const b2Body *ball) {
  PlaySoundAt(ball, &player1_score);
}

void CollisionSoundPlayer::PlayPlayer1Win(const b2Body *ball) {
  PlaySoundAt(ball, &player1_score7);
  PlaySoundAt(ball, &player1_winfade);
}

void CollisionSoundPlayer::PlayPlayer2Hit(const b2Body *ball) {
  ofSoundPlayer *choice = &backhit[static_cast<int>(ofRandom(0, 4))];
  PlaySoundAt(ball, choice);
}

void CollisionSoundPlayer::PlayPlayer2Score(const b2Body *ball) {
  PlaySoundAt(ball, &player2_score);
}

void CollisionSoundPlayer::PlayPlayer2Win(const b2Body *ball) {
  PlaySoundAt(ball, &player2_score7);
  PlaySoundAt(ball, &player2_winfade);
}

void CollisionSoundPlayer::PlaySound(const b2Body *body, ofSoundPlayer *sound, int &next_index) {
  const float speed = ofClamp(body->GetLinearVelocity().Length() / 10.0, 0.8f, 1.0f);
  sound[next_index].setSpeed(speed + 0.01 * ofRandomf());
  PlaySoundAt(body, &sound[next_index]);
  next_index = (next_index + 1) % kConcurrentSounds;
}

void CollisionSoundPlayer::PlaySoundAt(const b2Body *body, ofSoundPlayer *sound) {
  if (body && sound) {
    sound->setPan(body->GetPosition().x / kHalfCourtWidth);
    sound->play();
  }
}
