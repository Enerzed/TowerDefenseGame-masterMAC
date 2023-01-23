#pragma once
#include "Entitys.h"
#include "View.h"


class Player :
    public Entitys
{
protected:
    enum{left,right,up,down,jump,stay,rightTop,leftTop} state;
    int score;
	bool isShoot;
	float currentFrame = 0;
	float currentTime;
	int last_dir;
public:
    Player(Image& myImage, String myName, Level& myLevel, float myX, float myY, int myWidth, int myHeight) :Entitys(myImage, myName, myX, myY, myWidth, myHeight)
    {
        score = 0; state = stay; obj = myLevel.GetAllObjects();
        if (name == "player")
        {
            sprite.setTextureRect(IntRect(0, 0, width, height));
        }
    }
    void control()
    {
		if (Keyboard::isKeyPressed) {
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				currentFrame += 0.01 * currentTime;
				state = left; speed = 0.1;
				if (currentFrame > 8)
					currentFrame -= 8;
				sprite.setTextureRect(IntRect(16 * int(currentFrame)+16, 0, -16, 16));
				last_dir = 1;
			}
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				currentFrame += 0.01 * currentTime;
				state = right; speed = 0.1;
				if (currentFrame > 8)
					currentFrame -= 8;
				sprite.setTextureRect(IntRect(16 * int(currentFrame), 0, 16, 16));
				last_dir = 0;
			}
			if ((Keyboard::isKeyPressed(Keyboard::W)) && (onGround)) {
				state = jump; dy = -0.45; onGround = false;
			}

			if (Keyboard::isKeyPressed(Keyboard::S)) {
				state = down;
			}

			if ((Keyboard::isKeyPressed(Keyboard::D)) && (Keyboard::isKeyPressed(Keyboard::W))) {
				state = rightTop;
			}

			if ((Keyboard::isKeyPressed(Keyboard::A)) && (Keyboard::isKeyPressed(Keyboard::W))) {
				state = leftTop;
			}
			if (!(Keyboard::isKeyPressed(Keyboard::A)) && !(Keyboard::isKeyPressed(Keyboard::D))) {
				if(last_dir == 0)
					sprite.setTextureRect(IntRect(0, 0, width, height));
				if(last_dir == 1)
					sprite.setTextureRect(IntRect(16, 0, -width, height));
			}
		}
    }
	void checkCollisionsWithMap(float myDx, float myDy)
	{
		for (int i = 0; i < obj.size(); i++)
			if (getRect().intersects(obj[i].rect))
			{
				if (obj[i].name == "solid")
				{
					if (myDy > 0) { y = obj[i].rect.top - height;  dy = 0; onGround = true; }
					if (myDy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
					if (myDx > 0) { x = obj[i].rect.left - width; }
					if (myDx < 0) { x = obj[i].rect.left + obj[i].rect.width; }
				}
			}
	}
	void update(float time)
	{
		control();
		switch (state)
		{
		case right:dx = speed; break;
		case left:dx = -speed; break;
		case up: break;
		case down: dx = 0; break;
		case stay: break;
		case rightTop: dx = speed; break;
		case leftTop: dx = -speed; break;
		}
		x += dx * time;
		checkCollisionsWithMap(dx, 0);
		y += dy * time;
		checkCollisionsWithMap(0, dy);
		sprite.setPosition(x + width / 2, y + height / 2);
		if (health <= 0) { life = false; }
		if (!isMove) { speed = 0; }
		if (life) { setPlayerCoordinateForView(x, y); }
		dy = dy + 0.0015 * time;
		currentTime = time;
	}
	void setScore(int myScore)
	{
		score = myScore;
	}
	int getScore()
	{
		return score;
	}
};

