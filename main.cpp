#include "Entitys.h"
#include "Level.h"
#include "Player.h"
#include "Bullet.h"
#include "HealthBar.h"

bool start()
{
	float dXForEnemy = 0.02;
	float dYForBird = 0.01;
	float dXForBird = 0.02;
	float dXForRat = 0.0175;

	Font font;
	font.loadFromFile("font.TTF");

	Text text("", font, 16);
	//text.setColor(Color::Black);
	text.setStyle(Text::Regular);

	Text end("", font, 32);
	//text.setColor(Color::Black);
	end.setStyle(Text::Regular);
	end.setString("GAME OVER\nPRESS 'R' TO RESTART");
	end.setPosition(view.getCenter().x-220, view.getCenter().y);

	RenderWindow window(VideoMode(1280, 720), "Tower Defense Game");

	view.reset(FloatRect(0, 0, 1280, 720));
	view.zoom(0.5);

	SoundBuffer shootBuffer;
	shootBuffer.loadFromFile("sounds/shot.wav");
	Sound shoot(shootBuffer);

	Music bgMusic;
	bgMusic.openFromFile("bg_music.flac");
	bgMusic.play();
	bgMusic.setLoop(true);

	HealthBar healthBarPlayer;

	Level level;
	level.LoadFromFile("map.tmx");

	Image wolf;
	wolf.loadFromFile("images/enemy.png");
	wolf.createMaskFromColor(Color(255, 255, 255));

	Image bird;
	bird.loadFromFile("images/bird.png");

	Image rat;
	rat.loadFromFile("images/rat.png");
	rat.createMaskFromColor(Color(255, 255, 255));

	Image cat;
	cat.loadFromFile("images/cat.png");
	cat.createMaskFromColor(Color(255, 255, 255));

	Object p = level.GetObject("player");
	Object tower = level.GetObject("tower");

	Player player(cat, "player", level, p.rect.left, p.rect.top, 15, 13);

	Image bullet;
	bullet.loadFromFile("images/bullet.png");
	bullet.createMaskFromColor(Color(255, 255, 255));

	list<Entitys*>  entities;
	list<Entitys*>::iterator it;
	list<Entitys*>::iterator it2;
	vector<Object> enemies = level.GetObjects("enemy");
	vector<Object> birds = level.GetObjects("bird");
	vector<Object> rats = level.GetObjects("rat");

	for (int i = 0;i < enemies.size();i++)
	{
		entities.push_back(new Enemy(wolf, "enemy", level, enemies[i].rect.left, enemies[i].rect.top, 50, 50, dXForEnemy, 0));
	}
	for (int i = 0;i < birds.size();i++)
	{
		entities.push_back(new Enemy(bird, "bird", level, birds[i].rect.left, birds[i].rect.top, 48, 32, dXForBird, dYForBird));
	}
	for (int i = 0;i < rats.size();i++)
	{
		entities.push_back(new Enemy(rat, "rat", level, rats[i].rect.left, rats[i].rect.top, 30, 20, dXForEnemy, 0));
	}

	Clock clock;
	Clock totalTimeSurvivedClock;
	int totalTimeSurvived;
	bool lost = false;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		if (player.getLife() == true)
			totalTimeSurvived = totalTimeSurvivedClock.getElapsedTime().asSeconds();
		clock.restart();
		time = time / 800;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if(!lost)
			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
				{
					Vector2i pixelPos = Mouse::getPosition(window);
					Vector2f pos = window.mapPixelToCoords(pixelPos);
					entities.push_back(new Bullet(bullet, "bullet", level, player.getX(), player.getY(), 5, 5, pos.x, pos.y));
					shoot.play();
				}
			if (Keyboard::isKeyPressed(Keyboard::R))
				return true;
			if (Keyboard::isKeyPressed(Keyboard::Escape))
				window.close();
		}
		if(!lost)
		for (it = entities.begin(); it != entities.end();)
		{
			Entitys* b = *it;
			b->update(time);
			if (b->getLife() == false)
			{
				it = entities.erase(it);
				delete b;
			}
			else it++;
		}
		if(!lost)
		for (auto i = entities.begin();i != entities.end();i++)
		{
			if ((*i)->getName() == "bullet")
			{
				for (auto j = entities.begin();j != entities.end();j++)
				{
					if (((*j)->getName() == "enemy" || (*j)->getName() == "bird" || (*j)->getName() == "rat") && (*i)->getRect().intersects((*j)->getRect()))
					{
						(*j)->setHealth((*j)->getHealth() - 50);
						if ((*j)->getHealth() <= 0)
							if ((*j)->getName() == "enemy" && player.getLife() == true)
								player.setScore(player.getScore() + 1);
							else
								if ((*j)->getName() == "bird" && player.getLife() == true)
									player.setScore(player.getScore() + 2);
								else
									if ((*j)->getName() == "rat" && player.getLife() == true)
										player.setScore(player.getScore() + 3);
						(*i)->setLife(false);
					}
				}
			}
		}
		if(!lost)
		for (auto i = entities.begin();i != entities.end();i++)
			if (((*i)->getName() == "enemy" || (*i)->getName() == "bird" || (*i)->getName() == "rat") && (*i)->getRect().intersects(tower.rect))
			{
				player.setHealth(player.getHealth() - 20);
				healthBarPlayer.update(player.getHealth());
				(*i)->setLife(false);
			}
		bool is_enemy = false;
		if(!lost)
		for (auto i = entities.begin();i != entities.end();i++)
			if ((*i)->getName() == "enemy" || (*i)->getName() == "bird" || (*i)->getName() == "rat")
				is_enemy = true;
		if (!lost)
		if (!is_enemy)
		{
			dXForEnemy += 0.005;
			dXForBird += 0.0075;
			dYForBird = dXForBird / 2;
			dXForRat += 0.006;
			for (int i = 0;i < enemies.size();i++)
			{
				entities.push_back(new Enemy(wolf, "enemy", level, enemies[i].rect.left, enemies[i].rect.top, 50, 50, dXForEnemy, 0));
			}
			for (int i = 0;i < birds.size();i++)
			{
				entities.push_back(new Enemy(bird, "bird", level, birds[i].rect.left, birds[i].rect.top, 55, 55, dXForEnemy, dYForBird));
			}
			for (int i = 0;i < rats.size();i++)
			{
				entities.push_back(new Enemy(rat, "rat", level, rats[i].rect.left, rats[i].rect.top, 30, 20, dXForRat, 0));
			}
		}
		if (!lost)
		player.update(time);
		window.setView(view);
		window.clear(Color(65, 140, 180));
		level.Draw(window);
		if(!lost)
		for (it = entities.begin(); it != entities.end(); it++)
		{
			window.draw((*it)->getSprite());
		}
		if(!lost)
		window.draw(player.getSprite());
		healthBarPlayer.draw(window);
		text.setString("TIME:" + to_string(totalTimeSurvived) + "\n" + "\n" + "SCORE:" + to_string(player.getScore()));
		text.setPosition(view.getCenter().x - 50, view.getCenter().y - 175);
		window.draw(text);
		if (player.getLife() == false)
		{
			window.draw(end);
			lost = true;
		}
		window.display();
	}
}

void runGame()
{
	if (start())
	{
		runGame();
	}
}

int main()
{
	runGame();
	return 0;
}