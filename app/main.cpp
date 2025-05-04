#include "../code/quadtree.cpp"
#include <iostream>
#include <random>

using namespace std;

int main() {
    // Create a quadtree with bounds (0, 0, 1000, 1000) and a capacity of 4
    QuadTreeNode* qt = new QuadTreeNode(0, 0, 1000, 1000, 4);


    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dist(0.0f, 1000.0f);

    
    cout << "Inserting uniformly distributed points..." << endl;
    for (int i = 0; i < 100; i++) {
        Point p = {dist(gen), dist(gen)};
        qt->quad_insert(p);
    }
    
    
    
    /* Insert some points
    qt->quad_insert({10, 10});
    cout << qt->points.size() << endl; 

    qt->quad_insert({20, 20});
    cout << qt->points.size() << endl;

    qt->quad_insert({30, 30});
    cout << qt->points.size() << endl;

    qt->quad_insert({40, 40});
    cout << qt->points.size() << endl;

    qt->print(200);

    for (int i = 0; i < qt->node_capacity; i++) {
      cout << qt->points[i].x << " " << qt->points[i].y << endl;
    }

    qt->quad_insert({50, 50});
    cout << qt->points.size() << endl;

    qt->quad_insert({60, 60});
    cout << qt->points.size() << endl;

    qt->quad_insert({70, 70});
    cout << qt->points.size() << endl;

    qt->quad_insert({80, 80});
    cout << qt->points.size() << endl;

    qt->quad_insert({85, 85});
    cout << qt->points.size() << endl;

    for (int i = 0; i < qt->node_capacity; i++) {
      cout << qt->points[i].x << " " << qt->points[i].y << endl;
    }

    */




    // Query for points within range (15, 15, 600, 600)
    vector<Point> pointsInRange = qt->query(15, 15, 600, 600);

    // Print the points within range
    cout << "Points in range (15, 15, 600, 600):" << endl;
    
    int cursor = 0;

    for (Point p : pointsInRange) {        
        cursor++;            
        cout << "(" << p.x << ", " << p.y << ")" << endl;
        cout << "There are " << cursor << " points in range" << endl;

        
    }

    delete qt;

    return 0;
}