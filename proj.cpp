#include <cstdio>
#include <vector>
#include <iostream>
#include <memory>
using namespace std;

vector<vector<pair<vector<int>, vector<bool>>>> readInput(int* N, int* M, int* target, vector<vector<int>>& tableRef) {
    cin >> *N >> *M;
    tableRef.resize(*N, vector<int>(*N));
    for (int i = 0; i < *N; i++) {
        for (int j = 0; j < *N; j++)
            cin >> tableRef[i][j];
    }
vector<vector<pair<vector<int>, vector<bool>>>> tableCalculated(*M, vector<pair<vector<int>, vector<bool>>>(*M, make_pair(vector<int>(), vector<bool>(*N, false))));
    for (int i = 0; i < *M; i++) {
        int num;
        cin >> num;
        tableCalculated[i][i].first.push_back(num);
        tableCalculated[i][i].first.push_back(0);
        tableCalculated[i][i].first.push_back(0);
        tableCalculated[i][i].first.push_back(0);
        tableCalculated[i][i].second[num - 1] = true;
    }
    cin >> *target;
    
    return tableCalculated;
}

bool calculate(int N, int M, int target, vector<vector<pair<vector<int>, vector<bool>>>> &tableCalculated, vector<vector<int>>& tableRef) {
    for (int len = 2; len <= M; len++) {    // Vai iterando sobre a sequencia inicial com os varios tamanhos possiveis ate M
        for (int i = 0; (i + len) <= M; i++) {  // Vai a cada linha
            int f = i + len - 1;    // Obtem o ultimo indice do termo da sequencia a ser observada
            int counter = 0;
            for (int k = f; k > i; k--) {   // Vai com o K desde o penultimo elemento ate o segundo
                if (counter >= N) continue;
                size_t size1 = tableCalculated[i][k - 1].first.size();
                size_t size2 = tableCalculated[k][f].first.size();  
                for (size_t v1 = 0; v1 < size1; v1 += 4) {          
                    for (size_t v2 = 0; v2 < size2; v2 += 4) {
                        int res = tableRef[tableCalculated[i][k-1].first[v1] - 1][tableCalculated[k][f].first[v2] - 1];
                        if (tableCalculated[i][f].second[res - 1] == 0) {
                            tableCalculated[i][f].first.push_back(res);
                            tableCalculated[i][f].first.push_back(k);
                            tableCalculated[i][f].first.push_back(v1); // Indice onde esta guardado val1
                            tableCalculated[i][f].first.push_back(v2); // Indice onde esta guardado val2
                            tableCalculated[i][f].second[res - 1] = true;
                            counter++;
                            if (len == M && res == target)  // Verifica se o res da ultima linha é aquele que se quer obter
                                return true;
                        } 
                    }
                }                 
            }
        }
    }
    return false;
} //M^3 N^2


string printResult(int i, int j, int valIndice, vector<vector<pair<vector<int>, vector<bool>>>> &tableCalculated) {

    if (i == j)
        return to_string(tableCalculated[i][j].first[0]);
    if (i == j - 1)
        return "(" + to_string(tableCalculated[i][i].first[0]) + " " + to_string(tableCalculated[j][j].first[0]) + ")";
    
    int k = tableCalculated[i][j].first[valIndice + 1];
    int v1 = tableCalculated[i][j].first[valIndice + 2];
    int v2 = tableCalculated[i][j].first[valIndice + 3];

    return "(" + printResult(i, k - 1, v1, tableCalculated) + " " + printResult(k, j, v2, tableCalculated) + ")";
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, M, target;
    vector<vector<int>> tableRef;

    vector<vector<pair<vector<int>, vector<bool>>>> tableCalculated = readInput(&N, &M, &target, tableRef);

    if (M == 1)
        (tableCalculated[0][0].first[0] == target) ? (cout << ("1\n" + to_string(tableCalculated[0][0].first[0])) << endl) : cout << "0\n";

    else if (calculate(N, M, target, tableCalculated, tableRef)) {
        cout << "1\n";
        size_t size = tableCalculated[0][M-1].first.size();
        cout << printResult(0, M-1, size - 4, tableCalculated) << endl; 
    }
    else
        cout << "0\n";

    return 0;
}