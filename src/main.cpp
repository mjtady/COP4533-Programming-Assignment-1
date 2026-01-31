#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "matcher.cpp"

using namespace std;

int main() {
   int n = 3;
   vector<vector<int>> hospitalPrefs = {{1, 2, 3}, {2, 3, 1}, {2, 1, 3}};
   vector<vector<int>> studentPrefs = {{2, 1, 3}, {1, 2, 3}, {1, 2, 3}};

   Matcher matcher(n, hospitalPrefs, studentPrefs);
   matcher.match();
   matcher.print();

   return 0;
}