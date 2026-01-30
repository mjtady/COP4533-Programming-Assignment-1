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
        this->hospitalMatches = vector<int>(n, -1); // -1 indicates unmatched
        this->studentMatches = vector<int>(n, -1); // -1 indicates unmatched
        this->hospitalNextProposal = vector<int>(n, 0);
        this->counter = 0;

        // step 1 of the given pseudocode from chapter 1 slides
        for(int i = 0; i < n; i++){
            freeHospitals.push(i); // initially all hospitals are free
        }
    }

    void match(){
        if(n == 0){
            return; // no matching needed for 0 hospitals/students
        }

        while(!freeHospitals.empty()){ // the populated queue will be iterated through 
            // "some hospital is free and hasn't been matched/assigned to every applicant"
            int hospital = freeHospitals.front();
            freeHospitals.pop(); // removes the hospital from the queue as it is being processed
            int student = hospitalPreferences[hospital][hospitalNextProposal[hospital]]; // accesses the array of student preferences for the specific hospital
            
            hospitalNextProposal[hospital]++; // move to the next student for future proposals
            counter++; // increment proposal counter


        }
    }
};
