#ifndef WITCHBALL_TITLESCREENVIEW_H_
#define WITCHBALL_TITLESCREENVIEW_H_

#define GRID_W 10
#define GRID_H 5

#include "ofMain.h"
#include "model.h"

class TitleScreenView {
public:
	TitleScreenView();
	
	virtual ~TitleScreenView();
	
	void Draw() const;
	
	void Setup();
	
private:
	void DrawCourt() const;
	void DrawPlayer() const;
	void DrawPlayer(ofPoint playerPosition, ofColor color) const;
	void DrawPlayers() const;
	
	void DrawFramesPerSecond() const;
	void SetupViewpoint() const;
	
	ofColor color_p1;
	ofColor color_p2;
	
	ofPoint p1_top, p2_top, p1_bottom, p2_bottom;
};

#endif  // WITCHBALL_TITLESCREENVIEW_H_
