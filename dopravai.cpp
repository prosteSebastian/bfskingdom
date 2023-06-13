#include <sstream>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <cassert>
using namespace std;



static unsigned lineCounter = 0;
class CMHD
{
public:
    void Add ( istringstream & is )
    {
        string l;

        while(getline(is,l)){

            for(const auto &line : _linesOfStations[l]){
                _graph[lineCounter].insert(line);
                _graph[line].insert(lineCounter);
            }

            _linesOfStations[l].insert(lineCounter);
            _stationsOfLines[lineCounter].insert(l);
        }
        _graph[lineCounter];
        lineCounter++;
    }


    set < string > Dest ( const string & from, int maxCost ) const {
        queue<unsigned> q;
        set<unsigned> visited;
        set <string> res{from};

        int currentCost = 0;
        if(_linesOfStations.count(from) == 0){
            return res;
        }
        for(const auto &line : _linesOfStations.at(from)){
            q.push(line);
            visited.insert(line);
        }

        int toSerach = q.size();

        while(!q.empty()){
            if(toSerach == 0){
                currentCost++;
                toSerach = q.size();
            }
            if(currentCost == maxCost){
                for(const auto &line : visited){
                   res.insert(_stationsOfLines.at(line).begin(),_stationsOfLines.at(line).end());
                }
                return res;
            }

            auto v = q.front();
            q.pop();
            for(const auto &w : _graph.at(v)){
                if(visited.count(w) == 0){
                    visited.insert(w);
                    q.push(w);
                }
            }
            toSerach--;
        }
        return res;
    }

private:
    map<unsigned ,set<unsigned>> _graph;
    map<string, set<unsigned>> _linesOfStations;
    map<unsigned, set<string>> _stationsOfLines;
};

int main ( void )
{
    CMHD city;
    istringstream iss;
    iss.clear();

    iss . str ( "A\nB\nC\nD\nE\n" );
    city . Add ( iss );
    iss . clear();

    iss . str ( "B\nC\nF\nH\n" );
    city . Add ( iss );
    iss . clear();

    iss . str ( "F\nG\nI\nJ\nK\nN\n" );
    city . Add ( iss );
    iss . clear();

    iss . str ( "H\nL\n" );
    city . Add ( iss );
    iss . clear();

    iss . str ( "L\nM\nN\nO\n" );
    city . Add ( iss );
    iss . clear();

    iss . str ( "P\nQ\nR\nN\nS" );
    city . Add ( iss );
    iss . clear();

    assert ( city . Dest ( "S", 0 ) == set < string > ( {"S", "N", "R", "Q", "P"} ) );

    assert ( city . Dest ( "S", 1 ) == set < string > ( { "S", "N", "R", "Q", "P",
                                                          "O", "M", "L",
                                                          "K", "J", "I", "G", "F" } ) );

    assert ( city . Dest ( "N", 0 ) == set < string > ( { "S", "N", "R", "Q", "P",
                                                          "O", "M", "L",
                                                          "K", "J", "I", "G", "F" } ) );

    assert ( city . Dest ( "N", 1 ) == set < string > ( { "S", "N", "R", "Q", "P",
                                                          "O", "M", "L",
                                                          "K", "J", "I", "G", "F",
                                                          "H", "F", "C", "B" } ) );

    assert ( city . Dest ( "N", 2 ) == set < string > ( { "S", "N", "R", "Q", "P",
                                                          "O", "M", "L",
                                                          "K", "J", "I", "G", "F",
                                                          "H", "F", "C", "B",
                                                          "A", "D", "E" } ) );

    assert ( city . Dest ( "unknown", 0 ) == set < string > ( { "unknown" } ) );
    assert ( city . Dest ( "unknown", 1 ) == set < string > ( { "unknown" } ) );
    assert ( city . Dest ( "unknown", 2 ) == set < string > ( { "unknown" }) );

    return 0;
}

