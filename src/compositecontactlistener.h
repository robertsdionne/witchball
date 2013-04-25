#ifndef WITCHBALL_COMPOSITECONTACTLISTENER_H_
#define WITCHBALL_COMPOSITECONTACTLISTENER_H_

#include <Box2D/Box2D.h>
#include <vector>

/**
 * A b2ContactListener that maintains a list of other b2ContactListeners to notify upon a Box2D
 * collision.
 */
class CompositeContactListener : public b2ContactListener {
public:
  CompositeContactListener();
  
  virtual ~CompositeContactListener() {}
  
  /**
   * Adds a b2ContactListener to notify upon collision.
   */
  virtual void AddContactListener(b2ContactListener *listener);
  
  virtual void BeginContact(b2Contact *contact);
  
  virtual void EndContact(b2Contact *contact);
  
  virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
  
  virtual void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);
  
private:
  std::vector<b2ContactListener *> listeners;
};

#endif  // WITCHBALL_COMPOSITECONTACTLISTENER_H_
