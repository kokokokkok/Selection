#include <sstream>
#include <Windows.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "GameLib/Framework.h"
#include "GameLib/Input/Manager.h"
#include "GameLib/Input/Manager.h"
#include "Robo.h"
#include "Bullet.h"
#include "Sword.h"
#include "Pad.h"
#include "Circle.h"
#include "Library/Matrix34.h"
#include "Library/GraphicsDatabase.h"
#include "Library/Model.h"
#include "GameLib/GameLibMath.h"


using namespace GameLib;
using namespace std;


const int Robo::mJumpUpTime = 20; //上昇していく時間
const double Robo::mJump = 0.5;
const double Robo::mJumpHeight = 100.0; //最大高度
const int Robo::mJumpStayTime = 60; //上昇後下降までの時間
const int Robo::mJumpFallTime = 10; //下降にかかる時間
const double Robo::mCameraDistanceZ = 8.0; //何メートル後ろから写す？
const double Robo::mCameraDistanceY = 4.0; //見下ろし具合
const double Robo::mCameraTargetDistanceZ = 20.0; //注視点は何メートル先？
const double Robo::mTurnSpeed = 1.0; //旋回速度
const int Robo::mMaxEnergy = 100; //最大武器ポイント
const int Robo::mEnergyPerBullet = 50; //遠距離武器の消費エネルギー
const int Robo::mEnergyPerSword = 50; //近処理武器の消費エネルギー
const int Robo::mCloseAttackRange = 10;
const int Robo::mLongAttackRange = 4;

const int Robo::mMaxAccelEnergy = 100;//回避エネルギーの上限の値
const double Robo::mLockOnAngleIn = 10.0; //ロックオンする角度
const double Robo::mLockOnAngleOut = 15.0; //ロックオンが外れる角度
const double Robo::mMouseSensitivity = 0.2; //マウスの感度
const double Robo::mBasicSpeed = 0.4; //基本スピード
const double Robo::mAccelDash = 25; //回避時の速さ
const int Robo::mAttackedState = 0;//攻撃されたときの状態
const int Robo::mAttackState = 0;//攻撃したときの状態


//const int Robo::mScore = 0;
const int Robo::mAttackDistance = 3;
const double Robo::mJumpPerTime = 0.2;
const double Robo::mFallPerTime = 0.05;


/*
//---------------------------------------------------------------------------------変動ステータス
double  Robo::mCloseRangeAttackRatio = 1;//近距離攻撃倍率
double  Robo::mLongRangeAttackRatio = 1;//遠距離攻撃倍率
double  Robo::mGuardDamageCutRatio = 1.5;//防御率カット
float Robo::mMaxHitPoint = 100; //最大ヒットッポイント
float Robo::mBulletEnergyIncreaseSpeed = 1; //弾エネルギー回復速度
float  Robo::mDashEnergyIncreaseSpeed = 1;//回避エネルギー回復速度
//-----------------------------------------------------------------------------------
*/
const double Robo::mLongRangeDamage = 10;//遠距離ダメージ
const double Robo::mCloseRangeDamage = 15;//近距離ダメージ
bool Robo::mGravity = false;


