#include <cstdio>
#include <vector>
#include <iostream>
#include <memory>
using namespace std;

vector<vector<vector<int>>> readInput(int* N, int* M, int* target, vector<vector<int>>& tableRef) {
    cin >> *N >> *M;
    tableRef.resize(*N, vector<int>(*N));
    for (int i = 0; i < *N; i++) {
        for (int j = 0; j < *N; j++)
            cin >> tableRef[i][j];
    }
    vector<vector<vector<int>>> tableCalculated(*M, vector<vector<int>>(*M, vector<int>()));
    for (int i = 0; i < *M; i++) {
        int num;
        cin >> num;
        tableCalculated[i][i].push_back(num);
        tableCalculated[i][i].push_back(0);
        tableCalculated[i][i].push_back(0);
        tableCalculated[i][i].push_back(0);
    }
    cin >> *target;
    
    return tableCalculated;
}

bool calculate(int N, int M, int target, vector<vector<vector<int>>> &tableCalculated, vector<vector<int>>& tableRef) {
    for (int len = 2; len <= M; len++) {    // Vai iterando sobre a sequencia inicial com os varios tamanhos possiveis ate M
        for (int i = 0; (i + len) <= M; i++) {  // Vai a cada linha
            int f = i + len - 1;    // Obtem o ultimo indice do termo da sequencia a ser observada
            vector<int> tempSecond(N, false);
            for (int k = f; k > i; k--) {   // Vai com o K desde o penultimo elemento ate o segundo
                if (tableCalculated[i][f].size() / 4 >= static_cast<size_t>(N)) continue;
                size_t size1 = tableCalculated[i][k - 1].size();
                size_t size2 = tableCalculated[k][f].size();  
                for (size_t v1 = 0; v1 < size1; v1 += 4) {          
                    for (size_t v2 = 0; v2 < size2; v2 += 4) {
                        int res = tableRef[tableCalculated[i][k-1][v1] - 1][tableCalculated[k][f][v2] - 1];
                        if (tempSecond[res - 1] == false) {
                            tableCalculated[i][f].push_back(res);
                            tableCalculated[i][f].push_back(k);
                            tableCalculated[i][f].push_back(v1); // Indice onde esta guardado val1
                            tableCalculated[i][f].push_back(v2); // Indice onde esta guardado val2
                            tempSecond[res - 1] = true;                            
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


string printResult(int i, int j, int valIndice, vector<vector<vector<int>>> &tableCalculated) {
    if (i == j)
        return to_string(tableCalculated[i][j][0]);
    
    int k = tableCalculated[i][j][valIndice + 1];
    int v1 = tableCalculated[i][j][valIndice + 2];
    int v2 = tableCalculated[i][j][valIndice + 3];

    return "(" + printResult(i, k - 1, v1, tableCalculated) + " " + printResult(k, j, v2, tableCalculated) + ")";
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, M, target;
    vector<vector<int>> tableRef;
    vector<vector<vector<int>>> tableCalculated = readInput(&N, &M, &target, tableRef);

    if (M == 1)
        (tableCalculated[0][0][0] == target) ? (cout << ("1\n" + to_string(tableCalculated[0][0][0])) << endl) : cout << "0\n";
    else if (calculate(N, M, target, tableCalculated, tableRef)) {
        cout << "1\n";
        size_t size = tableCalculated[0][M-1].size();
        cout << printResult(0, M-1, size - 4, tableCalculated) << endl; 
    }
    else
        cout << "0\n";

    return 0;
}