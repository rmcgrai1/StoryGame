#pragma once

#include "resource\ResourceLocator.h"
#include "generic/data/byte.h"
using namespace std;

byte values[] = { 0, 84, 169, 255 };
byte
black = values[0],
darkGray = values[1],
liteGray = values[2],
white = values[3];

class Tetris {
	public:
	Tetris() {
		grid = new int[width * height];

		int i = 0;
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				grid[i++] = 0;
			}
		}
	}
	~Tetris() {
		delete grid;
	}

	void tick() {

	}

	void draw() {
		int i = 0;
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				drawBlock(x, y, grid[i++]);
			}
		}
	}

	private:
	void drawBlock(int x, int y, int blockType) {
		IGraphics *g = ResourceLocator::get()->getGraphics();
		IGraphicsPrimitive *gp = g->getGraphicsPrimitive();
		IGraphics2D *g2d = g->getGraphics2D();

		int blockSize = pixelSize * gridSize;

		int val = (blockType == 2) ? liteGray : darkGray;

		switch (blockType) {
			case 1:
				gp->color4b(black, black, black, 1);
				g2d->fillRectangle(x*blockSize, y*blockSize, blockSize, blockSize);
				gp->color4b(white, white, white, 1);
				g2d->fillRectangle(x*blockSize + 1 * pixelSize, y*blockSize + 1 * pixelSize, blockSize - 2 * pixelSize, blockSize - 2 * pixelSize);
				gp->color4b(black, black, black, 1);
				g2d->fillRectangle(x*blockSize + 2 * pixelSize, y*blockSize + 2 * pixelSize, blockSize - 4 * pixelSize, blockSize - 4 * pixelSize);
				break;

			case 2:
				gp->color4b(black, black, black, 1);
				g2d->fillRectangle(x*blockSize, y*blockSize, blockSize, blockSize);
				gp->color4b(liteGray, liteGray, liteGray, 1);
				g2d->fillRectangle(x*blockSize + 1 * pixelSize, y*blockSize + 1 * pixelSize, blockSize - 2 * pixelSize, blockSize - 2 * pixelSize);
				gp->color4b(black, black, black, 1);
				g2d->fillRectangle(x*blockSize + 3 * pixelSize, y*blockSize + 3 * pixelSize, blockSize - 6 * pixelSize, blockSize - 6 * pixelSize);
				break;

			case 3:
			case 4:
				gp->color4b(black, black, black, 1);
				g2d->fillRectangle(x*blockSize, y*blockSize, blockSize, blockSize);
				gp->color4b(val, val, val, 1);
				g2d->fillRectangle(x*blockSize + 1 * pixelSize, y*blockSize + 1 * pixelSize, blockSize - 2 * pixelSize, blockSize - 2 * pixelSize);
				gp->color4b(black, black, black, 1);
				g2d->fillRectangle(x*blockSize + 2 * pixelSize, y*blockSize + 2 * pixelSize, blockSize - 4 * pixelSize, blockSize - 4 * pixelSize);
				gp->color4b(white, white, white, 1);
				g2d->fillRectangle(x*blockSize + 3 * pixelSize, y*blockSize + 3 * pixelSize, blockSize - 6 * pixelSize, blockSize - 6 * pixelSize);
				break;

			case 5:
				gp->color4b(black, black, black, 1);
				g2d->fillRectangle(x*blockSize, y*blockSize, blockSize, blockSize);
				gp->color4b(liteGray, liteGray, liteGray, 1);
				g2d->fillRectangle(x*blockSize + 1 * pixelSize, y*blockSize + 1 * pixelSize, blockSize - 2 * pixelSize, blockSize - 2 * pixelSize);
				gp->color4b(black, black, black, 1);
				g2d->fillRectangle(x*blockSize + 2 * pixelSize, y*blockSize + 5 * pixelSize, blockSize - 4 * pixelSize, 1 * pixelSize);
				g2d->fillRectangle(x*blockSize + 5 * pixelSize, y*blockSize + 3 * pixelSize, 1 * pixelSize, 2 * pixelSize);
				gp->color4b(white, white, white, 1);
				g2d->fillRectangle(x*blockSize + 2 * pixelSize, y*blockSize + 2 * pixelSize, blockSize - 4 * pixelSize, 1 * pixelSize);
				g2d->fillRectangle(x*blockSize + 2 * pixelSize, y*blockSize + 3 * pixelSize, 1 * pixelSize, 2 * pixelSize);
				break;

			case 6:
				gp->color4b(black, black, black, 1);
				g2d->fillRectangle(x*blockSize, y*blockSize, blockSize, blockSize);
				gp->color4b(darkGray, darkGray, darkGray, 1);
				g2d->fillRectangle(x*blockSize + 1 * pixelSize, y*blockSize + 1 * pixelSize, blockSize - 2 * pixelSize, blockSize - 2 * pixelSize);
				break;

			case 7:
				gp->color4b(black, black, black, 1);
				g2d->fillRectangle(x*blockSize, y*blockSize, blockSize, blockSize);
				gp->color4b(liteGray, liteGray, liteGray, 1);
				g2d->fillRectangle(x*blockSize + 1 * pixelSize, y*blockSize + 1 * pixelSize, blockSize - 2 * pixelSize, blockSize - 2 * pixelSize);
				break;

			default:
				gp->color4d(1, 1, 1, 1);
				g2d->fillRectangle(x*blockSize, y*blockSize, blockSize, blockSize);
		}
	}

	int width = 10, height = 20, pixelSize = 2, gridSize = 8;
	int *grid;
};