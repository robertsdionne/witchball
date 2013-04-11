#include "constants.h"
#include "utilities.h"
#include "model.h"
#include "ofChaser.h"

Model::Model()
: world(kZeroGravity), ball(nullptr), border(nullptr),
  player1_top(nullptr), player1_bottom(nullptr), player2_top(nullptr), player2_bottom(nullptr),
  mouse_pressed(false), mouse_position(-kHalfCourtWidth, kHalfCourtHeight),
  top_left_quadrant_gravity(GetTopLeftQuadrantGravity(EnumValue(CourtPosition::POSITION_1))),
  top_right_quadrant_gravity(GetTopRightQuadrantGravity(EnumValue(CourtPosition::POSITION_1))),
  bottom_left_quadrant_gravity(GetBottomLeftQuadrantGravity(EnumValue(CourtPosition::POSITION_1))),
  bottom_right_quadrant_gravity(GetBottomRightQuadrantGravity(EnumValue(CourtPosition::POSITION_1))),
  gravity_angle(0.0), court_position(CourtPosition::POSITION_1), play_gravity(false),
  last_hit_player(0), strike_position(), strike_alpha(0.0), counter_clockwise_alpha(0.0),
  clockwise_alpha(0.0),
  player1_position(0.0), player2_position(0.0), draw_gravity(GravityVisual::NONE),
  elapsed_time(ofGetElapsedTimef()), last_collision_time(ofGetElapsedTimef() + kCollisionDelay),
  ball_trail(), player1_top_trail(), player1_bottom_trail(),
  player2_top_trail(), player2_bottom_trail() {}

void Model::Setup() {
  CreateBall();
  CreateBorder();
  CreatePlayers();
  //CHASERS
  nChasers=99;
  testPoint.set(0, 0);

  topChaser = new ofChaser*[nChasers];
  for (int i = 0; i < nChasers; i++){
    float a = ofRandom(-kCourtWidth / 2.0, kCourtWidth / 2.0);
    float b = kCourtHeight / 2.0;
    float c = a;
    float d = b;
    float targX = testPoint.x;
    float targY = testPoint.y;
    float extX= ball->GetPosition().x;
    float extY= ball->GetPosition().y;

    topChaser[i] = new ofChaser(a,b,c,d, targX, targY, extX, extY);
  }
  botChaser = new ofChaser*[nChasers];
  for (int i = 0; i < nChasers; i++){
    float a = ofRandom(-kCourtWidth / 2.0, kCourtWidth / 2.0);
    float b = -kCourtHeight / 2.0;
    float c = a;
    float d = b;
    float targX = testPoint.x;
    float targY = testPoint.y;
    float extX= ball->GetPosition().x;
    float extY= ball->GetPosition().y;

    botChaser[i] = new ofChaser(a,b,c,d, targX, targY, extX, extY);
  }
  leftChaser = new ofChaser*[nChasers];
  for (int i = 0; i < nChasers; i++){
    float a = -kCourtWidth / 2.0;
    float b = ofRandom(-kCourtHeight / 2.0, kCourtHeight / 2.0);
    float c = a;
    float d = b;
    float targX = testPoint.x;
    float targY = testPoint.y;
    float extX= ball->GetPosition().x;
    float extY= ball->GetPosition().y;

    leftChaser[i] = new ofChaser(a,b,c,d, targX, targY, extX, extY);
  }
  rightChaser = new ofChaser*[nChasers];
  for (int i = 0; i < nChasers; i++){
    float a = kCourtWidth / 2.0;
    float b = ofRandom(-kCourtHeight / 2.0, kCourtHeight / 2.0);
    float c = a;
    float d = b;
    float targX = testPoint.x;
    float targY = testPoint.y;
    float extX = ball->GetPosition().x;
    float extY = ball->GetPosition().y;

    rightChaser[i] = new ofChaser(a,b,c,d, targX, targY, extX, extY);
  }
    
    
}

