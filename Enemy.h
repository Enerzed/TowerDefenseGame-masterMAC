#pragma once
#include "Entitys.h"

class Enemy :
    public Entitys
{
protected:
	float currentFrameEnemy;
	float currentFrameRat;
	float currentFrameBird;
	float currentTime;
public:
	Enemy(Image& myImage, String myName, Level& myLevel, float myX, float myY, int myWidth, int myHeight, float myDx, float myDy) :Entitys(myImage, myName, myX, myY, myWidth, myHeight)
	{
		currentFrameEnemy = 0;
		currentFrameRat = 0;
		currentFrameBird = 0;
		currentTime = 0;
		obj = myLevel.GetAllObjects();
		if (name == "enemy")
		{
			sprite.setTextureRect(IntRect(0, 0, width, height));
			if (x < 640)
				dx = myDx;
			else
				dx = -myDx;
		}
		if (name == "bird")
		{
			sprite.setTextureRect(IntRect(192, 223, width, height));
			if (x < 640)
			{
				dx = myDx;
				dy = myDy;
			}
			else
			{
				dx = -myDx;
				dy = myDy;
			}
		}
		if (name == "rat")
		{
			sprite.setTextureRect(IntRect(0, 0, width, height));
			if (x < 640)
				dx = myDx;
			else
				dx = -myDx;
		}
	}
	void checkCollisionsWithMap(float myDx, float myDy)
	{
		for (int i = 0; i < obj.size(); i++)
			if (getRect().intersects(obj[i].rect))
			{

			}
	}
	void update(float time)
	{
		if (name == "enemy")
		{
			if (dx > 0)
			{
				currentFrameEnemy += 0.005 * currentTime;
				if (currentFrameEnemy > 3)
					currentFrameEnemy -= 3;
				sprite.setTextureRect(IntRect(50 * int(currentFrameEnemy) + 50, 0, -50, 50));
			}
			if (dx < 0)
			{
				currentFrameEnemy += 0.005 * currentTime;
				if (currentFrameEnemy > 3)
					currentFrameEnemy -= 3;
				sprite.setTextureRect(IntRect(50 * int(currentFrameEnemy), 0, 50, 50));
			}
		}
		if (name == "rat")
		{
			if (dx > 0)
			{
				currentFrameRat += 0.005 * currentTime;
				if (currentFrameRat > 4)
					currentFrameRat -= 4;
				sprite.setTextureRect(IntRect(30 * int(currentFrameRat) + 30, 0, -30, 20));
			}
			if (dx < 0)
			{
				currentFrameRat += 0.005 * currentTime;
				if (currentFrameRat > 4)
					currentFrameRat -= 4;
				sprite.setTextureRect(IntRect(30 * int(currentFrameRat), 0, 30, 20));
			}
		}
		if (name == "bird")
		{
			if (dx > 0)
			{
				currentFrameBird += 0.005 * currentTime;
				if (currentFrameBird > 8)
					currentFrameBird -= 8;
				sprite.setTextureRect(IntRect(48 * int(currentFrameBird), 192, 48, 32));
			}
			if (dx < 0)
			{
				currentFrameBird += 0.005 * currentTime;
				if (currentFrameBird > 8)
					currentFrameBird -= 8;
				sprite.setTextureRect(IntRect(48 * int(currentFrameBird) + 48, 192, -48, 32));
			}
		}
		if (name == "enemy" || name == "rat") {
			currentTime = time;
			checkCollisionsWithMap(dx, 0);
			x += dx * time;
			sprite.setPosition(x + width / 2, y + height / 2);
			if (health <= 0) { life = false; }
		}
		if (name == "bird")
		{
			currentTime = time;
			checkCollisionsWithMap(dx, 0);
			x += dx * time;
			y += dy * time;
			sprite.setPosition(x + width / 2, y + height / 2);
			if (health <= 0) { life = false; }
		}
	}
};

