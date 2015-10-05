#include <iostream>
#include <Box2D/Box2D.h>
using namespace std;

//input?
enum {
	TDC_LEFT = 0x1,
	TDC_RIGHT = 0x2,
	TDC_UP = 0x4,
	TDC_DOWN = 0x8
};

//?????
enum fixtureUserDataType {
	FUD_CAR_TIRE,
	FUD_GROUND_AREA
};

class FixtureUserData {
	fixtureUserDataType m_type;
protected:
	FixtureUserData(fixtureUserDataType type) : m_type(type) {}
public:
	virtual fixtureUserDataType getType() { return m_type; }
	virtual ~FixtureUserData() {}
};

class CarTireFUD : public FixtureUserData {
public:
	CarTireFUD() : FixtureUserData(FUD_CAR_TIRE) {}
};
//?????




class Car{
public:
	b2Body* w_body;
	float maxForwardSpeed;
	float maxBackwardSpeed;
	float maxDriveForce;
	float maxLateralImpulse;
	float currentTraction;

	//constructor
	Car(b2World* world){
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		w_body = world->CreateBody(&bodyDef);


		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(0.5f, 1.25f);
		b2Fixture* fixture = w_body->CreateFixture(&polygonShape, 1);//shape, density
		fixture->SetUserData(new CarTireFUD());

		w_body->SetUserData(this);

		currentTraction = 1;
	}

	//destructor
	~Car(){
		w_body->GetWorld()->DestroyBody(w_body);
	}



	void setCharacteristics(float maxForwardSpeed, float maxBackwardSpeed ,float maxDriveForce, float maxLateralImpulse) {
		maxForwardSpeed = maxForwardSpeed;
		maxBackwardSpeed = maxBackwardSpeed;
		maxDriveForce = maxDriveForce;
		maxLateralImpulse = maxLateralImpulse;
	}


	b2Vec2 getLateralVelocity() {
		b2Vec2 currentRightNormal = w_body->GetWorldVector(b2Vec2(1, 0));
		return b2Dot(currentRightNormal, w_body->GetLinearVelocity()) * currentRightNormal;
	}

	b2Vec2 getForwardVelocity() {
		b2Vec2 currentForwardNormal = w_body->GetWorldVector(b2Vec2(0, 1));
		return b2Dot(currentForwardNormal, w_body->GetLinearVelocity()) * currentForwardNormal;
	}
	void updateDrive(int controlState) {

		//find desired speed
		float desiredSpeed = 0;
		switch (controlState & (TDC_UP | TDC_DOWN)) {
		case TDC_UP:   desiredSpeed = maxForwardSpeed;  break;
		case TDC_DOWN: desiredSpeed = maxBackwardSpeed; break;
		default: return;//do nothing
		}

		//find current speed in forward direction
		b2Vec2 currentForwardNormal = w_body->GetWorldVector(b2Vec2(0, 1));
		float currentSpeed = b2Dot(getForwardVelocity(), currentForwardNormal);

		//apply necessary force
		float force = 0;
		if (desiredSpeed > currentSpeed)
			force = maxDriveForce;
		else if (desiredSpeed < currentSpeed)
			force = -maxDriveForce;
		else
			return;
		//w_body->ApplyForce(currentTraction * force * currentForwardNormal, w_body->GetWorldCenter());
	}

	void updateTurn(int controlState) {
		float desiredTorque = 0;
		switch (controlState & (TDC_LEFT | TDC_RIGHT)) {
		case TDC_LEFT:  desiredTorque = 15;  break;
		case TDC_RIGHT: desiredTorque = -15; break;
		default:;//nothing
		}
		//w_body->ApplyTorque(desiredTorque);
	}


};