Robo::Robo(int id,int gTime) ://gTime
	mPosition(0.0, 0.0, 0.0),
	mAngleY(0.0),
	mId(id),
	//	mNpcKind(),
	mDatabase(0),
	mModel(0),
	mBullets(0),
	mSwords(0),
	mBulletNumber(100), //きめうち
	mSwordNumber(100),
	mCameraCount(0),
	mCount(0),
	mVelocity(0.0, 0.0, 0.0),
	mPushRange(0.0, 0.0, 0.0),//攻撃されたときに代入されて、moveに入れ込む
	mMode(MODE_ON_LAND),
	mHitPoint(100),
	mEnergy(mMaxEnergy),
	mGuard(false),//この一のほうが正しい？　ここで敵のガードしてるかどうかを決めている　ほぼ意味ないが。。。

	mAttacked(mAttackedState),//攻撃されている状態か、その時ガードしているか
	mAttackedCount(0),

	mAttack(mAttackState),
	mAttackCount(0),

	mAccelEnergy(mMaxAccelEnergy),//回避のためのエネルギー
	mAngleVelocityY(0),

	mNpcAttackKind(rand()%2),//近距離or遠距離の抽選　
	mNpcAttackLongRange(rand() % 20),//遠距離攻撃の攻撃に必要な距離　
	mNpcAttackCloseRange(rand() % 10),//近距離攻撃の攻撃に必要な距離　//-------------------------ソードの距離参照
	firstTime(true),
	gTime(gTime),
	mEnemyId(1),

	//--------------------------変動ステータス
	mCloseRangeAttackRatio(1),//近距離攻撃倍率
	mLongRangeAttackRatio(1),//遠距離攻撃倍率
	mGuardDamageCutRatio(1.5),//防御率カット
	mBulletEnergyIncreaseSpeed(1), //弾エネルギー回復速度
	mDashEnergyIncreaseSpeed(1),//回避エネルギー回復速度
	mMaxHitPoint(100),

	mLockOn(true) { 
	mDatabase = new GraphicsDatabase("player.txt");
	mModel = mDatabase->createModel("robo");
	mModel->setColor((mId == 0) ? 0xcc0088ff : 0xccff8800);//---------------------------------plyaerの色-------------------------------------
	
	mBullets = new Bullet[mBulletNumber];
	mSwords = new Sword[mSwordNumber];

	Vector3 c = mPosition;//ロボ同士の衝突半径
	c.y += 0.5;//球の中心を上にずらす
	mCircle.setPosition(c);
	mCircle.setRadius(0.5);
	//mGuard(false) ここより
}
	

Robo::~Robo() {
	SAFE_DELETE_ARRAY(mBullets);
	SAFE_DELETE_ARRAY(mSwords);

	SAFE_DELETE(mModel); 
	SAFE_DELETE(mDatabase);
}
//-------------------------------------------------------実際に攻撃するときなどにこの値を掛けといけない
void Robo::statusCloseRangeAttack(double changeNumber) {
	mCloseRangeAttackRatio += changeNumber;
}
void Robo::statusLongRangeAttack(double changeNumber) {
	mLongRangeAttackRatio += changeNumber;
}
void Robo::statusGuardCut(double changeNumber) {
	mGuardDamageCutRatio += changeNumber;
}
void Robo::statusMaxHpIncrease(int changeNumber) {
	mMaxHitPoint += changeNumber;
}
void Robo::statusHpRecover(int changeNumber) {
	mHitPoint += changeNumber;
	if (mHitPoint > mMaxHitPoint) {
		mHitPoint = mMaxHitPoint;
	}
}
void Robo::statusBulletEnergySpeed(float changeNumber) {
	mBulletEnergyIncreaseSpeed += changeNumber;
}
void Robo::statusDashEnergySpeed(float changeNumber) {
	mDashEnergyIncreaseSpeed += changeNumber;
}




void Robo::setPosition(const Vector3& a) {
	mPosition = a;
	Vector3 c = mPosition;
	c.y += 0.5; //中心が上にずれてる
	mCircle.setPosition(c);
}

void Robo::setAngleY(double a) {
	mAngleY = a;
}

