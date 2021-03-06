#ifndef TEXTTENNIS_PARAMETER_H_
#define TEXTTENNIS_PARAMETER_H_

#include <iostream>
#include <set>
#include <string>
#include <tr1/functional>
#include <vector>

#define DEFINE_PARAMETER(type, name, value) \
  auto name = Parameter<type>(#name, [] (Dependent *dependent) -> type {return (value);});

#define DEFINE_PARAMETER_RANGE(type, name, value, min, max) \
  auto name = Parameter<type>( \
      #name, [] (Dependent *dependent) -> type {return (value);}, true, min, max);

#define DEPENDENCY(dependency) \
  dependency.GetValue(dependent)

class Dependent {
public:
  virtual ~Dependent() {}

  void SetStale(bool stale) {
    this->stale = stale;
  }

protected:
  Dependent() : stale(true) {}

  bool stale;
};

template <typename T>
class Parameter;

template <typename T>
std::vector<Parameter<T> *> &GetParameters();

template <typename T>
class Parameter : public Dependent {
public:
  typedef std::tr1::function<T(Dependent *)> Getter;

  Parameter(const std::string name, Getter get_value, bool ranged = false, T min = T(), T max = T())
  : Dependent(), name(name), get_value(get_value), value(), dependents(), min(min), max(max) {
    if (ranged) {
      AddParameter(this);
    }
  }

  virtual ~Parameter() {}

  const std::string &GetName() const {
    return name;
  }

  T GetValue(Dependent *dependent = nullptr) {
    if (dependent) {
      dependents.insert(dependent);
    }
    if (stale) {
      value = get_value(this);
      stale = false;
    }
    return value;
  };

  void Set(T value) {
    this->value = value;
    NotifyDependents();
  }

  operator T() {
    return GetValue();
  }

  Parameter<T> &operator =(T value) {
    Set(value);
    return *this;
  }

  Parameter<T> &operator +=(T value) {
    Set(this->value + value);
    return *this;
  }

  Parameter<T> &operator -=(T value) {
    Set(this->value - value);
    return *this;
  }

  template <typename U>
  Parameter<T> &operator *=(U value) {
    Set(this->value * value);
    return *this;
  }

  template <typename U>
  Parameter<T> &operator /=(U value) {
    Set(this->value / value);
    return *this;
  }

  const T min;
  const T max;

private:
  static void AddParameter(Parameter<T> *parameter) {
    GetParameters<T>().push_back(parameter);
  }

  void NotifyDependents() {
    for (auto dependent : dependents) {
      dependent->SetStale(true);
    }
  }

private:
  const std::string name;
  Getter get_value;
  T value;
  std::set<Dependent *> dependents;
};

#endif  // TEXTTENNIS_PARAMETER_H_
