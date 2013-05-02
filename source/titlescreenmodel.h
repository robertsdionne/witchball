//
//  titlescreenmodel.h
//  witchball
//
//  Created by Shervin Ghazazani on 5/1/13.
//
//

#ifndef WITCHBALL_TITLESCREENMODEL_H
#define WITCHBALL_TITLESCREENMODEL_H

#include <Box2D/Box2D.h>
#include <list>

#include "ofChaser.h"
#include "ofMain.h"

class TitleScreenModel {
public:
  TitleScreenModel();
  
  virtual ~TitleScreenModel() {}
  
  void Setup();
  
  void Update();
	
private:
  b2Body *CreatePlayer(ofPoint position = ofPoint());
  
  void CreatePlayers();
  
  void UpdatePlayerPosition(b2Body *player, ofPoint target);
  
  void UpdateTrails();
	
public:
  enum class CourtPosition {
    POSITION_1,
    POSITION_2,
    POSITION_3,
    POSITION_4
  };
  
  b2World world;
  
  b2Body *player1_top, *player1_bottom, *player2_top, *player2_bottom;
  
  CourtPosition court_position;
  
	float player1_position;
  float player2_position;
  
  bool show_sliders = false;
};

#endif  // WITCHBALL_TITLESCREENMODEL_H