void Robo::getMove(Vector3* move) {
	move->set(0.0, 0.0, 0.0);
	move->set(mPushRange.x, mPushRange.y, mPushRange.z);//-----------------------------------------------ここで攻撃で押された分を入れ込む 現在は機能していない理由を詮索中・・・
	Pad* pad = Pad::instance();
	if (pad->isOn(Pad::UP, mId)) {
		move->z = -mBasicSpeed;
	}
	if (pad->isOn(Pad::DOWN, mId)) {
		move->z = mBasicSpeed;
	}
	if (pad->isOn(Pad::LEFT, mId)) {
		move->x = -mBasicSpeed;
	}
	if (pad->isOn(Pad::RIGHT, mId)) {
		move->x = mBasicSpeed;
	}
	if ( (pad->isOn(Pad::DASH, mId) && (mAccelEnergy > 100) && ( (pad->isOn(Pad::UP, mId)) || (pad->isOn(Pad::DOWN, mId)) || (pad->isOn(Pad::LEFT, mId)) || (pad->isOn(Pad::RIGHT, mId)) ))){//一回発動すると-100だけで永遠この関数の回し、高速移動になってしまう
		*move *= mAccelDash;
		mAccelEnergy -= 100;//当たり前だがconstをつけると変更できないぞ
		//cout << "mAccelEnergy" << mAccelEnergy << endl;
	}
	
	if (pad->isOn(Pad::JUMP, mId)) {
		move->y = mJumpPerTime;
	}
	else {
		if (Robo::mGravity == false){
			move->y -= mFallPerTime;
		}
	}
	
	Matrix34 m;
	m.setRotationY(mAngleY + 180.0);
	m.multiply(move, *move);
}


int Robo::Print() const{
	return mPushRange.x;

}


void gravityCheck(bool gravityJudge) {
	Robo::mGravity = gravityJudge;

}


