#include <sstream>
#include <stdlib.h>
#include <Windows.h>
#include <cmath>
#include <random>
#include <memory>
#include "GameLib/Framework.h"
#include "Pad.h"
#include "Robo.h"
#include "Stage.h"
#include "LineSegment.h"
#include "Library/Matrix44.h"
#include "Library/Matrix34.h"
#include "Library/Vector2.h"
#include "GameLib/Framework.h"
#include "GameLib/Sound/Wave.h"
#include "GameLib/Sound/Player.h"


using namespace GameLib::Sound;
using namespace GameLib;
using namespace std;

Wave gWaveSE;
Wave gWaveBGM;

Player gPlayerBGM;
Player gPlayerSEBulletHit;
Player gPlayerSESwordHit;

Player gPlayerSEStatus;
Player gPlayerSEStatusUp;



Robo* gRobo[ 10 ];
//std::unique_ptr<Robo*> gRobo[100];
//unique_ptr<unique_ptr<Robo&>[]> gRobo = std::make_unique<unique_ptr<Robo&>[]>(10);
//unique_ptr<unique_ptr<Robo>[]> gRobo = std::make_unique<unique_ptr<Robo>[]>(10);
//unique_ptr<unique_ptr<Robo*>[]> gRobo = std::make_unique<unique_ptr<Robo*>[]>(10);
Stage* gStage;
//std::unique_ptr<Stage> gStage(gStage);// unique Pointer
//stage* gWall;

int gTime;
bool gPlaying = false;

bool status;
bool description;

bool End;
int wid = GetSystemMetrics(SM_CXSCREEN);
int het = GetSystemMetrics(SM_CYSCREEN);
int x_0 = 0;
int y_0 = 0;

int npc = 0; //現在フィールドに
int npcCountForScoreLevel = 5;

int Score = 0; //スコア

int npc_1 = 1; //強さスコアこれに合わせて、得られるスコアと経験値、レベルによる敵生成数をきめる！	
int npc_2 = 5; 

int npcGeneratePosition[8] = {0,0,-10,-10,20,-20,30,-30};

Vector3 gEyePosition(0.0, 0.0, 1.0);
Vector3 gEyeTarget(0.0, 0.0, 0.0);


Vector3 mPosi;
Vector3 enemyPosi;

//------------------各ステータス上昇に必要なスコア
int CloseAttckUpScore = 300;
int LongAttckUpScore = 400;
int GuardScore = 400;
int MaxHPScore = 200;
int HPRecoverScore = 200;
int BulletESppedScore = 300;
int DashESpeedScore = 300;


enum Sequence {
	SEQUENCE_PLAY,
	SEQUENCE_STATUS,
	SEQUENCE_GAMEOVER,
	SEQUENCE_DESCRIPTION,
};

Sequence gSequence = SEQUENCE_PLAY;//最初からプレイ状態

void drawRect(Vector2* p, unsigned c) {
	Framework f = Framework::instance();
	double p4[4][4];
	for (int i = 0; i < 4; ++i) {
		p4[i][0] = p[i].x;
		p4[i][1] = p[i].y;
		p4[i][2] = 0.0; //zは0固定
		p4[i][3] = 1.0; //wは1固定
	}
	f.drawTriangle3DH(p4[0], p4[1], p4[2], 0, 0, 0, c, c, c);
	f.drawTriangle3DH(p4[3], p4[1], p4[2], 0, 0, 0, c, c, c);
}

