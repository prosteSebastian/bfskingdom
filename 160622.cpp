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


struct path{
    long _distance;
    list<string> _steps;
};

class CDelivery
{
public:
    CDelivery() = default;
    ~CDelivery() = default;

    // add connection from -> to, fluent interface
    CDelivery & addConn ( const string & from, const string & to );

    // returns a map containing shortest path to each customer from any of the depots
    // map key is the customer name, value is a list of nodes on the shortest path (depot -> customer)
    // if there is no path, the value is an empty list
    map<string, list<string>> serveCustomers ( const set<string> & customers, const set<string> & depots ) const;

    path bfs(const string &from, const string &to)const;
private:
    map<string,list<string>> _graph;
};

CDelivery & CDelivery::addConn ( const string & from, const string & to )
{
    _graph[from].push_back(to);
    return *this;
}



path CDelivery::bfs(const string &from, const string &to) const {
    path res;
    res._distance = INT64_MAX;
    queue<pair<string,list<string>>> q;
    set<string> visited;
    q.push({from,{{from}}});
    visited.insert(from);
    while(!q.empty()){
        auto v = q.front();
        q.pop();
        if(v.first == to){
            res._distance = static_cast<int>(v.second.size());
            res._steps = v.second;
            return res;
        }
        for(auto & w : _graph.at(v.first)){
            if(visited.count(w) == 0){
                visited.insert(w);
                list<string> newList = v.second;
                newList.push_back(w);
                q.push({w,newList});
            }
        }
    }
    return res;
}

map<string, list<string>> CDelivery::serveCustomers ( const set<string> & customers, const set<string> & depots ) const
{
    map<string,list<string>> res;
    for(const auto &customer : customers){
        path minPath = {INT64_MAX};
        for(const auto &depot : depots){
            path newP = bfs(depot,customer);
            if(newP._distance < minPath._distance){
                minPath._distance = newP._distance;
                minPath._steps = newP._steps;
            }
        }
        if(minPath._distance != INT64_MAX){
            res[customer] = minPath._steps;
        }
        else{
            res[customer] = {};
        }
    }
    return res;
}

int main ()
{
    CDelivery t0;
    map<string, list<string>> r;
    t0.addConn("Austin", "Berlin");
    t0.addConn("Chicago", "Berlin");
    t0.addConn("Berlin", "Dallas");
    t0.addConn("Dallas", "Essen");
    t0.addConn("Essen", "Austin");
    t0.addConn("Frankfurt", "Gyor");
    t0.addConn("Gyor", "Helsinki");
    t0.addConn("Helsinki", "Frankfurt");

    r = t0.serveCustomers(set<string>{"Berlin", "Gyor"}, set<string>{"Essen", "Helsinki"});
    assert ( r == (map<string, list<string>>{ {"Berlin", {"Essen", "Austin", "Berlin"}}, {"Gyor", {"Helsinki", "Frankfurt", "Gyor"}} }) );

    r = t0.serveCustomers(set<string>{"Austin", "Gyor", "Chicago"}, set<string>{"Austin", "Dallas"});
    assert ( r == (map<string, list<string>>{ {"Austin", {"Austin"}}, {"Chicago", { }}, {"Gyor", { }} }) );
    t0.addConn("Chicago", "Helsinki");

    r = t0.serveCustomers(set<string>{"Austin", "Gyor", "Chicago"}, set<string>{"Austin", "Dallas"});
    assert ( r == (map<string, list<string>>{ {"Austin", {"Austin"}}, {"Chicago", { }}, {"Gyor", { }} }) );
    t0.addConn("Berlin", "Chicago");

    r = t0.serveCustomers(set<string>{"Austin", "Gyor", "Chicago"}, set<string>{"Austin", "Dallas"});
    assert ( r == (map<string, list<string>>{ {"Austin", {"Austin"}}, {"Chicago", {"Austin", "Berlin", "Chicago"}}, {"Gyor", {"Austin", "Berlin", "Chicago", "Helsinki", "Frankfurt", "Gyor"}} }) );
    t0.addConn("Essen", "Frankfurt");

    r = t0.serveCustomers(set<string>{"Austin", "Gyor", "Chicago"}, set<string>{"Austin", "Dallas"});
    assert ( r == (map<string, list<string>>{ {"Austin", {"Austin"}}, {"Chicago", {"Austin", "Berlin", "Chicago"}}, {"Gyor", {"Dallas", "Essen", "Frankfurt", "Gyor"}} }) );

    return EXIT_SUCCESS;
}
