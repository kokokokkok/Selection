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


const int Robo::mJumpUpTime = 20; //�㏸���Ă�������
const double Robo::mJump = 0.5;
const double Robo::mJumpHeight = 100.0; //�ő卂�x
const int Robo::mJumpStayTime = 60; //�㏸�㉺�~�܂ł̎���
const int Robo::mJumpFallTime = 10; //���~�ɂ����鎞��
const double Robo::mCameraDistanceZ = 8.0; //�����[�g����납��ʂ��H
const double Robo::mCameraDistanceY = 4.0; //�����낵�
const double Robo::mCameraTargetDistanceZ = 20.0; //�����_�͉����[�g����H
const double Robo::mTurnSpeed = 1.0; //���񑬓x
const int Robo::mMaxEnergy = 100; //�ő啐��|�C���g
const int Robo::mEnergyPerBullet = 50; //����������̏���G�l���M�[
const int Robo::mEnergyPerSword = 50; //�ߏ�������̏���G�l���M�[
const int Robo::mCloseAttackRange = 10;
const int Robo::mLongAttackRange = 4;

const int Robo::mMaxAccelEnergy = 100;//����G�l���M�[�̏���̒l
const double Robo::mLockOnAngleIn = 10.0; //���b�N�I������p�x
const double Robo::mLockOnAngleOut = 15.0; //���b�N�I�����O���p�x
const double Robo::mMouseSensitivity = 0.2; //�}�E�X�̊��x
const double Robo::mBasicSpeed = 0.4; //��{�X�s�[�h
const double Robo::mAccelDash = 25; //������̑���
const int Robo::mAttackedState = 0;//�U�����ꂽ�Ƃ��̏��
const int Robo::mAttackState = 0;//�U�������Ƃ��̏��


//const int Robo::mScore = 0;
const int Robo::mAttackDistance = 3;
const double Robo::mJumpPerTime = 0.2;
const double Robo::mFallPerTime = 0.05;


/*
//---------------------------------------------------------------------------------�ϓ��X�e�[�^�X
double  Robo::mCloseRangeAttackRatio = 1;//�ߋ����U���{��
double  Robo::mLongRangeAttackRatio = 1;//�������U���{��
double  Robo::mGuardDamageCutRatio = 1.5;//�h�䗦�J�b�g
float Robo::mMaxHitPoint = 100; //�ő�q�b�g�b�|�C���g
float Robo::mBulletEnergyIncreaseSpeed = 1; //�e�G�l���M�[�񕜑��x
float  Robo::mDashEnergyIncreaseSpeed = 1;//����G�l���M�[�񕜑��x
//-----------------------------------------------------------------------------------
*/
const double Robo::mLongRangeDamage = 10;//�������_���[�W
const double Robo::mCloseRangeDamage = 15;//�ߋ����_���[�W
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
	mBulletNumber(100), //���߂���
	mSwordNumber(100),
	mCameraCount(0),
	mCount(0),
	mVelocity(0.0, 0.0, 0.0),
	mPushRange(0.0, 0.0, 0.0),//�U�����ꂽ�Ƃ��ɑ������āAmove�ɓ��ꍞ��
	mMode(MODE_ON_LAND),
	mHitPoint(100),
	mEnergy(mMaxEnergy),
	mGuard(false),//���̈�̂ق����������H�@�����œG�̃K�[�h���Ă邩�ǂ��������߂Ă���@�قڈӖ��Ȃ����B�B�B

	mAttacked(mAttackedState),//�U������Ă����Ԃ��A���̎��K�[�h���Ă��邩
	mAttackedCount(0),

	mAttack(mAttackState),
	mAttackCount(0),

	mAccelEnergy(mMaxAccelEnergy),//����̂��߂̃G�l���M�[
	mAngleVelocityY(0),

	mNpcAttackKind(rand()%2),//�ߋ���or�������̒��I�@
	mNpcAttackLongRange(rand() % 20),//�������U���̍U���ɕK�v�ȋ����@
	mNpcAttackCloseRange(rand() % 10),//�ߋ����U���̍U���ɕK�v�ȋ����@//-------------------------�\�[�h�̋����Q��
	firstTime(true),
	gTime(gTime),
	mEnemyId(1),

	//--------------------------�ϓ��X�e�[�^�X
	mCloseRangeAttackRatio(1),//�ߋ����U���{��
	mLongRangeAttackRatio(1),//�������U���{��
	mGuardDamageCutRatio(1.5),//�h�䗦�J�b�g
	mBulletEnergyIncreaseSpeed(1), //�e�G�l���M�[�񕜑��x
	mDashEnergyIncreaseSpeed(1),//����G�l���M�[�񕜑��x
	mMaxHitPoint(100),

	mLockOn(true) { 
	mDatabase = new GraphicsDatabase("player.txt");
	mModel = mDatabase->createModel("robo");
	mModel->setColor((mId == 0) ? 0xcc0088ff : 0xccff8800);//---------------------------------plyaer�̐F-------------------------------------
	
	mBullets = new Bullet[mBulletNumber];
	mSwords = new Sword[mSwordNumber];

	Vector3 c = mPosition;//���{���m�̏Փ˔��a
	c.y += 0.5;//���̒��S����ɂ��炷
	mCircle.setPosition(c);
	mCircle.setRadius(0.5);
	//mGuard(false) �������
}
	

