#include "constants.h"
#include "utilities.h"
#include "model.h"

Model::Model()
: world(kZeroGravity), ball(nullptr), border(nullptr),
  player1_top(nullptr), player1_bottom(nullptr), player2_top(nullptr), player2_bottom(nullptr),
  mouse_position(), court_position(CourtPosition::POSITION_1) {}

void Model::Setup() {
  CreateBall();
  CreateBorder();
  CreatePlayers();
}

void Model::Update() {
  Gravity();
  world.Step(kTimeStep, kBox2dVelocityIterations, kBox2dPositionIterations);
}

void Model::CreateBall(ofPoint position, ofVec2f velocity) {
  b2BodyDef ball_definition;
  ball_definition.type = b2_dynamicBody;
  ball_definition.position = Box2dVector(position);
  ball_definition.linearVelocity = Box2dVector(velocity);
  ball_definition.linearDamping = kLinearDamping;
  ball_definition.angularDamping = kAngularDamping;
  ball = world.CreateBody(&ball_definition);
  ball->SetUserData(this);
  b2CircleShape ball_shape;
  ball_shape.m_radius = kBallRadius;
  b2FixtureDef ball_fixture_definition;
  ball_fixture_definition.shape = &ball_shape;
  ball_fixture_definition.density = kDensity;
  ball_fixture_definition.friction = kFriction;
  ball_fixture_definition.restitution = kRestitution;
  ball->CreateFixture(&ball_fixture_definition);
}

void Model::CreateBorder() {
  b2BodyDef border_definition;
  border_definition.position.Set(0.0, 0.0);
  border = world.CreateBody(&border_definition);
  border->SetUserData(this);
  b2Vec2 vertex[4];
  vertex[0].Set(-kHalfCourtWidth, -kHalfCourtHeight);
  vertex[1].Set(kHalfCourtWidth, -kHalfCourtHeight);
  vertex[2].Set(kHalfCourtWidth, kHalfCourtHeight);
  vertex[3].Set(-kHalfCourtWidth, kHalfCourtHeight);
  b2ChainShape border_shape;
  border_shape.CreateLoop(vertex, 4);
  b2FixtureDef border_fixture_definition;
  border_fixture_definition.shape = &border_shape;
  border_fixture_definition.friction = kFriction;
  border->CreateFixture(&border_fixture_definition);
}

b2Body *Model::CreatePlayer(ofPoint position) {
  b2BodyDef player_definition;
  player_definition.position.Set(position.x, position.y);
  b2Body *player = world.CreateBody(&player_definition);
  player->SetUserData(this);
  b2CircleShape player_shape;
  player_shape.m_radius = kPlayerRadius;
  b2FixtureDef player_fixture_definition;
  player_fixture_definition.shape = &player_shape;
  player_fixture_definition.friction = kFriction;
  player->CreateFixture(&player_fixture_definition);
  return player;
}

void Model::CreatePlayers() {
  player1_top = CreatePlayer(kPlayer1TopBack[EnumValue(CourtPosition::POSITION_1)]);
  player1_bottom = CreatePlayer(kPlayer1BottomBack[EnumValue(CourtPosition::POSITION_1)]);
  player2_top = CreatePlayer(kPlayer2TopBack[EnumValue(CourtPosition::POSITION_1)]);
  player2_bottom = CreatePlayer(kPlayer2BottomBack[EnumValue(CourtPosition::POSITION_1)]);
}

void Model::IncrementPlayerOneCount() {
	if(player1_increment_count == 3) {
		player1_score++;
		
		if(player1_score == kPointsToWin) {
			printf("P1 Wins\n");
			player1_score = 0;
			player1_increment_count = 0;
		}
	}
	else {
		player1_increment_count++;
	}
	player2_increment_count = 0;
	
	printf("P1 Score: %d\n",player1_score);
}

void Model::IncrementPlayerTwoCount() {
	if(player2_increment_count == 3) {
		player2_score++;
		if(player2_score == kPointsToWin) {
			printf("P2 Wins\n");
			player2_score = 0;
			player2_increment_count = 0;
		}
	}
	else {
		player2_increment_count++;
	}
	player1_increment_count = 0;
	printf("P2 Score: %d\n",player2_score);
}

void Model::Gravity() {
  const float y = ball->GetPosition().y;
  if (y > kBallRadius) {
    ball->ApplyForceToCenter(ball->GetMass() * kGravity);
  }  else if (0 < y && y <= kBallRadius) {
    ball->ApplyForceToCenter(ball->GetMass() * Lerp(b2Vec2(), kGravity, y / kBallRadius));
  } else if (-kBallRadius <= y && y < 0) {
    ball->ApplyForceToCenter(ball->GetMass() * Lerp(b2Vec2(), kAntiGravity, -y / kBallRadius));
  } else if (y < -kBallRadius) {
    ball->ApplyForceToCenter(ball->GetMass() * kAntiGravity);
  }
}
