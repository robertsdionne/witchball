#include <Box2D/Box2D.h>

#include "constants.h"
#include "witchball.h"

WitchBall::WitchBall()
: world(kGravity) {}

void WitchBall::setup() {
  ofSetFrameRate(60);
  CreateBall(ofPoint(100.0, 100.0));
  CreateBorder();
}

void WitchBall::update() {
  world.Step(kTimeStep, kBox2dVelocityIterations, kBox2dPositionIterations);
}

void WitchBall::draw() {
  ofCircle(OpenFrameworksVector(ball_body->GetPosition()), kBallRadius);
}

void WitchBall::keyPressed(int key) {
}

void WitchBall::keyReleased(int key) {
}

void WitchBall::mouseMoved(int x, int y) {
}

void WitchBall::mouseDragged(int x, int y, int button) {
}

void WitchBall::mousePressed(int x, int y, int button) {
}

void WitchBall::mouseReleased(int x, int y, int button) {
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
  vertex[0].Set(0.0, 0.0);
  vertex[1].Set(ofGetWidth(), 0.0);
  vertex[2].Set(ofGetWidth(), ofGetHeight());
  vertex[3].Set(0.0, ofGetHeight());
  border_shape.CreateLoop(vertex, 4);
  b2FixtureDef border_fixture_definition;
  border_fixture_definition.shape = &border_shape;
  border_fixture = border_body->CreateFixture(&border_fixture_definition);
}
