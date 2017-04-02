#pragma once

#include <stdarg.h>
#include "resource\ResourceLocator.h"
#include "generic/data/byte.h"
using namespace std;

byte values[] = { 0, 84, 169, 255 };
byte
black = values[0],
darkGray = values[1],
liteGray = values[2],
white = values[3];

template <typename T>
class Grid {
	public:
	Grid(int width, int height, ...) {
		int n = width*height;
		this->width = width;
		this->height = height;

		grid = new T[n];

		va_list ap;
		va_start(ap, n);
		for (int i = 0; i < n; i++) {
			grid[i] = va_arg(ap, T);
		}
		va_end(ap);
	}

	Grid(int width, int height, T *data) {
		int n = width*height;
		this->width = width;
		this->height = height;

		grid = new T[n];

		for (int i = 0; i < n; i++) {
			grid[i] = data[i];
		}
	}

	T get(int x, int y) { return grid[y*width + x]; }
	void set(int x, int y, T value) { grid[y*width + x] = value; }
	int getWidth() { return width; }
	int getHeight() { return height; }

	private:
	int width, height;
	T *grid;
};

class Form {
	public:
	Form(Grid<bool> *grid) {
		this->grid = grid;
	}

	bool get(int x, int y) { return grid->get(x, y); }
	int getWidth() { return grid->getWidth(); }
	int getHeight() { return grid->getHeight(); }

	private:
	Grid<bool> *grid;
};

class Tetronimo {
	public:
	Tetronimo(byte blockType, int formCount, Form *forms[]) {
		this->blockType = blockType;
		this->formCount = formCount;
		this->forms = forms;
	}

	byte getBlockType() {
		return blockType;
	}

	int getFormCount() {
		return formCount;
	}

	Form* getForm(int i) {
		return forms[i];
	}

	private:
	byte blockType;
	int formCount;
	Form **forms;
};

// Define Tetronimoes.
Tetronimo **tetronimoes = new Tetronimo*[7];

class Tetris {
	public:
	Tetris() {
		//TODO: Go back to using ... .

		// Block.
		tetronimoes[0] = new Tetronimo(1, 1,
									   new Form*[1]{
										   new Form(new Grid<bool>(2, 2, new bool[4] {true, true, true, true}))
		}
		);

		// Z
		tetronimoes[1] = new Tetronimo(2, 2,
									   new Form*[2]{
										   new Form(new Grid<bool>(3, 2, new bool[6] {true, true, false, false, true, true})),
										   new Form(new Grid<bool>(2, 3, new bool[6] {false, true, true, true, true, false}))
		}
		);

		// Reverse-L
		tetronimoes[2] = new Tetronimo(3, 4,
									   new Form*[4]{
										   new Form(new Grid<bool>(3, 3, new bool[9] {
												0, 0, 0,
												1, 1, 1,
												0, 0, 1
											})),
										   new Form(new Grid<bool>(3, 3, new bool[9]{
												0, 1, 1,
												0, 1, 0,
												0, 1, 0
											})),
										   new Form(new Grid<bool>(3, 3, new bool[9]{
												1, 0, 0,
												1, 1, 1,
												0, 0, 0
											})),
										   new Form(new Grid<bool>(3, 3, new bool[9]{
												0, 1, 0,
												0, 1, 0,
												1, 1, 0
											}))
		}
		);

		// S
		tetronimoes[3] = new Tetronimo(4, 2,
									   new Form*[2]{
										   new Form(new Grid<bool>(3, 2, new bool[6] {false, true, true, true, true, false})),
										   new Form(new Grid<bool>(2, 3, new bool[6]{ true, false, true, true, false, true })),
		}
		);

		// L
		tetronimoes[4] = new Tetronimo(5, 4,
									   new Form*[4]{
										   new Form(new Grid<bool>(3, 3, new bool[9] {
												0, 0, 0,
												1, 1, 1,
												1, 0, 0
											})),
										   new Form(new Grid<bool>(3, 3, new bool[9]{
												0, 1, 0,
												0, 1, 0,
												0, 1, 1
											})),
										   new Form(new Grid<bool>(3, 3, new bool[9]{
												0, 0, 1,
												1, 1, 1,
												0, 0, 0
											})),
										   new Form(new Grid<bool>(3, 3, new bool[9]{
												1, 1, 0,
												0, 1, 0,
												0, 1, 0
											}))
		}
		);

		// T
		tetronimoes[5] = new Tetronimo(6, 4,
									   new Form*[4]{
										   new Form(new Grid<bool>(3, 3, new bool[9] {
												0, 0, 0,
												1, 1, 1,
												0, 1, 0
											})),
										   new Form(new Grid<bool>(3, 3, new bool[9]{ 
   												0, 1, 0,
												0, 1, 1,
												0, 1, 0
											})),
										   new Form(new Grid<bool>(3, 3, new bool[9]{
												0, 1, 0,
												1, 1, 1,
												0, 0, 0
											})),
										   new Form(new Grid<bool>(3, 3, new bool[9]{
												0, 1, 0,
												1, 1, 0,
												0, 1, 0
										   })),
		}
		);

		// |
		tetronimoes[6] = new Tetronimo(7, 2,
									   new Form*[2]{
										   new Form(new Grid<bool>(4, 1, new bool[4] {true, true, true, true})),
										   new Form(new Grid<bool>(1, 4, new bool[4]{ true, true, true, true }))
		}
		);


		srand(time(NULL));

		grid = new Grid<byte>(10, 20);

		for (int y = 0; y < grid->getHeight(); y++) {
			for (int x = 0; x < grid->getWidth(); x++) {
				grid->set(x, y, 0);
			}
		}

		spawnBlock();
	}
	~Tetris() {
		delete grid;
	}

