#include <Box2D/Box2D.h>

#include "compositecontactlistener.h"

CompositeContactListener::CompositeContactListener()
: listeners() {}

void CompositeContactListener::AddContactListener(b2ContactListener *listener) {
  listeners.push_back(listener);
}

void CompositeContactListener::BeginContact(b2Contact *contact) {
  for (auto listener : listeners) {
    listener->BeginContact(contact);
  }
}

void CompositeContactListener::EndContact(b2Contact *contact) {
  for (auto listener : listeners) {
    listener->EndContact(contact);
  }
}

void CompositeContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold) {
  for (auto listener : listeners) {
    listener->PreSolve(contact, oldManifold);
  }
}

void CompositeContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) {
  for (auto listener : listeners) {
    listener->PostSolve(contact, impulse);
  }
}