void drawMap(double x, double y, unsigned backgroundColor, unsigned playerColor, unsigned enemyColor) {
	Framework f = Framework::instance();
	
	double p[3][4];
	double r = 0.2;//半径
	double pi = 3.14;
	int ra = 20;
	double mapPlayerSize = 0.005;
	Vector2 p2[4];

	for (int i = 0;i < ra;i++) {
		p[0][0] = x - r * cos(pi / (ra / 2) * i + pi / ra - pi / ra) * het / wid;//縦横比を調整　これがないと横伸びたものになる
		p[0][1] = y - r * sin(pi / (ra / 2) * i + pi / ra - pi / ra);
		p[0][2] = 0;
		p[0][3] = 1.0;

		p[1][0] = x;
		p[1][1] = y;
		p[1][2] = 0;
		p[1][3] = 1.0;

		p[2][0] = x - r * cos(pi / (ra / 2) * i - pi / ra - pi / ra) * het / wid;
		p[2][1] = y - r * sin(pi / (ra / 2) * i - pi / ra - pi / ra);
		p[2][2] = 0;
		p[2][3] = 1.0;

		f.drawTriangle3DH(p[0], p[1], p[2], 0, 0, 0, backgroundColor, backgroundColor, backgroundColor);
	}

	Vector2 t;
	for (int j = 0;j <= npc ;j++) {
		if (j == 0) {
			p2[0].set(x - mapPlayerSize, y - mapPlayerSize);
			p2[1].set(x - mapPlayerSize, y + mapPlayerSize);
			p2[2].set(x + mapPlayerSize, y - mapPlayerSize);
			p2[3].set(x + mapPlayerSize, y + mapPlayerSize);
			drawRect(p2, 0xFFFFDC0D);
			//cout << npc << endl;
		}
		else{
			//cout << "OK" << endl;
			double DistX = (gRobo[0]->position()->x - gRobo[j]->position()->x) * (gRobo[0]->position()->x - gRobo[j]->position()->x) * 0.0005;//距離と0から見た角度----------------------------------------
			double DistY = (gRobo[0]->position()->z - gRobo[j]->position()->z) * (gRobo[0]->position()->z - gRobo[j]->position()->z) * 0.0005;
			double sita = atan2(gRobo[0]->position()->z - gRobo[j]->position()->z, gRobo[0]->position()->x - gRobo[j]->position()->x);//敵との角度 
			//double mysita = gRobo[0]->angle();// 自分と世界との角度

			int as = 90;
		
			p2[0].set(x + DistX * cos(sita + gRobo[0]->angle() - as) - mapPlayerSize, y + DistY * sin(sita + gRobo[0]->angle() - as) - mapPlayerSize);
			p2[1].set(x + DistX * cos(sita + gRobo[0]->angle() - as) - mapPlayerSize, y + DistY * sin(sita + gRobo[0]->angle() - as) + mapPlayerSize);
			p2[2].set(x + DistX * cos(sita + gRobo[0]->angle() - as) + mapPlayerSize, y + DistY * sin(sita + gRobo[0]->angle() - as) - mapPlayerSize);
			p2[3].set(x + DistX * cos(sita + gRobo[0]->angle() - as) + mapPlayerSize, y + DistY * sin(sita + gRobo[0]->angle() - as) + mapPlayerSize);
		
			if (DistX * wid/het + DistY < r ){
				drawRect(p2, 0xFFFFDC0D);
			}
		}
	}

	/*
	p[0][0] = x - r/2;
	p[0][1] = y + r*0.866; //0.866 = √3/4
	p[0][2] = 0;
	p[0][3] = 1.0;

	p[1][0] = x - r;
	p[1][1] = y ;
	p[1][2] = 0;
	p[1][3] = 1.0;

	p[2][0] = x - r/2;
	p[2][1] = y - r*0.866; 
	p[2][2] = 0;
	p[2][3] = 1.0;

	f.drawTriangle3DH(p[0], p[1], p[2], 0, 0, 0, backgroundColor, backgroundColor, backgroundColor);

	p[0][0] = x + r/2;
	p[0][1] = y + r*0.866; //0.866 = √3/4
	p[0][2] = 0;
	p[0][3] = 1.0;

	p[1][0] = x + r;
	p[1][1] = y;
	p[1][2] = 0;
	p[1][3] = 1.0;

	p[2][0] = x + r/2;
	p[2][1] = y - r*0.866;
	p[2][2] = 0;
	p[2][3] = 1.0;

	f.drawTriangle3DH(p[0], p[1], p[2], 0, 0, 0, backgroundColor, backgroundColor, backgroundColor);
	
	q[0].set(x - r/2, y + r*0.866);
	q[1].set(x + r/2, y + r*0.866);
	q[2].set(x - r/2, y - r*0.866);
	q[3].set(x + r/2, y - r*0.866);
	drawRect(q, playerColor);
	*/

}

