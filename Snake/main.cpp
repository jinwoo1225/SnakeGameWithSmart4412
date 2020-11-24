//
//  main.cpp
//  Snake
//
//  Created by HongJinwoo on 2020/11/24.
//

#include <iostream>
#include <vector>

using namespace std;

typedef struct coord{
    int y;
    int x;
} coord;

class Snake {
private:
    int y,x;
    int size;
    vector<coord> trail;
    
    
public:
    Snake(int y, int x){
        this->size=1;
        pushTrail( y, x);
    }
    
    void pushTrail(int y, int x){
        coord A = {y, x};
        trail.insert(trail.begin(), A);
    }
    
    vector<coord> getTrail(int size){
        vector<coord> ret;
        ret.assign(trail.begin(), trail.begin() + size);
        return ret;
    }
    

};

int main(int argc, const char * argv[]) {
    // insert code here...
    Snake s(4,4);
    s.pushTrail(5, 6);
    s.pushTrail(5, 7);
    s.pushTrail(6, 8);
    
    vector<coord> trailT = s.getTrail(3);
    
    for (coord i : trailT) {
        cout << i.y << i.x << endl;
    }
    
    return 0;
}
