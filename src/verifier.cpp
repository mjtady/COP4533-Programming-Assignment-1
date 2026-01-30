#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
using namespace std;


bool isValid(vector<int> hospitalMatches, vector<int> studentMatches,
    vector<vector<int>> hospitalPreferences,
    vector<vector<int>> studentPreferences)
{
    for (int i = 0; i < hospitalMatches.size(); i++) {
        int student = hospitalMatches[i];
        if (student != -1) {
            if (student < 0 || student >= studentMatches.size()) {
                return false;
            }
            if (studentMatches[student] != i) {
                return false;
            }
        }
    }

    for (int j = 0; j < studentMatches.size(); j++){
        int hospital = studentMatches[j];
        if (hospital != -1) {
            if (hospital < 0 || hospital >= hospitalMatches.size()) {
                return false;
            }
            if (hospitalMatches[hospital] != j) {
                return false;
            }
        }
    }
    return true;    
}

bool isStable(vector<int> hospitalMatches, vector<int> studentMatches,
    vector<vector<int>> hospitalPreferences, vector<vector<int>> studentPreferences)
{
    
    return true;    
}