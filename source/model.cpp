#include "constants.h"
#include "utilities.h"
#include "model.h"
#include "ofChaser.h"
#include "witchball.h"

Model::Model(bool fake, CollisionSoundPlayer *sound_player)
: fake(fake), sound_player(sound_player), world(kZeroGravity), ball(nullptr), border(nullptr),
  player1_top(nullptr), player1_bottom(nullptr), player2_top(nullptr), player2_bottom(nullptr),
  mouse_pressed(false), mouse_position(-kHalfCourtWidth, kHalfCourtHeight),
  top_left_quadrant_gravity(GetTopLeftQuadrantGravity(EnumValue(CourtPosition::POSITION_1))),
  top_right_quadrant_gravity(GetTopRightQuadrantGravity(EnumValue(CourtPosition::POSITION_1))),
  bottom_left_quadrant_gravity(GetBottomLeftQuadrantGravity(EnumValue(CourtPosition::POSITION_1))),
  bottom_right_quadrant_gravity(GetBottomRightQuadrantGravity(EnumValue(CourtPosition::POSITION_1))),
  gravity_angle(0.0), court_position(CourtPosition::POSITION_1), play_gravity(false),
  last_hit_player(0), strike_position(), strike_alpha(0.0), p1_score_alpha(0.0), p2_score_alpha(0.0),
  counter_clockwise_alpha(0.0), clockwise_alpha(0.0),
  player1_position(0.0), player2_position(0.0), draw_gravity(GravityVisual::NONE),
  elapsed_time(ofGetElapsedTimef()), last_collision_time(-kCollisionDelay),
  ball_trail(), player1_top_trail(), player1_bottom_trail(),
  player2_top_trail(), player2_bottom_trail(), last_input_time(0) {
    boom.loadSound("boom2.wav");
}

Model::~Model() {
  for (int i = 0; i < nChasers; ++i) {
    delete topChaser[i];
  }
  for (int i = 0; i < nChasers; ++i) {
    delete botChaser[i];
  }
  for (int i = 0; i < nChasers; ++i) {
    delete leftChaser[i];
  }
  for (int i = 0; i < nChasers; ++i) {
    delete rightChaser[i];
  }
}

