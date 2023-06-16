#ifndef __PROGTEST__
#include <algorithm>
#include <assert.h>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

using pos = pair<int,int>;

class CPos {
public:
    CPos(int y, int x, int hour)
            : m_hour(hour), m_posY(y), m_posX(x)
    {
    }

    int m_hour;
    int m_posY;
    int m_posX;
};
#endif /* __PROGTEST__ */

class CBattleRoyale {
public:
    CBattleRoyale(unsigned height, unsigned width, const std::list<CPos> &zones) {
        for(int y = 0 ; y < height ; ++y ){
            for(int x = 0 ; x < width ; ++x){
                pos vertex = {y,x};
                //up
                if(y -1 >= 0){
                    _graph[vertex].insert({y-1,x});
                }
                //down
                if(y + 1 < height){
                    _graph[vertex].insert({y+1,x});
                }
                //left
                if(x - 1 >= 0){
                    _graph[vertex].insert({y,x-1});
                }
                //right
                if(x + 1 < width){
                    _graph[vertex].insert({y,x+1});
                }
            }
        }
        for(const auto &zone : zones){
            _forbidden[{zone.m_posY,zone.m_posX}] = zone.m_hour;
        }
    }

    unsigned findRoute(int ySt, int xSt, int yEn, int xEn) const {
        pos start = {ySt,xSt};
        pos end = {yEn,xEn};

        queue<pos> q;
        set<pos> visited;
        unsigned distance = 0;
        int toSearch;

        if(_forbidden.count(start) != 0 && _forbidden.at(start) == 0){
            throw logic_error("Start is forbidden");
        }

        if(start == end){
            return distance;
        }

        if(_graph.count(start) == 0 || _graph.count(end) == 0){
            throw logic_error("out of range");
        }

        q.push(start);
        visited.insert(start);
        toSearch = q.size();

        while(!q.empty()){
            if(toSearch == 0){
                distance++;
                toSearch = q.size();
            }
            auto current = q.front();
            q.pop();
            if(_graph.count(current) == 0){
                continue;
            }
            for(const auto &neighbor : _graph.at(current)){
                if(visited.count(neighbor) == 0 && (_forbidden.count(neighbor) == 0 || distance +1 < _forbidden.at(neighbor))){
                    if(neighbor == end){
                        return distance + 1;
                    }
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
            toSearch--;
        }
        throw logic_error("Path not found");
    }


private:
    map<pos,set<pos>> _graph;
    map<pos,int> _forbidden;
};

#ifndef __PROGTEST__
int main() {
    CBattleRoyale r1(5, 5, {});
    assert(r1.findRoute(0, 0, 4, 0) == 4);
    assert(r1.findRoute(4, 4, 4, 4) == 0);

    CBattleRoyale r2(6, 7, {CPos(1, 0, 1), CPos(2, 1, 2), CPos(3, 2, 5)});
    assert(r2.findRoute(0, 0, 4, 0) ==  10);


    CBattleRoyale r3(8, 8, {CPos(0, 2, 1), CPos(3, 1, 2), CPos(2, 1, 0)});
    try {
        r3.findRoute(2, 1, 4, 7);
        assert("Exception missing!" == nullptr);
    } catch (const logic_error &e) {
    } catch (...) {
        assert("Invalid exception thrown!" == nullptr);
    }
    assert(r3.findRoute(0,2,3,0)==5);

    CBattleRoyale b(5,5,{CPos(0,1,1),CPos(1,1,0)});
    assert(b.findRoute(0,0,2,2)==4);
    assert(b.findRoute(0,0,0,2)==6);
    assert(b.findRoute(3,3,3,3)==0);
    try{
        assert(b.findRoute(1,1,2,1)==1);
        assert("Kde vyjimka?"==nullptr);
    } catch (logic_error & x){}
    try{
        assert(b.findRoute(1,1,1,1)==0);
        assert("Kde vyjimka? xd"==nullptr);
    } catch (logic_error & x){}

    CBattleRoyale b1(5,5,{CPos(2,0,2), CPos(2,1,1),CPos(2,2,1), CPos(2,3,3),CPos(2,4,4)});
    try{
        b1.findRoute(1,1,3,1);
        assert("Kde vyjimka?"==nullptr);
    } catch (logic_error & x){}


}
#endif /* __PROGTEST__ */

