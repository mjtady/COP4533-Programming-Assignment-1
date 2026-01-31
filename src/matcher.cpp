#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Matcher {
private:
    int n; // will indicate number of nodes (n hospitals, n students)
    
    // lists
    // example for myself because im lowkey stupid and will forget this later: 
    // hospitalPreferences[0] = {2, 0, 1} means hospital 0 prefers student 2 the most, then student 0, then student 1
    vector<vector<int>> hospitalPreferences;
    vector<vector<int>> studentPreferences;

    vector<int> hospitalMatches; 
    vector<int> studentMatches;
    vector<int> hospitalNextProposal;
    queue<int> freeHospitals; // a queue to manage free hospitals, fifo;
    // allows for better tracking of what hospitals are matched and unmatched
    int counter; // to count number of proposals made

public:
    Matcher(int n, vector<vector<int>> hospitalPrefs, vector<vector<int>> studentPrefs){
        this->n = n;
        this->hospitalPreferences = hospitalPrefs;
        this->studentPreferences = studentPrefs;
        this->hospitalMatches = vector<int>(n + 1, -1); // -1 indicates unmatched
        this->studentMatches = vector<int>(n + 1, -1); // -1 indicates unmatched
        this->hospitalNextProposal = vector<int>(n + 1, 0); // index of next student to propose to for each hospital
        this->counter = 0;

        // step 1 of the given pseudocode from chapter 1 slides
        for(int i = 1; i <= n; i++){
            freeHospitals.push(i); // initially all hospitals are free
        }
    }

    void match(){
        if(n == 0){
            return; // no matching needed for 0 hospitals/students
        }

        while(!freeHospitals.empty()){ 
            // "some hospital is free and hasn't been matched/assigned to every applicant"
            int hospital = freeHospitals.front();
            freeHospitals.pop(); // removes the hospital from the queue as it is being processed
            
            if(hospitalNextProposal[hospital] >= n){
                continue;
            }
            //"a = 1st applicant on h's list to whom h has not been matched"
            int student = hospitalPreferences[hospital - 1][hospitalNextProposal[hospital]]; // accesses the array of student preferences for the specific hospital
            hospitalNextProposal[hospital]++;
            counter++; // increment proposal counter

            if(studentMatches[student] == -1){ // "if (a is free)"
                hospitalMatches[hospital] = student;
                studentMatches[student] = hospital;
            }else if (tradeUp(student, hospital)){ // "else if (a prefers h to her/his current assignment h')"
                int curr = studentMatches[student];
                
                hospitalMatches[curr] = -1;
                freeHospitals.push(curr);
                
                hospitalMatches[hospital] = student;
                studentMatches[student] = hospital;
            }else{ // "a rejects h"
                freeHospitals.push(hospital); 
            }
        }
    }

    // helper function for "trade up" step
    // readjusted tradeUp logic was incorrect indexing when it came to accessing student preferences
    // and there was a flaw when making comparisons using boolean logic directly on indices rather than the preference values
    bool tradeUp(int student, int newHospital){
        int curr = studentMatches[student];
        int newPref = -1;
        int currPref = -1;
        for(int i = 0; i < n; i++){
            if(studentPreferences[student - 1][i] == newHospital){
                newPref = i;
            }
            if(studentPreferences[student - 1][i] == curr){
                currPref = i;
            }
        }
        return newPref < currPref;
    }

    void print(){
        cout << n << endl;
        for(int i = 1; i < n + 1; i++){
            cout << i << " " << hospitalMatches[i] << endl;
        }
    }

};
