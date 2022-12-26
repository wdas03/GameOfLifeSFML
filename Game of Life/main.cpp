#include <SFML/Graphics.hpp>
#include "Life.h"
#include "Cell.h"

Cell& getCell(std::vector<std::vector<Cell>> &grid, int x, int y);
void tickGrid(std::vector<std::vector<Cell>> &grid);

int main()
{
	sf::RenderWindow window(sf::VideoMode(GRIDSIZE * CELLSIZE, GRIDSIZE * CELLSIZE), "Game of Life");

	std::vector<std::vector<Cell>> grid(GRIDSIZE, std::vector<Cell>(GRIDSIZE, Cell()));

	// Setup grid positions
	for (int row = 0; row < GRIDSIZE; row++) {
		for (int col = 0; col < GRIDSIZE; col++) {
			grid[row][col].cellshape.setPosition(col * CELLSIZE, row * CELLSIZE);
		}
	}

	bool paused = true;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);

				Cell& cell = getCell(grid, mousePos.x / CELLSIZE, mousePos.y / CELLSIZE);
				cell.onClick();
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space) {
					paused = !paused;
				}
			}

		}

		if (!paused) {
			tickGrid(grid);

			for (auto &row : grid) {
				for (auto &cell : row) {
					cell.tickCell();
				}
			}
		}

		window.clear();

		for (auto &row : grid) {
			for (auto &cell : row) {
				cell.drawCell(window);
			}
		}

		window.display();
	}

}

void tickGrid(std::vector<std::vector<Cell>> &grid)
{
	const int offsets[8][2] = { { -1, -1 },{ -1, 0 },{ -1, 1 },{ 0, -1 },{ 0, 1 },{ 1, -1 },{ 1, 0 },{ 1, 1 } };

	for (int row = 0; row < GRIDSIZE; row++) {
		for (int col = 0; col < GRIDSIZE; col++) {
			int current_neighbors = 0;
			for (auto offset : offsets) {
				current_neighbors += getCell(grid, col + offset[0], row + offset[1]).cellstate;
			}
			grid[row][col].neighbors = current_neighbors;
		}
	}
}

Cell& getCell(std::vector<std::vector<Cell>> &grid, int x, int y) {

	// Check if in range
	if (x < 0) {
		x = GRIDSIZE - 1;
	}
	if (x >= GRIDSIZE) {
		x = 0;
	}
	if (y < 0) {
		y = GRIDSIZE - 1;
	}
	if (y >= GRIDSIZE) {
		y = 0;
	}

	return grid[y][x];

}