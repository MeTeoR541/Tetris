#include "Gamemanger.h"
block::block(int type, int center_x, int center_y, int num) {
	this->type = type;
	this->center_x = center_x;
	this->center_y = center_y;
	this->block_num = num;
	coordinate temp;
	switch (type) {
	case 0:
		temp.set(this->center_x - 1, this->center_y);
		location.push_back(temp);
		temp.set(this->center_x - 2, this->center_y);
		location.push_back(temp);
		temp.set(this->center_x + 1, this->center_y);
		location.push_back(temp);
		break;
	case 1:
		temp.set(this->center_x - 1, this->center_y);
		location.push_back(temp);
		temp.set(this->center_x - 2, this->center_y);
		location.push_back(temp);
		temp.set(this->center_x, this->center_y + 1);
		location.push_back(temp);
		break;
	case 2:
		temp.set(this->center_x - 1, this->center_y);
		location.push_back(temp);
		temp.set(this->center_x - 1, this->center_y - 1);
		location.push_back(temp);
		temp.set(this->center_x, this->center_y + 1);
		location.push_back(temp);
		break;
	case 3:
		temp.set(this->center_x - 1, this->center_y);
		location.push_back(temp);
		temp.set(this->center_x - 1, this->center_y + 1);
		location.push_back(temp);
		temp.set(this->center_x, this->center_y + 1);
		location.push_back(temp);
		break;
	case 4:
		temp.set(this->center_x - 1, this->center_y);
		location.push_back(temp);
		temp.set(this->center_x, this->center_y + 1);
		location.push_back(temp);
		temp.set(this->center_x + 1, this->center_y);
		location.push_back(temp);
		break;
	}
}

void change_map(int** map) {
	
}