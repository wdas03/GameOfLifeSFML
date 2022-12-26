#include "Cell.h"

Cell::Cell()
{
	cellshape = sf::RectangleShape(sf::Vector2f(CELLSIZE, CELLSIZE));
	cellshape.setOutlineColor(sf::Color(190, 190, 190));
	cellshape.setOutlineThickness(1.0f);

	cellstate = 0;
}

void Cell::tickCell() {
	if (neighbors == 3) {
		// A cell with exactly 3 live neighbors comes to life
		cellstate = 1;
	}
	else if (neighbors < 2) {
		// A cell with fewer than 2 live neighbors dies.
		cellstate = 0;
	}
	else if (neighbors > 3) {
		// A cell with greater than 3 live neighbors dies.
		cellstate = 0;
	}
}

void Cell::onClick()
{

	if (cellstate == 0) {
		cellstate = 1;
	}
	else {
		cellstate = 0;
	}

	return;
}


void Cell::drawCell(sf::RenderWindow &window)
{
	if (cellstate == 0) {
		cellshape.setFillColor(sf::Color::White);
	}
	else {
		cellshape.setFillColor(sf::Color::Black);
	}
	window.draw(cellshape);
}
