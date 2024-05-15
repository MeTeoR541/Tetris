#include "Tetris.h"

Tetris::Tetris(QWidget *parent) :QWidget(parent) {
	this->setMinimumWidth(320);
	this->setMinimumHeight(640);
	this->setMaximumWidth(320);
	this->setMaximumHeight(640);
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(500);
	for (int i = 0; i < map_height; ++i) {
		for (int j = 0; j < map_width; ++j) {
			map[i][j] = 0;
		}
	}
	num = 1;
	now_block = new block(rand() % 5, rand() % 12 + 2, 1, 1);
	map[now_block->center_y][now_block->center_x] = now_block->block_num;
	map[now_block->location[0].extract_y()][now_block->location[0].extract_x()] = now_block->block_num;
	map[now_block->location[1].extract_y()][now_block->location[1].extract_x()] = now_block->block_num;
	map[now_block->location[2].extract_y()][now_block->location[2].extract_x()] = now_block->block_num;
	num++;
}

Tetris::~Tetris()
{
}
void Tetris::paintEvent(QPaintEvent*) {
	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing);
	

	for (int i = 0; i < map_height; ++i) {
		for (int j = 0; j < map_width; ++j) {
			if (map[i][j] != 0) {
				int color = map[i][j] * 10;
				if (color > 255)
					color = (color - 255) % 256;
				else
					color = (255 - color) % 256;
				QBrush brush(QColor(color, color, color));
				QPen pen(QColor(0, 0, 0));
				painter.setBrush(brush);
				painter.setPen(pen);
				painter.drawRect(j * 20, i * 20, 20, 20);
			}
		}
	}
	land();
	checkLine();
}

