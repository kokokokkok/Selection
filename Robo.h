#ifndef INCLUDED_ROBO_H
#define INCLUDED_ROBO_H

#include "Library/Vector3.h"
#include "Library/Vector2.h"
#include "Circle.h"
#include "LineSegment.h"


class Matrix34;
class Matrix44;
class GraphicsDatabase;
class Model;
class Bullet;
class Sword;
class Circle;

class Robo {
public:
	Robo(int id,int gTime); 
	~Robo();
	void draw(const Matrix44& perspectiveViewMatrix) const;
	void getMove(Vector3* move);
	void npcMove(const Vector3& myPosition, const Vector3& enemyPosition, Vector3* move);


	void update(Robo* robo, const Vector3& move);
	//void update(std::unique_ptr<Robo&> robo, const Vector3& move);
	void setPosition(const Vector3&);
	void setAngleY(double);
	const Vector3* position() const;
	const double angle() const;

	void getViewMatrix(Matrix34*) const;
	void setDamage(double damage ,bool guard);
	//bool CollisionCircleToLiner(Circle circle, L)const;//�����Ɖ~�̃R���W����

	int enemyId() const;//���b�N�I�����̔��ʂɎg�p
	//Vector3 enemyPos() const;//���b�N�I�����̔��ʂɎg�p

	
	int Print() const;//--------�m�F�p�֐�


	double hitPoint() const;
	double  pCloseRangeAttackRatio() const;
	double  pLongRangeAttackRatio() const;
	double  pGuardDamageCutRatio() const;
	float pBulletEnergyIncreaseSpeed() const;
	float pDashEnergyIncreaseSpeed() const;
	float pMaxHitPoint() const;
	
	int attacked() const; 
	int attackedCount() const;


	int attack() const;
	int attackCount() const;

	double energy() const;
	float AccelEnergy() const;//����G�l���M�[
	bool isLockOn() const;
	void gravityCheck(bool gravityJudge);

	//-----------------------------�ϓ��X�e�[�^�X�֐�
	void statusCloseRangeAttack(double changeNumber);
	void statusLongRangeAttack(double changeNumber);
	void statusGuardCut(double changeNumber);
	void statusMaxHpIncrease(int changeNumber);
	void statusHpRecover(int changeNumber);
	void statusBulletEnergySpeed(float changeNumber);
	void statusDashEnergySpeed(float changeNumber);
	
	//------------------------�ϓ��X�e�[�^�X
	/*
	static double  mCloseRangeAttackRatio;//�ߋ����U���{��
	static double  mLongRangeAttackRatio;//�������U���{��
	static double  mGuardDamageCutRatio;//�h�䗦�J�b�g
	static float mMaxHitPoint; //�ő�q�b�g�|�C���g
	static float  mBulletEnergyIncreaseSpeed;//�e�G�l���M�[�񕜑��x
	static float  mDashEnergyIncreaseSpeed;//����G�l���M�[�񕜑��x*/
	//-------------------------------
	static const double mLongRangeDamage;
	static const double mCloseRangeDamage;
	static const int mCloseAttackRange ;
	static const int mLongAttackRange;


	static const int mJumpUpTime; //�㏸���Ă�������
	static const double mJump;
	static const double mJumpHeight; //�ő卂�x
	static const int mJumpStayTime; //�㏸�㉺�~�܂ł̎���
	static const int mJumpFallTime; //���~�ɂ����鎞��
	
	static const int mCameraDelayCount; //�W�����v�J�n�㉽�t���[���œG�̕���������
	static const double mCameraDistanceZ; //�����[�g����납��ʂ��H
	static const double mCameraDistanceY; //�����낵�
	static const double mCameraTargetDistanceZ; //�����_�͉����[�g����H
	static const double mTurnSpeed; //���񑬓x
	
