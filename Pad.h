#ifndef INCLUDED_PAD_H
#define INCLUDED_PAD_H

class Pad {
public:
	enum Button {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		JUMP,
		FIRE,
		SWING,
		TURN,
		DASH,
		GUARD,
		QUIT,
		ONE,
		TWO,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		NINE,
		STATUS_MENU_QUIT,
		STATUS_MENU_START,

	};

	int VelocityX() const;
	int VelocityY() const;

	int X();
	int Y();

	static Pad* instance();
	static void create();
	static void destroy();
	bool isOn(Button, int id) const;
	bool isTriggered(Button, int id) const;
private:
	Pad();
	~Pad();
	static Pad* mInstance;
};


#endif