void Model::Setup() {
  CreateBall();
  CreateBorder();
  CreatePlayers();

  // Create platforms
  p1_top_platform_left = GetPlayer1TopLeft(EnumValue(court_position));
  p1_top_platform_right = GetPlayer1TopRight(EnumValue(court_position));
  p1_bottom_platform_left = GetPlayer1BottomLeft(EnumValue(court_position));
  p1_bottom_platform_right = GetPlayer1BottomRight(EnumValue(court_position));
  p2_top_platform_left = GetPlayer2TopLeft(EnumValue(court_position));
  p2_top_platform_right = GetPlayer2TopRight(EnumValue(court_position));
  p2_bottom_platform_left = GetPlayer2BottomLeft(EnumValue(court_position));
  p2_bottom_platform_right = GetPlayer2BottomRight(EnumValue(court_position));

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
  if (!fake && ofGetElapsedTimef() > last_input_time + 10.0) {
    dynamic_cast<WitchBall *>(ofGetAppPtr())->RunTitleScreen();
    return;
  }
  if (winning_alpha <= 1.0 - 1.0 / 60.0) {
    winning_alpha += 1.0 / 60.0;
  }
  if (show_winning_state && ofGetElapsedTimef() > win_time + 2.0) {
    show_winning_state = false;
    court_position = CourtPosition::POSITION_1;
    last_collision_time = ofGetElapsedTimef();
    p1glowMax = 0;
    p2glowMax = 0;
    boom.play();
  }
  if (kDampingSpeed > kDampingSpeedMinimum) {
    kDampingSpeed.Set(ofLerp(kDampingSpeed, kDampingSpeedMinimum, kDampingSpeedRate));
  }
  if (player1_increment_count > 0 && p1glowMax < 1.0) {
    p1glowMax += 0.1;
  } else if (player1_increment_count < 1 && p1glowMax > 0.0) {
    p1glowMax = 0.0;
  } else if (player1_increment_count > 1 && p1glowMax < 2.0 * kCourtWidth) {
    p1glowMax += 0.5;
  }

  if (player2_increment_count > 0 && p2glowMax < 1.0) {
    p2glowMax += 0.1;
  } else if (player2_increment_count < 1 && p2glowMax > 0.0) {
    p2glowMax = 0.0;
  } else if (player2_increment_count > 1&& p2glowMax < 2.0 * kCourtWidth) {
    p2glowMax += 0.5;
  }

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
  if (p1_score_alpha >= kStrikeAlphaRate) {
    p1_score_alpha -= kStrikeAlphaRate;
  }
  if (p2_score_alpha >= kStrikeAlphaRate) {
    p2_score_alpha -= kStrikeAlphaRate;
  }
  if (counter_clockwise_alpha >= kRotateAlphaRate) {
    counter_clockwise_alpha -= kRotateAlphaRate;
  }
  if (clockwise_alpha >= kRotateAlphaRate) {
    clockwise_alpha -= kRotateAlphaRate;
  }
  ball->ApplyForceToCenter(ball->GetMass() * GravityAt(ball->GetPosition()));

  UpdatePlatformPositions(&p1_top_platform_left, &p1_top_platform_right,
                          GetPlayer1TopLeft(EnumValue(court_position)),
                          GetPlayer1TopRight(EnumValue(court_position)));

  UpdatePlatformPositions(&p1_bottom_platform_left, &p1_bottom_platform_right,
                          GetPlayer1BottomLeft(EnumValue(court_position)),
                          GetPlayer1BottomRight(EnumValue(court_position)));

  UpdatePlatformPositions(&p2_top_platform_left, &p2_top_platform_right,
                          GetPlayer2TopLeft(EnumValue(court_position)),
                          GetPlayer2TopRight(EnumValue(court_position)));

  UpdatePlatformPositions(&p2_bottom_platform_left, &p2_bottom_platform_right,
                          GetPlayer2BottomLeft(EnumValue(court_position)),
                          GetPlayer2BottomRight(EnumValue(court_position)));

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
  UpdateGravities();
  if (ball->GetPosition().x >= kHalfCourtWidth-2*kBallRadius){
    ball->ApplyForceToCenter(-kBumperForce.GetValue());
  } else if (ball->GetPosition().x <= -kHalfCourtWidth+2*kBallRadius){
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

float Model::Player1Position() {
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

float Model::Player2Position() {
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
  player_fixture_definition.restitution = 1.01;
  player->CreateFixture(&player_fixture_definition);
  return player;
}

void Model::CreatePlayers() {
  player1_top = CreatePlayer(GetPlayer1TopLeft(EnumValue(CourtPosition::POSITION_1)));
  player1_bottom = CreatePlayer(GetPlayer1BottomLeft(EnumValue(CourtPosition::POSITION_1)));
  player2_top = CreatePlayer(GetPlayer2TopLeft(EnumValue(CourtPosition::POSITION_1)));
  player2_bottom = CreatePlayer(GetPlayer2BottomLeft(EnumValue(CourtPosition::POSITION_1)));
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
    if (!fake) {
      kDampingSpeed.Set(kDampingSpeed * kDampingSpeedBump);
    }
    last_collision_time = elapsed_time;
    if(player1_increment_count >= 2) {
      player1_score++;
      p1_score_alpha = kStrikeAlphaStart;

      if(player1_score == kPointsToWin) {
        winner = 1;
        winning_alpha = 0.0;
        show_winning_state = true;
        win_time = ofGetElapsedTimef();
        printf("P1 Wins\n");
        player1_score = 0;
        player2_score = 0;
        player1_increment_count = 0;
        player2_increment_count = 0;
        if (sound_player) {
          sound_player->PlayPlayer1Win(ball);
        }
      } else if (sound_player) {
        sound_player->PlayPlayer1Score(ball);
      }
    } else if (sound_player) {
      sound_player->PlayPlayer1Hit(ball);
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
    if (!fake) {
      kDampingSpeed.Set(kDampingSpeed * kDampingSpeedBump);
    }
    last_collision_time = elapsed_time;
    if(player2_increment_count >= 2) {
      player2_score++;
      p2_score_alpha = kStrikeAlphaStart;

      if(player2_score == kPointsToWin) {
        winner = 2;
        winning_alpha = 0.0;
        show_winning_state = true;
        win_time = ofGetElapsedTimef();
        printf("P2 Wins\n");
        player1_score = 0;
        player2_score = 0;
        player1_increment_count = 0;
        player2_increment_count = 0;
        if (sound_player) {
          sound_player->PlayPlayer2Win(ball);
        }
      } else if (sound_player) {
        sound_player->PlayPlayer2Score(ball);
      }
    } else if (sound_player) {
      sound_player->PlayPlayer2Hit(ball);
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
  const b2Vec2 new_position = b2Vec2(ofLerp(player->GetPosition().x, target.x, kControllerRateY),
                                     ofLerp(player->GetPosition().y, target.y, kControllerRateY));
  player->SetTransform(new_position, 0.0);
}

void Model::UpdatePlatformPositions(ofPoint *left, ofPoint *right,
                             ofPoint left_target, ofPoint right_target) {
  const ofPoint new_left_position = ofPoint(ofLerp(left->x, left_target.x, kControllerRateY),
                                            ofLerp(left->y, left_target.y, kControllerRateY));
  const ofPoint new_right_position = ofPoint(ofLerp(right->x, right_target.x, kControllerRateY),
                                             ofLerp(right->y, right_target.y, kControllerRateY));
  *left = new_left_position;
  *right = new_right_position;
}