void Tetris::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key_Backspace) 
		while (land());
	else if (event->key() == Qt::Key_Left) {
		if (now_block->center_x != 0 && now_block->location[0].extract_x() != 0 && now_block->location[1].extract_x() != 0 && now_block->location[2].extract_x() != 0) {
			if (map[now_block->center_y][now_block->center_x - 1] == 0 || map[now_block->center_y][now_block->center_x - 1] == now_block->block_num) {
				if (map[now_block->location[0].extract_y()][now_block->location[0].extract_x() - 1] == 0 || map[now_block->location[0].extract_y()][now_block->location[0].extract_x() - 1] == now_block->block_num) {
					if (map[now_block->location[1].extract_y()][now_block->location[1].extract_x() - 1] == 0 || map[now_block->location[1].extract_y()][now_block->location[1].extract_x() - 1] == now_block->block_num) {
						if (map[now_block->location[2].extract_y()][now_block->location[2].extract_x() - 1] == 0 || map[now_block->location[2].extract_y()][now_block->location[2].extract_x() - 1] == now_block->block_num) {
							map[now_block->center_y][now_block->center_x] = 0;
							map[now_block->location[0].extract_y()][now_block->location[0].extract_x()] = 0;
							map[now_block->location[1].extract_y()][now_block->location[1].extract_x()] = 0;
							map[now_block->location[2].extract_y()][now_block->location[2].extract_x()] = 0;
							map[now_block->center_y][now_block->center_x - 1] = now_block->block_num;
							map[now_block->location[0].extract_y()][now_block->location[0].extract_x() - 1] = now_block->block_num;
							map[now_block->location[1].extract_y()][now_block->location[1].extract_x() - 1] = now_block->block_num;
							map[now_block->location[2].extract_y()][now_block->location[2].extract_x() - 1] = now_block->block_num;
							now_block->center_x -= 1;
							now_block->location[0].set(now_block->location[0].extract_x() - 1, now_block->location[0].extract_y());
							now_block->location[1].set(now_block->location[1].extract_x() - 1, now_block->location[1].extract_y());
							now_block->location[2].set(now_block->location[2].extract_x() - 1, now_block->location[2].extract_y());
						}
					}
				}
			}
		}
	}
	else if (event->key() == Qt::Key_Right) {
		if (now_block->center_x != 15 && now_block->location[0].extract_x() != 15 && now_block->location[1].extract_x() != 15 && now_block->location[2].extract_x() != 15) {
			if (map[now_block->center_y][now_block->center_x + 1] == 0 || map[now_block->center_y][now_block->center_x + 1] == now_block->block_num) {
				if (map[now_block->location[0].extract_y()][now_block->location[0].extract_x() + 1] == 0 || map[now_block->location[0].extract_y()][now_block->location[0].extract_x() + 1] == now_block->block_num) {
					if (map[now_block->location[1].extract_y()][now_block->location[1].extract_x() + 1] == 0 || map[now_block->location[1].extract_y()][now_block->location[1].extract_x() + 1] == now_block->block_num) {
						if (map[now_block->location[2].extract_y()][now_block->location[2].extract_x() + 1] == 0 || map[now_block->location[2].extract_y()][now_block->location[2].extract_x() + 1] == now_block->block_num) {
							map[now_block->center_y][now_block->center_x] = 0;
							map[now_block->location[0].extract_y()][now_block->location[0].extract_x()] = 0;
							map[now_block->location[1].extract_y()][now_block->location[1].extract_x()] = 0;
							map[now_block->location[2].extract_y()][now_block->location[2].extract_x()] = 0;
							map[now_block->center_y][now_block->center_x + 1] = now_block->block_num;
							map[now_block->location[0].extract_y()][now_block->location[0].extract_x() + 1] = now_block->block_num;
							map[now_block->location[1].extract_y()][now_block->location[1].extract_x() + 1] = now_block->block_num;
							map[now_block->location[2].extract_y()][now_block->location[2].extract_x() + 1] = now_block->block_num;
							now_block->center_x += 1;
							now_block->location[0].set(now_block->location[0].extract_x() + 1, now_block->location[0].extract_y());
							now_block->location[1].set(now_block->location[1].extract_x() + 1, now_block->location[1].extract_y());
							now_block->location[2].set(now_block->location[2].extract_x() + 1, now_block->location[2].extract_y());
						}
					}
				}
			}
		}
	}

	else if (event->key() == Qt::Key_Up) {
		if (now_block->type != 3) {
			if (now_block->type == 4) {
				switch (now_block->state) {
				case 0:
					map[now_block->location[0].extract_y()][now_block->location[0].extract_x()] = 0;
					map[now_block->location[1].extract_y()][now_block->location[1].extract_x()] = 0;
					map[now_block->location[2].extract_y()][now_block->location[2].extract_x()] = 0;
			
					map[now_block->location[0].extract_y() + 1][now_block->location[0].extract_x() + 1] = now_block->block_num;
					map[now_block->location[1].extract_y() - 1][now_block->location[1].extract_x() + 1] = now_block->block_num;
					map[now_block->location[2].extract_y() - 1][now_block->location[2].extract_x() - 1] = now_block->block_num;
				
					now_block->location[0].set(now_block->location[0].extract_x() + 1, now_block->location[0].extract_y() + 1);
					now_block->location[1].set(now_block->location[1].extract_x() + 1, now_block->location[1].extract_y() - 1);
					now_block->location[2].set(now_block->location[2].extract_x() - 1, now_block->location[2].extract_y() - 1);
					++now_block->state;
					break;
				case 1:
					map[now_block->location[0].extract_y()][now_block->location[0].extract_x()] = 0;
					map[now_block->location[1].extract_y()][now_block->location[1].extract_x()] = 0;
					map[now_block->location[2].extract_y()][now_block->location[2].extract_x()] = 0;

					map[now_block->location[0].extract_y() - 1][now_block->location[0].extract_x() + 1] = now_block->block_num;
					map[now_block->location[1].extract_y() - 1][now_block->location[1].extract_x() - 1] = now_block->block_num;
					map[now_block->location[2].extract_y() + 1][now_block->location[2].extract_x() - 1] = now_block->block_num;

					now_block->location[0].set(now_block->location[0].extract_x() + 1, now_block->location[0].extract_y() - 1);
					now_block->location[1].set(now_block->location[1].extract_x() - 1, now_block->location[1].extract_y() - 1);
					now_block->location[2].set(now_block->location[2].extract_x() - 1, now_block->location[2].extract_y() + 1);
					++now_block->state;
					break;
				case 2:
					map[now_block->location[0].extract_y()][now_block->location[0].extract_x()] = 0;
					map[now_block->location[1].extract_y()][now_block->location[1].extract_x()] = 0;
					map[now_block->location[2].extract_y()][now_block->location[2].extract_x()] = 0;

					map[now_block->location[0].extract_y() - 1][now_block->location[0].extract_x() - 1] = now_block->block_num;
					map[now_block->location[1].extract_y() + 1][now_block->location[1].extract_x() - 1] = now_block->block_num;
					map[now_block->location[2].extract_y() + 1][now_block->location[2].extract_x() + 1] = now_block->block_num;

					now_block->location[0].set(now_block->location[0].extract_x() - 1, now_block->location[0].extract_y() - 1);
					now_block->location[1].set(now_block->location[1].extract_x() - 1, now_block->location[1].extract_y() + 1);
					now_block->location[2].set(now_block->location[2].extract_x() + 1, now_block->location[2].extract_y() + 1);
					++now_block->state;
					break;
				case 3:
					map[now_block->location[0].extract_y()][now_block->location[0].extract_x()] = 0;
					map[now_block->location[1].extract_y()][now_block->location[1].extract_x()] = 0;
					map[now_block->location[2].extract_y()][now_block->location[2].extract_x()] = 0;

					map[now_block->location[0].extract_y() + 1][now_block->location[0].extract_x() - 1] = now_block->block_num;
					map[now_block->location[1].extract_y() + 1][now_block->location[1].extract_x() + 1] = now_block->block_num;
					map[now_block->location[2].extract_y() - 1][now_block->location[2].extract_x() + 1] = now_block->block_num;

					now_block->location[0].set(now_block->location[0].extract_x() - 1, now_block->location[0].extract_y() + 1);
					now_block->location[1].set(now_block->location[1].extract_x() + 1, now_block->location[1].extract_y() + 1);
					now_block->location[2].set(now_block->location[2].extract_x() + 1, now_block->location[2].extract_y() - 1);
					now_block->state = 0;
					break;
				}
			}
			else if (now_block->type == 1) {
				switch (now_block->state) {
				case 0:
					++now_block->state;
					break;
				case 1:
					++now_block->state;
					break;
				case 2:
					++now_block->state;
					break;
				case 3:
					now_block = 0;
					break;
				}
			}
		}
	}
	update();
}

