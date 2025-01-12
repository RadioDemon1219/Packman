#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

const int heightOfMap = 21;
const int widthOfMap = 19;

const int sizeOfPlate = 25;

int coins = 0;
bool life = true;

String tileMap[heightOfMap] = {
"AAAAAAAAAAAAAAAAAAA",
"A1       A       2A",
"A AA AAA A AAA AA A",
"A        A        A",
"A AA A AAAAA A AA A",
"A    A   A   A    A",
"AAAA AAA A AAA AAAA",
"BBBA A       A ABBB",
"AAAA A AAAAA A AAAA",
"BBBB   ABBBA   BBBB",
"AAAA A AAAAA A AAAA",
"BBBA A       A ABBB",
"AAAA A AAAAA A AAAA",
"A        A        A",
"A AA AAA A AAA AA A",
"A  A     C     A  A",
"AA A A AAAAA A A AA",
"A    A   A   A    A",
"A AAAAAA A AAAAAA A",
"A3               4A",
"AAAAAAAAAAAAAAAAAAA",

};

class Player {
public:
	float frameOfPackman = 0;
	int x = 9, y = 15;
	int newx = 0, newy = 0;
	int rotate = 1, delayOfStep = 0;

	void update() {
		frameOfPackman += 0.01;
		if (frameOfPackman > 5)
			frameOfPackman -= 5;

        //движение игрока
		delayOfStep++;
		if (delayOfStep >= 900) {
			switch (rotate)
			{
			case 1:
				if (tileMap[y][newx + 1] != 'A')
					newx += 1;
				break;
			case 2:
				if (tileMap[y][newx - 1] != 'A')
					newx -= 1;
				break;
			case 3:
				if (tileMap[newy - 1][x] != 'A')
					newy -= 1;
				break;
			case 4:
				if (tileMap[newy + 1][x] != 'A')
					newy += 1;
				break;
			}

			delayOfStep = 0;
		}

	    //сбор монет игроком
		if (tileMap[newy][newx] == ' ' || tileMap[newy][newx] == 'B') {
			if (tileMap[newy][newx] == ' ')
				coins++;

			if (tileMap[newy][newx] == '1'
				|| tileMap[newy][newx] == '2' || tileMap[newy][newx] == '3' || tileMap[newy][newx] == '4')
				life = false;

			tileMap[y][x] = 'B';

			tileMap[newy][newx] = 'C';

			x = newx;
			y = newy;
		}

		//переход из одного края карты в другой
		if (newy == 9 && (newx == 0 || newx == 18)) {
			if (newx == 0)
				newx = 17;
			else
				newx = 1;

			tileMap[y][x] = 'B';
			tileMap[newy][newx] = 'C';

			x = newx;
			y = newy;
		}
	}
};

class Enemy {
public:
	int x[4] = { 1, 17 , 1, 17 }, y[4] = { 1, 1, 19, 19 };
	int newx[4] = { 0 , 0 , 0, 0 }, newy[4] = { 0, 0, 0, 0 };
	int rotate[4] = { 1, 1, 1, 1 }, delayOfStep = 0;

	void update() {
		delayOfStep++;

		if (delayOfStep >= 900) {
			for (int i = 0; i < 4; i++) {
				rotate[i] = rand() % 4 + 1;

				newx[i] = x[i];
				newy[i] = y[i];

				bool found_empty_space = false;
				//передвижение врагов
				while (!found_empty_space) {
					switch (rotate[i]) {
					case 1:
						if (tileMap[y[i]][newx[i] + 1] != 'A') {
							newx[i] += 1;
							found_empty_space = true;
						}
						else {
							rotate[i] = (rotate[i] % 4) + 1;}
						break;
					case 2:
						if (tileMap[y[i]][newx[i] - 1] != 'A') {
							newx[i] -= 1;
							found_empty_space = true;
						}
						else {
							rotate[i] = (rotate[i] % 4) + 1;
						}
						break;
					case 3:
						if (tileMap[newy[i] - 1][x[i]] != 'A') {
							newy[i] -= 1;
							found_empty_space = true;
						}
						else {
							rotate[i] = (rotate[i] % 4) + 1;
						}
						break;
					case 4:
						if (tileMap[newy[i] + 1][x[i]] != 'A') {
							newy[i] += 1;
							found_empty_space = true;
						}
						else {
							rotate[i] = (rotate[i] % 4) + 1;
						}
						break;
					}
				}

			}


			delayOfStep = 0;
		}

		for (int i = 0; i < 4; i++) {
			if (tileMap[newy[i]][newx[i]] == ' ' || tileMap[newy[i]][newx[i]] == 'B' ||
				tileMap[newy[i]][newx[i]] == 'C') {
				if (tileMap[newy[i]][newx[i]] == 'B')
					tileMap[y[i]][x[i]] = 'B';
				else if (tileMap[newy[i]][newx[i]] == ' ')
					tileMap[y[i]][x[i]] = ' ';
				else if (tileMap[newy[i]][newx[i]] == 'C')
					life = false;

				if (i == 0)
					tileMap[newy[i]][newx[i]] = '1';
				if (i == 1)
					tileMap[newy[i]][newx[i]] = '2';
				if (i == 2)
					tileMap[newy[i]][newx[i]] = '3';
				if (i == 3)
					tileMap[newy[i]][newx[i]] = '4';

				x[i] = newx[i];
				y[i] = newy[i];
			}
			//переход из одного края карты в другой
			if (newy[i] == 9 && (newx[i] == 0 || newx[i] == 18)) {
				if (newx[i] == 0)
					newx[i] = 17;
				else
					newx[i] = 1;

				tileMap[y[i]][x[i]] = 'B';

				if (i == 0)
					tileMap[newy[i]][newx[i]] = '1';
				if (i == 1)
					tileMap[newy[i]][newx[i]] = '2';
				if (i == 2)
					tileMap[newy[i]][newx[i]] = '3';
				if (i == 3)
					tileMap[newy[i]][newx[i]] = '4';

				x[i] = newx[i];
				y[i] = newy[i];
			}
		}
	}
};