Robo::~Robo() {
	SAFE_DELETE_ARRAY(mBullets);
	SAFE_DELETE_ARRAY(mSwords);

	SAFE_DELETE(mModel); 
	SAFE_DELETE(mDatabase);
}
//-------------------------------------------------------���ۂɍU������Ƃ��Ȃǂɂ��̒l���|���Ƃ����Ȃ�
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
	c.y += 0.5; //���S����ɂ���Ă�
	mCircle.setPosition(c);
}

void Robo::setAngleY(double a) {
	mAngleY = a;
}

void Robo::getMove(Vector3* move) {
	move->set(0.0, 0.0, 0.0);
	move->set(mPushRange.x, mPushRange.y, mPushRange.z);//-----------------------------------------------�����ōU���ŉ����ꂽ������ꍞ�� ���݂͋@�\���Ă��Ȃ����R��F�����E�E�E
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
	if ( (pad->isOn(Pad::DASH, mId) && (mAccelEnergy > 100) && ( (pad->isOn(Pad::UP, mId)) || (pad->isOn(Pad::DOWN, mId)) || (pad->isOn(Pad::LEFT, mId)) || (pad->isOn(Pad::RIGHT, mId)) ))){//��񔭓������-100�����ŉi�����̊֐��̉񂵁A�����ړ��ɂȂ��Ă��܂�
		*move *= mAccelDash;
		mAccelEnergy -= 100;//������O����const������ƕύX�ł��Ȃ���
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
	
	mPushRange.set(0, 0, 0);//-------------------------���Z�b�g�����Ő�����т��������A�����A������ѐ���͂����Ōv�Z����B


	mByLongHit = false;
	mByCloseHit = false;
	
	

	mPosition += nextMove;//�����x�N�g���𑫂��I
	//mPosition += nextMove;
	
	Vector3 c = mPosition;
	c.y += 0.5; //���S����ɂ���Ă�
	mCircle.setPosition(c);

	//����ł�
	if (mHitPoint <= 0) {
		return;
	}

	//�p�x�͈͕␳
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
	//�W�����v������Ă�H

	//jump(!iJump);
	//move(iLeft, iRight, iUp, iDown, iJump,iDash, iGuard); //�R�[�h�������Ȃ�̂Ŋ֐��ɔ�΂�--------------------------------------�����ŉ���G�l���M�[�𒲐����Ă���̂Ō�Œ����I
	sight_move(iMouseX, iMouseY, iVelocityX, iVelocityY);

	if (mAttackedCount > 0) {
		mAttackedCount -= 1;
	}
	if (mAttackedCount <= 0) {
		mAttacked = 0;//�U�����󂯂���Ԃ�߂�
	}
	if (mAttackCount > 0) {
		mAttackCount -= 1;
	}
	if (mAttackCount <= 0) {
		mAttack = 0;//�U����������Ԃ�߂�
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
		if (!iJump) { //�W�����v���͂��Ȃ��̂ŉ��~�ɕω�
			mMode = MODE_JUMP_FALL;
			mCount = 0;
		}
		else if (mCount >= mJumpUpTime) { //�㏸�I��
			mMode = MODE_JUMP_STAY;
			mCount = 0;
		}
		mVelocity.x = mVelocity.z = 0.0; //X,Z�ړ��𖕎E
		break;
		
	case MODE_JUMP_STAY:
		mVelocity.y = 0.0;
		if (!iJump) { //�W�����v���͂��Ȃ��̂ŉ��~�ɕω�
			mMode = MODE_JUMP_FALL;
			mCount = 0;
		}
		else if (mCount >= mJumpStayTime) { //���~��
			mMode = MODE_JUMP_FALL;
			mCount = 0;
		}
		break;
	case MODE_JUMP_FALL:
		//���~
		t = mJumpHeight / static_cast<double>(mJumpFallTime);
		mVelocity.y = -t;
		//�ڒn����͍ŏI�I�ɂ͏Փˏ����ł��̂ł����ł͂��Ȃ��B
		break;
	case MODE_ON_LAND:
		if (iJump) {
			mMode = MODE_JUMP_UP;
			mCount = 0;
			mCameraCount = 0;
					}
		else if (iTurn) {
			turn(iLeft, iRight); //�R�[�h�������Ȃ�̂Ŋ֐��ɔ�΂�
		}
		else {
			
		mVelocity.y = 0.0;
		break;
	}
	*/

	if (mId != 0) {
		//�ڋߌ^���������^�������߂�@True False 
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
		//Npc��HP�ƍU���͂��Q�[���̐i�s�x�igTime�j�ɂ���ďグ��
		if (firstTime == true ) {
			mCloseRangeAttackRatio += gTime * 0.00005;
			mLongRangeAttackRatio += gTime * 0.00005;
			mHitPoint += mMaxHitPoint * 0.002;
		}
		firstTime = false;
	}

	
	//�������牺�͏Փˏ���������Ƃ��̌�ɂȂ�B
	/*
	mPosition += mVelocity;//�����ő����Ă���
	if (mPosition.y < 0.0) {
		mPosition.y = 0.0;
		mMode = MODE_ON_LAND;
	}*/
	//���퐶��
	if (iFire) {
		//�㏸�A���~���͌��ĂȂ�
		if ((mMode != MODE_JUMP_FALL) && (mMode != MODE_JUMP_UP)) {
			//�G�l���M�[����Ă邩�ǂ���
			if (mEnergy >= mEnergyPerBullet) {
				//�󂫕����T��
				for (int i = 0; i < mBulletNumber; ++i) {
					if (mBullets[i].isEmpty()) {
						unsigned c = (mId == 0) ? 0xcc0088ff : 0xccff8800;//�e�̐F-------------------------------------------
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
	//����X�V
	for (int i = 0; i < mBulletNumber; ++i) {
		if (!mBullets[i].isEmpty()) {
			mBullets[i].update(enemyPos);
			//�Փˏ���
			Vector3 t;
			t.setSub(*mBullets[i].position(), enemyPos);
			if (t.squareLength() < mLongAttackRange) {
				mAttack = 2;//�������U����^�����ꍇ
				mAttackCount = 10;
				enemy->setDamage(mLongRangeDamage * mLongRangeAttackRatio,enemyGuard); //1�_���炵�Ă݂��B
				mByLongHit = true;
				mBullets[i].die(); //�e�����܂��B
			}
		}
	}
	
	if (iSwing) {
		if (mEnergy >= mEnergyPerSword) {
			//�󂫕����T��
			for (int i = 0; i < mSwordNumber; ++i) {
				if (mSwords[i].isEmpty()) {
					unsigned c = (mId == 0) ? 0xcc0088ff : 0xccff8800;//�e�̐F-------------------------------------------
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
	//����X�V
	for (int i = 0; i < mSwordNumber; ++i) {
		if (!mSwords[i].isEmpty()) {
			mSwords[i].update(mAngleY, &mPosition);
			//�Փˏ���
			Vector3 t;
			t.setSub(*mSwords[i].position(), enemyPos);
			if (t.squareLength() < mCloseAttackRange) {
				mAttack = 1;//�ߋ����U����^�����ꍇ
				mAttackCount = 10;
				enemy->setDamage(mCloseRangeDamage * mCloseRangeAttackRatio, enemyGuard);
				//mPushRange = mSwords[i].Push(mPosition, enemyPos);//---------------------------------------------------------------------
				mByCloseHit = true;
				mSwords[i].die(); //���������܂��B
			}
			if (mSwords[i].angle()->y > mAngleY + 180) {
				mSwords[i].die();
			}
		}
	}
	//���b�N�I������
	Vector3 toEnemy;
	toEnemy.setSub(enemyPos, mPosition);
	Vector3 myDir(0.0, 0.0, -1.0);
	Matrix34 m;
	m.setRotationY(mAngleY + 180.0);
	m.multiply(&myDir, myDir);
	toEnemy *= 1.0 / toEnemy.length(); //������1��
	double dotProduct = toEnemy.dot(myDir);
	//�p�x�ɒ����ƁA
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

	//����G�l���M�[�`���[�W
	mEnergy += mBulletEnergyIncreaseSpeed;
	if (mEnergy > mMaxEnergy) {
		mEnergy = mMaxEnergy;
	}
	
	/*�l�\��
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
	if (mId == 0) { //�v���C���[
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
		//�e�͌��Ă邾������
		*jump = false;
		*fire = false;
		*swing = false;

		//����͂��Ȃ�
		//*turn = false;
		//�ړ��͕ϐ������̂��ʓ|�Ȃ̂ł��Ȃ��B
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
	if (VelocityY != 0) {//�����̎��_ mAngleY�K�v�H
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
	if(!guard){//guard��false�̎��̂ݓ�����I
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

	if ( (dash) && (mAccelEnergy > 100) && (up || down || left || right) )//��񔭓������-100�����ŉi�����̊֐��̉񂵁A�����ړ��ɂȂ��Ă��܂�
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
	else if (!up && !down && !right && !left) { //(up && down && right && left)�@(move.x == 0.0 && move.z == 0.0)�������x���v���H�@�����Ă��Ȃ����ɂ�move�ɒl�������Ă��邩��x���H
		mVelocity.set(0.0, 0.0, 0.0); 
		cout << "stop" << endl;
	}*/
	else {
		mVelocity.set(0.0, 0.0, 0.0);
	}
}

void Robo::npcMove(const Vector3& myPosition, const Vector3& enemyPosition, Vector3* move){ //���̕��@�ł͋߂��Ȃ�قǌ�������
	double distanceZ = (enemyPosition.z - myPosition.z) ; //z���̍�
	double distanceX = (enemyPosition.x - myPosition.x) ; //x���̍�
	double cpuSpeed = 0.002;//�����Ŏ�ނɂ���ăX�s�[�h��ς��Ă�����
	int stopDistance = 0;
	if (mNpcAttackKind == 0) {
		stopDistance = mNpcAttackCloseRange;
	}
	else {
		stopDistance = mNpcAttackLongRange;
	}
	
	double randomVibtration = 0.00005; //������cpu�̓����Ɍ����o���Ă���B

	//cout << (rand() % 101) * randomVibtration << endl;
	
	if (abs(distanceX) > stopDistance || abs(distanceZ) > stopDistance){
		move ->x = (distanceX * cpuSpeed);//+(rand() % 21 - 11) * randomVibtration; //(rand() % 11 - 10)��10~-10�܂ł̗����l
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
		iFire = false;//-----------------------�����̏����ȍ~�ɍU���������Ȃ��̂ňӖ��Ȃ��E�E�E
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
		mAttacked = 2;//�K�[�h��ԂōU�����󂯂��ꍇ
		mAttackedCount += 10;
	}
	else {
		mHitPoint -= d;
		mAttacked = 1;//���̂܂܍U�����󂯂��ꍇ
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

