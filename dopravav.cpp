#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <memory>
#include <cassert>

using namespace std;

class CTransport
{
public:
    void AddLine(istream &is);
    map<string, int> FindDest(const string &from, int costMax) const;

private:
    map<string,set<string>> _graph;
};
void CTransport::AddLine(istream &is)
{
    string line;
    vector<string> tmp;
    while(getline(is,line)){
        tmp.push_back(line);
    }
   if(tmp.size() > 1){
       for(int i = 1 ; i < tmp.size() ; ++ i){
           _graph[tmp[i-1]].insert(tmp[i]);
       }
       _graph[tmp[tmp.size()-1]].insert(tmp[0]);
   }
}
map<string, int> CTransport::FindDest(const string &from, int costMax) const
{
    map<string,int> visited;
    queue<string> q;
    int currentCost = 0;
    q.push(from);
    visited[from] = 0;
    int toSearch = q.size();
    if(_graph.count(from) == 0){
        return visited;
    }
    while(!q.empty()){
        if(toSearch == 0){
            toSearch = q.size();
            currentCost++;
        }
        if(currentCost == costMax){
            return visited;
        }
        auto v = q.front();
        q.pop();
        for(auto &w : _graph.at(v)){
            if(visited.count(w) == 0){
                visited[w] = currentCost+1;
                q.push(w);
            }
        }
        toSearch--;
    }
    return visited;
}

