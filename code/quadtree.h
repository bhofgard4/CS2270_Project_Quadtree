#ifndef QUADTREE_H__
#define QUADTREE_H__

#include <iostream>
#include <vector>

using namespace std;

// Structure to represent a point
struct Point
{
	float x;
	float y;
};

class QuadTreeNode
{
public:
	// bounding box of the node, node_x and node_y are origin location
	float node_x;
	float node_y;
	float node_width;
	float node_height;

	// max capacity of points a node can hold before subdivsion
	int node_capacity;

	// vector to store points in the node
	vector<Point> points;

	// child nodes
	QuadTreeNode *topLeft;
	QuadTreeNode *topRight;
	QuadTreeNode *bottomLeft;
	QuadTreeNode *bottomRight;

	// constructor
	QuadTreeNode(float node_x, float node_y, float node_width, float node_height, int node_capacity);

	// destructor
	~QuadTreeNode();

	// insert point
	bool quad_insert(Point p);

	// subdivide node
	void subdivide();

	// check if node contains point being passed through function
	bool contains(Point p);

	// query for points in a region
	vector<Point> query(float rangeX, float rangeY, float rangeWidth, float rangeHeight);

	// checks if the range input intersects with a node
	bool intersects(float rangeX, float rangeY, float rangeWidth, float rangeHeight);


};

#endif // QUADTREE_H__