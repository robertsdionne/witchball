#include "constants.h"
#include "utilities.h"
#include "model.h"

Model::Model()
: world(kZeroGravity) {}

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
  b2BodyDef ball_body_definition;
  ball_body_definition.type = b2_dynamicBody;
  ball_body_definition.position = Box2dVector(position);
  ball_body_definition.linearVelocity = Box2dVector(velocity);
  ball_body_definition.linearDamping = kLinearDamping;
  ball_body_definition.angularDamping = kAngularDamping;
  ball_body = world.CreateBody(&ball_body_definition);
  b2CircleShape ball_shape;
  ball_shape.m_radius = kBallRadius;
  b2FixtureDef ball_fixture_definition;
  ball_fixture_definition.shape = &ball_shape;
  ball_fixture_definition.density = kDensity;
  ball_fixture_definition.friction = kFriction;
  ball_fixture_definition.restitution = kRestitution;
  ball_body->CreateFixture(&ball_fixture_definition);
}

void Model::CreateBorder() {
  b2BodyDef border_body_definition;
  border_body_definition.position.Set(0.0, 0.0);
  border_body = world.CreateBody(&border_body_definition);
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
  border_body->CreateFixture(&border_fixture_definition);
}

b2Body *Model::CreatePlayer(ofPoint position) {
  b2BodyDef player_body_definition;
  player_body_definition.position.Set(position.x, position.y);
  b2Body *player_body = world.CreateBody(&player_body_definition);
  b2CircleShape player_shape;
  player_shape.m_radius = kBallRadius;
  b2FixtureDef player_fixture_definition;
  player_fixture_definition.shape = &player_shape;
  player_fixture_definition.friction = kFriction;
  player_body->CreateFixture(&player_fixture_definition);
  return player_body;
}

void Model::CreatePlayers() {
  player1_top_body = CreatePlayer(ofPoint(-9, 1));
  player1_bottom_body = CreatePlayer(ofPoint(9, -1));
  player2_top_body = CreatePlayer(ofPoint(9, 1));
  player2_bottom_body = CreatePlayer(ofPoint(-9, -1));
}

void Model::Gravity() {
  const float y = ball_body->GetPosition().y;
  if (y > kBallRadius) {
    ball_body->ApplyForceToCenter(ball_body->GetMass() * kGravity);
  }  else if (0 < y && y <= kBallRadius) {
    ball_body->ApplyForceToCenter(ball_body->GetMass() * Lerp(b2Vec2(), kGravity, y / kBallRadius));
  } else if (-kBallRadius <= y && y < 0) {
    ball_body->ApplyForceToCenter(ball_body->GetMass() * Lerp(b2Vec2(), kAntiGravity, -y / kBallRadius));
  } else if (y < -kBallRadius) {
    ball_body->ApplyForceToCenter(ball_body->GetMass() * kAntiGravity);
  }
}
