#include "constants.h"
#include "utilities.h"
#include "witchball.h"
#include "titlescreenmodel.h"
#include "ofChaser.h"

TitleScreenModel::TitleScreenModel()
: world(kZeroGravity), player1_top(nullptr), player1_bottom(nullptr), player2_top(nullptr), player2_bottom(nullptr),
court_position(CourtPosition::POSITION_1) {}

void TitleScreenModel::Setup() {
  CreatePlayers();
}

void TitleScreenModel::Update() {
	
  UpdatePlayerPosition(player1_top,
                       Lerp(GetPlayer1TopBack(EnumValue(court_position)),
                            GetPlayer1TopForward(EnumValue(court_position)), player1_position));
  UpdatePlayerPosition(player1_bottom,
                       Lerp(GetPlayer1BottomBack(EnumValue(court_position)),
                            GetPlayer1BottomForward(EnumValue(court_position)), player1_position));
  UpdatePlayerPosition(player2_top,
                       Lerp(GetPlayer2TopBack(EnumValue(court_position)),
                            GetPlayer2TopForward(EnumValue(court_position)), player2_position));
  UpdatePlayerPosition(player2_bottom,
                       Lerp(GetPlayer2BottomBack(EnumValue(court_position)),
                            GetPlayer2BottomForward(EnumValue(court_position)), player2_position));
  
	if(player1_position == 1.0f && player2_position == 1.0f) {
		dynamic_cast<WitchBall *>(ofGetAppPtr())->RunPlayScreen();
	}
  world.Step(kTimeStep, kBox2dVelocityIterations, kBox2dPositionIterations);
}



b2Body *TitleScreenModel::CreatePlayer(ofPoint position) {
  b2BodyDef player_definition;
  player_definition.position.Set(position.x, position.y);
  b2Body *player = world.CreateBody(&player_definition);
  player->SetUserData(this);
  b2CircleShape player_shape;
  player_shape.m_radius = kPlayerHitRadius;
  b2FixtureDef player_fixture_definition;
  player_fixture_definition.shape = &player_shape;
  player_fixture_definition.friction = kFriction;
  player->CreateFixture(&player_fixture_definition);
  return player;
}

void TitleScreenModel::CreatePlayers() {
  player1_top = CreatePlayer(GetPlayer1TopBack(EnumValue(CourtPosition::POSITION_1)));
  player1_bottom = CreatePlayer(GetPlayer1BottomBack(EnumValue(CourtPosition::POSITION_1)));
  player2_top = CreatePlayer(GetPlayer2TopBack(EnumValue(CourtPosition::POSITION_1)));
  player2_bottom = CreatePlayer(GetPlayer2BottomBack(EnumValue(CourtPosition::POSITION_1)));
}

void TitleScreenModel::UpdatePlayerPosition(b2Body *player, ofPoint target) {
  const b2Vec2 new_position = b2Vec2(ofLerp(player->GetPosition().x, target.x, kControllerRateX),
                                     ofLerp(player->GetPosition().y, target.y, kControllerRateY));
  player->SetTransform(new_position, 0.0);
}
