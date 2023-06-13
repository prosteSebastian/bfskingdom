#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <cassert>
#include <queue>

using namespace std;

struct distances{
    map<string,int> _distance;
};

struct results{
    vector<distances> _distances;
};

class CTrain {
public:
    void Add(istream &is) {
       string line;
       vector<string> tmp;
       while(getline(is, line)){
           tmp.push_back(line);
       }
        for (size_t i = 1; i < tmp.size(); ++i){
            _graph[tmp[i]].insert(tmp[i-1]);
            _graph[tmp[i-1]].insert(tmp[i]);
        }
    }

    set<string> Dest(const vector<string> &stations, int &cost) {

        results res;
        for(const auto &station : stations){
            queue<string> q;
            distances visited;

            q.push(station);
            visited._distance.emplace(station,0);

            while(!q.empty()){
                auto v = q.front();
                q.pop();
                for(const auto &w : _graph[v]){
                    if(visited._distance.count(w) == 0){
                        visited._distance.emplace(w,visited._distance[v]+1);
                        q.push(w);
                    }
                }
            }
            res._distances.push_back(visited);
        }

        set<string> resultKeys;
        int minDistance = 0xfffffff;
        for(const auto &[key,val] : _graph){
            bool found = false;
            int distance = 0;
            for(auto & _distance : res._distances) {
                if(_distance._distance.count(key) != 0){
                    found = true;
                    distance+=_distance._distance[key];
                }
                else{
                    found = false;
                    break;
                }
            }
            if(found){
                if(minDistance > distance){
                    minDistance = distance;
                    resultKeys.clear();
                    resultKeys.insert(key);
                }
                else if(minDistance == distance){
                    resultKeys.insert(key);
                }
            }
        }

        if(!resultKeys.empty()){
            cost = minDistance;
        }

        return resultKeys;
    }

private:
    map<string,set<string>> _graph;
};

int main(void) {
    CTrain t0;
    istringstream iss;

    iss.clear();
    iss.str(
            "1\n"
            "2\n"
            "3\n"
            "4\n"
            "5\n"
            "6\n"
            "7\n"
            "8\n");
    t0.Add(iss);
    iss.clear();
    iss.str(
            "12\n"
            "11\n"
            "4\n"
            "9\n"
            "10\n");
    t0.Add(iss);
    iss.clear();
    iss.str(
            "15\n"
            "11\n"
            "13\n"
            "14\n");
    t0.Add(iss);
    iss.clear();
    iss.str(
            "7\n"
            "16\n"
            "17\n");
    t0.Add(iss);
    iss.clear();
    iss.str(
            "20\n"
            "19\n"
            "17\n"
            "18\n");
    t0.Add(iss);
    iss.clear();
    iss.str(
            "21\n"
            "22\n"
            "23\n"
            "25\n"
            "24\n"
            "21\n");
    t0.Add(iss);
    iss.clear();
    iss.str(
            "26\n"
            "27\n"
            "28\n");
    t0.Add(iss);
    iss.clear();
    iss.str(
            "27\n"
            "29\n"
            "30\n");
    t0.Add(iss);

    int cost = 5381;
    assert (t0.Dest({"2", "5", "11"}, cost) == set<string>({"4"})
            && cost == 4);
    assert (t0.Dest({"12", "10"}, cost) == set<string>({"10", "9", "4", "11", "12"})
            && cost == 4);
    assert (t0.Dest({"2", "9", "19"}, cost) == set<string>({"4"})
            && cost == 9);
    assert (t0.Dest({"15", "12", "13"}, cost) == set<string>({"11"})
            && cost == 3);
    cost = 5381;
    assert (t0.Dest({"21", "26"}, cost) == set<string>()
            && cost == 5381);
    cost = 1256;
    assert (t0.Dest({"10", "28"}, cost) == set<string>()
            && cost == 1256);
    assert (t0.Dest({"21", "25"}, cost) == set<string>({"21", "24", "25"})
            && cost == 2);
    assert (t0.Dest({"21", "21"}, cost) == set<string>({"21"})
            && cost == 0);
    assert (t0.Dest({"23", "21"}, cost) == set<string>({"21", "22", "23"})
            && cost == 2);
    assert (t0.Dest({"12", "20"}, cost) == set<string>({"12", "11", "4", "5", "6", "7", "16", "17", "19", "20"})
            && cost == 9);
    assert (t0.Dest({"50"}, cost) == set<string>({"50"})
            && cost == 0);
    assert (t0.Dest({"13", "10"}, cost) == set<string>({"10", "11", "13", "4", "9"})
            && cost == 4);
    assert (t0.Dest({"17", "19"}, cost) == set<string>({"17", "19"})
            && cost == 1);
    cost = 1999;
    assert (t0.Dest({"29", "25"}, cost) == set<string>()
            && cost == 1999);
    assert (t0.Dest({"8", "5"}, cost) == set<string>({"5", "6", "7", "8"})
            && cost == 3);
    assert (t0.Dest({"4", "4"}, cost) == set<string>({"4"})
            && cost == 0);

    return 0;
}
