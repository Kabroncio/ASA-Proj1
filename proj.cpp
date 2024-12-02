#include <cstdio>
#include <vector>
#include <iostream>
#include <memory>
using namespace std;

vector<vector<pair<vector<int>, vector<int>>>> readInput(int* N, int* M, int* target, vector<vector<int>>& tableRef) {
    cin >> *N >> *M;
    tableRef.resize(*N, vector<int>(*N));
    for (int i = 0; i < *N; i++) {
        for (int j = 0; j < *N; j++)
            cin >> tableRef[i][j];
    }
vector<vector<pair<vector<int>, vector<int>>>> tableCalculated(*M, vector<pair<vector<int>, vector<int>>>(*M, make_pair(vector<int>(), vector<int>(*N, 0))));
    for (int i = 0; i < *M; i++) {
        int num;
        cin >> num;
        tableCalculated[i][i].first.push_back(num);
        tableCalculated[i][i].first.push_back(0);
        tableCalculated[i][i].first.push_back(i);
        tableCalculated[i][i].first.push_back(i);
        tableCalculated[i][i].second[num - 1] = 1;
    }
    cin >> *target;
    
    return tableCalculated;
}

int calculate(int N, int M, int target, vector<vector<pair<vector<int>, vector<int>>>> &tableCalculated, vector<vector<int>>& tableRef) {
    for (int len = 2; len <= M; len++) {    // Vai iterando sobre a sequencia inicial com os varios tamanhos possiveis ate M
        for (int i = 0; (i + len) <= M; i++) {  // Vai a cada linha
            int f = i + len - 1;    // Obtem o ultimo indice do termo da sequencia a ser observada
            for (int k = f; k > i; k--) {   // Vai com o K desde o penultimo elemento ate o segundo
                int counter = 0;
                size_t size1 = tableCalculated[i][k - 1].first.size();
                size_t size2 = tableCalculated[k][f].first.size();
                if (counter < N) {
                    for (size_t v1 = 0; v1 < size1; v1 += 4) {          
                        for (size_t v2 = 0; v2 < size2; v2 += 4) {
                            int res = tableRef[tableCalculated[i][k-1].first[v1] - 1][tableCalculated[k][f].first[v2] - 1];
                            if (tableCalculated[i][f].second[res - 1] == 0) {
                                tableCalculated[i][f].first.push_back(res);
                                tableCalculated[i][f].first.push_back(k);
                                tableCalculated[i][f].first.push_back(v1);
                                tableCalculated[i][f].first.push_back(v2);
                                tableCalculated[i][f].second[res - 1] = 1;
                                counter++;

                                if (len == M && res == target)  // Verifica se o res da ultima linha é aquele que se quer obter
                                    return counter;
                            } 
                        }
                    }           
                }   
            }
        }
    }
    return -1;
}


string printResult(int i, int j, int v1, int v2, vector<vector<pair<vector<int>, vector<int>>>> &tableCalculated) {

    if (i == j)
        return to_string(tableCalculated[i][j].first[0]);
    if (i == j - 1)
        return "(" + printResult(i, i, 0, 0, tableCalculated) + " " + printResult(j, j, 0, 0, tableCalculated) + ")";
    
    return "(" + printResult(i, tableCalculated[i][j].first[1 + v1] - 1, tableCalculated[i][j].first[2 + v1], tableCalculated[i][j].first[3 + v1], tableCalculated) + " " 
        + printResult(tableCalculated[i][j].first[1 + v2], j, tableCalculated[i][j].first[2 + v2], tableCalculated[i][j].first[3 + v2], tableCalculated) + ")";
}

void printTableCalculated(const vector<vector<pair<vector<int>, vector<int>>>>& tableCalculated) {
    cout << "Table Calculated:\n";
    for (size_t i = 0; i < tableCalculated.size(); i++) {
        for (size_t j = 0; j < tableCalculated[i].size(); j++) {
            cout << "[" << i << "][" << j << "] -> First: {";
            for (size_t k = 0; k < tableCalculated[i][j].first.size(); k++) {
                cout << tableCalculated[i][j].first[k];
                if (k < tableCalculated[i][j].first.size() - 1) cout << ", ";
            }
            cout << "} Second: {";
            for (size_t k = 0; k < tableCalculated[i][j].second.size(); k++) {
                cout << tableCalculated[i][j].second[k];
                if (k < tableCalculated[i][j].second.size() - 1) cout << ", ";
            }
            cout << "}\n";
        }
    }
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, M, target;
    vector<vector<int>> tableRef;

    vector<vector<pair<vector<int>, vector<int>>>> tableCalculated = readInput(&N, &M, &target, tableRef);

    if (M == 1)
        (tableCalculated[0][0].first[0] == target) ? (cout << ("1\n" + to_string(tableCalculated[0][0].first[0])) << endl) : cout << "0\n";

    else if (int count = calculate(N, M, target, tableCalculated, tableRef) != -1) {
        cout << "1\n";
        cout << printResult(0, M-1, tableCalculated[0][M-1].first[2*count], tableCalculated[0][M-1].first[3*count], tableCalculated) << endl; 
    }
    else
        cout << "0\n";

    printTableCalculated(tableCalculated);

    return 0;
}

