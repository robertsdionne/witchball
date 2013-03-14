#include <Box2D/Box2D.h>

#include "constants.h"
#include "model.h"
#include "ofMain.h"
#include "utilities.h"
#include "view.h"

void View::Draw(const Model &model) const {
  DrawFramesPerSecond();
  SetupViewpoint();
  ofBackground(ofColor::black);
  DrawScore(model);
  DrawGravity(model);
  DrawCourt(model);
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

void View::DrawCourt(const Model &model) const {
  ofPushStyle();
  // Draw a horizontal or vertical court line depending on the current gravity configuration.
  ofSetColor(ofColor::white);
  if (EnumValue(model.court_position) % 2 == 0) {
    ofLine(ofPoint(-kHalfCourtWidth, 0.0), ofPoint(kHalfCourtWidth, 0.0));
  } else {
    ofLine(ofPoint(0.0, -kHalfCourtHeight), ofPoint(0.0, kHalfCourtHeight));
  }
  // Draw connectors between the players and their nearest vertical walls.
  ofSetColor(color_p1 / 2.0);
  ofLine(OpenFrameworksVector(model.player1_top->GetPosition()),
         ofPoint(kPlayer1TopBack[EnumValue(model.court_position)].x, model.player1_top->GetPosition().y));
  ofLine(OpenFrameworksVector(model.player1_bottom->GetPosition()),
         ofPoint(kPlayer1BottomBack[EnumValue(model.court_position)].x, model.player1_bottom->GetPosition().y));
  ofSetColor(color_p2 / 2.0);
  ofLine(OpenFrameworksVector(model.player2_top->GetPosition()),
         ofPoint(kPlayer2TopBack[EnumValue(model.court_position)].x, model.player2_top->GetPosition().y));
  ofLine(OpenFrameworksVector(model.player2_bottom->GetPosition()),
         ofPoint(kPlayer2BottomBack[EnumValue(model.court_position)].x, model.player2_bottom->GetPosition().y));
  ofPopStyle();
}

void View::DrawFramesPerSecond() const {
  ofPushStyle();
  ofDrawBitmapString(ofToString(ofGetFrameRate()), ofPoint(0, 10));
  ofPopStyle();
}

void View::DrawGravity(const Model &model) const {
  // Draw arrows indicating the strength and direction of gravity, either at the ball or in each
  // quadrant.
  if (EnumValue(model.draw_gravity) & 1) {
    DrawGravityAt(OpenFrameworksVector(model.ball->GetPosition()), model);
  }
  if (EnumValue(model.draw_gravity) & 2) {
    DrawGravityAt(ofPoint(-kHalfCourtWidth / 2.0, -kHalfCourtHeight / 2.0), model);
    DrawGravityAt(ofPoint(-kHalfCourtWidth / 2.0, kHalfCourtHeight / 2.0), model);
    DrawGravityAt(ofPoint(kHalfCourtWidth / 2.0, -kHalfCourtHeight / 2.0), model);
    DrawGravityAt(ofPoint(kHalfCourtWidth / 2.0, kHalfCourtHeight / 2.0), model);
  }
}

void View::DrawGravityAt(ofPoint position, const Model &model) const {
  const ofVec2f gravity = OpenFrameworksVector(model.GravityAt(Box2dVector(position)));
  ofPushStyle();
  ofPushMatrix();
  ofTranslate(position.x, position.y);
  ofSetColor(ofColor::slateGrey);
  const ofVec2f arrowhead = gravity / 9.81;
  ofTriangle(arrowhead, ofVec2f(kBallRadius, 0), -ofVec2f(kBallRadius, 0));
  ofPopMatrix();
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

void View::DrawScore(const Model &model) const {
  ofPushStyle();
  // Draw a number of rectangles for each player's score.
  ofSetColor(color_p1 / 3.0);
  for (int i = 0; i < model.player1_score; ++i) {
    ofPushMatrix();
    ofRect(-kHalfCourtWidth + i * 1.1, -kHalfCourtHeight, 1.0, kCourtHeight);
    ofPopMatrix();
  }
  ofSetColor(color_p2 / 3.0);
  for (int i = 0 ; i < model.player2_score; ++i) {
    ofPushMatrix();
    ofRect(kHalfCourtWidth - i * 1.1, -kHalfCourtHeight, -1.0, kCourtHeight);
    ofPopMatrix();
  }
  ofPopStyle();
}

void View::SetupViewpoint() const {
  ofMultMatrix(kViewMatrix);
}
