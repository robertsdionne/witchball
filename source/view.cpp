#include <Box2D/Box2D.h>
#include <list>

#include "collisionscorekeeper.h"
#include "constants.h"
#include "model.h"
#include "ofMain.h"
#include "utilities.h"
#include "view.h"

void View::Draw(const Model &model) const {
  DrawFramesPerSecond();
  ofPushMatrix();
  SetupViewpoint();
  ofBackground(ofColor::black);
  //CHASERS-------------------
  for (int i = 0; i < model.nChasers; i++){
    model.topChaser[i]->draw();
    model.botChaser[i]->draw();
    model.rightChaser[i]->draw();
    model.leftChaser[i]->draw();
  }
  DrawGravity(model);
  DrawScore(model);
  DrawCourt(model);
  DrawPlayers(model);
  ofColor ball_color = model.player1_increment_count > 2 ? color_p1 :
      model.player2_increment_count > 2 ? color_p2 : ofColor::white;
  DrawBallTrail(model, model.ball_trail, ball_color);
  DrawStrikeIndicator(model);
  DrawBall(model.ball, ball_color);
  ofPopMatrix();
}

void View::Setup() {
  ofSetFrameRate(60);
  ofSetVerticalSync(true);
  ofEnableAlphaBlending();
  
  color_p1 = ofColor(ofRandom(150, 255), 0, ofRandom(150, 255));
  color_p2 = ofColor(0, ofRandom(150, 255), ofRandom(150, 255));
}

void View::DrawStrikeIndicator(const Model &model) const {
  ofPushMatrix();
  ofTranslate(model.strike_position.x, model.strike_position.y);
  ofScale(model.strike_alpha * kPlayerRadius, model.strike_alpha * kPlayerRadius);
  ofSetColor(model.last_hit_player == 1 ? color_p1 : model.last_hit_player == 2 ? color_p2 : ofColor::white,
             model.strike_alpha * 255.0);
  ofCircle(ofPoint(), 1.0);
  ofPopMatrix();
  if (model.counter_clockwise_alpha) { //green triangle
    const float alpha = -10.0 * (1.0 - model.counter_clockwise_alpha);
    ofPushMatrix();
    ofTranslate(-kCourtWidth / 4.0, kCourtHeight / 4.0);
    ofSetColor(color_p2, model.counter_clockwise_alpha * 255.0);
    ofTranslate(0, alpha);
    ofTriangle(-0.5, 0.5, 0.5, 0.5, 0, -1);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(-kCourtWidth / 4.0, -kCourtHeight / 4.0);
    ofRotateZ(90);
    ofSetColor(color_p2, model.counter_clockwise_alpha * 255.0);
    ofTranslate(0, 2*alpha);
    ofTriangle(-0.5, 0.5, 0.5, 0.5, 0, -1);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(kCourtWidth / 4.0, -kCourtHeight / 4.0);
    ofRotateZ(180);
    ofSetColor(color_p2, model.counter_clockwise_alpha * 255.0);
    ofTranslate(0, alpha);
    ofTriangle(-0.5, 0.5, 0.5, 0.5, 0, -1);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(kCourtWidth / 4.0, kCourtHeight / 4.0);
    ofRotateZ(270);
    ofSetColor(color_p2, model.counter_clockwise_alpha * 255.0);
    ofTranslate(0, 2*alpha);
    ofTriangle(-0.5, 0.5, 0.5, 0.5, 0, -1);
    ofPopMatrix();
  }
  if (model.clockwise_alpha) { //pink triangle
    const float alpha = 10.0 * (1.0 - model.clockwise_alpha);
    ofPushMatrix();
    ofTranslate(-kCourtWidth / 4.0, kCourtHeight / 4.0);
    ofRotateZ(-90);
    ofSetColor(color_p1, model.clockwise_alpha * 255.0);
    ofTranslate(0, 2*alpha);
    ofTriangle(-0.5, -0.5, 0.5, -0.5, 0, 1);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(-kCourtWidth / 4.0, -kCourtHeight / 4.0);
    ofRotateZ(0);
    ofSetColor(color_p1, model.clockwise_alpha * 255.0);
    ofTranslate(0, alpha);
    ofTriangle(-0.5, -0.5, 0.5, -0.5, 0, 1);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(kCourtWidth / 4.0, -kCourtHeight / 4.0);
    ofRotateZ(90);
    ofSetColor(color_p1, model.clockwise_alpha * 255.0);
    ofTranslate(0, 2*alpha);
    ofTriangle(-0.5, -0.5, 0.5, -0.5, 0, 1);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(kCourtWidth / 4.0, kCourtHeight / 4.0);
    ofRotateZ(180);
    ofSetColor(color_p1, model.clockwise_alpha * 255.0);
    ofTranslate(0, alpha);
    ofTriangle(-0.5, -0.5, 0.5, -0.5, 0, 1);
    ofPopMatrix();
  }
}

