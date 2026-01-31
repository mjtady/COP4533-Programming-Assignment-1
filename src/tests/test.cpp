#include "../matcher.cpp"

int main() {
    ifstream in("example.in");
    int n;
    in >> n;
    vector<vector<int>> hp(n);
    for(int i = 0; i < n; i++) {
        hp[i].resize(n);
        for(int j = 0; j < n; j++) {
            in >> hp[i][j];
        }
    }
    vector<vector<int>> sp(n);
    for(int i = 0; i < n; i++) {
        sp[i].resize(n);
        for(int j = 0; j < n; j++) {
            in >> sp[i][j];
        }
    }
    in.close();
    Matcher matcher(n, hp, sp);
    matcher.match();
    matcher.print();
    
    return 0;
}