void Robo::update(
	Robo* enemy,
	//std::unique_ptr<Robo&> enemy,
	const Vector3& nextMove) {
	
	mPushRange.set(0, 0, 0);//-------------------------リセットここで吹っ飛びを初期化、もし、吹っ飛び制御はここで計算する。


	mByLongHit = false;
	mByCloseHit = false;
	
	

	mPosition += nextMove;//合成ベクトルを足す！
	//mPosition += nextMove;
	
	Vector3 c = mPosition;
	c.y += 0.5; //中心が上にずれてる
	mCircle.setPosition(c);

	//死んでる
	if (mHitPoint <= 0) {
		return;
	}

	//角度範囲補正
	if (mAngleY > 180.0) {
		mAngleY -= 360.0;
	}
	else if (mAngleY < -180.0) {
		mAngleY += 360.0;
	}

	bool iJump;
	bool iFire;
	bool iSwing;
	bool iTurn;
	bool iLeft;
	bool iRight;
	bool iUp;
	bool iDown;
	bool iDash;
	bool iGuard;
	int iMouseX;
	int iMouseY;
	int iVelocityX;
	int iVelocityY;

	const Vector3& enemyPos = *enemy->position();
	const bool enemyGuard = enemy->mGuard;
	const double myAngle = mAngleY;

	think(&iJump, &iFire, &iSwing,&iTurn, &iLeft, &iRight, &iDash ,&iUp, &iDown, &iGuard, &iMouseX , &iMouseY ,&iVelocityX, &iVelocityY, &mGuard, enemyPos, myAngle);



	++mCount;
	//ジャンプ押されてる？

	//jump(!iJump);
	//move(iLeft, iRight, iUp, iDown, iJump,iDash, iGuard); //コードが長くなるので関数に飛ばす--------------------------------------ここで回避エネルギーを調整しているので後で直せ！
	sight_move(iMouseX, iMouseY, iVelocityX, iVelocityY);

	if (mAttackedCount > 0) {
		mAttackedCount -= 1;
	}
	if (mAttackedCount <= 0) {
		mAttacked = 0;//攻撃を受けた状態を戻す
	}
	if (mAttackCount > 0) {
		mAttackCount -= 1;
	}
	if (mAttackCount <= 0) {
		mAttack = 0;//攻撃をした状態を戻す
	}

	if (mAccelEnergy < mMaxAccelEnergy + 1) {
		mAccelEnergy += mDashEnergyIncreaseSpeed;
	}
/*
	double t;

	switch (mMode) {
	case MODE_JUMP_UP:
		t = mJumpHeight / static_cast<double>(mJumpUpTime);
		mVelocity.y = t;
		if (!iJump) { //ジャンプ入力がないので下降に変化
			mMode = MODE_JUMP_FALL;
			mCount = 0;
		}
		else if (mCount >= mJumpUpTime) { //上昇終了
			mMode = MODE_JUMP_STAY;
			mCount = 0;
		}
		mVelocity.x = mVelocity.z = 0.0; //X,Z移動を抹殺
		break;
		
	case MODE_JUMP_STAY:
		mVelocity.y = 0.0;
		if (!iJump) { //ジャンプ入力がないので下降に変化
			mMode = MODE_JUMP_FALL;
			mCount = 0;
		}
		else if (mCount >= mJumpStayTime) { //下降へ
			mMode = MODE_JUMP_FALL;
			mCount = 0;
		}
		break;
	case MODE_JUMP_FALL:
		//下降
		t = mJumpHeight / static_cast<double>(mJumpFallTime);
		mVelocity.y = -t;
		//接地判定は最終的には衝突処理でやるのでここではやらない。
		break;
	case MODE_ON_LAND:
		if (iJump) {
			mMode = MODE_JUMP_UP;
			mCount = 0;
			mCameraCount = 0;
					}
		else if (iTurn) {
			turn(iLeft, iRight); //コードが長くなるので関数に飛ばす
		}
		else {
			
		mVelocity.y = 0.0;
		break;
	}
	*/

	if (mId != 0) {
		//接近型か遠距離型かを決める　True False 
		npcTurn(mPosition, enemyPos);
		//npcMove(mPosition, enemyPos);
		npcAttack(mPosition, enemyPos, iFire);
		
		double distanceZ = abs(enemyPos.z - mPosition.z);
		double distanceX = abs(enemyPos.x - mPosition.x);

		if ((mNpcAttackKind == 0) && (distanceX < mNpcAttackCloseRange && distanceZ < mNpcAttackCloseRange)) {
			iSwing = true;
		}
		else if ((mNpcAttackKind == 1) && (distanceX < mNpcAttackLongRange && distanceZ < mNpcAttackLongRange)) {
			iFire = true;
		}
		//NpcのHPと攻撃力をゲームの進行度（gTime）によって上げる
		if (firstTime == true ) {
			mCloseRangeAttackRatio += gTime * 0.00005;
			mLongRangeAttackRatio += gTime * 0.00005;
			mHitPoint += mMaxHitPoint * 0.002;
		}
		firstTime = false;
	}

	
	//ここから下は衝突処理が入るとその後になる。
	/*
	mPosition += mVelocity;//ここで足している
	if (mPosition.y < 0.0) {
		mPosition.y = 0.0;
		mMode = MODE_ON_LAND;
	}*/
	//武器生成
	if (iFire) {
		//上昇、下降中は撃てない
		if ((mMode != MODE_JUMP_FALL) && (mMode != MODE_JUMP_UP)) {
			//エネルギー足りてるかどうか
			if (mEnergy >= mEnergyPerBullet) {
				//空き武器を探す
				for (int i = 0; i < mBulletNumber; ++i) {
					if (mBullets[i].isEmpty()) {
						unsigned c = (mId == 0) ? 0xcc0088ff : 0xccff8800;//弾の色-------------------------------------------
						mBullets[i].create(
							mDatabase,
							"bullet",
							mPosition,
							15.0,//angleX
							mAngleY,
							mLockOn,
							c);
						mEnergy -= mEnergyPerBullet;
						break;
					}
				}
			}
		}
	}
	//武器更新
	for (int i = 0; i < mBulletNumber; ++i) {
		if (!mBullets[i].isEmpty()) {
			mBullets[i].update(enemyPos);
			//衝突処理
			Vector3 t;
			t.setSub(*mBullets[i].position(), enemyPos);
			if (t.squareLength() < mLongAttackRange) {
				mAttack = 2;//遠距離攻撃を与えた場合
				mAttackCount = 10;
				enemy->setDamage(mLongRangeDamage * mLongRangeAttackRatio,enemyGuard); //1点減らしてみた。
				mByLongHit = true;
				mBullets[i].die(); //弾消えます。
			}
		}
	}
	
	if (iSwing) {
		if (mEnergy >= mEnergyPerSword) {
			//空き武器を探す
			for (int i = 0; i < mSwordNumber; ++i) {
				if (mSwords[i].isEmpty()) {
					unsigned c = (mId == 0) ? 0xcc0088ff : 0xccff8800;//弾の色-------------------------------------------
					mSwords[i].create(
						mDatabase,
						"sword",
						mPosition,
						15.0,//angleX
						mAngleY,
						c);
					mEnergy -= mEnergyPerSword;
					break;
				}
			}
		}
	}
	//武器更新
	for (int i = 0; i < mSwordNumber; ++i) {
		if (!mSwords[i].isEmpty()) {
			mSwords[i].update(mAngleY, &mPosition);
			//衝突処理
			Vector3 t;
			t.setSub(*mSwords[i].position(), enemyPos);
			if (t.squareLength() < mCloseAttackRange) {
				mAttack = 1;//近距離攻撃を与えた場合
				mAttackCount = 10;
				enemy->setDamage(mCloseRangeDamage * mCloseRangeAttackRatio, enemyGuard);
				//mPushRange = mSwords[i].Push(mPosition, enemyPos);//---------------------------------------------------------------------
				mByCloseHit = true;
				mSwords[i].die(); //剣が消えます。
			}
			if (mSwords[i].angle()->y > mAngleY + 180) {
				mSwords[i].die();
			}
		}
	}
	//ロックオン処理
	Vector3 toEnemy;
	toEnemy.setSub(enemyPos, mPosition);
	Vector3 myDir(0.0, 0.0, -1.0);
	Matrix34 m;
	m.setRotationY(mAngleY + 180.0);
	m.multiply(&myDir, myDir);
	toEnemy *= 1.0 / toEnemy.length(); //長さを1に
	double dotProduct = toEnemy.dot(myDir);
	//角度に直すと、
	double angle = GameLib::acos(dotProduct);
	if (mLockOn) {
		if (angle > mLockOnAngleOut) {
			mLockOn = false;
		}
	}
	else {
		if (angle < mLockOnAngleIn) {
			mLockOn = true;
			mEnemyId = enemy->mId;
		}
	}

	//武器エネルギーチャージ
	mEnergy += mBulletEnergyIncreaseSpeed;
	if (mEnergy > mMaxEnergy) {
		mEnergy = mMaxEnergy;
	}
	
	/*値表示
	ostringstream oss;
	oss << "VEL: " ;
	Framework().drawDebugString(0, 0, oss.str().c_str());
	*/

}



