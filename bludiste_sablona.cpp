#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <cassert>

using namespace std;
using point = pair<int,int>;
using mazeMap = vector<vector<int>>;

class Maze{
public:
    void loadMaze(const vector<vector<int>> &maze);

    list<point> findMaze(const pair<int,int> &start, const pair<int,int> &end)const;
private:
  //todo
};

void Maze::loadMaze(const vector<vector<int>> & maze) {
  //todo
}

list <point> Maze::findMaze(const pair<int,int> &start, const pair<int,int> &end)const {
//todo
}

int main(){

    Maze m;

    mazeMap m1= {{1,1,1,1},
                 {1,0,1,0},
                 {1,1,1,1}};
    point start ={0,0};
    point end = {0,3};
    m.loadMaze(m1);
    auto res = m.findMaze(start,end);
    assert(res == list<point>({{0,0},{0,1},{0,2},{0,3}}));

    Maze m2;
    mazeMap m2m = {{1,1,0,0},
                   {0,1,1,1},
                   {0,1,0,1}};
    start ={0,0};
    end = {2,3};
    m2.loadMaze(m2m);
    res = m2.findMaze(start,end);
    assert(res == list<point>({{0,0},{0,1},{1,1},{1,2},{1,3},{2,3}}));

    Maze m3;

    mazeMap m3m ={
            {1,1,1,0,1,1,0,1,1,1,1,1,1,0},
            {1,0,1,0,1,0,0,0,0,1,0,1,0,1},
            {0,0,1,0,1,0,1,1,1,1,1,1,0,1},
            {1,0,1,0,1,0,0,0,0,0,0,0,0,0},
            {1,1,1,0,1,1,1,1,1,1,1,1,0,1},
            {1,0,1,0,0,0,0,0,0,0,0,0,0,1},
            {0,0,1,1,1,0,1,1,1,1,1,1,0,1},
            {1,0,0,0,1,0,1,0,1,0,0,0,0,1},
            {1,1,1,1,1,1,1,0,1,1,1,1,1,1}
    };

    start ={0,1};
    end = {6,13};

    m3.loadMaze(m3m);
    res = m3.findMaze(start,end);
    assert(res == list<point>({{0,1},{0,2},{1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{6,3},{6,4},{7,4},{8,4},{8,5},{8,6},
                               {7,6},{6,6},{6,7},{6,8},{7,8},{8,8},{8,9},{8,10},{8,11},{8,12},{8,13},{7,13},{6,13}}));

    start = {20,20};
    end = {0,0};
    try{
        res = m3.findMaze(start,end);
        assert(false);
    }catch (std::out_of_range &e){
        assert(true);
    }

    start = {0,0};
    end = {0,12};
    try{
        res = m3.findMaze(start, end);
        assert(false);
    }
    catch (std::logic_error &er){
        assert(true);
    }

    start = {0,0};
    end = {0,13};

    try{
        res = m3.findMaze(start, end);
        assert(false);
    }
    catch (std::out_of_range &er){
        assert(true);
    }
    
    return 0;
}
