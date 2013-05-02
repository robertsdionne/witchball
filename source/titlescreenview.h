#ifndef WITCHBALL_TITLESCREENVIEW_H_
#define WITCHBALL_TITLESCREENVIEW_H_

#define GRID_W 10
#define GRID_H 5

#include "ofMain.h"
#include "titlescreenmodel.h"

class TitleScreenView {
public:
	TitleScreenView();
	
	virtual ~TitleScreenView();
	
	void Draw(const TitleScreenModel &model) const;
	
	void Setup();
	
private:
	void DrawCourt() const;
	void DrawPlayer(const b2Body *player, ofColor color) const;
  void DrawPlayers(const TitleScreenModel &model) const;
	void DrawPlayer(ofPoint playerPosition, ofColor color) const;
	void DrawTriangles(float player1_position, float player2_position) const;
	void DrawFramesPerSecond() const;
	void SetupViewpoint() const;
	
	ofColor color_p1;
	ofColor color_p2;
	
	ofPoint p1_top, p2_top, p1_bottom, p2_bottom;
};

#endif  // WITCHBALL_TITLESCREENVIEW_H_
