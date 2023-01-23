#pragma once
#include "libs.h"
class HealthBar
{
protected:
	Image image;
	Texture texture;
	Sprite sprite;
	int maxHealth;
	RectangleShape bar;
public:
	HealthBar()
	{
		image.loadFromFile("images/health_bar.png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 100, 10));
		bar.setFillColor(Color(0, 0, 0));
		maxHealth = 100;
	}
	void update(int health)
	{
		if (health < 0)
			health = 0;
		bar.setSize(Vector2f((maxHealth - health) * 98 / maxHealth,8));
	}
	void draw(RenderWindow& window)
	{
		Vector2f center = window.getView().getCenter();
		Vector2f size = window.getView().getSize();
		sprite.setPosition(center.x - size.x / 2 + 10, center.y - size.y / 2 + 10);
		bar.setPosition(center.x - size.x / 2 + 11, center.y - size.y / 2 + 11);
		window.draw(sprite);
		window.draw(bar);
	}
};