void View::DrawBall(const b2Body *ball, ofColor color) const {
  ofPushStyle();
  ofPushMatrix();
  ofTranslate(ball->GetPosition().x, ball->GetPosition().y);
  ofRotateZ(ofRadToDeg(ball->GetAngle()));
  ofScale(kBallRadius, kBallRadius);
  ofSetColor(color);
  ofCircle(ofPoint(), 1.0);
  if (!kFixedRotation) {
    ofSetColor(ofColor::black);
    ofLine(ofPoint(-1.0, 0.0), ofPoint(1.0, 0.0));
  }
  ofPopMatrix();
  ofPopStyle();
}

void View::DrawBallTrail(const Model &model, const std::list<ofVec2f> ball_trail, ofColor color) const {
  float alpha = kBallTrailAlphaStart;
  float player_alpha = kPlayerTrailAlphaStart;
  float scale = 1.0;
  ofPushStyle();
  Model temp_model;
  temp_model.Setup();
  temp_model.elapsed_time = ofGetElapsedTimef();
  temp_model.ball->SetTransform(model.ball->GetPosition(), model.ball->GetAngle());
  temp_model.ball->SetLinearVelocity(model.ball->GetLinearVelocity());
  temp_model.ball->SetAngularVelocity(model.ball->GetAngularVelocity());
  temp_model.player1_position = model.player1_position;
  temp_model.player2_position = model.player2_position;
  temp_model.player1_top->SetTransform(model.player1_top->GetPosition(), 0.0);
  temp_model.player1_bottom->SetTransform(model.player1_bottom->GetPosition(), 0.0);
  temp_model.player2_top->SetTransform(model.player2_top->GetPosition(), 0.0);
  temp_model.player2_bottom->SetTransform(model.player2_bottom->GetPosition(), 0.0);
  temp_model.top_left_quadrant_gravity = model.top_left_quadrant_gravity;
  temp_model.top_right_quadrant_gravity = model.top_right_quadrant_gravity;
  temp_model.bottom_left_quadrant_gravity = model.bottom_left_quadrant_gravity;
  temp_model.bottom_right_quadrant_gravity = model.bottom_right_quadrant_gravity;
  temp_model.mouse_gravity_position = model.mouse_gravity_position;
  temp_model.mouse_mass_scale = model.mouse_mass_scale;
  temp_model.mouse_position = model.mouse_position;
  temp_model.mouse_pressed = model.mouse_pressed;
  temp_model.court_position = model.court_position;
  temp_model.gravity_angle = model.gravity_angle;
  temp_model.player1_top->SetActive(false);
  temp_model.player1_bottom->SetActive(false);
  temp_model.player2_top->SetActive(false);
  temp_model.player2_bottom->SetActive(false);
  temp_model.play_gravity = model.play_gravity;
  collisionscorekeeper keeper;
  temp_model.world.SetContactListener(&keeper);
  for (int i = 0; i < kBallTrailLength * kBallTrailSpacing; ++i) {
    temp_model.elapsed_time += kTimeStep;
    temp_model.Update();
    if ((ofGetFrameNum() + i) % kBallTrailSpacing == 0) {
      ofPushMatrix();
      ofTranslate(temp_model.ball->GetPosition().x, temp_model.ball->GetPosition().y);
      ofScale(scale * kBallRadius, scale * kBallRadius);
      ofSetColor(color, alpha);
      ofCircle(ofPoint(), 1.0);
      ofPopMatrix();
      ofPushMatrix();
      ofTranslate(temp_model.player1_top->GetPosition().x, temp_model.player1_top->GetPosition().y);
      ofScale(scale * kPlayerRadius, scale * kPlayerRadius);
      ofSetColor(color_p1, player_alpha);
      ofCircle(ofPoint(), 1.0);
      ofPopMatrix();
      ofPushMatrix();
      ofTranslate(temp_model.player1_bottom->GetPosition().x, temp_model.player1_bottom->GetPosition().y);
      ofScale(scale * kPlayerRadius, scale * kPlayerRadius);
      ofSetColor(color_p1, player_alpha);
      ofCircle(ofPoint(), 1.0);
      ofPopMatrix();
      ofPushMatrix();
      ofTranslate(temp_model.player2_top->GetPosition().x, temp_model.player2_top->GetPosition().y);
      ofScale(scale * kPlayerRadius, scale * kPlayerRadius);
      ofSetColor(color_p2, player_alpha);
      ofCircle(ofPoint(), 1.0);
      ofPopMatrix();
      ofPushMatrix();
      ofTranslate(temp_model.player2_bottom->GetPosition().x, temp_model.player2_bottom->GetPosition().y);
      ofScale(scale * kPlayerRadius, scale * kPlayerRadius);
      ofSetColor(color_p2, player_alpha);
      ofCircle(ofPoint(), 1.0);
      ofPopMatrix();
      scale *= 1.0;
      alpha *= kBallTrailFadeCoefficient;
      player_alpha *= kPlayerTrailFadeCoefficient;
    }
  }
  ofPopStyle();
}

