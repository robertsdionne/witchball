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

void View::Setup() {
  ofSetFrameRate(60);
  ofSetVerticalSync(true);
  
  color_p1 = ofColor(ofRandom(150,255), 0, ofRandom(150,255));
  color_p2 = ofColor(0, ofRandom(150,255), ofRandom(150,255));
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
  ofPopMatrix();
  ofPopStyle();
}

void View::DrawCourt() const {
  ofBackground(ofColor::black);
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

void View::DrawPlayer(const b2Body *player, ofColor color) const {
  ofPushStyle();
  ofPushMatrix();
  ofTranslate(player->GetPosition().x, player->GetPosition().y);
  ofScale(kPlayerRadius, kPlayerRadius);
  ofSetColor(color);
  ofCircle(ofPoint(), 1.0);
  ofPopMatrix();
  ofPopStyle();
}

void View::DrawPlayers(const Model &model) const {
  DrawPlayer(model.player1_top, color_p1);
  DrawPlayer(model.player1_bottom, color_p1);
  DrawPlayer(model.player2_top, color_p2);
  DrawPlayer(model.player2_bottom, color_p2);
}

void View::SetupViewpoint() const {
  ofMultMatrix(kViewMatrix);
}