void Model::Update() {
  //CHASERS----------------
  for (int i = 0; i < nChasers; i++){
    topChaser[i]->targX=testPoint.x;
    topChaser[i]->targY=testPoint.y;
    topChaser[i]->extX=ball->GetPosition().x;
    topChaser[i]->extY=ball->GetPosition().y;

    botChaser[i]->targX=testPoint.x;
    botChaser[i]->targY=testPoint.y;
    botChaser[i]->extX=ball->GetPosition().x;
    botChaser[i]->extY=ball->GetPosition().y;

    rightChaser[i]->targX=testPoint.x;
    rightChaser[i]->targY=testPoint.y;
    rightChaser[i]->extX=ball->GetPosition().x;
    rightChaser[i]->extY=ball->GetPosition().y;

    leftChaser[i]->targX=testPoint.x;
    leftChaser[i]->targY=testPoint.y;
    leftChaser[i]->extX=ball->GetPosition().x;
    leftChaser[i]->extY=ball->GetPosition().y;

    topChaser[i]->update();
    botChaser[i]->update();
    rightChaser[i]->update();
    leftChaser[i]->update();
  }
  if (elapsed_time > last_collision_time + kCollisionDelay) {
    player1_top->SetActive(true);
    player1_bottom->SetActive(true);
    player2_top->SetActive(true);
    player2_bottom->SetActive(true);
  } else {    player1_top->SetActive(false);
    player1_bottom->SetActive(false);
    player2_top->SetActive(false);
    player2_bottom->SetActive(false);
  }
  if (strike_alpha >= kStrikeAlphaRate) {
    strike_alpha -= kStrikeAlphaRate;
  }
  if (counter_clockwise_alpha >= kRotateAlphaRate) {
    counter_clockwise_alpha -= kRotateAlphaRate;
  }
  if (clockwise_alpha >= kRotateAlphaRate) {
    clockwise_alpha -= kRotateAlphaRate;
  }
  ball->ApplyForceToCenter(ball->GetMass() * GravityAt(ball->GetPosition()));
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
  UpdateGravities();
  if (ball->GetPosition().x >= kCourtWidth-2*kBallRadius){
    ball->ApplyForceToCenter(-kBumperForce.GetValue());
  }else if (ball->GetPosition().x <= -kCourtWidth/2+2*kBallRadius){
    ball->ApplyForceToCenter(kBumperForce);
  }
  
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
    if (ball_trail.size() > kBallTrailLength) {
      ball_trail.pop_back();
    }
  }
  if (ofGetFrameNum() % kPlayerTrailSpacing == 0) {
    player1_top_trail.push_front(OpenFrameworksVector(player1_top->GetPosition()));
    player1_bottom_trail.push_front(OpenFrameworksVector(player1_bottom->GetPosition()));
    player2_top_trail.push_front(OpenFrameworksVector(player2_top->GetPosition()));
    player2_bottom_trail.push_front(OpenFrameworksVector(player2_bottom->GetPosition()));
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
  top_left_quadrant_gravity = Lerp(top_left_quadrant_gravity,
                                   GetTopLeftQuadrantGravity(EnumValue(court_position)),
                                   kGravityMixerRate);
  top_right_quadrant_gravity = Lerp(top_right_quadrant_gravity,
                                    GetTopRightQuadrantGravity(EnumValue(court_position)),
                                    kGravityMixerRate);
  bottom_left_quadrant_gravity = Lerp(bottom_left_quadrant_gravity,
                                      GetBottomLeftQuadrantGravity(EnumValue(court_position)),
                                      kGravityMixerRate);
  bottom_right_quadrant_gravity = Lerp(bottom_right_quadrant_gravity,
                                       GetBottomRightQuadrantGravity(EnumValue(court_position)),
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
  b2PolygonShape border_bottom_shape, border_top_shape, border_left_shape, border_right_shape;
  border_bottom_shape.SetAsBox(kHalfCourtWidth + 2.0, 1.0, b2Vec2(0.0, -kHalfCourtHeight - 1.0), 0.0);
  border_top_shape.SetAsBox(kHalfCourtWidth + 2.0, 1.0, b2Vec2(0.0, kHalfCourtHeight + 1.0), 0.0);
  border_left_shape.SetAsBox(1.0, kHalfCourtHeight, b2Vec2(-kHalfCourtWidth - 1.0, 0.0), 0.0);
  border_right_shape.SetAsBox(1.0, kHalfCourtHeight, b2Vec2(kHalfCourtWidth + 1.0, 0.0), 0.0);
  b2FixtureDef border_bottom_fixture, border_top_fixture, border_left_fixture, border_right_fixture;
  border_bottom_fixture.shape = &border_bottom_shape;
  border_bottom_fixture.friction = kFriction;
  border_top_fixture.shape = &border_top_shape;
  border_top_fixture.friction = kFriction;
  border_left_fixture.shape = &border_left_shape;
  border_left_fixture.friction = kFriction;
  border_right_fixture.shape = &border_right_shape;
  border_right_fixture.friction = kFriction;
  border->CreateFixture(&border_bottom_fixture);
  border->CreateFixture(&border_top_fixture);
  border->CreateFixture(&border_left_fixture);
  border->CreateFixture(&border_right_fixture);
}

b2Body *Model::CreatePlayer(ofPoint position) {
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

void Model::CreatePlayers() {
  player1_top = CreatePlayer(GetPlayer1TopBack(EnumValue(CourtPosition::POSITION_1)));
  player1_bottom = CreatePlayer(GetPlayer1BottomBack(EnumValue(CourtPosition::POSITION_1)));
  player2_top = CreatePlayer(GetPlayer2TopBack(EnumValue(CourtPosition::POSITION_1)));
  player2_bottom = CreatePlayer(GetPlayer2BottomBack(EnumValue(CourtPosition::POSITION_1)));
}

b2Vec2 Model::GravityAt(b2Vec2 position) const {
  const float x_range = kSmoothGravityDiscontinuityXRange;
  const float y_range = kSmoothGravityDiscontinuityYRange;
  const float xt = (ofClamp(position.x, -x_range, x_range) / x_range + 1.0) / 2.0;
  const float yt = (ofClamp(position.y, -y_range, y_range) / y_range + 1.0) / 2.0;
  if (play_gravity) {
    return Lerp(Lerp(bottom_left_quadrant_gravity, bottom_right_quadrant_gravity, xt),
                Lerp(top_left_quadrant_gravity, top_right_quadrant_gravity, xt), yt);
  } else {
    return Box2dVector(-9.81 * OpenFrameworksVector(position).normalized());
  }
}

void Model::IncrementPlayerOneCount() {
  if (elapsed_time > last_collision_time + kCollisionDelay) {
    last_collision_time = elapsed_time;
    if(player1_increment_count >= 2) {
      player1_score++;

      if(player1_score == kPointsToWin) {
        printf("P1 Wins\n");
        player1_score = 0;
        player2_score = 0;
        player1_increment_count = 0;
        player2_increment_count = 0;
      }
    }
    player1_increment_count++;
    player2_increment_count = 0;
    last_hit_player = 1;
    strike_position = OpenFrameworksVector(ball->GetPosition());
    strike_alpha = kStrikeAlphaStart;

    printf("P1 Score: %d\n",player1_score);
  }
}

void Model::IncrementPlayerTwoCount() {
  if (elapsed_time > last_collision_time + kCollisionDelay) {
    last_collision_time = elapsed_time;
    if(player2_increment_count >= 2) {
      player2_score++;
      if(player2_score == kPointsToWin) {
        printf("P2 Wins\n");
        player1_score = 0;
        player2_score = 0;
        player1_increment_count = 0;
        player2_increment_count = 0;
      }
    }
    player2_increment_count++;
    player1_increment_count = 0;
    last_hit_player = 2;
    strike_position = OpenFrameworksVector(ball->GetPosition());
    strike_alpha = kStrikeAlphaStart;
    
    printf("P2 Score: %d\n",player2_score);
  }
}

void Model::RotateClockwise() {
  court_position = Model::CourtPosition((EnumValue(court_position) + 1) % 4);
  clockwise_alpha = kRotateAlphaStart;
  play_gravity = true;
}

void Model::RotateCounterClockwise() {
  court_position = Model::CourtPosition((EnumValue(court_position) + 3) % 4);
  counter_clockwise_alpha = kRotateAlphaStart;
  play_gravity = true;
}

void Model::UpdatePlayerPosition(b2Body *player, ofPoint target) {
  const b2Vec2 new_position = b2Vec2(ofLerp(player->GetPosition().x, target.x, kControllerRateX),
                                     ofLerp(player->GetPosition().y, target.y, kControllerRateY));
  player->SetTransform(new_position, 0.0);
}