int main()
{
    istringstream iss;
    CTransport t;
    iss.clear();
    iss.str("Newton\nBlack Hill\nWood Side\nGreen Hill\nLakeside\n");
    t.AddLine(iss);
    iss.clear();
    iss.str("Great Newton\nLittle Burnside\nGreen Hill\nWood Side\n");
    t.AddLine(iss);
    iss.clear();
    iss.str("Little Newton\nLittle Burnside\nCastle Hill\nNewton Crossroad\nLakeside Central\n");
    t.AddLine(iss);
    iss.clear();
    iss.str("Tidmouth\nGordon's Hill\nSuderry\nKnapford\nGreat Waterton\nBrendam Docks\n");
    t.AddLine(iss);
    iss.clear();
    iss.str("Sodor Ironworks\nSodor Steamwork\nKnapford\nMaron\nGordon's Hill\n");
    t.AddLine(iss);
    iss.clear();
    iss.str("Lakeside Central\nLittle Waterton\n");
    t.AddLine(iss);
    iss.clear();
    iss.str("Waterton Central\nWaterton East\nWaterton Woods\nWaterton North\nWaterton East\nLittle Waterton\nWaterton West");
    t.AddLine(iss);
    assert(t.FindDest("Maron", 0) == (map<string, int>{{"Maron", 0}}));
    assert(t.FindDest("Maron", 1) == (map<string, int>{{"Gordon's Hill", 1},
                                                       {"Maron", 0}}));
    assert(t.FindDest("Maron", 2) == (map<string, int>{{"Gordon's Hill", 1},
                                                       {"Maron", 0},
                                                       {"Sodor Ironworks", 2},
                                                       {"Suderry", 2}}));
    assert(t.FindDest("Maron", 3) == (map<string, int>{{"Gordon's Hill", 1},
                                                       {"Knapford", 3},
                                                       {"Maron", 0},
                                                       {"Sodor Ironworks", 2},
                                                       {"Sodor Steamwork", 3},
                                                       {"Suderry", 2}}));
    assert(t.FindDest("Maron", 4) == (map<string, int>{{"Gordon's Hill", 1},
                                                       {"Great Waterton", 4},
                                                       {"Knapford", 3},
                                                       {"Maron", 0},
                                                       {"Sodor Ironworks", 2},
                                                       {"Sodor Steamwork", 3},
                                                       {"Suderry", 2}}));
    assert(t.FindDest("Maron", 5) == (map<string, int>{{"Brendam Docks", 5},
                                                       {"Gordon's Hill", 1},
                                                       {"Great Waterton", 4},
                                                       {"Knapford", 3},
                                                       {"Maron", 0},
                                                       {"Sodor Ironworks", 2},
                                                       {"Sodor Steamwork", 3},
                                                       {"Suderry", 2}}));
    assert(t.FindDest("Waterton Central", 0) == (map<string, int>{{"Waterton Central", 0}}));
    assert(t.FindDest("Waterton Central", 1) == (map<string, int>{{"Waterton Central", 0},
                                                                  {"Waterton East", 1}}));
    assert(t.FindDest("Waterton Central", 2) == (map<string, int>{{"Little Waterton", 2},
                                                                  {"Waterton Central", 0},
                                                                  {"Waterton East", 1},
                                                                  {"Waterton Woods", 2}}));
    assert(t.FindDest("Waterton Central", 3) == (map<string, int>{{"Lakeside Central", 3},
                                                                  {"Little Waterton", 2},
                                                                  {"Waterton Central", 0},
                                                                  {"Waterton East", 1},
                                                                  {"Waterton North", 3},
                                                                  {"Waterton West", 3},
                                                                  {"Waterton Woods", 2}}));
    assert(t.FindDest("Waterton Central", 4) == (map<string, int>{{"Lakeside Central", 3},
                                                                  {"Little Newton", 4},
                                                                  {"Little Waterton", 2},
                                                                  {"Waterton Central", 0},
                                                                  {"Waterton East", 1},
                                                                  {"Waterton North", 3},
                                                                  {"Waterton West", 3},
                                                                  {"Waterton Woods", 2}}));
    assert(t.FindDest("Waterton Central", 5) == (map<string, int>{{"Lakeside Central", 3},
                                                                  {"Little Burnside", 5},
                                                                  {"Little Newton", 4},
                                                                  {"Little Waterton", 2},
                                                                  {"Waterton Central", 0},
                                                                  {"Waterton East", 1},
                                                                  {"Waterton North", 3},
                                                                  {"Waterton West", 3},
                                                                  {"Waterton Woods", 2}}));
    assert(t.FindDest("Waterton Central", 6) == (map<string, int>{{"Castle Hill", 6},
                                                                  {"Green Hill", 6},
                                                                  {"Lakeside Central", 3},
                                                                  {"Little Burnside", 5},
                                                                  {"Little Newton", 4},
                                                                  {"Little Waterton", 2},
                                                                  {"Waterton Central", 0},
                                                                  {"Waterton East", 1},
                                                                  {"Waterton North", 3},
                                                                  {"Waterton West", 3},
                                                                  {"Waterton Woods", 2}}));
    assert(t.FindDest("Waterton Central", 9) == (map<string, int>{{"Black Hill", 9},
                                                                  {"Castle Hill", 6},
                                                                  {"Great Newton", 8},
                                                                  {"Green Hill", 6},
                                                                  {"Lakeside", 7},
                                                                  {"Lakeside Central", 3},
                                                                  {"Little Burnside", 5},
                                                                  {"Little Newton", 4},
                                                                  {"Little Waterton", 2},
                                                                  {"Newton", 8},
                                                                  {"Newton Crossroad", 7},
                                                                  {"Waterton Central", 0},
                                                                  {"Waterton East", 1},
                                                                  {"Waterton North", 3},
                                                                  {"Waterton West", 3},
                                                                  {"Waterton Woods", 2},
                                                                  {"Wood Side", 7}}));
    assert(t.FindDest("Waterton Central", 10) == (map<string, int>{{"Black Hill", 9},
                                                                   {"Castle Hill", 6},
                                                                   {"Great Newton", 8},
                                                                   {"Green Hill", 6},
                                                                   {"Lakeside", 7},
                                                                   {"Lakeside Central", 3},
                                                                   {"Little Burnside", 5},
                                                                   {"Little Newton", 4},
                                                                   {"Little Waterton", 2},
                                                                   {"Newton", 8},
                                                                   {"Newton Crossroad", 7},
                                                                   {"Waterton Central", 0},
                                                                   {"Waterton East", 1},
                                                                   {"Waterton North", 3},
                                                                   {"Waterton West", 3},
                                                                   {"Waterton Woods", 2},
                                                                   {"Wood Side", 7}}));
    iss.clear();
    iss.str("Newton\nNewton Crossroad\nTidmouth");
    t.AddLine(iss);
    assert(t.FindDest("Waterton East", 0) == (map<string, int>{{"Waterton East", 0}}));
    assert(t.FindDest("Waterton East", 1) == (map<string, int>{{"Little Waterton", 1},
                                                               {"Waterton East", 0},
                                                               {"Waterton Woods", 1}}));
    assert(t.FindDest("Waterton East", 2) == (map<string, int>{{"Lakeside Central", 2},
                                                               {"Little Waterton", 1},
                                                               {"Waterton East", 0},
                                                               {"Waterton North", 2},
                                                               {"Waterton West", 2},
                                                               {"Waterton Woods", 1}}));
    assert(t.FindDest("Waterton East", 3) == (map<string, int>{{"Lakeside Central", 2},
                                                               {"Little Newton", 3},
                                                               {"Little Waterton", 1},
                                                               {"Waterton Central", 3},
                                                               {"Waterton East", 0},
                                                               {"Waterton North", 2},
                                                               {"Waterton West", 2},
                                                               {"Waterton Woods", 1}}));
    assert(t.FindDest("Waterton East", 4) == (map<string, int>{{"Lakeside Central", 2},
                                                               {"Little Burnside", 4},
                                                               {"Little Newton", 3},
                                                               {"Little Waterton", 1},
                                                               {"Waterton Central", 3},
                                                               {"Waterton East", 0},
                                                               {"Waterton North", 2},
                                                               {"Waterton West", 2},
                                                               {"Waterton Woods", 1}}));
    assert(t.FindDest("Waterton East", 5) == (map<string, int>{{"Castle Hill", 5},
                                                               {"Green Hill", 5},
                                                               {"Lakeside Central", 2},
                                                               {"Little Burnside", 4},
                                                               {"Little Newton", 3},
                                                               {"Little Waterton", 1},
                                                               {"Waterton Central", 3},
                                                               {"Waterton East", 0},
                                                               {"Waterton North", 2},
                                                               {"Waterton West", 2},
                                                               {"Waterton Woods", 1}}));
    assert(t.FindDest("Waterton East", 6) == (map<string, int>{{"Castle Hill", 5},
                                                               {"Green Hill", 5},
                                                               {"Lakeside", 6},
                                                               {"Lakeside Central", 2},
                                                               {"Little Burnside", 4},
                                                               {"Little Newton", 3},
                                                               {"Little Waterton", 1},
                                                               {"Newton Crossroad", 6},
                                                               {"Waterton Central", 3},
                                                               {"Waterton East", 0},
                                                               {"Waterton North", 2},
                                                               {"Waterton West", 2},
                                                               {"Waterton Woods", 1},
                                                               {"Wood Side", 6}}));
    assert(t.FindDest("Waterton East", 9) == (map<string, int>{{"Black Hill", 8},
                                                               {"Castle Hill", 5},
                                                               {"Gordon's Hill", 8},
                                                               {"Great Newton", 7},
                                                               {"Green Hill", 5},
                                                               {"Lakeside", 6},
                                                               {"Lakeside Central", 2},
                                                               {"Little Burnside", 4},
                                                               {"Little Newton", 3},
                                                               {"Little Waterton", 1},
                                                               {"Newton", 7},
                                                               {"Newton Crossroad", 6},
                                                               {"Sodor Ironworks", 9},
                                                               {"Suderry", 9},
                                                               {"Tidmouth", 7},
                                                               {"Waterton Central", 3},
                                                               {"Waterton East", 0},
                                                               {"Waterton North", 2},
                                                               {"Waterton West", 2},
                                                               {"Waterton Woods", 1},
                                                               {"Wood Side", 6}}));
    assert(t.FindDest("Waterton East", 10) == (map<string, int>{{"Black Hill", 8},
                                                                {"Castle Hill", 5},
                                                                {"Gordon's Hill", 8},
                                                                {"Great Newton", 7},
                                                                {"Green Hill", 5},
                                                                {"Knapford", 10},
                                                                {"Lakeside", 6},
                                                                {"Lakeside Central", 2},
                                                                {"Little Burnside", 4},
                                                                {"Little Newton", 3},
                                                                {"Little Waterton", 1},
                                                                {"Newton", 7},
                                                                {"Newton Crossroad", 6},
                                                                {"Sodor Ironworks", 9},
                                                                {"Sodor Steamwork", 10},
                                                                {"Suderry", 9},
                                                                {"Tidmouth", 7},
                                                                {"Waterton Central", 3},
                                                                {"Waterton East", 0},
                                                                {"Waterton North", 2},
                                                                {"Waterton West", 2},
                                                                {"Waterton Woods", 1},
                                                                {"Wood Side", 6}}));
    assert(t.FindDest("Waterton East", 11) == (map<string, int>{{"Black Hill", 8},
                                                                {"Castle Hill", 5},
                                                                {"Gordon's Hill", 8},
                                                                {"Great Newton", 7},
                                                                {"Great Waterton", 11},
                                                                {"Green Hill", 5},
                                                                {"Knapford", 10},
                                                                {"Lakeside", 6},
                                                                {"Lakeside Central", 2},
                                                                {"Little Burnside", 4},
                                                                {"Little Newton", 3},
                                                                {"Little Waterton", 1},
                                                                {"Maron", 11},
                                                                {"Newton", 7},
                                                                {"Newton Crossroad", 6},
                                                                {"Sodor Ironworks", 9},
                                                                {"Sodor Steamwork", 10},
                                                                {"Suderry", 9},
                                                                {"Tidmouth", 7},
                                                                {"Waterton Central", 3},
                                                                {"Waterton East", 0},
                                                                {"Waterton North", 2},
                                                                {"Waterton West", 2},
                                                                {"Waterton Woods", 1},
                                                                {"Wood Side", 6}}));
    assert(t.FindDest("Waterton East", 1000000) == (map<string, int>{{"Black Hill", 8},
                                                                     {"Brendam Docks", 12},
                                                                     {"Castle Hill", 5},
                                                                     {"Gordon's Hill", 8},
                                                                     {"Great Newton", 7},
                                                                     {"Great Waterton", 11},
                                                                     {"Green Hill", 5},
                                                                     {"Knapford", 10},
                                                                     {"Lakeside", 6},
                                                                     {"Lakeside Central", 2},
                                                                     {"Little Burnside", 4},
                                                                     {"Little Newton", 3},
                                                                     {"Little Waterton", 1},
                                                                     {"Maron", 11},
                                                                     {"Newton", 7},
                                                                     {"Newton Crossroad", 6},
                                                                     {"Sodor Ironworks", 9},
                                                                     {"Sodor Steamwork", 10},
                                                                     {"Suderry", 9},
                                                                     {"Tidmouth", 7},
                                                                     {"Waterton Central", 3},
                                                                     {"Waterton East", 0},
                                                                     {"Waterton North", 2},
                                                                     {"Waterton West", 2},
                                                                     {"Waterton Woods", 1},
                                                                     {"Wood Side", 6}}));
    assert(t.FindDest("Suddery Woodside", 0) == (map<string, int>{{"Suddery Woodside", 0}}));
    assert(t.FindDest("Suddery Woodside", 666) == (map<string, int>{{"Suddery Woodside", 0}}));
    return 0;
}

