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
	int newX = 0, newY = 0;
	int rotate = 1, delayOfStep = 0;

	void update() {


		frameOfPackman += 0.01;
		if (frameOfPackman > 5) {
			frameOfPackman -= 5;
		}

        

		delayOfStep++;
		if (delayOfStep >= 900) {
			switch (rotate)
			{
			case 1:
				if (tileMap[y][newX + 1] != 'A')
					newX += 1;
				break;
			case 2:
				if (tileMap[y][newX - 1] != 'A')
					newX -= 1;
				break;
			case 3:
				if (tileMap[newY - 1][x] != 'A')
					newY -= 1;
				break;
			case 4:
				if (tileMap[newY + 1][x] != 'A')
					newY += 1;
				break;
			}

			delayOfStep = 0;
		}

	    

		if (tileMap[newY][newX] == ' ' || tileMap[newY][newX] == 'B') {
			if (tileMap[newY][newX] == ' ') {
				coins++;
			}

			if (tileMap[newY][newX] == '1'
				|| tileMap[newY][newX] == '2' || tileMap[newY][newX] == '3' || tileMap[newY][newX] == '4') {
				life = false;
			}

			tileMap[y][x] = 'B';

			tileMap[newY][newX] = 'C';

			x = newX;
			y = newY;
		}

		

		if (newY == 9 && (newX == 0 || newX == 18)) {
			if (newX == 0) {
				newX = 17;
			}
			else {
				newX = 1;
			}

			tileMap[y][x] = 'B';
			tileMap[newY][newX] = 'C';

			x = newX;
			y = newY;
		}
	}
};

class Enemy {
public:
	int x[4] = { 1, 17 , 1, 17 }, y[4] = { 1, 1, 19, 19 };
	int newX[4] = { 0 , 0 , 0, 0 }, newY[4] = { 0, 0, 0, 0 };
	int rotate[4] = { 1, 1, 1, 1 }, delayOfStep = 0;

	void update() {
		delayOfStep++;

		if (delayOfStep >= 900) {
			for (int i = 0; i < 4; i++) {
				rotate[i] = rand() % 4 + 1;

				newX[i] = x[i];
				newY[i] = y[i];

				bool found_empty_space = false;
				

				while (!found_empty_space) {
					switch (rotate[i]) {
					case 1:
						if (tileMap[y[i]][newX[i] + 1] != 'A') {
							newX[i] += 1;
							found_empty_space = true;
						}
						else {
							rotate[i] = (rotate[i] % 4) + 1;}
						break;
					case 2:
						if (tileMap[y[i]][newX[i] - 1] != 'A') {
							newX[i] -= 1;
							found_empty_space = true;
						}
						else {
							rotate[i] = (rotate[i] % 4) + 1;
						}
						break;
					case 3:
						if (tileMap[newY[i] - 1][x[i]] != 'A') {
							newY[i] -= 1;
							found_empty_space = true;
						}
						else {
							rotate[i] = (rotate[i] % 4) + 1;
						}
						break;
					case 4:
						if (tileMap[newY[i] + 1][x[i]] != 'A') {
							newY[i] += 1;
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
			if (tileMap[newY[i]][newX[i]] == ' ' || tileMap[newY[i]][newX[i]] == 'B' ||
				tileMap[newY[i]][newX[i]] == 'C') {
				if (tileMap[newY[i]][newX[i]] == 'B') {
					tileMap[y[i]][x[i]] = 'B';
				}
				else if (tileMap[newY[i]][newX[i]] == ' ') {
					tileMap[y[i]][x[i]] = ' ';
				}
				else if (tileMap[newY[i]][newX[i]] == 'C') {
					life = false;
				}

				if (i == 0) {
					tileMap[newY[i]][newX[i]] = '1';
				}
				if (i == 1) {
					tileMap[newY[i]][newX[i]] = '2';
				}
				if (i == 2) {
					tileMap[newY[i]][newX[i]] = '3';
				}
				if (i == 3) {
					tileMap[newY[i]][newX[i]] = '4';
				}

				x[i] = newX[i];
				y[i] = newY[i];
			}
			

			if (newY[i] == 9 && (newX[i] == 0 || newX[i] == 18)) {
				if (newX[i] == 0) {
					newX[i] = 17;
				}
				else {
					newX[i] = 1;
				}

				tileMap[y[i]][x[i]] = 'B';

				if (i == 0) {
					tileMap[newY[i]][newX[i]] = '1';
				}
				if (i == 1) {
					tileMap[newY[i]][newX[i]] = '2';
				}
				if (i == 2) {
					tileMap[newY[i]][newX[i]] = '3';
				}
				if (i == 3) {
					tileMap[newY[i]][newX[i]] = '4';
				}

				x[i] = newX[i];
				y[i] = newY[i];
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
	Sprite youWin(pictureYouWin);
	youWin.setPosition(100, 210);

	Texture pictureYouLoose;
	pictureYouLoose.loadFromFile("../Paint/youlose.png");
	Sprite youLoose(pictureYouLoose);
	youLoose.setPosition(100, 210);

	Player player;
	Enemy enemy;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}
			
			
			if (coins < 171 && life) {
				if (event.type == Event::KeyPressed) {
					player.newX = player.x;
					player.newY = player.y;

					if (event.key.code == Keyboard::Right) {
						player.rotate = 1;
					}
					else if (event.key.code == Keyboard::D) {
						player.rotate = 1;
					}
					if (event.key.code == Keyboard::Left) {
						player.rotate = 2;
					}
					else if (event.key.code == Keyboard::A) {
						player.rotate = 2;
					}
					if (event.key.code == Keyboard::Up) {
						player.rotate = 3;
					}
					else if (event.key.code == Keyboard::W) {
						player.rotate = 3;
					}
					if (event.key.code == Keyboard::Down) {
						player.rotate = 4;
					}
					else if (event.key.code == Keyboard::S) {
						player.rotate = 4;
					}
				}
			}
		}

		if (coins < 171 && life) {
			player.update();
			enemy.update();
		}
		window.clear(Color::Black);
		

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
			window.draw(youWin);
		if (!life)
			window.draw(youLoose);

		window.display();
	}
	return 0;
}