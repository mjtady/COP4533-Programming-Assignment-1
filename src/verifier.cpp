#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

bool checkValid(vector<int> hospitalMatches, vector<int> studentMatches,
    vector<vector<int>> hospitalPreferences,vector<vector<int>> studentPreferences)
{
    int n = hospitalMatches.size() - 1;
    //check if everyone is matched
    for (int i = 1;i <= n;i++) {
        if (hospitalMatches[i] == 0) { 
            cout << "INVALID: Hospital " << i << " is not matched" << endl;
            return false;
        }
        if (studentMatches[i] == 0) {
            cout << "INVALID: Student " << i << " is not matched" << endl;
            return false;
        }
    }

    //check if matches are valid indexes
    for (int i = 1;i <= n;i++) {
        if (hospitalMatches[i] < 1|| hospitalMatches[i] > n) { 
            cout << "INVALID: Hospital " << i << " is matched to wrong student " 
                 << hospitalMatches[i] << endl;
            return false;
        }
        if (studentMatches[i] < 1 || studentMatches[i] > n) { 
            cout << "INVALID: Student " << i << " is matched to wrong hospital " 
                 << studentMatches[i] << endl;
            return false;
        }
    }

    vector<bool> studentMatched(n + 1, false);
    for (int h = 1;h <= n; h++) {
        int s = hospitalMatches[h];
        //check multiple matches
        if (studentMatched[s]) {
            cout << "INVALID: Student " << s << " has multiple matches" << endl;
            return false;
        }
        studentMatched[s] = true;
        //check consistency
        if (studentMatches[s] != h) {
            cout << "INVALID: Hospital " << h << " matched with wrong student " << s << endl;
            return false;
        }
    }
    
    return true;  
}

bool checkStable(vector<int> hospitalMatches, vector<int> studentMatches,
    vector<vector<int>> hospitalPreferences, vector<vector<int>> studentPreferences)
{
    int n = hospitalMatches.size() - 1;
    for (int h = 1;h <= n; h++) {
        int currentStudent = hospitalMatches[h];
        
        //check preferences
        for (int i = 0;i < n; i++) {
            int potStudent = hospitalPreferences[h][i];
            if (potStudent == currentStudent) {
                break;
            }
            int currentHospital = studentMatches[potStudent];
            
            //check if this student prefers hospital h over their current match
            for (int j = 0;j < n; j++) {
                int preferredHospital = studentPreferences[potStudent][j];
                
                //blocking pair check
                if (preferredHospital == h) {
                    cout << "UNSTABLE: Hospital " << h << " and student " 
                         << potStudent << endl;
                    return false;
                }
                
                //stop when no block
                if (preferredHospital == currentHospital) {
                    break; 
                }
            }
        }
    }
    return true;    
}

//checks if isValid and isStable are true
void verify(vector<int> hospitalMatches, vector<int> studentMatches,
            vector<vector<int>> hospitalPreferences, vector<vector<int>> studentPreferences)
{   
    //goes through valid and stable check
    if (!checkValid(hospitalMatches, studentMatches, hospitalPreferences, studentPreferences)) {
        return;
    }
    if (!checkStable(hospitalMatches, studentMatches, hospitalPreferences, studentPreferences)) {
        return;
    }
    cout << "VALID STABLE" << endl;
}

//test