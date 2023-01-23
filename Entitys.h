#pragma once
#include "libs.h"
#include "Level.h"

class Entitys
{
protected:

	vector<Object> obj;
	float x, y, dx, dy, speed, moveTimer;
	int width, height, health;
	bool life, isMove, onGround;
	String name;
	Texture texture;
	Sprite sprite;

public:

	Entitys(Image &myImage,String myName, float myX, float myY, int myWidth, int myHeight)
	{
		x = myX;
		y = myY;
		width = myWidth;
		height = myHeight;
		name = myName;
		moveTimer = 0;
		speed = 0;
		health = 100;
		dx = 0;
		dy = 0;
		life = true;
		onGround = false;
		isMove = false;

		texture.loadFromImage(myImage);
		sprite.setTexture(texture);
		sprite.setOrigin(width / 2, height / 2);
	}
	virtual ~Entitys()
	{
	}

	FloatRect getRect()
	{
		return FloatRect(x, y, width, height);
	}

	virtual void update(float time) = 0;

	float getX()
	{
		return x;
	}

	float getY()
	{
		return y;
	}

	float getDx()
	{
		return dx;
	}

	float getDy()
	{
		return dy;
	}

	float getSpeed()
	{
		return speed;
	}

	float getMoveTimer()
	{
		return moveTimer;
	}

	int getWidth()
	{
		return width;
	}

	int getHeight()
	{
		return height;
	}

	int getHealth()
	{
		return health;
	}

	bool getLife()
	{
		return life;
	}

	bool getIsMove()
	{
		return isMove;
	}

	bool getOnGround()
	{
		return onGround;
	}

	String getName()
	{
		return name;
	}

	Texture getTexture()
	{
		return texture;
	}

	virtual Sprite getSprite()
	{
		return sprite;
	}

	void setX(float myX)
	{
		x = myX;
	}

	void setY(float myY)
	{
		y = myY;
	}

	void setDx(float myDx)
	{
		dx = myDx;
	}
	void setDy(float myDy)
	{
		dy = myDy;
	}

	void setMoveTimer(float MyMoveTime)
	{
		moveTimer = MyMoveTime;
	}

	void setHealth(int myHealth)
	{
		health = myHealth;
	}

	void setLife(bool myLife)
	{
		life = myLife;
	}

	void setIsMove(bool myIsMove)
	{
		isMove = myIsMove;
	}

	void setOnGroud(bool myOnGround)
	{
		onGround = myOnGround;
	}

	void setName(String myName)
	{
		name = myName;
	}

	void setWidth(int myWidth)
	{
		width = myWidth;
	}

	void setHeight(int myHeight)
	{
		height = myHeight;
	}

	void setSpeed(float mySpeed)
	{
		speed = mySpeed;
	}

	void setTexture(Texture myTexture)
	{
		texture = myTexture;
	}

	void setSprite(Sprite mySprite)
	{
		sprite = mySprite;
	}
};

