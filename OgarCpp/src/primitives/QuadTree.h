#pragma once

#include "Rect.h"
#include <string>

using namespace std;

class QuadNode;
class QuadItem : public Point {
public:
	QuadNode* root;
	Rect& range;
	QuadItem(const double x, const double y, Rect& range) : 
		Point(x, y), range(range), root(nullptr) {};
};

class QuadTree {
	friend ostream& operator<<(ostream& stream, QuadTree& quad);
private:
	QuadNode* root;
	int maxLevel;
	int maxItem;
public:
	QuadTree(Rect& range, int maxLevel, int maxItem);
	~QuadTree();
	void insert(QuadItem*);
	void update(QuadItem*);
	void remove(QuadItem*);
	void search(Rect&, void(callback)(QuadItem*));
	bool containAny(Rect&, bool(selector)(QuadItem*));
};