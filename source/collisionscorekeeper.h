#ifndef WITCHBALL_collisionscorekeeper_H_
#define WITCHBALL_collisionscorekeeper_H_

#include <Box2D/Box2D.h>

#include "constants.h"
#include "ofMain.h"

class collisionscorekeeper : public b2ContactListener {
public:
  collisionscorekeeper();
  
  virtual ~collisionscorekeeper() {}
  
  virtual void BeginContact(b2Contact *contact);
  virtual void EndContact(b2Contact *contact);
private:
  
};

#endif  // WITCHBALL_collisionscorekeeper_H_
