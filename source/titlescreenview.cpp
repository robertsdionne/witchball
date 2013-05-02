
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

void TitleScreenView::Draw(const TitleScreenModel &model) const {
  ofBackground(ofColor::black);
  DrawFramesPerSecond();
  ofPushMatrix();
  SetupViewpoint();

	DrawTriangles(model.player1_position,model.player2_position);
	DrawCourt();
	DrawPlayers(model);	
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
	ofPopStyle();
  ofSetLineWidth(1.0);

}

void TitleScreenView::DrawPlayer(const b2Body *player, ofColor color) const {
  ofPushStyle();
  ofPushMatrix();
  ofTranslate(player->GetPosition().x, player->GetPosition().y);
  ofScale(kPlayerRadius, kPlayerRadius);
  ofSetColor(color);
  ofCircle(ofPoint(), 1.0);
  ofPopMatrix();
  ofPopStyle();
}

void TitleScreenView::DrawPlayers(const TitleScreenModel &model) const {
	DrawPlayer(model.player1_top, color_p1);
  DrawPlayer(model.player1_bottom, color_p1);
	DrawPlayer(model.player2_top, color_p2);
  DrawPlayer(model.player2_bottom, color_p2);
}

void TitleScreenView::DrawTriangles(float player1_position, float player2_position) const {
	ofPushStyle();
	ofSetColor(color_p1.r, color_p1.g, color_p1.b,player1_position * 255);
	ofFill();
	ofTriangle(-kHalfCourtWidth, kHalfCourtHeight, -kHalfCourtWidth * 0.75, -kHalfCourtHeight, -kHalfCourtWidth * 0.5, kCourtHeight);
	ofTriangle(-kHalfCourtWidth * 0.5, kHalfCourtHeight, -kHalfCourtWidth * 0.25, -kHalfCourtHeight, 0, kCourtHeight);
	ofSetColor(color_p2.r, color_p2.g, color_p2.b,player2_position * 255);
	ofTriangle(0, kHalfCourtHeight, kHalfCourtWidth, kHalfCourtHeight * 0.5, 0, 0);
	ofTriangle(0, 0, kHalfCourtWidth, -kHalfCourtHeight * 0.5, 0, -kHalfCourtHeight);
	
	ofPopStyle();
}

void TitleScreenView::DrawFramesPerSecond() const {
  ofPushStyle();
  ofDrawBitmapString(ofToString(ofGetFrameRate()), ofPoint(0, 10));
  ofPopStyle();
}
void TitleScreenView::SetupViewpoint() const {
  ofMultMatrix(kViewMatrix);
}