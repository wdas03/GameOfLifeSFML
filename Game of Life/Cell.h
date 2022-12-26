#ifndef CELL_H
#define CELL_H
#include "Life.h"
#include <SFML/Graphics.hpp>

class Cell {
public:
	int cellstate = 0;
	int neighbors = 0;

	sf::RectangleShape cellshape;

	Cell();

	void drawCell(sf::RenderWindow &window);
	void onClick();
	void tickCell();

	
};


#endif
