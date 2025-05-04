#include "quadtree.h"

// initializes the quadtree node
QuadTreeNode::QuadTreeNode(float x, float y, float width, float height, int capacity)
{
	node_x = x;
	node_y = y;
	node_width = width;
	node_height = height;

	node_capacity = capacity;

	topLeft = nullptr;
	topRight = nullptr;
	bottomLeft = nullptr;
	bottomRight = nullptr;
}

// destructor for deleting quadtree node
QuadTreeNode::~QuadTreeNode()
{
	delete topLeft;
	delete topRight;
	delete bottomLeft;
	delete bottomRight;
}

// inserts a point into the quadtree
bool QuadTreeNode::quad_insert(Point p)
{
	// if  point is not within the bounds of node, return false.
	// "contains" function checks against node_x,y,height,wdith
	// for example, the "contains" function runs and checks if point p is within bounds
	// if it is, true is returned and the ! flips it to false, so the if statement does not return false (implying that point is within bounds)
	// if it is not, then contains returns false because it is not, and if statement is carried out
	if (!contains(p))
	{
		return false;
	}

	// if number of points in node is less than capacity, add point to node
	if (points.size() < node_capacity)
	{
		points.push_back(p);
		return true;
	}

	// if node is leaf node, subdivide 

	if (topLeft == nullptr)
	{
		subdivide();


		// make sure that the initial points that are placed are set to correct quadrant and not part of the root node
		vector<Point> oldPoints = points;
		points.clear(); // clear the root node points

		for (Point oldPoint : oldPoints)
		{
			// insert each point into the subdivided structure, similar to insert below
			if (topLeft->quad_insert(oldPoint))
				continue;
			if (topRight->quad_insert(oldPoint))
				continue;
			if (bottomLeft->quad_insert(oldPoint))
				continue;
			if (bottomRight->quad_insert(oldPoint))
				continue;
		}
	}

	// try inserting into different nodes, the contains function will run and select the right node to insert into
	// if not, the contain function returns false and these if statements wont run
	// if one returns true, that means it has either been added to a node because there was capacity
	if (topLeft->quad_insert(p))
		return true;
	if (topRight->quad_insert(p))
		return true;
	if (bottomLeft->quad_insert(p))
		return true;
	if (bottomRight->quad_insert(p))
		return true;

	// point could not be inserted into any of the child nodes, return false
	return false;
}

// subdivide
void QuadTreeNode::subdivide()
{
	float halfWidth = node_width / 2;
	float halfHeight = node_height / 2;

	topLeft = new QuadTreeNode(node_x, node_y, halfWidth, halfHeight, node_capacity);
	topRight = new QuadTreeNode(node_x + halfWidth, node_y, halfWidth, halfHeight, node_capacity);
	bottomLeft = new QuadTreeNode(node_x, node_y + halfHeight, halfWidth, halfHeight, node_capacity);
	bottomRight = new QuadTreeNode(node_x + halfWidth, node_y + halfHeight, halfWidth, halfHeight, node_capacity);
}

// check if node contains point
bool QuadTreeNode::contains(Point p)
{
	return (p.x >= node_x && p.x < node_x + node_width && p.y >= node_y && p.y < node_y + node_height);
}

// query for points in a range
vector<Point> QuadTreeNode::query(float rangeX, float rangeY, float rangeWidth, float rangeHeight)
{

	vector<Point> pointsInRange;

	// if the range doesnt contain node, return empty vector
	if (!intersects(rangeX, rangeY, rangeWidth, rangeHeight))
	{
		return pointsInRange;
	}

	// if points in this node are within range
	for (Point p : points)
	{
		if (p.x >= rangeX && p.x < rangeX + rangeWidth && p.y >= rangeY && p.y < rangeY + rangeHeight)
		{
			pointsInRange.push_back(p); // add points to vector that displays what points are in range
		}
	}

	// node is not a leaf node, query child nodes
	if (topLeft != nullptr)
	{
		vector<Point> tlPoints = topLeft->query(rangeX, rangeY, rangeWidth, rangeHeight);
		pointsInRange.insert(pointsInRange.end(), tlPoints.begin(), tlPoints.end());

		vector<Point> trPoints = topRight->query(rangeX, rangeY, rangeWidth, rangeHeight);
		pointsInRange.insert(pointsInRange.end(), trPoints.begin(), trPoints.end());

		vector<Point> blPoints = bottomLeft->query(rangeX, rangeY, rangeWidth, rangeHeight);
		pointsInRange.insert(pointsInRange.end(), blPoints.begin(), blPoints.end());

		vector<Point> brPoints = bottomRight->query(rangeX, rangeY, rangeWidth, rangeHeight);
		pointsInRange.insert(pointsInRange.end(), brPoints.begin(), brPoints.end());
	}

	return pointsInRange;
}


// check if range intersects with node
bool QuadTreeNode::intersects(float rangeX, float rangeY, float rangeWidth, float rangeHeight)
{

	return !(rangeX > node_x + node_width || rangeX + rangeWidth < node_x || rangeY > node_y + node_height || rangeY + rangeHeight < node_y);
};