void Robo::think(
	bool* jump,
	bool* fire,
	bool* swing,
	bool* turn,
	bool* left,
	bool* right,
	bool* dash,
	bool* up,
	bool* down,
	bool* guard,
	int* iMouseX,
	int* iMouseY,
	int* VelocityX,
	int* VelocityY,
	bool* mGuard,
	const Vector3& enemyPos,
	const double mAngleY) const {
	Pad* pad = Pad::instance();
	if (mId == 0) { //プレイヤー
		*jump = pad->isOn(Pad::JUMP, mId);
		*fire = pad->isTriggered(Pad::FIRE, mId);
		*swing = pad->isTriggered(Pad::SWING, mId);
		*turn = pad->isOn(Pad::TURN, mId);
		*left = pad->isOn(Pad::LEFT, mId);
		*right = pad->isOn(Pad::RIGHT, mId);
		*dash = pad->isOn(Pad::DASH, mId);
		*up = pad->isOn(Pad::UP, mId);
		*down = pad->isOn(Pad::DOWN, mId);
		*guard = pad->isOn(Pad::GUARD, mId);
		*iMouseX = pad->X();
		*iMouseY = pad->Y();
		*VelocityX = pad->VelocityX();
		*VelocityY = pad->VelocityY();
		*mGuard = pad->isOn(Pad::GUARD, mId);
	}
	else { //NPC
		//*jump = !mLockOn;
		//弾は撃てるだけ撃つ
		*jump = false;
		*fire = false;
		*swing = false;

		//旋回はしない
		//*turn = false;
		//移動は変数を持つのが面倒なのでしない。
		*left = *right = *up = *down = false;
		*guard = false;
		
	}
}

