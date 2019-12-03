#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <Windows.h>

std::vector <std::vector <std::string>> gameBoard = {	{" ", " ", " "} ,
														{" ", " ", " "} ,
														{" " ," ", " "} };

std::string winner = "";

void drawGrid(sf::RenderWindow&), takeTurn(int, sf::RenderWindow&), drawText(sf::RenderWindow&), gameOver(sf::RenderWindow&), emptyGrid();
bool checkWin();

int main() {
	sf::RenderWindow window(sf::VideoMode(640, 480), "Noughts and Crosses!");
	window.setVerticalSyncEnabled(true);

	int turn = 0;

	while (window.isOpen()) {

		sf::Event event;

		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
			}
		}

		takeTurn(turn, window);
		Sleep(100);
		if (checkWin()) {
			Sleep(100);
			gameOver(window);

		}

		turn = 1 - turn;
	}
}

void drawGrid(sf::RenderWindow& window) {
	double rectWidth = window.getSize().x / 100;
	std::vector <sf::RectangleShape> lines;

	for (int i = 1; i < 3; i++) {
		sf::RectangleShape rect(sf::Vector2f(window.getSize().x, rectWidth));
		rect.setFillColor(sf::Color::Black);
		rect.move(0, i * window.getSize().y / 3);
		lines.push_back(rect);
	}

	for (int i = 1; i < 3; i++) {
		sf::RectangleShape rect(sf::Vector2f(rectWidth,window.getSize().y));
		rect.setFillColor(sf::Color::Black);
		rect.move(i * window.getSize().x / 3,0);
		lines.push_back(rect);
	}

	for (int i = 0; i < lines.size(); i++) {
		window.draw(lines[i]);
	}
	return;
}

void takeTurn(int turn,sf::RenderWindow& window) {
	int x, y;
	std::vector < std::string> chars = { "O","X" };

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch(event.type){
			case sf::Event::Closed:
				window.close();
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			x = sf::Mouse::getPosition(window).x;
			y = sf::Mouse::getPosition(window).y;
			x = ceil(x / (window.getSize().x / 3));
			y = ceil(y / (window.getSize().y / 3));
			if (gameBoard[y][x] == " ") {
				gameBoard[y][x] = chars[turn];
				return;
			}
		}


		window.clear(sf::Color::White);

		drawGrid(window);
		drawText(window);

		window.display();
	}
}

void drawText(sf::RenderWindow& window) {
	sf::Font font;
	sf::Text text;
	if (!font.loadFromFile("Arial.ttf")) {
		std::cout << "Error";
	}
	text.setFont(font);
	text.setCharacterSize(96);
	text.setFillColor(sf::Color::Black);
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			text.setPosition(sf::Vector2f(0, 0));
			text.move(c * (window.getSize().x / 3) + window.getSize().x / 10, r * (window.getSize().y / 3) + window.getSize().y / 20);
			text.setString(gameBoard[r][c]);
			window.draw(text);
		}
	}
}

bool checkWin() {
	for (int i = 0; i < 3; i++) {
		if (gameBoard[i][0] == gameBoard[i][1] && gameBoard[i][1] == gameBoard[i][2] && gameBoard[i][0] != " ") {
			winner = gameBoard[i][0];
			return true;
		}
		if (gameBoard[0][i] == gameBoard[1][i] && gameBoard[1][i] == gameBoard[2][i] && gameBoard[0][i] != " ") {
			winner = gameBoard[0][i];
			return true;
		}
	}
	if (gameBoard[0][0] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][2] && gameBoard[1][1] != " ") {
		winner = gameBoard[0][0];
		return true;
	}
	if (gameBoard[0][2] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][0] && gameBoard[1][1] != " ") {
		winner = gameBoard[1][1];
		return true;
	}
}

void gameOver(sf::RenderWindow& window){
	sf::Font font;
	sf::Text text;
	if (!font.loadFromFile("Arial.ttf")) {
		std::cout << "Error";
	}
	text.setFont(font);
	text.setCharacterSize(96);
	text.setFillColor(sf::Color::Blue);
	text.setString(winner + " WINS!");
	text.move(window.getSize().x / 5, window.getSize().y / 3);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			Sleep(100);
			emptyGrid();
			window.close();
			main();
		}
		window.clear(sf::Color::White);
		drawGrid(window);
		drawText(window);
		window.draw(text);
		window.display();
	}

}

void emptyGrid() {
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			gameBoard[y][x] = " ";
		}
	}
}