bool Tetris::land() {

	if (now_block->center_y + 1 < 32&&(map[now_block->center_y + 1][now_block->center_x] == 0 || map[now_block->center_y + 1][now_block->center_x] == now_block->block_num)) {
		if (now_block->location[0].extract_y() + 1 < 32&&(map[now_block->location[0].extract_y() + 1][now_block->location[0].extract_x()] == 0 || map[now_block->location[0].extract_y() + 1][now_block->location[0].extract_x()] == now_block->block_num)) {
			if (now_block->location[1].extract_y() + 1 < 32&&(map[now_block->location[1].extract_y() + 1][now_block->location[1].extract_x()] == 0 || map[now_block->location[1].extract_y() + 1][now_block->location[1].extract_x()] == now_block->block_num)) {
				if (now_block->location[2].extract_y() + 1 < 32&&(map[now_block->location[2].extract_y() + 1][now_block->location[2].extract_x()] == 0 || map[now_block->location[2].extract_y() + 1][now_block->location[2].extract_x()] == now_block->block_num)) {
					map[now_block->center_y][now_block->center_x] = 0;
					map[now_block->location[0].extract_y()][now_block->location[0].extract_x()] = 0;
					map[now_block->location[1].extract_y()][now_block->location[1].extract_x()] = 0;
					map[now_block->location[2].extract_y()][now_block->location[2].extract_x()] = 0;
					map[now_block->center_y + 1][now_block->center_x] = now_block->block_num;
					map[now_block->location[0].extract_y() + 1][now_block->location[0].extract_x()] = now_block->block_num;
					map[now_block->location[1].extract_y() + 1][now_block->location[1].extract_x()] = now_block->block_num;
					map[now_block->location[2].extract_y() + 1][now_block->location[2].extract_x()] = now_block->block_num;
					now_block->center_y += 1;
					now_block->location[0].set(now_block->location[0].extract_x(), now_block->location[0].extract_y() + 1);
					now_block->location[1].set(now_block->location[1].extract_x(), now_block->location[1].extract_y() + 1);
					now_block->location[2].set(now_block->location[2].extract_x(), now_block->location[2].extract_y() + 1);
					return true;
				}
				else
					return arrive();
			}
			else
				return arrive();
		}
		else
			return arrive();
	}
	else
		return arrive();
}

bool Tetris::arrive() {
	delete now_block;
	now_block = new block(rand() % 5, rand() % 12 + 2, 1, num);
	map[now_block->center_y][now_block->center_x] = now_block->block_num;
	map[now_block->location[0].extract_y()][now_block->location[0].extract_x()] = now_block->block_num;
	map[now_block->location[1].extract_y()][now_block->location[1].extract_x()] = now_block->block_num;
	map[now_block->location[2].extract_y()][now_block->location[2].extract_x()] = now_block->block_num;
	num++;
	return false;
}
void Tetris::checkLine() {
	bool test_loop = true;
	int now_height = 31;
	while (test_loop) {
		int i;
		for (i = 0; i < map_width; ++i) {
			if (map[i][now_height] == 0)
				break;
		}
		if (i == map_width) {
			for (int k = now_height; k > 0; --k) {
				int temp = 0;
				for (int j = 0; j < map_width; ++j) {
					map[k][j] = map[k - 1][j];
					if (map[k - 1][j] == 0)
						temp++;
				}
				if (temp == map_width)
					break;
			}
			continue;
		}
		int check;
		for (check = 0; check < map_width; ++check) {
			if (map[check][now_height] != 0)
				break;
		}
		if (check == map_width)
			test_loop = false;
		--now_height;
	}
}