
#include <Box2D/Box2D.h>
#include "titlescreenview.h"
#include "constants.h"
#include "ofMain.h"
#include "utilities.h"


TitleScreenView::TitleScreenView() {
	p1_top.set(-9.7, 0.28);
	p2_top.set(9.7, 0.28);
	
	p1_bottom.set(9.7, -0.28);
	p2_bottom.set(-9.7, -0.28);
}

TitleScreenView::~TitleScreenView() {
	
}


void TitleScreenView::Setup() {
  ofSetFrameRate(kFrameRate);
  ofSetVerticalSync(true);
  ofEnableAlphaBlending();
  
  color_p1 = ofColor(ofRandom(150, 255), 0, ofRandom(150, 255));
  color_p2 = ofColor(0, ofRandom(150, 255), ofRandom(150, 255));
}

void TitleScreenView::Draw() const {
  ofBackground(ofColor::black);
  DrawFramesPerSecond();
  ofPushMatrix();
  SetupViewpoint();

	DrawCourt();
	DrawPlayers();
	ofPopMatrix();
}

void TitleScreenView::DrawCourt() const {
	ofPushStyle();
  // Draw a horizontal or vertical court line depending on the current gravity configuration.
  ofSetLineWidth(10.0);
  ofSetColor(ofColor::white);
  ofLine(-kCourtWidth / 2.0, 0.0, kCourtWidth / 2.0, 0.0);
  ofSetColor(ofColor::white);
  ofLine(0.0, 2.0 * kPlayerRadius, 0.0, -2.0 * kPlayerRadius);
  // Draw connectors between the players and their nearest vertical walls.
  /*
	ofSetLineWidth(3.0);
  ofSetColor(color_p1);
  float player1_top_offset = -0.8 * kPlayerRadius;
  float player1_bottom_offset = 0.8 * kPlayerRadius;
  float player2_top_offset = -0.8 * kPlayerRadius;
  float player2_bottom_offset = 0.8 * kPlayerRadius;
	ofLine(0,ofGetHeight() * 0.5,ofGetWidth(),ofGetHeight() * 0.5);
  ofLine(ofPoint(ofVec2f(-kPlayerRadius, kPlayerRadius).x, ofPoint(0,ofGetHeight() * 0.5).y),
         ofPoint(GetPlayer1TopBack(EnumValue(model.court_position)).x, model.player1_top->GetPosition().y + player1_top_offset));
  ofLine(ofPoint(GetPlayer1BottomForward(EnumValue(model.court_position)).x, model.player1_bottom->GetPosition().y +
                 player1_bottom_offset),
         ofPoint(GetPlayer1BottomBack(EnumValue(model.court_position)).x, model.player1_bottom->GetPosition().y +
                 player1_bottom_offset));
  ofSetColor(color_p2);
  ofLine(ofPoint(GetPlayer2TopForward(EnumValue(model.court_position)).x, model.player2_top->GetPosition().y + player2_top_offset),
         ofPoint(GetPlayer2TopBack(EnumValue(model.court_position)).x, model.player2_top->GetPosition().y + player2_top_offset));
  ofLine(ofPoint(GetPlayer2BottomForward(EnumValue(model.court_position)).x, model.player2_bottom->GetPosition().y +
                 player2_bottom_offset),
         ofPoint(GetPlayer2BottomBack(EnumValue(model.court_position)).x, model.player2_bottom->GetPosition().y +
                 player2_bottom_offset));
	*/
  ofPopStyle();
  ofSetLineWidth(1.0);

}

void TitleScreenView::DrawPlayer(ofPoint playerPosition, ofColor color) const {
	ofPushStyle();
	ofPushMatrix();
	ofTranslate(playerPosition.x, playerPosition.y);
	ofScale(kPlayerRadius, kPlayerRadius);
	ofSetColor(color);
	ofCircle(ofPoint(), 1.0);
	ofPopMatrix();
	ofPopStyle();
}

void TitleScreenView::DrawPlayers() const {
	/*
	ofPushStyle();
  ofPushMatrix();
  ofTranslate(player->GetPosition().x, player->GetPosition().y);
  ofScale(kPlayerRadius, kPlayerRadius);
  ofSetColor(color);
  ofCircle(ofPoint(), 1.0);
  ofPopMatrix();
  ofPopStyle();
	*/
	DrawPlayer(p1_top, color_p1);
  DrawPlayer(p1_bottom, color_p1);
	DrawPlayer(p2_top, color_p2);
  DrawPlayer(p2_bottom, color_p2);
	/*
	ofPushStyle();
	ofPushMatrix();
	ofSetColor(color_p1);
	ofCircle(p1_top.x, p1_top.y, kPlayerRadius);
	ofCircle(p1_bottom.x, p1_bottom.y, kPlayerRadius);
	ofSetColor(color_p2);
	ofCircle(p2_top.x, p2_top.y, kPlayerRadius);
	ofCircle(p2_bottom.x, p2_bottom.y, kPlayerRadius);
	ofPopMatrix();
	ofPopStyle();
	*/
}

void TitleScreenView::DrawFramesPerSecond() const {
  ofPushStyle();
  ofDrawBitmapString(ofToString(ofGetFrameRate()), ofPoint(0, 10));
  ofPopStyle();
}
void TitleScreenView::SetupViewpoint() const {
  ofMultMatrix(kViewMatrix);
}