#include "GameLib/GameLib.h"
using namespace GameLib;

#include "Library/Vector3.h"
#include "Library/Matrix34.h"
#include "Library/GraphicsDatabase.h"
#include "Library/Model.h"
#include "GameLib/GameLibMath.h"
using namespace std;

#include "Sword.h"

const float Sword::mSwordPush = 3;

Sword::Sword() : mModel(0),mCount(-1){

}

Sword::~Sword() {
	SAFE_DELETE(mModel);
}


bool Sword::isEmpty() const {
	return (mCount < 0);
}

void Sword::create(
	GraphicsDatabase* db,
	const char* batchName,
	const Vector3& position,
	double angleX,
	double angleY,
	unsigned color) {
		SAFE_DELETE(mModel);
		mModel = db->createModel(batchName);
		mModel->setPosition(position);
		mModel->setAngle(Vector3(angleX, angleY-100, 0.0));
		mModel->setColor(color);
		mCount = 0;
}

const Vector3* Sword::position() const {//positionの値を返す関数
	return mModel->position();
}

const Vector3* Sword::angle() const {
	return mModel->angle();
}

void Sword::update(double myAngleY, Vector3* position) {
	mModel->setPosition(*position);
	Vector3 p = *mModel->position();
	p.y += 2;
	p.z += cos(myAngleY);
	p.x += sin(myAngleY);

	mModel->setPosition(p);
	
	Vector3 a = *mModel->angle();
	a.y += 2;
	mModel->setAngle(a);
	++mCount;

}
void Sword::draw(const Matrix44& pvm)const {
	mModel->draw(pvm);
}
void Sword::die() {
	mCount = -1;
}

Vector3 Sword::Push(Vector3 myPosition, Vector3 enemyPosition) {//インスタンスとして持つ必要はないが、剣の吹っ飛び方に種類をつける場合いる
	double rad = atan2(enemyPosition.z - myPosition.z, enemyPosition.x - myPosition.x);
	Vector3 pushVec(Sword::mSwordPush * cos(rad), 4, Sword::mSwordPush * sin(rad));//相手の方向に吹っ飛ぶ
	return pushVec; 
}