int main() {
	srand(time(0));

	RenderWindow window(VideoMode(widthOfMap * sizeOfPlate, heightOfMap * sizeOfPlate), "Maze!"); 

	Texture mapGame;
	mapGame.loadFromFile("../Paint/title.png");
	Sprite plat(mapGame);

	Texture pictureYouWin;
	pictureYouWin.loadFromFile("../Paint/youwin.png");
	Sprite youwin(pictureYouWin);
	youwin.setPosition(100, 210);

	Texture pictureYouLoose;
	pictureYouLoose.loadFromFile("../Paint/youlose.png");
	Sprite youloose(pictureYouLoose);
	youloose.setPosition(100, 210);

	Player player;
	Enemy enemy;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			//управление игроком
			if (coins < 171 && life)
				if (event.type == Event::KeyPressed) {
					player.newx = player.x;
					player.newy = player.y;

					if (event.key.code == Keyboard::Right)
						player.rotate = 1;
					else if(event.key.code == Keyboard::D)
						player.rotate = 1;
					if (event.key.code == Keyboard::Left)
						player.rotate = 2;
					else if (event.key.code == Keyboard::A)
						player.rotate = 2;
					if (event.key.code == Keyboard::Up)
						player.rotate = 3;
					else if (event.key.code == Keyboard::W)
						player.rotate = 3;
					if (event.key.code == Keyboard::Down)
						player.rotate = 4;
					else if (event.key.code == Keyboard::S)
						player.rotate = 4;
				}
		}

		if (coins < 171 && life) {
			player.update();
			enemy.update();
		}
		window.clear(Color::Black);
		//преображение карты
		for (int i = 0; i < heightOfMap; i++)
			for (int j = 0; j < widthOfMap; j++) {
				if (tileMap[i][j] == 'A')
					plat.setTextureRect(IntRect(0, 0, sizeOfPlate, sizeOfPlate));
				if (tileMap[i][j] == 'C')
					plat.setTextureRect(IntRect(sizeOfPlate * int(player.frameOfPackman), sizeOfPlate * player.rotate, sizeOfPlate, sizeOfPlate));
				if (tileMap[i][j] == ' ')
					plat.setTextureRect(IntRect(sizeOfPlate, 0, sizeOfPlate, sizeOfPlate));
				if (tileMap[i][j] == '1')
					plat.setTextureRect(IntRect(sizeOfPlate * 5, sizeOfPlate * enemy.rotate[0], sizeOfPlate, sizeOfPlate));
				if (tileMap[i][j] == '2')
					plat.setTextureRect(IntRect(sizeOfPlate * 5, sizeOfPlate * enemy.rotate[1], sizeOfPlate, sizeOfPlate));
				if (tileMap[i][j] == '3')
					plat.setTextureRect(IntRect(sizeOfPlate * 5, sizeOfPlate * enemy.rotate[2], sizeOfPlate, sizeOfPlate));
				if (tileMap[i][j] == '4')
					plat.setTextureRect(IntRect(sizeOfPlate * 5, sizeOfPlate * enemy.rotate[3], sizeOfPlate, sizeOfPlate));
				if (tileMap[i][j] == 'B')
					continue;

				plat.setPosition(j * sizeOfPlate, i * sizeOfPlate);
				window.draw(plat);
			}

		if (coins == 171)
			window.draw(youwin);
		if (!life)
			window.draw(youloose);

		window.display();
	}
	return 0;
}