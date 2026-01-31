#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>

#include "matcher.cpp"
#include "verifier.cpp"

using namespace std;
using namespace std::chrono;

// these functions will generate random preferences and create matching instances and write these into a .csv file that will be used in a .py script for graphing
// initial goal with using c++ is that its more efficient for larger scaling tests, however, python's matplotlib is easier for graphing

void randomPreferencesGenerator(int n, vector<vector<int>> &hospitalPrefs, vector<vector<int>> &studentPrefs){
    hospitalPrefs.clear();
    studentPrefs.clear();

    // random number generator setup
    random_device rd;
    mt19937 g(rd());

    // this will generate random preferences for hospitals and students
    hospitalPrefs.resize(n);
    for (int i = 0; i < n; i++) {
        hospitalPrefs[i].resize(n);
        for (int j = 0; j < n; j++) {
            hospitalPrefs[i][j] = j + 1; 
        }
        shuffle(hospitalPrefs[i].begin(), hospitalPrefs[i].end(), g);
    }
    studentPrefs.resize(n);
    for (int i = 0; i < n; i++) {
        studentPrefs[i].resize(n);
        for (int j = 0; j < n; j++) {
            studentPrefs[i][j] = j + 1;
        }
        shuffle(studentPrefs[i].begin(), studentPrefs[i].end(), g);
    }
}

// utilizing long long to ensure that we can handle large time durations in scaling tests
// measure the matching time in microseconds for given matching instance
long long matchingTime(int n, vector<vector<int>> &hospitalPrefs, vector<vector<int>> &studentPrefs){
    Matcher matcher(n, hospitalPrefs, studentPrefs);

    auto start = high_resolution_clock::now();
    matcher.match();
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    return duration.count();
}

// measures verification time in microseconds for given matching instance
long long verificationTime(int n, vector<vector<int>> &hospitalPrefs, vector<vector<int>> &studentPrefs, 
        vector<int> &hospitalMatches, vector<int> &studentMatches){

    auto start = high_resolution_clock::now();
    bool valid = checkValid(hospitalMatches, studentMatches, hospitalPrefs, studentPrefs);
    bool stable = checkStable(hospitalMatches, studentMatches, hospitalPrefs, studentPrefs);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    return duration.count();
    
}

int main(){
    int power;
    string filename;

    cout << "Enter the power for scaling tests (2^power): ";
    cin >> power;
    cout << "Enter the filename to save results: ";
    cin >> filename;

    if(filename.find(".csv") == string::npos){
        filename += ".csv";
    }

    string fullPath = "output/" + filename;

    // will write the header
    ofstream outFile(fullPath);
    outFile << "n,matchingTime,verificationTime\n";
    
    // iterates through powers of 2 up to the specified power and performs matching and verification, recording the time taken for each
    for(int i = 1; i <= power; i++){
        int n = pow(2, i);

        vector<vector<int>> hospitalPrefs;
        vector<vector<int>> studentPrefs;

        randomPreferencesGenerator(n, hospitalPrefs, studentPrefs);

        long long matchTime = matchingTime(n, hospitalPrefs, studentPrefs);

        Matcher matcher(n, hospitalPrefs, studentPrefs);
        matcher.match();
        vector<int> hospitalMatches = matcher.getHospital();
        vector<int> studentMatches = matcher.getStudent();

        long long verifyTime = verificationTime(n, hospitalPrefs, studentPrefs, hospitalMatches, studentMatches);

        // outFile << n << "," << matchTime << "," << verifyTime << "\n";
        outFile.flush();

        // cout << "Completed for n = " << n << "\n";
    }

    outFile.close();
    return 0;
}
