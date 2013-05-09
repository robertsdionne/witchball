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
                       Lerp(GetPlayer1TopLeft(EnumValue(court_position)),
                            GetPlayer1TopRight(EnumValue(court_position)), Player1Position()));
  UpdatePlayerPosition(player1_bottom,
                       Lerp(GetPlayer1BottomLeft(EnumValue(court_position)),
                            GetPlayer1BottomRight(EnumValue(court_position)), Player1Position()));
  UpdatePlayerPosition(player2_top,
                       Lerp(GetPlayer2TopLeft(EnumValue(court_position)),
                            GetPlayer2TopRight(EnumValue(court_position)), Player2Position()));
  UpdatePlayerPosition(player2_bottom,
                       Lerp(GetPlayer2BottomLeft(EnumValue(court_position)),
                            GetPlayer2BottomRight(EnumValue(court_position)), Player2Position()));
  
	if(player1_position == 1.0f && player2_position == 1.0f) {
      dynamic_cast<WitchBall *>(ofGetAppPtr())->RunPlayScreen();
      return;
	}
  world.Step(kTimeStep, kBox2dVelocityIterations, kBox2dPositionIterations);
}

float TitleScreenModel::Player1Position() {
  switch (court_position) {
      break;
    case CourtPosition::POSITION_2:
    case CourtPosition::POSITION_3:
      return 1.0 - player1_position;
      break;
    case CourtPosition::POSITION_1:
    case CourtPosition::POSITION_4:
      return player1_position;
      break;
  }
}

float TitleScreenModel::Player2Position() {
  switch (court_position) {
      break;
    case CourtPosition::POSITION_3:
    case CourtPosition::POSITION_4:
      return 1.0 - player2_position;
      break;
    case CourtPosition::POSITION_1:
    case CourtPosition::POSITION_2:
      return player2_position;
      break;
  }
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
  player1_top = CreatePlayer(GetPlayer1TopLeft(EnumValue(CourtPosition::POSITION_1)));
  player1_bottom = CreatePlayer(GetPlayer1BottomLeft(EnumValue(CourtPosition::POSITION_1)));
  player2_top = CreatePlayer(GetPlayer2TopLeft(EnumValue(CourtPosition::POSITION_1)));
  player2_bottom = CreatePlayer(GetPlayer2BottomLeft(EnumValue(CourtPosition::POSITION_1)));
}

void TitleScreenModel::UpdatePlayerPosition(b2Body *player, ofPoint target) {
  const b2Vec2 new_position = b2Vec2(ofLerp(player->GetPosition().x, target.x, kControllerRateX),
                                     ofLerp(player->GetPosition().y, target.y, kControllerRateY));
  player->SetTransform(new_position, 0.0);
}
