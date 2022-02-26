#include "Pad.h"
#include "GameLib/GameLib.h"
#include "GameLib/Input/Manager.h"
#include "GameLib/Input/Keyboard.h"
#include "GameLib/Input/Mouse.h"
#include <sstream>

using namespace GameLib::Input;


int Pad::X() {
	Manager m = Manager::instance();
	//マウス追加	
	Mouse mo = m.mouse();
	return mo.x();
}


int Pad::Y() {
	Manager m = Manager::instance();
	Mouse mo = m.mouse();
	return mo.y();
}

int Pad::VelocityX() const {
	Manager m = Manager::instance();
	Mouse mo = m.mouse();
	return mo.velocityX();
}

int Pad::VelocityY() const {
	Manager m = Manager::instance();
	Mouse mo = m.mouse();
	return mo.velocityY();
}


Pad* Pad::mInstance = 0;

Pad::Pad() {
}

Pad::~Pad() {
}

void Pad::create() {
	ASSERT(!mInstance);
	mInstance = new Pad();
	//std::unique_ptr<Pad> mInstance(mInstance);

}

void Pad::destroy() {
	ASSERT(mInstance);
	SAFE_DELETE(mInstance);
}

Pad* Pad::instance() {
	return mInstance;
}

bool Pad::isOn(Button b, int id) const {
	bool r = false;
	Manager m = Manager::instance();
	//キーボードを追加
	Keyboard k = m.keyboard();
	if (id == 0) { //1P
		char c = 0;
		switch (b) {
		case UP: c = 'w'; break;
		case DOWN: c = 's'; break;
		case LEFT: c = 'a'; break;
		case RIGHT: c = 'd'; break;
		case JUMP: c = 'z'; break;
		case FIRE: c = 'x'; break;
		case SWING: c = 'r'; break;
		case TURN: c = 'e'; break;
		case DASH: c = 'q'; break;
		case GUARD: c = 'c'; break;
		case QUIT: c = 'l'; break;
		case ONE: c = '1';break;
		case TWO: c = '2';break;
		case THREE: c = '3';break;
		case FOUR: c = '4';break;
		case FIVE: c = '5';break;
		case SIX: c = '6';break;
		case SEVEN: c = '7';break;
		case EIGHT: c = '8';break;
		case NINE: c = '9';break;
		case STATUS_MENU_QUIT: c = '0';break;
		case STATUS_MENU_START: c = '-';break;
		default: ASSERT(false); break;
		}

		r = r || k.isOn(c);
	}
	return r;
}

bool Pad::isTriggered(Button b, int id) const {
	bool r = false;
	Manager m = Manager::instance();
	//キーボードを追加
	Keyboard k = m.keyboard();
	if (id == 0) { 
		char c = 0;
		switch (b) {
		case UP: c = 'w'; break;
		case DOWN: c = 's'; break;
		case LEFT: c = 'a'; break;
		case RIGHT: c = 'd'; break;
		case JUMP: c = 'z'; break;
		case FIRE: c = 'x'; break;
		case SWING: c = 'r'; break;
		case TURN: c = 'e'; break;
		case DASH: c = 'q'; break;
		case GUARD: c = 'c'; break;
		case QUIT: c = 'l'; break;
		case ONE: c = '1';break;
		case TWO: c = '2';break;
		case THREE: c = '3';break;
		case FOUR: c = '4';break;
		case FIVE: c = '5';break;
		case SIX: c = '6';break;
		case SEVEN: c = '7';break;
		case EIGHT: c = '8';break;
		case NINE: c = '9';break;
		case STATUS_MENU_QUIT: c = '0';break;
		case STATUS_MENU_START: c = '-';break;

		default: ASSERT(false); break;
		}
		r = r || k.isTriggered(c);
		return r;
	}
}