void View::DrawCourt(const Model &model) const {
  ofPushStyle();
  // Draw a horizontal or vertical court line depending on the current gravity configuration.
  ofSetLineWidth(10.0);
  ofSetColor(ofColor::white);
  ofLine(-kCourtWidth / 2.0, 0.0, kCourtWidth / 2.0, 0.0);
  ofSetColor(model.last_hit_player == 1 ? color_p1 : model.last_hit_player == 2 ? color_p2 : ofColor::white);
  ofLine(0.0, 2.0 * kPlayerRadius, 0.0, -2.0 * kPlayerRadius);
  // Draw connectors between the players and their nearest vertical walls.
  ofSetLineWidth(3.0);
  ofSetColor(color_p1);
  float player1_top_offset = -0.8 * kPlayerRadius;
  float player1_bottom_offset = 0.8 * kPlayerRadius;
  float player2_top_offset = -0.8 * kPlayerRadius;
  float player2_bottom_offset = 0.8 * kPlayerRadius;
  ofLine(ofPoint(kPlayer1TopForward[EnumValue(model.court_position)].x, model.player1_top->GetPosition().y + player1_top_offset),
         ofPoint(kPlayer1TopBack[EnumValue(model.court_position)].x, model.player1_top->GetPosition().y + player1_top_offset));
  ofLine(ofPoint(kPlayer1BottomForward[EnumValue(model.court_position)].x, model.player1_bottom->GetPosition().y +
                 player1_bottom_offset),
         ofPoint(kPlayer1BottomBack[EnumValue(model.court_position)].x, model.player1_bottom->GetPosition().y +
                 player1_bottom_offset));
  ofSetColor(color_p2);
  ofLine(ofPoint(kPlayer2TopForward[EnumValue(model.court_position)].x, model.player2_top->GetPosition().y + player2_top_offset),
         ofPoint(kPlayer2TopBack[EnumValue(model.court_position)].x, model.player2_top->GetPosition().y + player2_top_offset));
  ofLine(ofPoint(kPlayer2BottomForward[EnumValue(model.court_position)].x, model.player2_bottom->GetPosition().y +
                 player2_bottom_offset),
         ofPoint(kPlayer2BottomBack[EnumValue(model.court_position)].x, model.player2_bottom->GetPosition().y +
                 player2_bottom_offset));
  ofPopStyle();
  ofSetLineWidth(1.0);
}

void View::DrawFramesPerSecond() const {
  ofPushStyle();
  ofDrawBitmapString(ofToString(ofGetFrameRate()), ofPoint(0, 10));
  ofPopStyle();
}

void View::DrawGravity(const Model &model) const {
  // Draw arrows indicating the strength and direction of gravity, in each quadrant.
  if (model.draw_gravity == Model::GravityVisual::QUADRANT) {
    for (float i = -kHalfCourtWidth; i <= kHalfCourtWidth; i += 1.0) {
      for (float j = -kHalfCourtHeight; j <= kHalfCourtHeight; j += 1.0) {
        DrawGravityAt(ofPoint(i, j), model);
      }
    }
  }
  // Draw the source of mouse gravity.
  ofPushStyle();
  ofPushMatrix();
  ofTranslate(model.mouse_gravity_position.x, model.mouse_gravity_position.y);
  const float radius = sqrt(model.mouse_mass_scale * kMouseMass / M_PI / kMouseDensity);
  ofScale(radius, radius);
  ofSetColor(ofColor::slateGrey, 128.0);
  ofCircle(ofPoint(), 1.0);
  ofPopMatrix();
  ofPopStyle();
}

void View::DrawGravityAt(ofPoint position, const Model &model) const {
  const ofVec2f gravity = OpenFrameworksVector(model.GravityAt(Box2dVector(position)));
  ofPushStyle();
  ofPushMatrix();
  ofTranslate(position.x, position.y);
  ofScale(0.5, 0.5);
  ofSetColor(ofColor::slateGrey, 64.0);
  const ofVec2f arrowhead = gravity / 9.81;
  ofTriangle(arrowhead, kBallRadius * arrowhead.perpendiculared(),
             -kBallRadius * arrowhead.perpendiculared());
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
  ofSetColor(color_p1 / 3.0, 127.0);
  for (int i = 0; i < model.player1_score; ++i) {
    ofPushMatrix();
    ofRect(-kHalfCourtWidth + i * 1.1, -kHalfCourtHeight, 1.0, kCourtHeight);
    ofPopMatrix();
  }
  ofSetColor(color_p2 / 3.0, 127.0);
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
