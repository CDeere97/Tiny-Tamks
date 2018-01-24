////////////////////////////////////////////////////////////
// File: main.cpp
// Author: Chris Deere
// Date Created: 11/05/17
// Brief: main file for CT4019 assignment 2 - Tiny Tanks
////////////////////////////////////////////////////////////
#include "UGFW.h"
#include "Enumerations.h"
#include "Vector2.h"
#include "Matrix3.h"
#include "Matrix4.h"

#include <iostream>
#include <set>

#define EPSILON 10e-7

float Signf(float a_f)
{
	if (a_f < 0.f)
	{
		return -1.f;
	}
	return 1.f;
}

//\===========================================================================================================
//\ Node -
//\   This is a small structure/class that contains a matrix that is used to store rotation and positional data
//\ for an object. This node structure allows for parenting objects so that they can maintain a hierarchy for 
//\ matrix transformation detail, this permits easy parenting of objects like swords and other items onto a 
//\ character or in this scenario parenting a turret with a tank base.
//\===========================================================================================================
struct Node
{
	//Constructor
	Node() {
		m_pParent = nullptr;
		m3PosRot = Matrix3::IDENTITY;

	}
	//destructor (virtual as we will use node as a base class)
	virtual ~Node() {
		for (auto iter = m_pChildren.begin(); iter != m_pChildren.end(); ++iter)
		{
			RemoveChild(*iter);
		}
		m_pParent = nullptr;
	}

	//Function to set this node's parent 
	void SetParent(Node* a_parent)
	{
		if (a_parent == this)
			return;

		if (m_pParent != nullptr)
		{
			m_pParent->RemoveChild(this);
		}
		m_pParent = a_parent;
		m_pParent->AddChild(this);
	}
	//Function to add a child to the node
	void AddChild(Node* a_child)
	{
		auto iter = m_pChildren.find(a_child);
		//Children are stored in a set. One of the features of a set is easy searching for an item
		//this allows us to see if the child already exists in the set of children. 
		//If it exists already we will not add it to the set multiple times.
		if (iter == m_pChildren.end())
		{
			m_pChildren.emplace(a_child);
		}
	}
	//Remove a child from our node hierarchy structure
	void RemoveChild(Node* a_child)
	{
		//if we can find the child remove it, a successful find returns an iterator to the object
		//we are looking for. An unsuccessful find returns an iterator that is one item past the end of the set
		auto iter = m_pChildren.find(a_child);
		if (iter != m_pChildren.end())
		{
			m_pChildren.erase(iter);
		}
	}
	//Where is this node in the world 
	// this requires us to transform (multiply) this node by any parents it may have (and their parents in turn).
	void GetWorldTransform(Matrix3& transform)
	{
		if (m_pParent)
		{
			m_pParent->GetWorldTransform(transform);
			transform = m3PosRot * transform;
		}
		else
		{
			transform = m3PosRot;
		}
	}
	//Get the local transform for our point
	void GetLocalTransform(Matrix3 a_m3Transform)
	{
		a_m3Transform = m3PosRot;
	}
	//Set our translation
	void SetTranslation(Vector2 a_v2Translation)
	{
		Vector3 v3 = Vector3(a_v2Translation.x, a_v2Translation.y, 0.f);
		m3PosRot.SetRow(2, v3);
	}
	//Rotate this node around it's z axis
	void RotateZ(float a_fRotation)
	{
		Matrix3 m3Rotation = Matrix3::IDENTITY;
		m3Rotation.RotateZ(a_fRotation);
		m3PosRot = m3Rotation * m3PosRot;
	}
	//scale this node
	void Scale(float a_fScale)
	{
		Vector3 translation = Vector3::ZERO;
		m3PosRot.GetRow(2, translation);

		Matrix3 scale = Matrix3::IDENTITY;
		scale.operator*(a_fScale);
		m3PosRot = scale * m3PosRot;

		m3PosRot.SetRow(2, translation);

	}

protected:
	Matrix3 m3PosRot;
private:
	Node* m_pParent;
	std::set<Node*>m_pChildren;
	
};