	void control(int key) {
		switch (key) {
			case GLFW_KEY_A:
				moveBlock(-1, 0);
				break;
			case GLFW_KEY_S:
				moveBlock(0, 1);
				break;
			case GLFW_KEY_D:
				moveBlock(1, 0);
				break;

			case GLFW_KEY_Q:
				rotate(1);
				break;
			case GLFW_KEY_E:
				rotate(-1);
				break;
		}
	}

	void tick() {
		if (tTimer-- == 0) {
			moveBlock(0, 1);
		}
		/*else if (tTimer == tTimerMax / 2) {
			int r;
			r = (rand() % 3) - 1;

			if (r != 0) {
				moveBlock(r, 0);
			} else {
				r = (rand() % 3) - 1;
				rotate(r);
			}
		}*/
	}

	void draw() {
		for (int y = 0; y < grid->getHeight(); y++) {
			for (int x = 0; x < grid->getWidth(); x++) {
				drawBlock(x, y, grid->get(x, y));
			}
		}
	}

	private:
	void drawBlock(int x, int y, byte blockType) {
		IGraphics *g = ResourceLocator::get()->getGraphics();
		IGraphicsPrimitive *gp = g->getGraphicsPrimitive();
		IGraphics2D *g2d = g->getGraphics2D();

		int blockSize = pixelSize * gridSize;

		int val = (blockType == 3) ? liteGray : darkGray;

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
				gp->color4b(darkGray, darkGray, darkGray, 1);
				g2d->fillRectangle(x*blockSize + 1 * pixelSize, y*blockSize + 1 * pixelSize, blockSize - 2 * pixelSize, blockSize - 2 * pixelSize);
				break;

			case 6:
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

	int pixelSize = 2, gridSize = 8;
	Grid<byte> *grid;

	int tX, tY, tTimerMax = 1000, tTimer = tTimerMax, tF = 0;
	Tetronimo *t;

	void spawnBlock() {
		tX = grid->getWidth() / 2;
		tY = 0;
		tTimer = tTimerMax;
		tF = 0;

		int r = rand() % 7;
		t = tetronimoes[r];

		// TODO: If can't place, game over.
		if (!checkVacant()) {
		}

		stamp(true);
	}

	void clearLines() {
		Form *f = t->getForm(tF);

		int h = f->getHeight();

		// Check if lines are full.
		bool *lines = new bool[h];
		for (int i = 0; i < h; i++) {
			lines[i] = true;

			for (int x = 0; x < grid->getWidth(); x++) {
				lines[i] = lines[i] && (grid->get(x, tY + i) != 0);
			}
		}

		// Copy lines down.
		for (int i = h - 1; i >= 0; i--) {
			if (lines[i]) {
				for (int y = tY + i; y >= 1; y--) {
					for (int x = 0; x < grid->getWidth(); x++) {
						grid->set(x, y, grid->get(x, y - 1));
					}
				}
			}
		}

		delete lines;
	}

	void moveBlock(int dX, int dY) {
		// Erase current block.
		stamp(false);

		tX += dX;
		tY += dY;

		bool isVacant = checkVacant();

		if (!isVacant) {
			tX -= dX;
			tY -= dY;
		} else {
			if (dY != 0) {
				tTimer = tTimerMax;
			}
		}

		stamp(true);

		if (!isVacant && dY != 0) {
			clearLines();
			spawnBlock();
		}
	}

	void rotate(int amt) {
		stamp(false);

		int oF = tF, fC = t->getFormCount();

		tF += amt;
		if (tF < 0) {
			tF += fC;
		} else if (tF >= fC) {
			tF -= fC;
		}

		if (!checkVacant()) {
			tF = oF;
		}

		stamp(true);
	}

	void stamp(bool place) {
		int newVal = (place) ? t->getBlockType() : 0;

		Form *f = t->getForm(tF);
		for (int y = 0; y < f->getHeight(); y++) {
			for (int x = 0; x < f->getWidth(); x++) {
				if (f->get(x, y)) {
					grid->set(tX + x, tY + y, newVal);
				}
			}
		}
	}

	bool checkVacant() {
		Form *f = t->getForm(tF);
		for (int y = 0; y < f->getHeight(); y++) {
			for (int x = 0; x < f->getWidth(); x++) {

				if (f->get(x, y)) {
					if ((tX + x) < 0 || (tX + x) >= grid->getWidth() || (tY + y) < 0 || (tY + y) >= grid->getHeight()) {
						return false;
					}

					if (grid->get(tX + x, tY + y) != 0) {
						return false;
					}
				}
			}
		}

		return true;
	}
};