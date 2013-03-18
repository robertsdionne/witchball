#include "constants.h"
#include "utilities.h"
#include "model.h"

Model::Model()
: world(kZeroGravity), ball(nullptr), border(nullptr),
  player1_top(nullptr), player1_bottom(nullptr), player2_top(nullptr), player2_bottom(nullptr),
  mouse_pressed(false), mouse_position(-kHalfCourtWidth, kHalfCourtHeight),
  mouse_gravity_position(mouse_position), mouse_mass_scale(0.0),
  top_left_quadrant_gravity(kTopLeftQuadrantGravity[EnumValue(CourtPosition::POSITION_1)]),
  top_right_quadrant_gravity(kTopRightQuadrantGravity[EnumValue(CourtPosition::POSITION_1)]),
  bottom_left_quadrant_gravity(kBottomLeftQuadrantGravity[EnumValue(CourtPosition::POSITION_1)]),
  bottom_right_quadrant_gravity(kBottomRightQuadrantGravity[EnumValue(CourtPosition::POSITION_1)]),
  gravity_angle(0.0), court_position(CourtPosition::POSITION_1),
  player1_position(0.0), player2_position(0.0), draw_gravity(GravityVisual::QUADRANT),
  ball_trail(), player1_top_trail(), player1_bottom_trail(),
  player2_top_trail(), player2_bottom_trail() {}

void Model::Setup() {
  CreateBall();
  CreateBorder();
  CreatePlayers();
}

void Model::Update() {
  ball->ApplyForceToCenter(ball->GetMass() * GravityAt(ball->GetPosition()));
  UpdatePlayerPosition(player1_top,
                       Lerp(kPlayer1TopBack[EnumValue(court_position)],
                            kPlayer1TopForward[EnumValue(court_position)], player1_position));
  UpdatePlayerPosition(player1_bottom,
                       Lerp(kPlayer1BottomBack[EnumValue(court_position)],
                            kPlayer1BottomForward[EnumValue(court_position)], player1_position));
  UpdatePlayerPosition(player2_top,
                       Lerp(kPlayer2TopBack[EnumValue(court_position)],
                            kPlayer2TopForward[EnumValue(court_position)], player2_position));
  UpdatePlayerPosition(player2_bottom,
                       Lerp(kPlayer2BottomBack[EnumValue(court_position)],
                            kPlayer2BottomForward[EnumValue(court_position)], player2_position));
  UpdateGravities();
  world.Step(kTimeStep, kBox2dVelocityIterations, kBox2dPositionIterations);
  UpdateTrails();
  if (ball->GetLinearVelocity().Length() < kDampingSpeed) {
    ball->SetLinearDamping(0.0);
  } else {
    ball->SetLinearDamping(kLinearDamping);
  }
}

void Model::UpdateTrails() {
  if (ofGetFrameNum() % kBallTrailSpacing == 0) {
    ball_trail.push_front(OpenFrameworksVector(ball->GetPosition()));
    player1_top_trail.push_front(OpenFrameworksVector(player1_top->GetPosition()));
    player1_bottom_trail.push_front(OpenFrameworksVector(player1_bottom->GetPosition()));
    player2_top_trail.push_front(OpenFrameworksVector(player2_top->GetPosition()));
    player2_bottom_trail.push_front(OpenFrameworksVector(player2_bottom->GetPosition()));
    if (ball_trail.size() > kBallTrailLength) {
      ball_trail.pop_back();
    }
    if (player1_top_trail.size() > kPlayerTrailLength) {
      player1_top_trail.pop_back();
    }
    if (player1_bottom_trail.size() > kPlayerTrailLength) {
      player1_bottom_trail.pop_back();
    }
    if (player2_top_trail.size() > kPlayerTrailLength) {
      player2_top_trail.pop_back();
    }
    if (player2_bottom_trail.size() > kPlayerTrailLength) {
      player2_bottom_trail.pop_back();
    }
  }
}

void Model::UpdateGravities() {
  gravity_angle = ofLerpDegrees(gravity_angle, kGravityAngle[EnumValue(court_position)], kGravityMixerRate);
  mouse_mass_scale = ofLerp(mouse_mass_scale, mouse_pressed, kGravityMixerRate);
  mouse_gravity_position = Lerp(mouse_gravity_position, mouse_position, kGravityMixerRate);
  top_left_quadrant_gravity = Lerp(top_left_quadrant_gravity,
                                   kTopLeftQuadrantGravity[EnumValue(court_position)],
                                   kGravityMixerRate);
  top_right_quadrant_gravity = Lerp(top_right_quadrant_gravity,
                                    kTopRightQuadrantGravity[EnumValue(court_position)],
                                    kGravityMixerRate);
  bottom_left_quadrant_gravity = Lerp(bottom_left_quadrant_gravity,
                                      kBottomLeftQuadrantGravity[EnumValue(court_position)],
                                      kGravityMixerRate);
  bottom_right_quadrant_gravity = Lerp(bottom_right_quadrant_gravity,
                                       kBottomRightQuadrantGravity[EnumValue(court_position)],
                                       kGravityMixerRate);
}

void Model::CreateBall(ofPoint position, ofVec2f velocity) {
  b2BodyDef ball_definition;
  ball_definition.type = b2_dynamicBody;
  ball_definition.position = Box2dVector(position);
  ball_definition.fixedRotation = kFixedRotation;
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

b2Vec2 Model::GravityAt(b2Vec2 position) const {
  const ofVec2f radius = mouse_gravity_position - OpenFrameworksVector(position);
  const b2Vec2 mouse_gravity = Box2dVector(mouse_mass_scale * kMouseMass *
                                           radius.normalized() / radius.lengthSquared());
  const b2Vec2 gravity = Box2dVector(-9.81 * OpenFrameworksVector(position).normalized().rotate(gravity_angle));
  return gravity + mouse_gravity;
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

void Model::RotateClockwise() {
  court_position = Model::CourtPosition((EnumValue(court_position) + 1) % 4);
}

void Model::RotateCounterClockwise() {
  court_position = Model::CourtPosition((EnumValue(court_position) + 3) % 4);
}

void Model::UpdatePlayerPosition(b2Body *player, ofPoint target) {
  const ofVec2f position = OpenFrameworksVector(player->GetPosition());
  const ofVec2f delta = (target - position) * ofVec2f(kControllerRateX, kControllerRateY);
  const ofVec2f new_position = position + delta;
  player->SetTransform(Box2dVector(new_position), 0.0);
}
