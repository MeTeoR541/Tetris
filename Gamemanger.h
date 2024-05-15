#pragma once
# include <iostream>
# include <vector>
using namespace std;
class coordinate {
public:
	coordinate() {	
	}
	void set(int x, int y) {
		this->x = x;
		this->y = y;
	}
	int extract_x() { return x; }
	int extract_y() { return y; }
private:
	int x;
	int y;
};
class block {
public:
	block(int type, int center_x, int center_y, int num);
	void change_map(int** map);
	int block_num;
	int center_x;
	int center_y;
	int type;
	vector<coordinate> location;
};