void drawBar(int barEnegy, int RoboBarEnegy,
	double x, double y,//左上の座標 この座標値はsetpositionを基準に考える
	double barWidth, double barHeight,//横の幅、縦の幅
	unsigned backgroundColor, unsigned mainColor,
	double barSize) {

	Vector2 p[4];
	double length = static_cast<float>(barEnegy) * barSize / static_cast<float>(RoboBarEnegy);
	if (length > 0) {
		//メインバー
		p[0].set(x, y);
		p[1].set(x, y - barHeight);
		p[2].set(x + length, y);
		p[3].set(x + length, y - barHeight);
		drawRect(p, mainColor);
	}

	//背景バー
	p[0].set(x, y);
	p[1].set(x, y - barHeight);
	p[2].set(x + barWidth, y);
	p[3].set(x + barWidth, y - barHeight);
	drawRect(p, backgroundColor);

	//メインバー
	p[0].set(x, y);
	p[1].set(x, y - barHeight);
	p[2].set(x + length, y);
	p[3].set(x + length, y - barHeight);
	drawRect(p, mainColor);
}


void drawEmergency(int barWidth, int barHeight, unsigned c) {
	Framework f = Framework::instance();

	Vector2 p[4];

	p[0].set(-1, -1);
	p[1].set(-1, het);
	p[2].set(wid, -1);
	p[3].set(wid, het);
	drawRect(p, c);
	/*
	p[0].set(0, 0);
	p[1].set(0, 0 - barHeight);
	p[2].set(barWidth, 0);
	p[3].set(barWidth, 0 - barHeight);
	drawRect(p, c);

	p[0].set(0, -het + barHeight);
	p[1].set(0, -het);
	p[2].set(wid, -het + barHeight);
	p[3].set(wid, -het);
	drawRect(p, c);

	p[0].set(0, 0);
	p[1].set(0, -het);
	p[2].set(barWidth, 0);
	p[3].set(barWidth, -het);
	drawRect(p, c);

	p[0].set(wid - barWidth, 0);
	p[1].set(wid - barWidth, -het);
	p[2].set(wid, 0);
	p[3].set(wid, -het);
	drawRect(p, c);
	*/
}