void Robo::turn(bool left, bool right) {
	if (left) {
		mAngleY += mTurnSpeed;
		if (mAngleY > 180.0) { 
			mAngleY -= 360.0;
		}
	}
	if (right) {
		mAngleY -= mTurnSpeed;
		if (mAngleY < -180.0) { 
			mAngleY += 360.0;
		}
	}
}


void Robo::sight_move(int iMouseX, int iMouseY ,int VelocityX, int VelocityY) {
	int centerWidth = GetSystemMetrics(SM_CXSCREEN) / 2; 
	int centerHeight = GetSystemMetrics(SM_CYSCREEN) / 2;
	//SetCursorPos(centerWidth,centerHeight); //---------------------------------------------------------------------------

	if ( iMouseX > centerWidth -7 && VelocityX > 0) {
		mAngleY -= VelocityX * mMouseSensitivity;	
		}
	else if (iMouseX < centerWidth -7 && VelocityX < 0) {
		mAngleY -= VelocityX * mMouseSensitivity;
	}
	if (VelocityY != 0) {//垂直の視点 mAngleY必要？
		mAngleY += 0;	
	}
}


void Robo::jump(bool jump) {
	Vector3 moves(0.0, 0.0, 0.0);
	if (!jump) {
		moves.y += mJumpPerTime;
		mPosition += moves;
	}
	else {
		moves.y -= mFallPerTime;
		mPosition += moves;
	}	
}

void Robo::move(bool left, bool right, bool up, bool down, bool jump ,bool dash, bool guard) {
	Vector3 move(0.0, 0.0, 0.0);
	if(!guard){//guardがfalseの時のみ動ける！
		if (up) {
			move.z = -mBasicSpeed;
		}
		if (down) {
			move.z = mBasicSpeed;
		}
		if (left) {
			move.x = -mBasicSpeed;
		}
		if (right) {
			move.x = mBasicSpeed;
		}
	}

	if ( (dash) && (mAccelEnergy > 100) && (up || down || left || right) )//一回発動すると-100だけで永遠この関数の回し、高速移動になってしまう
	{
		move *= mAccelDash;
		mAccelEnergy -= 100;
		//cout << "mAccelEnergy" << mAccelEnergy << endl;
	}

	Matrix34 m;
	m.setRotationY(mAngleY + 180.0);
	m.multiply(&move, move);
	
	if (mVelocity.x == 0.0 && mVelocity.z == 0.0) {
		mVelocity += move;
	}
	/*
	else if (!up && !down && !right && !left) { //(up && down && right && left)　(move.x == 0.0 && move.z == 0.0)ここが遅れる要因？　押していない時にもmoveに値が入っているから遅れる？
		mVelocity.set(0.0, 0.0, 0.0); 
		cout << "stop" << endl;
	}*/
	else {
		mVelocity.set(0.0, 0.0, 0.0);
	}
}

void Robo::npcMove(const Vector3& myPosition, const Vector3& enemyPosition, Vector3* move){ //この方法では近くなるほど減速する
	double distanceZ = (enemyPosition.z - myPosition.z) ; //z軸の差
	double distanceX = (enemyPosition.x - myPosition.x) ; //x軸の差
	double cpuSpeed = 0.002;//ここで種類によってスピードを変えてもいい
	int stopDistance = 0;
	if (mNpcAttackKind == 0) {
		stopDistance = mNpcAttackCloseRange;
	}
	else {
		stopDistance = mNpcAttackLongRange;
	}
	
	double randomVibtration = 0.00005; //ここでcpuの動きに個性を出している。

	//cout << (rand() % 101) * randomVibtration << endl;
	
	if (abs(distanceX) > stopDistance || abs(distanceZ) > stopDistance){
		move ->x = (distanceX * cpuSpeed);//+(rand() % 21 - 11) * randomVibtration; //(rand() % 11 - 10)は10~-10までの乱数値
		move ->y = -mFallPerTime;
		move ->z = distanceZ * cpuSpeed;//+(rand() % 21 - 11) * randomVibtration;
	}
	else {
		move->x = 0;
		move->y = -mFallPerTime;
		move->z = 0;
	}
}