	static const int mMaxEnergy; //����|�C���g�ő�l
	static const int mEnergyPerBullet; //�ꔭ������̏���G�l���M�[
	static const int mEnergyPerSword; //�ߏ�������̏���G�l���M�[

	static const int mEnergyCharge; //���t���[�����܂�G�l���M�[
	static const double mLockOnAngleIn; //���b�N�I������p�x
	static const double mLockOnAngleOut; //���b�N�I������p�x
	static const double mMouseSensitivity; //�}�E�X�̊��x
	static const double mBasicSpeed; //��{�X�s�[�h
	static const double mAccelDash;//�_�b�V��
	static const int mMaxAccelEnergy;
	static const int mAttackedState;
	static const int mAttackState;
	static const int mScore;

	static const int mAttackDistance;
	static const double mJumpPerTime;
	static const double mFallPerTime;

	bool mByLongHit;
	bool mByCloseHit;
	static bool mGravity;

	const Circle* circle() const;

	int mNpcAttackKind;//�ڋߌ^:0�@or �������^:1
	int mNpcAttackLongRange;
	int mNpcAttackCloseRange;

private:
	void sight_move(int iMouseX, int iMouseY, int VelocityX, int VelocityY);
	void move(bool left, bool right, bool up, bool down,bool jump, bool dash, bool guard);
	void jump(bool jump);

	
	void npcTurn(const Vector3& myPosition, const Vector3& enemyPosition);
	void npcAttack(const Vector3& myPosition, const Vector3& enemyPosition,bool iFire);

	void turn(bool left, bool right);
	void think(bool* jump, bool* fire, bool* swing, bool* turn, bool* left, bool* right,bool* dash, bool* up, bool* down, bool* guard, int* iMouseX , int* iMouseY ,int* sightX, int* sightY, bool* mGuard, const Vector3& enemyPos,const double myAngle) const;
	
	Vector3 mPosition;
	double mAngleY;
	int mId;
	GraphicsDatabase* mDatabase;
	Model* mModel;

	Bullet* mBullets;
	int mBulletNumber;

	Sword* mSwords;
	int mSwordNumber;

	int mCameraCount;
	int mCount; //�ړ��J�n�㉽�t���[���o�����H

	Vector3 mVelocity; //���݂̕��ʑ��x
	double mAngleVelocityY; //�U��������x
	bool mGuard;
	Vector3 mPushRange;

	enum Mode {
		MODE_JUMP_UP, //�W�����v�㏸��
		MODE_JUMP_STAY, //�W�����v���Œ�~��
		MODE_JUMP_FALL, //�W�����v�~����
		MODE_ON_LAND, //���n���Ă�
	};

	Mode mMode;

	double mHitPoint; //�̗�
	double mEnergy; //��������̂ɕK�v�ȃG�l���M�[
	int mAttacked;//�_���[�W���󂯂Ď��̏��
	int mAttackedCount;//�_���[�W���󂯂��Ƃ��ɕ\��������J�E���g��
	int mAttack;//�_���[�W��^�������̏�ԁ@�ߋ����@or ������
	int mAttackCount;//
	bool firstTime;//�ŏ���NPC�̐����F�U����HP�̏����l
	int gTime;//�Q�[���̐i�s����
	int mEnemyId;

	

	

	bool mLockOn; //���b�N�I�����Ă܂����H
	bool guard(bool iGuard);


	float mAccelEnergy; //����ɕK�v�ȃG�l���M�[
	Circle mCircle;

	double  mCloseRangeAttackRatio;//�ߋ����U���{��
	double  mLongRangeAttackRatio;//�������U���{��
	double  mGuardDamageCutRatio;//�h�䗦�J�b�g
	float mBulletEnergyIncreaseSpeed; //�e�G�l���M�[�񕜑��x
	float mDashEnergyIncreaseSpeed;//����G�l���M�[�񕜑��x
	float mMaxHitPoint; //�ő�q�b�g�|�C���g

};
	
#endif