namespace GameLib {
	void Framework::update() {
		HWND hWnd = FindWindow(NULL, "3D Graphics1 samples");
		MoveWindow(hWnd, x_0, y_0, wid, het, true);
		//ShowCursor(FALSE);//-----------------------------------------------------------------------------------------
		ostringstream oss;
		oss << "Score   :" << Score;
		Framework().drawDebugString(50, 1, oss.str().c_str());
		//cout <<"gTime" << gTime << endl;
		//cout << "HP" << gTime *  0.0002<< endl;
		//cout << "Attack" << gTime * 0.00002 << endl;

		if (gTime % 10000 == 0) {
			npcCountForScoreLevel += 1;
		}

		/*
		Player gPlayerBGM;
		Player gPlayerSEBulletHit;
		Player gPlayerSESwordHit;

		Player gPlayerSEStatus;
		Player gPlayerSEStatusUp;*/

		//----------------------------------------------------------------------------BGM
		// Road Sound
		/*
		if (!gWaveSE) {
			gWaveSE = Sound::Wave::create("./dokaan.wav");
		}
		if (!gWaveBGM) {
			gWaveBGM = Sound::Wave::create("charara.wav");
		}

		//BGMプレイヤー作成
		if (!gPlayerBGM && gWaveBGM.isReady()) {
			if (!gWaveBGM.isError()) {
				gPlayerBGM = Sound::Player::create(gWaveBGM);
				gPlayerBGM.play(true); //ループ
			}
		}*/
		//----------------------------------------------------------------------------BGM


		switch (gSequence) {
		case SEQUENCE_DESCRIPTION: {
			//statusPad = Pad::instance();//bool値
			Pad* statusPad = Pad::instance();
			//ステータス画面（ここでRobo[0]の攻撃力などの変数の数値を変えるので）
			ostringstream oss;
			oss << "<Game Rule>\n Please knock down enemy appearing infinite to get score.\n If your HP is 0,This game is over.\n By Consuming score, you can increase your ability.\n But, Please attention \n The result of this game is score. \n 'maintaining your score to aim high score'\n or \n 'consuming your score to increase your ability'\n";
			oss << " If you properly select the ways, you would get a high score. \n \n \n<Control>\n move               :wasd\n avoidance          :q + move\n jump               :z\n perspective move   :mouse\n long range attack  :x\n close range attack :r\n guard              :c \n status mode        :- (quit:-)\n description mode   :0 (quit:0) \n";
			Framework().drawDebugString(2, 3, oss.str().c_str());
			
			if (statusPad->isTriggered(Pad::STATUS_MENU_QUIT, 0)) {//mId=0でないと反応しない
				gSequence = SEQUENCE_PLAY;
			}
			break;
		}
		case SEQUENCE_PLAY: {
			if (!gStage) {
				setFrameRate(60);
				Pad::create();
				gRobo[0] = new Robo(0,gTime);//Player
				//gRobo[0] = std::make_unique<Robo&>(0,gTime);
				//std::unique_ptr<Robo> gRobo[0](new Robo(0, gTime));
				//std::unique_ptr<Robo> gRobo[0](new Robo(0, gTime));

				gRobo[0]->setPosition(Vector3(-20.0, 10.0, 20.0));
				gRobo[0]->setAngleY(180.0);

				
				gStage = new Stage("map.txt");
				//std::unique_ptr<Stage> gStage(new Stage("map.txt"));//unique------------------------------ここで行っているコンストラクタが正常に動いてない！
				//そのせいでクラス内の変数が初期化、生成されていないため、エラーがでる
				//当たり前でこのブロック内しかgStage変数の寿命がないのでこのブロックの外で直ぐに開放されている！
				//gWall = new Stage("Wall.txt")
			}

			int i = gRobo[0]->Print();
			//cout << i << endl;
			//cout << "PLAY" << endl;

			//NPCの生成
			for (int i = 1;i < npcCountForScoreLevel; i++) {
				if (gRobo[i] == 0) {//gRoboが存在しない時
					int npcPositionrand = rand() % 3 * 2;
					int random = rand() % 20;
					gRobo[i] = new Robo(i, gTime);
					//gRobo[i] = std::make_unique<Robo&>(i, gTime);
					//std::unique_ptr<Robo> gRobo[i](gRobo[i]);

					gRobo[i]->setPosition(Vector3(-40, 10, 50));//ここで生成！　生成座標（わき地）を決めたらここで処理ー－－－－－－－－－－－－－－－－

					//gRobo[i]->setPosition(Vector3(npcGeneratePosition[npcPositionrand], 10, npcGeneratePosition[npcPositionrand + 1] + 1));//ここで生成！　生成座標（わき地）を決めたらここで処理ー－－－－－－－－－－－－－－－－
					//gRobo[i]->setPosition(Vector3(0,15,-10));
					npc += 1;
					//cout << npc << endl;
				}
			}
			//		衝突判定処理　ロボとステージ　ロボ同士
			Vector3 move[30];
			Circle spRobo[100];
			for (int i = 0;i < npc + 1;i++) {//すべてのロボのCircleクラスを作ってspRoboに入れ込む
				spRobo[i] = *gRobo[i]->circle();
				if (i == 0) {//プレイヤーの移動量を算出してupdateを行う
					gRobo[0]->getMove(&move[0]);
					for (int j = 1;j < npc + 1;j++) {
						spRobo[0].restrictMove(&move[0], spRobo[j]);//PlayerにNPCの移動量の情報が考慮されてなくない？
						gStage->restrictMove(&move[i], *gRobo[i]->position());
						//gWall->restrictMove(&move[i], *gRobo[i]->position());
						gRobo[0]->update(gRobo[j], move[0]);
						move[0].set(0.0, 0.0, 0.0);	
					}
				}
				else {//NPCの移動量を算出してupdateを行う
					enemyPosi = *gRobo[i]->position();
					mPosi = *gRobo[0]->position();
					gRobo[i]->npcMove(enemyPosi, mPosi, &move[i]);
					for (int j = 0;j < npc + 1;j++) {
						if (i != j) {
							spRobo[i].restrictMove(&move[i], spRobo[j]);
						}
					}
					gStage->restrictMove(&move[i], *gRobo[i]->position());
					//gWall->restrictMove(&move[i], *gRobo[i]->position());
					gRobo[i]->update(gRobo[0], move[i]);
				}
				
				/*
				解決案 :npc数にPlayerの移動量が依存する問題
				1:getMove()のBasicspeedだけnpcの数に依存して割る。。。これだとステージのすり抜けを防げない。。。
				2:Move[0]（移動量）を1度updateしたら０にする　採用！
				*/
				++gTime;
			}
			
			Pad* pad = Pad::instance();
			status = pad->isTriggered(Pad::STATUS_MENU_START, 0);
			description = pad->isTriggered(Pad::STATUS_MENU_QUIT, 0);

			if (status) {
				gSequence = SEQUENCE_STATUS;
			}
			if (description) {
				gSequence = SEQUENCE_DESCRIPTION;
			}
			//gPlayingの中身この中に入れる
			break;
		}
		case SEQUENCE_STATUS:{
			//cout << "STATUS" << endl;
			//statusPad = Pad::instance();//bool値
			Pad* statusPad = Pad::instance();
			//ステータス画面（ここでRobo[0]の攻撃力などの変数の数値を変えるので）
			ostringstream oss;
			oss << "1: CloseAtkRatio  300:   " << gRobo[0]->pCloseRangeAttackRatio() << "\n";
			oss << "2: LongAtkRatio   400:   " << gRobo[0]->pLongRangeAttackRatio() << "\n";
			oss << "3: DamageCutRatio 400:   " << gRobo[0]->pGuardDamageCutRatio() << "\n";
			oss << "4: MaxHp          200:   " << gRobo[0]->pMaxHitPoint() << "\n";
			oss << "5: HpRecover      200:   " << gRobo[0]->hitPoint() << "\n";
			oss << "6: BulletESpeed   300:   " << gRobo[0]->pBulletEnergyIncreaseSpeed() << "\n";
			oss << "7: DashESpeed     300:   " << gRobo[0]->pDashEnergyIncreaseSpeed() << "\n";
			Framework().drawDebugString(15, 11, oss.str().c_str());

			if (statusPad->isTriggered(Pad::ONE, 0)) {//mId=0でないと反応しない
				//Robo[0] -> change(入力は上昇値)//ステータスを変更する関数
				if (Score > CloseAttckUpScore) {
					gRobo[0]->statusCloseRangeAttack(0.1);
					Score -= CloseAttckUpScore;

				}
			}
			if (statusPad->isTriggered(Pad::TWO, 0)) {
				if (Score > LongAttckUpScore) {
					gRobo[0]->statusLongRangeAttack(0.1);
					Score -= LongAttckUpScore;
				}
			}
			if (statusPad->isTriggered(Pad::THREE, 0)) {
				if (Score > GuardScore) {
					gRobo[0]->statusGuardCut(0.2);
					Score -= GuardScore;
				}
			}
			if (statusPad->isTriggered(Pad::FOUR, 0)) {
				if (Score > MaxHPScore) {
					gRobo[0]->statusMaxHpIncrease(100);
					Score -= MaxHPScore;
				}
			}
			if (statusPad->isTriggered(Pad::FIVE, 0)) {
				if (Score > HPRecoverScore) {
					gRobo[0]->statusHpRecover(50);
					Score -= HPRecoverScore;

				}
			}
			if (statusPad->isTriggered(Pad::SIX, 0)) {
				if (Score > BulletESppedScore) {
					gRobo[0]->statusBulletEnergySpeed(0.5);
					Score -= BulletESppedScore;
				}
			}
			if (statusPad->isTriggered(Pad::SEVEN, 0)) {
				if (Score > DashESpeedScore) {
					gRobo[0]->statusDashEnergySpeed(0.5);
					Score -= DashESpeedScore;
				}
			}
			if (statusPad->isTriggered(Pad::STATUS_MENU_START, 0)) {
				gSequence = SEQUENCE_PLAY;
			}
			break;
		}
			case SEQUENCE_GAMEOVER: {
				cout << "gameover" << endl;
			}
		}
		

		/*
		if (gPlaying) {
			Vector3 move[30];
			for (int i = 1;i < npcCountForScoreLevel; i++) {//2
				if (gRobo[i] == 0) {//gRoboが存在しない時
					int npcPositionrand = rand() % 3 * 2;
					gRobo[i] = new Robo(i);
					gRobo[i]->setPosition(Vector3(npcGeneratePosition[npcPositionrand], 0.0, npcGeneratePosition[npcPositionrand + 1] + 1));//ここで生成！　生成座標（わき地）を決めたらここで処理ー－－－－－－－－－－－－－－－－
					npc += 1;
					}


				//		衝突判定処理　ロボとステージ　ロボ同士
				/*
					//先を予測して判定を行う！
				for (int i = 0;i < 2;i++) {
					if (i == 0) {
						gRobo[0]->getMove(&move[0]);
					}
					else {
						enemyPosi = *gRobo[i]->position();
						mPosi = *gRobo[0]->position();
						gRobo[i]->npcMove(enemyPosi, mPosi, &move[i]);
					}

					gStage->restrictMove(&move[0], *gRobo[0]->position());//------------------------------この式をforiをいれて文で書くとすり抜ける !
					//gRobo[i]->update(gRobo[0], move[i]);//ここも実行するとすり抜ける！　なぜ？
					gRobo[0]->update(gRobo[i],move[0]);//ここでRobo0も入っているので自分の攻撃でダメージを受ける
				}
				//*--------------

				gRobo[0]->getMove(&move[0]);	//先を予測して判定を行う！
				//cout << "gRobo-MOVE: "<< *gRobo[0]->position() << endl;
				//cout << "old　 move_X: " << move[0].x << "  move_Y: " << move[0].y << "  move_Z: " << move[0].z << endl;
				gStage->restrictMove(&move[0], *gRobo[0]->position());
				mPosi = *gRobo[0]->position();
				//cout << "new   move_X: " << move[0].x << "  move_Y: " << move[0].y << "  move_Z: " << move[0].z << endl;
				gRobo[0]->update(gRobo[1], move[0]);
				//gRobo[i]->update(gRobo[0], move[i]);
				//gRobo[0]->update(gRobo[i],move[i]);

			}
			++gTime;
		}
		*/
		//std::unique_ptr<Stage> gStage(new Stage("map.txt"));//unique------------------------------ここでスマートポインタにすると極端に動作が重くなる!


		

		//Playerからカメラ行列ゲット
		Matrix44 pvm;
		pvm.setPerspectiveTransform(45.0,
			static_cast<double>(width()),
			static_cast<double>(height()),
			1.0,
			10000.0);
		Matrix34 vm;
		gRobo[0]->getViewMatrix(&vm); 
		pvm *= vm;
		//描画
		gStage->draw(pvm);
		//gWall->draw(pvm);
		
		for (int i = 0; i < npc+1; ++i) {
			gRobo[i]->draw(pvm);
			}
		
		//フロント描画---------------------------------------------------------------------------------------
		//テクスチャを空に
		setTexture(0); //空このコマンド効かない・・何故？

		//必要な情報を抜いて
		int hp0 = gRobo[0]->hitPoint();
		//int hp1 = gRobo[1]->hitPoint();
		int stateEmergencyEffect = gRobo[0]->attacked();//1がダイレクト、2がガード
		int stateHitEffet = gRobo[0]->attack();//1が近距離、2が遠距離

		int attackedCount = gRobo[0]->attackedCount();
		//bool statehitEffect = gRobo[0]->mByCloseHit();
		//bool statehitEffect = gRobo[0]->mByCloseHit();---------------------------------------------------------------



		int accelE0 = gRobo[0]->AccelEnergy();//回避エネルギー
		int e0 = gRobo[0]->energy();//弾のエネルギー
		bool lockOn0 = gRobo[0]->isLockOn();

		//Zテスト無用。アルファブレンドON
		enableDepthTest(false);
		enableDepthWrite(false);
		setBlendMode(BLEND_LINEAR);
		setTexture(0); //空

		
	

		if (stateEmergencyEffect == 1) {//ガードなしで受けたとき赤
			drawEmergency(3, 4, 0x35E12200);
		}
		else if (stateEmergencyEffect == 2){//ガードありで受けたとき黄色
			drawEmergency(3, 4, 0x35FFDC0D);
		}
		else {
	
		}
		
		if (stateHitEffet == 1) {//近距離攻撃エフェクト
			Vector2 p[4];
			unsigned c1 = 0x80ff0000;
			int centWid = 0;
			int centHet = 0;
			float longW = 0.15;
			float longH = 0.15;
			float shortW = 0.03;
			float shortH = 0.03;
			p[0].set(centWid + longW, centHet + longH);
			p[1].set(centWid - shortW, centHet + shortH);
			p[2].set(centWid + shortW, centHet - shortH);
			p[3].set(centWid - longW, centHet - longH);
			drawRect(p, c1);
		}
		if (stateHitEffet == 2) {//遠距離攻撃エフェクト
			//drawEmergency(3, 4, 0x35E12200);
			Vector2 p[4];
			unsigned c1 = 0x80ff0000;
	
			float rectW = 0.12;
			float rectH = 0.01;
			p[0].set(rectW, rectH);
			p[1].set(- rectW, rectH);
			p[2].set(rectW, -rectH);
			p[3].set(- rectW,- rectH);
			drawRect(p, c1);

			float rectWs = 0.005;
			float rectHs = 0.15;
			p[0].set(rectWs, rectHs);
			p[1].set(-rectWs, rectHs);
			p[2].set(rectWs, -rectHs);
			p[3].set(-rectWs, -rectHs);
			drawRect(p, c1);
			
		}
		

		//PlayerのHPバー描画
		drawBar(hp0, gRobo[0]->pMaxHitPoint(),
			-0.9, 0.95,
			1, 0.08,
			0xff696969, 0xff1BF213,
			1);
		/*
		//敵のHPバー描画
		drawBar(hp1, Robo::mMaxHitPoint,
			-0.9, 0.85,
			1,0.08,
			0xff696969, 0xff1BF213,
			1);*/

	
		

		
		//弾エネルギー描画
		drawBar(e0, Robo::mMaxEnergy,
			-0.05, -0.7,
			0.1, 0.1,
			0x80404040, 0xffF62332,
			0.1);

		//回避エネルギー描画
		drawBar(accelE0, Robo::mMaxAccelEnergy,
			0.5, -0.7,
			0.1, 0.1,
			0x80404040, 0xff7EFFFF,
			0.1);


		drawMap(-0.5, -0.7, 0x307EFFFF, 0x80404040, 0x80404040);

		Vector2 p[4];
		unsigned c1;
		

		
		
		//ロックオンマーク
		if (lockOn0) {
			setBlendMode(BLEND_ADDITIVE); 
			
			Vector3 t = *gRobo[gRobo[0]->enemyId()]->position();//-----------------------------------------------------------------------------------
			t.y += 1.5;  //ｔ＋1.5は物体が浮いているからそれにロックオンマークを合わすため！
			
			double p4[4];
			pvm.multiply(p4, t);                  
			double x = p4[0] / p4[3];
			double y = p4[1] / p4[3];
			c1 = 0x80ff0000;
			p[0].set(x - 0.01, y + 0.2);
			p[1].set(x - 0.01, y + 0.1);
			p[2].set(x + 0.01, y + 0.2);
			p[3].set(x + 0.01, y + 0.1);
			drawRect(p, c1);
			p[0].set(x - 0.01, y - 0.2);
			p[1].set(x - 0.01, y - 0.1);
			p[2].set(x + 0.01, y - 0.2);
			p[3].set(x + 0.01, y - 0.1);
			drawRect(p, c1);
			p[0].set(x - 0.2, y - 0.01);
			p[1].set(x - 0.2, y + 0.01);
			p[2].set(x - 0.1, y - 0.01);
			p[3].set(x - 0.1, y + 0.01);
			drawRect(p, c1);
			p[0].set(x + 0.2, y - 0.01);
			p[1].set(x + 0.2, y + 0.01);
			p[2].set(x + 0.1, y - 0.01);
			p[3].set(x + 0.1, y + 0.01);
			drawRect(p, c1);
		}
		

		
		if (hp0 < 1) {	
			
			ostringstream oss;
			oss << "GameOver!    Your Score is :" << Score <<"\n";
			oss << "If you try again, Pleas press X "  << "\n";
			Framework().drawDebugString(30, 10, oss.str().c_str());
			gSequence = SEQUENCE_GAMEOVER;
			//npc = 0;
			
			
			if (Pad::instance()->isTriggered(Pad::FIRE, 0)) {
				Pad::destroy();
				//gRobo[0]->~Robo();
				SAFE_DELETE(gRobo[0]);
				//gStage->~Stage();
				SAFE_DELETE(gStage);
				//SAFE_DELETE(gWall);
				for (int i = 1; i < npc; ++i) {
					//SAFE_DELETE(gRobo[i]);
				}
				gSequence = SEQUENCE_PLAY;
				gTime = 0;
			
			}
		}

		

		Pad* pad = Pad::instance();
		End = pad->isOn(Pad::QUIT, 0);
		if (End) {
			exit(0);
		}

		for (int i = 1; i < npcCountForScoreLevel; ++i) {
			if (gRobo[i]->hitPoint() <= 1) {
				//gRobo[i]->~Robo();
				SAFE_DELETE(gRobo[i]);
				npc -= 1;
				//cout << "Clear!" <<"npc数" << npc<< endl;
				Score += 500;
				//cout << "Score" << Score << endl;
			}
			else if (gRobo[i]->position()->y <= -10) {//NPCがステージをから落ちた場合は、死んでもらう
				//gRobo[i]->~Robo();
				SAFE_DELETE(gRobo[i]);
				npc -= 1;
				
			}
		}

		if ( isEndRequested() ){
			if ( gStage ){
				Pad::destroy();
				//gRobo[0]->~Robo();
				SAFE_DELETE( gRobo[ 0 ] );
				//gStage->~Stage();
				SAFE_DELETE( gStage );
				for (int i = 1; i < npc; ++i) {
					//gRobo[i]->~Robo();
					SAFE_DELETE(gRobo[i]);
				}
			}
		}
	}
}