//A very simple sprite class that extends from node allowing us to have a sprite hierarchy tree in our game
struct Sprite : public Node{
	//Constructor -- makes a UG Sprite object for us to use
	Sprite(const char* a_fileName, int a_width, int a_height, Vector2 a_origin, Vector4 a_UVCoords) {
		float v2size[2] = { a_width, a_height };

		m_iSpriteID = UG::CreateSprite(a_fileName, v2size, a_origin, &a_UVCoords.x);
		float mat4x4[16];
		memset(mat4x4, 0, sizeof(float) * 16);
		UG::GetSpriteMatrix(m_iSpriteID, mat4x4);
		m3PosRot = Matrix3(mat4x4[0], mat4x4[1], mat4x4[2], mat4x4[4], mat4x4[5], mat4x4[6], mat4x4[12], mat4x4[13], 1.f);

	}
	//Destructor
	virtual ~Sprite() {
		UG::DestroySprite(m_iSpriteID);
	}
	//Set our sprite layer
	void SetLayer(unsigned int a_uiLayer)
	{
		UG::SetSpriteLayer(m_iSpriteID, a_uiLayer);
	}
	//an update function to call each frame to update our sprites data
	void Update(float a_fdt)
	{
		//OpenGL which is the underlying rendering pipeline that is being used by the framework
		//draws all components using a 4x4 matrix to represent their world coordinates, here I am constructing that matrix
		//from the 3x3 matrix that we are using internally
		//set the sprites matrix

		Matrix3 worldTx = Matrix3::IDENTITY;
		GetWorldTransform(worldTx);
		Matrix4 m4x4 = Matrix4(worldTx.m_11, worldTx.m_12, worldTx.m_13, 0.f,
								 worldTx.m_21, worldTx.m_22, worldTx.m_23, 0.f,
								 0.f,			0.f,			1.f,	   0.f,
								 worldTx.m_31, worldTx.m_32,    0.f,	   1.f);
		UG::SetSpriteMatrix(m_iSpriteID, m4x4);

	}
	//Function to move our sprite
	// The movement vector argument is not guaranteed to be a unit vector as we may be moving scaled by a velocity
	void MoveSprite(Vector3 a_movementVec)
	{
		Vector3 pos;
		m3PosRot.GetRow(2, pos);
		//Multiplying the movement vector by our local transform will put that vector in the local space of this object
		//if we were after moving this object along a world vector then we would need to multiply that vector by the inverse
		//of our worldspace matrix
		pos += a_movementVec * m3PosRot;
		
		m3PosRot.SetRow(2, pos);
	}

	void MarkForDraw()
	{
		UG::DrawSprite(m_iSpriteID);
	}

	void StopDrawing()
	{
		UG::StopDrawingSprite(m_iSpriteID);
	}

	void SetPosition(Vector2 a_pos) {
		Vector3 np = Vector3(a_pos.x, a_pos.y, 1.f);
		m3PosRot.SetRow(2, np);

	}

	float GetXPosition()
	{
		return m3PosRot.m_31;
	}

	float GetYPosition()
	{
		return m3PosRot.m_32;
	}
	
private:
	int m_iSpriteID;
	int m_iWidth;
	int m_iHeight;
	Vector2 m_v2Origin;
	

};

struct Bullet
{
	int iSpriteID = -1;
	int xDir = 0;
	int yDir = 0;
	//int iMovementSpeed = 1;
	//int iShootSpeed = 6;
	int iBWidth = 8;
	int iBHeight = 8;

	Vector2 pos;

	//short upKey = -1;
	//short downKey = -1;
	//short leftKey = -1;
	//short rightKey = 1;

	bool bBulletReset = true;
};

struct Enemy
{
	int iSpriteID = -1;
	int xDir = 0;
	int yDir = 0;
	int iSpeed = 4;
	int iRadius = 16;
	int iEWidth = 32;
	int iEHeight = 32;
	Vector2 pos;
	//A boolean variable to notify us if we need to be reset to the centre
	bool bEnemyReset = true;

};

void TestCollision(Bullet& a_Bullet, Enemy& a_Enemy);

//Variable to see if player is shooting
bool g_bIsShooting = false;
//Variable to see if enemy is dead
bool g_bIsDead = false;
//Variable to see if the player is powered up
bool g_bPoweredUp = false;
//Time player stays powered up
float g_fPowerTime = 6.f;
//Time until the power up moves
float g_fMoveTime = 4.f;

// Bullet Functions
//void ShootKeyPressed(Sprite& pBullet);
//void ShootBullet(Sprite& pBullet, Sprite& pTank);

