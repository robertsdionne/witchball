#include <Box2D/Box2D.h>

#include "constants.h"
#include "model.h"
#include "ofMain.h"
#include "utilities.h"
#include "view.h"

void View::Draw(const Model &model) const {
  DrawFramesPerSecond();
  SetupViewpoint();
  DrawCourt();
  DrawPlayers(model);
  DrawBall(model.ball);
}

void View::Setup() const {
  ofSetFrameRate(60);
  ofSetVerticalSync(true);
}

void View::DrawBall(const b2Body *ball) const {
  ofPushStyle();
  ofPushMatrix();
  ofTranslate(ball->GetPosition().x, ball->GetPosition().y);
  ofRotateZ(ofRadToDeg(ball->GetAngle()));
  ofScale(kBallRadius, kBallRadius);
  ofSetColor(ofColor::white);
  ofCircle(ofPoint(), 1.0);
  ofSetColor(ofColor::black);
  ofLine(ofPoint(-1.0, 0.0), ofPoint(1.0, 0.0));
  ofLine(ofPoint(0.0, -1.0), ofPoint(0.0, 1.0));
  ofPopMatrix();
  ofPopStyle();
}

void View::DrawCourt() const {
  ofPushStyle();
  ofSetColor(ofColor::white);
  ofLine(ofPoint(-kHalfCourtWidth, 0.0), ofPoint(kHalfCourtWidth, 0.0));
  ofPopStyle();
}

void View::DrawFramesPerSecond() const {
  ofPushStyle();
  ofDrawBitmapString(ofToString(ofGetFrameRate()), ofPoint(0, 10));
  ofPopStyle();
}

void View::DrawPlayer(const b2Body *player) const {
  ofPushStyle();
  ofPushMatrix();
  ofTranslate(player->GetPosition().x, player->GetPosition().y);
  ofScale(kBallRadius, kBallRadius);
  ofSetColor(ofColor::white);
  ofCircle(ofPoint(), 1.0);
  ofPopMatrix();
  ofPopStyle();
}

void View::DrawPlayers(const Model &model) const {
  DrawPlayer(model.player1_top);
  DrawPlayer(model.player1_bottom);
  DrawPlayer(model.player2_top);
  DrawPlayer(model.player2_bottom);
}

void View::SetupViewpoint() const {
  ofMultMatrix(kViewMatrix);
}
