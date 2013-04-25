#include <Box2D/Box2D.h>

#include "ofMain.h"
#include "parameter.h"

template <>
std::vector<Parameter<float> *> &GetParameters() {
  static std::vector<Parameter<float> *> parameters;
  return parameters;
}

template <>
std::vector<Parameter<int> *> &GetParameters() {
  static std::vector<Parameter<int> *> parameters;
  return parameters;
}

template <>
std::vector<Parameter<ofVec2f> *> &GetParameters() {
  static std::vector<Parameter<ofVec2f> *> parameters;
  return parameters;
}

template <>
std::vector<Parameter<b2Vec2> *> &GetParameters() {
  static std::vector<Parameter<b2Vec2> *> parameters;
  return parameters;
}

template <>
std::vector<Parameter<ofMatrix4x4> *> &GetParameters() {
  static std::vector<Parameter<ofMatrix4x4> *> parameters;
  return parameters;
}
