#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <cassert>

using namespace std;

class CTrain
{
public:
    void Add(istringstream &is);
    int Count(void) const;

private:
    map<string,set<string>> _graph;
};

void CTrain::Add(istringstream &is)
{
    string line;
    vector<string> tmp;
    while(getline(is,line)){
        if(!line.empty()){
            tmp.push_back(line);
        }
    }
    if(tmp.size() > 1){
        for(int i = 1 ; i < tmp.size() ; ++ i){
            _graph[tmp[i-1]].insert(tmp[i]);
            _graph[tmp[i]].insert(tmp[i-1]);
        }
    }
    else if(tmp.size() == 1){
        _graph[tmp[0]];
    }
}

int CTrain::Count(void) const
{
    set<string> visited;
    int count = 0;
    for(const auto &[key,val]  : _graph){
        if(visited.count(key) != 0){
            continue;
        }
        queue<string> q;
        visited.insert(key);
        q.push(key);
        while(!q.empty()){
            auto v = q.front();
            q.pop();
            for(const auto &w : _graph.at(v)){
                if(visited.count(w) == 0){
                    visited.insert(w);
                    q.push(w);
                }
            }
        }
        count++;
    }
    return count;
}

int main()
{
    CTrain t0;
    istringstream iss;
    assert(t0.Count() == 0);

    iss.clear();
    iss.str("Newton\n");
    t0.Add(iss);
    assert(t0.Count() == 1);

    iss.clear();
    iss.str("Newton\n");
    t0.Add(iss);
    assert(t0.Count() == 1);

    iss.clear();
    iss.str("\n");
    t0.Add(iss);
    assert(t0.Count() == 1);

    iss.clear();
    iss.str("\n\nNewton\n\nNewton\n\nNewton\n\n");
    t0.Add(iss);
    assert(t0.Count() == 1);

    iss.clear();
    iss.str("Black Hill\n");
    t0.Add(iss);
    assert(t0.Count() == 2);

    iss.clear();
    iss.str("Wood Side\n");
    t0.Add(iss);
    assert(t0.Count() == 3);

    iss.clear();
    iss.str("Green Hill\n");
    t0.Add(iss);
    assert(t0.Count() == 4);

    iss.clear();
    iss.str("Lakeside\n");
    t0.Add(iss);
    assert(t0.Count() == 5);

    iss.clear();
    iss.str("Newton\nBlack Hill\nWood Side\nGreen Hill\nLakeside\n");
    t0.Add(iss);
    assert(t0.Count() == 1);

    iss.clear();
    iss.str("Little Newton\nLittle Burnside\nCastle Hill\nNewton Crossroad\nLakeside Central\n");
    t0.Add(iss);
    assert(t0.Count() == 2);

    iss.clear();
    iss.str("Waterton West\nWaterton Central\nWaterton East\nWaterton Woods\nLittle Waterton\nWaterton West\n");
    t0.Add(iss);
    assert(t0.Count() == 3);

    iss.clear();
    iss.str("Little Waterton\nLakeside Central\n");
    t0.Add(iss);
    assert(t0.Count() == 2);

    iss.clear();
    iss.str("Great Newton\nLittle Burnside\nGreen Hill\nWood Side\n");
    t0.Add(iss);
    assert(t0.Count() == 1);

    iss.clear();
    iss.str("Sodor Ironworks\nSodor Steamworks\nKnapford\nMaron\n");
    t0.Add(iss);
    assert(t0.Count() == 2);

    iss.clear();
    iss.str("Tidmouth\nGordons Hill\nSuderry\nKnapford\nGreat Waterton\nBrendam Docks\n");
    t0.Add(iss);
    assert(t0.Count() == 2);

    iss.clear();
    iss.str("Newton\nNewton Crossroad\nTidmouth\nBrendam Docks\n");
    t0.Add(iss);
    assert(t0.Count() == 1);
    return 0;
}