void Robo::npcTurn(const Vector3& mPosition, const Vector3& enemyPosition) {
	double sita = -GameLib::atan2(enemyPosition.z - mPosition.z, enemyPosition.x - mPosition.x);
	mAngleY += (sita - 270 - mAngleY);
}

void Robo::npcAttack(const Vector3& mPosition, const Vector3& enemyPosition,bool iFire) {
	double distanceZ = (enemyPosition.z - mPosition.z); 
	double distanceX = (enemyPosition.x - mPosition.x);
	int attackDistance = 2;
	
	if (distanceX < attackDistance && distanceZ < attackDistance) {
		iFire = false;//-----------------------ここの処理以降に攻撃処理がないので意味なし・・・
	}
}


void Robo::draw(const Matrix44& pvm) const {
	mModel->setAngle(Vector3(0.0, mAngleY, 0.0));
	mModel->setPosition(mPosition);
	mModel->draw(pvm);
	for (int i = 0; i < mBulletNumber; ++i) {
		if (!mBullets[i].isEmpty()) {
			mBullets[i].draw(pvm);
		}
	}
	for (int i = 0; i < mSwordNumber; ++i) {
		if (!mSwords[i].isEmpty()) {
			mSwords[i].draw(pvm);
		}
	}
}


const Vector3* Robo::position() const {
	return &mPosition;
}

const double Robo::angle() const {
	return mAngleY;
}


void Robo::setDamage(double d, bool enemyGuard) {
	if (enemyGuard == true) {
		mHitPoint -= d/3 - mGuardDamageCutRatio;
		mAttacked = 2;//ガード状態で攻撃を受けた場合
		mAttackedCount += 10;
	}
	else {
		mHitPoint -= d;
		mAttacked = 1;//そのまま攻撃を受けた場合
		mAttackedCount += 10;
	}
}

double Robo::hitPoint() const {
	if (mHitPoint > 0) {
		return mHitPoint;
	}
	else{
		return 0;
	}
}

double  Robo::pCloseRangeAttackRatio() const {
	return mCloseRangeAttackRatio;
}

double  Robo::pLongRangeAttackRatio() const {
	return mLongRangeAttackRatio;
}
double  Robo::pGuardDamageCutRatio() const {
	return mGuardDamageCutRatio;
}
float Robo::pBulletEnergyIncreaseSpeed() const {
	return mBulletEnergyIncreaseSpeed;
}
float Robo::pDashEnergyIncreaseSpeed() const {
	return mDashEnergyIncreaseSpeed;
}

float Robo::pMaxHitPoint() const {
	return mMaxHitPoint;
}

double Robo::energy() const {
	return mEnergy;
}

int Robo::attacked() const {
	return mAttacked;
}

int Robo::attackedCount() const {
	return mAttackedCount;
}

int Robo::attack() const {
	return mAttack;
}

int Robo::attackCount() const {
	return mAttackCount;
}


float Robo::AccelEnergy() const {
	return mAccelEnergy;
}

bool Robo::isLockOn() const {
	return mLockOn;
}

bool Robo::guard(bool enemyGuard) {
	return enemyGuard;
}

int Robo::enemyId()const {
	return mEnemyId;
}


void Robo::getViewMatrix(Matrix34* vm) const {
	Vector3 d(0.0, 0.0, 1.0);
	Matrix34 m;
	m.setRotationY(mAngleY);
	m.multiply(&d, d);
	Vector3 t;
	t.setMul(d, mCameraTargetDistanceZ);
	t.y -= mPosition.y * 0.12; 
	Vector3 p;
	p.setMul(d, -mCameraDistanceZ);
	p.y += mCameraDistanceY;
	p.y += mPosition.y * 0.12; 
	t += mPosition;
	p += mPosition;
	vm->setViewTransform(p, t);
}

const Circle* Robo::circle() const {
	return &mCircle;
}

