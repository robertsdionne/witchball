//
//  collisionscorekeeper.cpp
//  witchball
//
//  Created by Shervin Ghazazani on 3/13/13.
//	Handles Ball to Player game collision and increments score.
//

#include "collisionscorekeeper.h"
#include "model.h"

collisionscorekeeper::collisionscorekeeper()  {
  
}

void collisionscorekeeper::BeginContact(b2Contact *contact) {
	b2Body *bodyA = contact->GetFixtureA()->GetBody();
	b2Body *bodyB = contact->GetFixtureB()->GetBody();
	
	void *bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	
	if ( bodyUserData ) {
		Model *model = static_cast<Model*>( bodyUserData );
		
		if(((bodyA == model->player1_bottom || bodyA == model->player1_top) && (bodyB == model->ball)) ||
			 ((bodyB == model->player1_bottom || bodyB == model->player1_top) && (bodyA == model->ball))) {
			model->IncrementPlayerOneCount();
		} else if(((bodyA == model->player2_bottom || bodyA == model->player2_top) && (bodyB == model->ball)) ||
						((bodyB == model->player2_bottom || bodyB == model->player2_top) && (bodyA == model->ball))) {
			model->IncrementPlayerTwoCount();
		}
	}
}

void collisionscorekeeper::EndContact(b2Contact *contact) {
	b2Body *bodyA = contact->GetFixtureA()->GetBody();
	b2Body *bodyB = contact->GetFixtureB()->GetBody();
	
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	
	if ( bodyUserData ) {
		Model *model = static_cast<Model*>( bodyUserData );
		
		if(((bodyA == model->player1_bottom || bodyA == model->player1_top) && (bodyB == model->ball)) ||
			 ((bodyB == model->player1_bottom || bodyB == model->player1_top) && (bodyA == model->ball))) {
			b2Vec2 ballVelocity = model->ball->GetLinearVelocity();
			ballVelocity *= kPlayerBallCollisionMultiplier;
			model->ball->ApplyForceToCenter(ballVelocity);
		}
		else if(((bodyA == model->player2_bottom || bodyA == model->player2_top) && (bodyB == model->ball)) ||
						((bodyB == model->player2_bottom || bodyB == model->player2_top) && (bodyA == model->ball))) {
			b2Vec2 ballVelocity = model->ball->GetLinearVelocity();
			ballVelocity *= kPlayerBallCollisionMultiplier;
			model->ball->ApplyForceToCenter(ballVelocity);
		}
	}
}