int main(int argv, char* argc[])
{
	if (UG::Create( 1024, 768, false, "Tiny Tanks", 100, 100 ))
	{

		int iScreenWidth = 0, iScreenHeight = 0;
		UG::GetScreenSize(iScreenWidth, iScreenHeight);
		
		UG::SetBackgroundColor(UG::SColour(0x2A, 0x57, 0x66, 0xFF));
		UG::AddFont("./fonts/invaders.fnt");
		
		//Create a sprite for our tank's base
		Sprite* pTank = new Sprite("./images/tanks.png", 66, 72, Vector2(0.5f, 0.5f), Vector4(0.058f, 0.536f, 0.442f, 0.964f));
		pTank->SetPosition(Vector2(iScreenWidth * 0.5f, iScreenHeight * 0.5f));
		pTank->MarkForDraw();
		pTank->SetLayer(0);

		//Create a sprite for our tank's turret
		Sprite* pTurret = new Sprite("./images/tanks.png", 38, 64, Vector2(0.5f, 0.29f), Vector4(0.622f, 0.607f, 0.843f, 0.988f));
		pTurret->SetParent(pTank);
		pTurret->MarkForDraw();
		pTurret->SetLayer(2);

		//Create a sprite for our tank's bullet
		Sprite* pBullet = new Sprite("./images/Ball.png", 8, 8, Vector2(0.5f, 0.5f), Vector4(0.0f, 0.0f, 1.0f, 1.0f));
		pBullet->SetPosition(Vector2(iScreenWidth * 0.5f, iScreenHeight * 0.5f));
		//pBullet->SetParent(pTank);
		//pBullet->SetParent(pTurret);
		pBullet->MarkForDraw();
		pBullet->SetLayer(0);

		//Create a sprite for enemy's tank's base
		Sprite* eTank = new Sprite("./images/tanks.png", 66, 72, Vector2(0.5f, 0.5f), Vector4(0.058f, 0.036f, 0.452f, 0.520f));
		eTank->SetPosition(Vector2(rand() % iScreenWidth, rand() % iScreenHeight));
		eTank->MarkForDraw();
		eTank->SetLayer(0);

		//Create a sprite for enemy's tank's turret
		Sprite* eTurret = new Sprite("./images/tanks.png", 38, 64, Vector2(0.5f, 0.29f), Vector4(0.632f, 0.134f, 0.843f, 0.532f));
		eTurret->SetParent(eTank);
		eTurret->MarkForDraw();
		eTurret->SetLayer(1);

		//Create a sprite for enemy's tank's turret
		Sprite* PowerUp = new Sprite("./images/SliderGrip.png", 16, 16, Vector2(0.5f, 0.5f), Vector4(0.0f, 0.0f, 1.0f, 1.0f));
		PowerUp->SetPosition(Vector2(rand() % iScreenWidth, rand() % iScreenHeight));
		PowerUp->MarkForDraw();
		PowerUp->SetLayer(1);

		//We will be using some simple physics to move our tank
		//Lets use a value for max speed for our tank to be 100
		//our cut off speed can be set to 5 so if we are below that then don't move
		float fCurrentVelocity = 0.f;
		float fMaxVelocity = 10.f;
		// Bullet's velocity
		float fBulletVelocity = 30.f;
		float fDrag = 0.03f;
		float fTankRotDifference = 0.f; // Difference between tank and bullet's rotation
		float fTotTurretRot = 0.f; // Total turret rotation
		float fBulletRot = 0.f; // Bullet rotation
		float delta = UG::GetDeltaTime();

		//Set up Enemy.
		Enemy enemy;
		//Set Up Bullet
		Bullet bullet;

		do
		{
			float dt = UG::GetDeltaTime();
			float xPos = 0; float yPos = 0;

			//Player position
			float pX = pTank->GetXPosition();
			float pY = pTank->GetYPosition();
			//Enemy position
			float eX = eTank->GetXPosition();
			float eY = eTank->GetYPosition();
			//Bullet position
			float bX = pBullet->GetXPosition();
			float bY = pBullet->GetYPosition();
			//Power up position
			float p_uX = PowerUp->GetXPosition();
			float p_uY = PowerUp->GetYPosition();

			int iTWidth = 66.f; // Tank Width
			int iTHeight = 72.f; // Tank Height

			float fHalfTWidth = iTWidth * 0.5f;
			float fHalfTHeight = iTHeight * 0.5f;
			
			//Create a vector to store our movement
			Vector3 movementVector = Vector3::AXIS_Y;
			//We're going to be treating moving forward and backward as traversing along the sprite's Y axis
			//If our sprite was rotated 90 degrees on the sprite sheet then we would treat that direction as forward.
			float fAccelleration = 0.f;

			if (UG::IsKeyDown(UG::KEY_W))
			{
				fAccelleration += 3.f;
				fDrag = 0.f;
			}

			if (UG::IsKeyDown(UG::KEY_S))
			{
				fAccelleration -= 2.f;
				fDrag = 0.f;
			}
			if (!UG::IsKeyDown(UG::KEY_S) && !UG::IsKeyDown(UG::KEY_W))
			{
				fDrag = 0.08f;
			}

			if (pX + fHalfTWidth < iScreenWidth && pX - fHalfTWidth > 0 && pY + fHalfTHeight < iScreenHeight && pY - fHalfTHeight > 0)
			{
				fCurrentVelocity += fAccelleration * dt;
				fCurrentVelocity -= fCurrentVelocity * fDrag;
				if (fabsf(fCurrentVelocity) > fMaxVelocity)
				{
					fCurrentVelocity = fMaxVelocity * Signf(fCurrentVelocity);
				}
				if (fabsf(fCurrentVelocity) > EPSILON)
				{
					movementVector *= fCurrentVelocity;
					pTank->MoveSprite(movementVector);
					if (g_bIsShooting == false)
					{
						pBullet->MoveSprite(movementVector);
					}
				}
			}
			else
			{
				if (fCurrentVelocity > 0)
				{
					movementVector.y = -movementVector.y * fCurrentVelocity;
					pTank->MoveSprite(movementVector);
				}
				else if (fCurrentVelocity < 0)
				{
					movementVector.y = movementVector.y * -fCurrentVelocity;
					pTank->MoveSprite(movementVector);
				}
			}
			//Tank Rotation
			if (UG::IsKeyDown(UG::KEY_A))
			{
				pTank->RotateZ(0.05f);
				if (g_bIsShooting == false)
				{
					pBullet->RotateZ(0.05f);
				}
				// If the bullet is shooting store how much the tank rotates 
				else if (g_bIsShooting == true)
				{
					fTankRotDifference += 0.05f;
				}
			}
			if (UG::IsKeyDown(UG::KEY_D))
			{
				pTank->RotateZ(-0.05f);
				if (g_bIsShooting == false)
				{
					pBullet->RotateZ(-0.05f);
				}
				// If the bullet is shooting store how much the tank rotates 
				else if (g_bIsShooting == true)
				{
					fTankRotDifference -= 0.05f;
				}
			}
			

			//Turret Rotation
			
			if (UG::IsKeyDown(UG::KEY_Q))
			{
				pTurret->RotateZ(0.085f);
				fTotTurretRot += 0.085f;
				//pBullet->RotateZ(0.085f);
				
			}
			if (UG::IsKeyDown(UG::KEY_E))
			{
				pTurret->RotateZ(-0.085f);
				fTotTurretRot -= 0.085f;
				
				//pBullet->RotateZ(-0.085f);
			}
			
			//Shooting
			if (UG::IsKeyDown(UG::KEY_SPACE))
			{
				if (g_bIsShooting == false) //Only rotate bullet when the bullet is not being fired
				{
					// Rotates the bullet by the same amount as the turret
					fBulletRot += fTotTurretRot;
					pBullet->RotateZ(fBulletRot);
					//Resets the rotations
					fBulletRot = 0;
					fTotTurretRot = 0;
					// Turret is now shooting
					g_bIsShooting = true;
				}
			}

			if (g_bIsShooting == true)
			{
				
				// New vector for the bullet movement
				Vector3 newMovementVector = Vector3::AXIS_Y;

				// Move the bullet
				newMovementVector *= fBulletVelocity;
				pBullet->MoveSprite(newMovementVector);
				
				
			}

			//Respawn bullet when it goes off screen
			if (bX < 0 || bX > iScreenWidth || bY < 0 || bY > iScreenHeight)
			{
				// Rotate the bullet so it's the same as the tank
				pBullet->RotateZ(fTankRotDifference);
				fTankRotDifference = 0.f;
				g_bIsShooting = false;
			}

			//Respawn bullet after it hits enemy tank
			if (bX < eX + fHalfTWidth && bX > eX - fHalfTWidth && bY < eY + fHalfTHeight && bY > eY - fHalfTHeight)
			{
				// Rotate the bullet so it's the same as the tank
				pBullet->RotateZ(fTankRotDifference);
				fTankRotDifference = 0.f;
				g_bIsDead = true;
				g_bIsShooting = false;
			}

			if (g_bIsDead == true)
			{
				//Spawn enemy tank in a different position
				eTank->SetPosition(Vector2(rand() % iScreenWidth, rand() % iScreenHeight));
				g_bIsDead = false;
			}

			//Reset bullet
			if (g_bIsShooting == false)
			{

				pBullet->SetPosition(Vector2(pTank->GetXPosition(), pTank->GetYPosition()));
			}

			g_fMoveTime -= delta;
			if (g_fMoveTime < 0)
			{
				PowerUp->SetPosition(Vector2(rand() % iScreenWidth, rand() % iScreenHeight));
				g_fMoveTime = 4.f;

			}

			//Power up player if they collides with a power up
			if (pX + fHalfTWidth > p_uX && pX - fHalfTWidth < p_uX && pY + fHalfTHeight > p_uY && pY - fHalfTHeight < p_uY && g_bPoweredUp == false)
			{
				g_bPoweredUp = true;
				PowerUp->SetPosition(Vector2(rand() % iScreenWidth, rand() % iScreenHeight));
			}
			
			//Bullet speed boost
			if (g_bPoweredUp == true)
			{
				g_fPowerTime -= delta;
				fBulletVelocity =  60.f;
				if (g_fPowerTime < 0)
				{
					fBulletVelocity = 30.f;
					g_bPoweredUp = false;
					g_fPowerTime = 6.f;
				}
			}

			// quit our application when escape is pressed
			if (UG::IsKeyDown(UG::KEY_ESCAPE))
				UG::Close();

			

			//Draw some text
			UG::ClearScreen();

			pTank->Update(dt);
			pTurret->Update(dt);
			pBullet->Update(dt);

			eTank->Update(dt);
			eTurret->Update(dt);

			PowerUp->Update(dt);

			
			//UG::SetFont("./fonts/invaders.fnt");
			//UG::DrawString("Nodes Demo", (int)(iScreenWidth * 0.47f), iScreenHeight - 2, 1.f);
			
			//\==============================================================================================================================
			//Some simple Line drawing to draw the lines on the court.
			//Top and Bottom lines
			//UG::DrawLine(0, iScreenHeight - 40, iScreenWidth, iScreenHeight - 40, UG::SColour(0xFF, 0xFF, 0xFF, 0xFF));
			//UG::DrawLine(0, 40, iScreenWidth, 40, UG::SColour(0xFF, 0xFF, 0xFF, 0xFF));
			//\==============================================================================================================================
			
			//UG::SetFont(nullptr);

		} while (UG::Process());

				
		UG::Dispose();


	}
	return 0;
}

void TestCollision(Bullet & a_Bullet, Enemy& a_Enemy)
{
	int halfBulletHeight = (int)(a_Bullet.iBHeight * 0.5f);
	int halfEnemyHeight = (int)(a_Enemy.iEHeight * 0.5f);

	float bX = 0.f, bY = 0.f;
	a_Bullet.pos.getPos(bX, bY);

	float eX = 0.f, eY = 0.f;
	a_Enemy.pos.getPos(eX, eY);
	
	//Collision testing between the enemy and bullet
	if (g_bIsShooting == true) // Only test for collisions if bullet is being shot
	{


		// Resets bullet if it collides with an enemy
		if (bY + halfBulletHeight > eY - halfEnemyHeight && bY - halfBulletHeight < eY + halfEnemyHeight)
		{
			int halfEnemyWidth = (int)(a_Enemy.iEWidth * 0.5f);
			int halfBulletWidth = (int)(a_Bullet.iBWidth * 0.5f);

			if (eX - halfEnemyWidth < bX + halfBulletWidth && eX + halfEnemyWidth > bX - halfBulletWidth)
			{
				//a_Bullet.bBulletReset = true;
				//a_Enemy.bEnemyReset = true;
				//g_iPlayerScore += 100;

			}

		}
	}
}
