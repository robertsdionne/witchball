#include <Box2D/Box2D.h>
#include <iostream>

#include "constants.h"
#include "witchball.h"

WitchBall::WitchBall()
: world(kZeroGravity), collision() {}

void WitchBall::setup() {
  ofSetFrameRate(60);
  ofSetVerticalSync(true);
  CreateBall();
  CreateBorder();
  world.SetContactListener(&collision);
}

void WitchBall::update() {
  Gravity();
  if (buttons[0]) {
    const ofVec2f force = mouse_position - OpenFrameworksVector(ball_body->GetPosition());
    ball_body->ApplyForce(Box2dVector(force.lengthSquared() * force.normalized()),
                          ball_body->GetWorldCenter() + kBallRadius * b2Vec2(
                          cos(ball_body->GetAngle()), sin(ball_body->GetAngle())));
  }
  world.Step(kTimeStep, kBox2dVelocityIterations, kBox2dPositionIterations);
  previous_buttons = buttons;
  previous_keys = keys;
}

void WitchBall::draw() {
  ofDrawBitmapString(ofToString(ofGetFrameRate()), ofPoint(0, 10));
  ofMultMatrix(kViewMatrix);
  const ofPoint ball_position = OpenFrameworksVector(ball_body->GetPosition());
  const float angle = ball_body->GetAngle();
  const ofVec2f b = ofVec2f(cos(angle), sin(angle));
  ofSetColor(ofColor::white);
  ofLine(ofPoint(-kHalfCourtWidth, 0.0), ofPoint(kHalfCourtWidth, 0.0));
  if (buttons[0]) {
    ofSetColor(ofColor::black);
    ofLine(ball_position + kBallRadius * b, mouse_position);
  }
  ofSetColor(ofColor::white);
  ofCircle(ball_position, kBallRadius);
  ofSetColor(ofColor::black);
  const ofVec2f a = ofVec2f(sin(angle), -cos(angle));
  ofLine(ball_position + kBallRadius * a, ball_position - kBallRadius * a);
//  const ofVec2f b = ofVec2f(cos(angle), sin(angle));
  ofLine(ball_position + kBallRadius * b, ball_position - kBallRadius * b);
}

void WitchBall::keyPressed(int key) {
  keys[key] = true;
}

void WitchBall::keyReleased(int key) {
  keys[key] = false;
}

void WitchBall::mouseMoved(int x, int y) {
  mouse_position = ofVec3f(x, y) * kViewMatrixInverse;
}

void WitchBall::mouseDragged(int x, int y, int button) {
  mouseMoved(x, y);
}

void WitchBall::mousePressed(int x, int y, int button) {
  buttons[button] = true;
}

void WitchBall::mouseReleased(int x, int y, int button) {
  buttons[button] = false;
}

void WitchBall::windowResized(int w, int h) {
}

void WitchBall::gotMessage(ofMessage msg) {
}

void WitchBall::dragEvent(ofDragInfo dragInfo) {
}

b2Vec2 WitchBall::Box2dVector(ofVec2f vector) {
  return b2Vec2(vector.x, vector.y);
}

b2Vec2 WitchBall::Lerp(b2Vec2 from, b2Vec2 to, float t) {
  return (1.0 - t) * from + t * to;
}

ofVec2f WitchBall::Lerp(ofVec2f from, ofVec2f to, float t) {
  return (1.0 - t) * from + t * to;
}

ofVec2f WitchBall::OpenFrameworksVector(b2Vec2 vector) {
  return ofVec2f(vector.x, vector.y);
}

void WitchBall::CreateBall(ofPoint position, ofVec2f velocity) {
  b2BodyDef ball_body_definition;
  ball_body_definition.type = b2_dynamicBody;
  ball_body_definition.position = Box2dVector(position);
  ball_body_definition.linearVelocity = Box2dVector(velocity);
  ball_body_definition.linearDamping = kLinearDamping;
  ball_body_definition.angularDamping = kAngularDamping;
  ball_body = world.CreateBody(&ball_body_definition);
  ball_shape.m_radius = kBallRadius;
  b2FixtureDef ball_fixture_definition;
  ball_fixture_definition.shape = &ball_shape;
  ball_fixture_definition.density = kDensity;
  ball_fixture_definition.friction = kFriction;
  ball_fixture_definition.restitution = kRestitution;
  ball_fixture = ball_body->CreateFixture(&ball_fixture_definition);
}

void WitchBall::CreateBorder() {
  b2BodyDef border_body_definition;
  border_body_definition.position.Set(0.0, 0.0);
  border_body = world.CreateBody(&border_body_definition);
  b2Vec2 vertex[4];
  vertex[0].Set(-kHalfCourtWidth, -kHalfCourtHeight);
  vertex[1].Set(kHalfCourtWidth, -kHalfCourtHeight);
  vertex[2].Set(kHalfCourtWidth, kHalfCourtHeight);
  vertex[3].Set(-kHalfCourtWidth, kHalfCourtHeight);
  border_shape.CreateLoop(vertex, 4);
  b2FixtureDef border_fixture_definition;
  border_fixture_definition.shape = &border_shape;
  border_fixture_definition.friction = kFriction;
  border_fixture = border_body->CreateFixture(&border_fixture_definition);
}

void WitchBall::Gravity() {
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
