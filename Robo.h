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
	//bool CollisionCircleToLiner(Circle circle, L)const;//線分と円のコリジョン

	int enemyId() const;//ロックオン時の判別に使用
	//Vector3 enemyPos() const;//ロックオン時の判別に使用

	
	int Print() const;//--------確認用関数


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
	float AccelEnergy() const;//回避エネルギー
	bool isLockOn() const;
	void gravityCheck(bool gravityJudge);

	//-----------------------------変動ステータス関数
	void statusCloseRangeAttack(double changeNumber);
	void statusLongRangeAttack(double changeNumber);
	void statusGuardCut(double changeNumber);
	void statusMaxHpIncrease(int changeNumber);
	void statusHpRecover(int changeNumber);
	void statusBulletEnergySpeed(float changeNumber);
	void statusDashEnergySpeed(float changeNumber);
	
	//------------------------変動ステータス
	/*
	static double  mCloseRangeAttackRatio;//近距離攻撃倍率
	static double  mLongRangeAttackRatio;//遠距離攻撃倍率
	static double  mGuardDamageCutRatio;//防御率カット
	static float mMaxHitPoint; //最大ヒットポイント
	static float  mBulletEnergyIncreaseSpeed;//弾エネルギー回復速度
	static float  mDashEnergyIncreaseSpeed;//回避エネルギー回復速度*/
	//-------------------------------
	static const double mLongRangeDamage;
	static const double mCloseRangeDamage;
	static const int mCloseAttackRange ;
	static const int mLongAttackRange;


	static const int mJumpUpTime; //上昇していく時間
	static const double mJump;
	static const double mJumpHeight; //最大高度
	static const int mJumpStayTime; //上昇後下降までの時間
	static const int mJumpFallTime; //下降にかかる時間
	
	static const int mCameraDelayCount; //ジャンプ開始後何フレームで敵の方を向くか
	static const double mCameraDistanceZ; //何メートル後ろから写す？
	static const double mCameraDistanceY; //見下ろし具合
	static const double mCameraTargetDistanceZ; //注視点は何メートル先？
	static const double mTurnSpeed; //旋回速度
	
	static const int mMaxEnergy; //武器ポイント最大値
	static const int mEnergyPerBullet; //一発あたりの消費エネルギー
	static const int mEnergyPerSword; //近処理武器の消費エネルギー

	static const int mEnergyCharge; //毎フレーム溜まるエネルギー
	static const double mLockOnAngleIn; //ロックオンする角度
	static const double mLockOnAngleOut; //ロックオンする角度
	static const double mMouseSensitivity; //マウスの感度
	static const double mBasicSpeed; //基本スピード
	static const double mAccelDash;//ダッシュ
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

	int mNpcAttackKind;//接近型:0　or 遠距離型:1
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
	int mCount; //移動開始後何フレーム経った？

	Vector3 mVelocity; //現在の平面速度
	double mAngleVelocityY; //振り向き速度
	bool mGuard;
	Vector3 mPushRange;

	enum Mode {
		MODE_JUMP_UP, //ジャンプ上昇中
		MODE_JUMP_STAY, //ジャンプ上空で停止中
		MODE_JUMP_FALL, //ジャンプ降下中
		MODE_ON_LAND, //着地してる
	};

	Mode mMode;

	double mHitPoint; //体力
	double mEnergy; //武器を撃つのに必要なエネルギー
	int mAttacked;//ダメージを受けて時の状態
	int mAttackedCount;//ダメージを受けたときに表示させるカウント数
	int mAttack;//ダメージを与えた時の状態　近距離　or 遠距離
	int mAttackCount;//
	bool firstTime;//最初のNPCの生成：攻撃とHPの処理様
	int gTime;//ゲームの進行時間
	int mEnemyId;

	

	

	bool mLockOn; //ロックオンしてますか？
	bool guard(bool iGuard);


	float mAccelEnergy; //回避に必要なエネルギー
	Circle mCircle;

	double  mCloseRangeAttackRatio;//近距離攻撃倍率
	double  mLongRangeAttackRatio;//遠距離攻撃倍率
	double  mGuardDamageCutRatio;//防御率カット
	float mBulletEnergyIncreaseSpeed; //弾エネルギー回復速度
	float mDashEnergyIncreaseSpeed;//回避エネルギー回復速度
	float mMaxHitPoint; //最大ヒットポイント

};
	
#endif
