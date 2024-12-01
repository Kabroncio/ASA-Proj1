#include <cstdio>
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
using namespace std;

vector<vector<int>> tableRef;

vector<vector<vector<int>>> readInput(int* N, int* M, int* target) {
    cin >> *N >> *M;
    tableRef.resize(*N, vector<int>(*N));
    for (int i = 0; i < *N; i++) {
        for (int j = 0; j < *N; j++)
            cin >> tableRef[i][j];
    }
    vector<vector<vector<int>>> tableCalculated(*M, vector<vector<int>>(*M, vector<int>()));
    for (int i = 0; i < *M; i++) {
        int val;
        cin >> val;
        tableCalculated[i][i].push_back(val);
        tableCalculated[i][i].push_back(0);
    }
    cin >> *target;
    
    return tableCalculated;
}

bool calculate(int N, int M, int target, vector<vector<vector<int>>> &tableCalculated) {
    for (int len = 2; len <= M; len++) {    // Vai iterando sobre a sequencia inicial com os varios tamanhos possiveis ate M
        for (int i = 0; (i + len) <= M; i++) {  // Vai a cada linha
            int f = i + len - 1;    // Obtem o ultimo indice do termo da sequencia a ser observada
            for (int k = f; k > i; k--) {   // Vai com o K desde o penultimo elemento ate o segundo
                int count1 = 0; 
                int count2 = 0;
                for (int val1 : tableCalculated[i][k-1]) {
                    if (count1 == 0) {
                        for (int val2 : tableCalculated[k][f]) {
                            // Verifica se o val1 é um valor calculado ou um k
                            if (count2 % 2 == 0) {
                                int res = tableRef[val1 - 1][val2 - 1];

                                if (find(tableCalculated[i][f].begin(), tableCalculated[i][f].end(), res) == tableCalculated[i][f].end()) { //Verifica se o res ja existe
                                    tableCalculated[i][f].push_back(res);
                                    tableCalculated[i][f].push_back(k);
                                    if (len == M && res == target) { // Verifica se o res da ultima linha é aquele que se quer obter
                                        return true;
                                    }
                                }
                            }
                            count2++;  
                        }  
                    }
                    count1++;                  
                }   
            }
        }
    }
    return false;
}

/*
v
*/


void printTableCalculated(int M, vector<vector<vector<int>>> &tableCalculated) {
    cout << "TableCalculated:\n";
    for (int i = 0; i < M; i++) {
        for (int f = i; f < M; f++) {
            cout << "Interval [" << (i) << ", " << (f) << "]: ";
            if (tableCalculated[i][f].empty()) {
                cout << "Empty";
            } else {
                for (int val : tableCalculated[i][f]) {
                    cout << val << " ";
                }
            }
            cout << "\n";
        }
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int N, M, target;

    vector<vector<vector<int>>> tableCalculated = readInput(&N, &M, &target);

    if (calculate(N, M, target, tableCalculated)) {
        cout << "1\n";
        // cout << printResult();
    }
    else
        cout << "0\n";
    printTableCalculated(M, tableCalculated);

    return 0;
}

/*
[[[2, 0], [1, 1], [2, 2, 1, 1], [2, 3, 2, 2, 1, 1]],
 [[2, 0], [2, 1], [2, 2]],
 [[3, 0], [3, 1]],
 [[3, 0]]]
*/












/*
    for (int d = 1; d < M; d++) {
        for (int i = 0; i <= (M - d); i++) {
            int j = i + 1;
            if (d == 1) 
                tableCalculated[i][j][0] = tableRef[tableCalculated[i][i][0] - 1][tableCalculated[j][j][0] - 1];
            else {
                int pos = 0;
                for (int k = d - 1; k >= i; k--) {
                    
                    
                }
            }
        }
    }

    return 0;
}
*/

/*

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <unordered_map>

using namespace std;

// Função para construir a parentização a partir da matriz de pares
string constructParentization(const vector<vector<pair<int, int>>>& parent, int i, int j) {
    if (i == j) return to_string(i + 1); // Elemento único
    int k = parent[i][j].first;
    return "(" + constructParentization(parent, i, k) + constructParentization(parent, k + 1, j) + ")";
}

int main() {
    int n, m;
    cin >> n >> m;

    // Leitura da tabela de operações ⊕
    vector<vector<int>> table(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> table[i][j];

    // Leitura da sequência
    vector<int> sequence(m);
    for (int i = 0; i < m; ++i) cin >> sequence[i];

    // Leitura do valor desejado
    int target;
    cin >> target;

    // DP e matriz de parentização
    vector<vector<set<int>>> dp(m, vector<set<int>>(m));
    vector<vector<pair<int, int>>> parent(m, vector<pair<int, int>>(m));

    // Casos base
    for (int i = 0; i < m; ++i) dp[i][i].insert(sequence[i]);

    // Preenchimento da tabela DP
    for (int len = 2; len <= m; ++len) {
        for (int i = 0; i + len - 1 < m; ++i) {
            int j = i + len - 1;
            for (int k = i; k < j; ++k) {
                for (int a : dp[i][k]) {
                    for (int b : dp[k + 1][j]) {
                        int result = table[a - 1][b - 1];
                        dp[i][j].insert(result);
                        if (dp[i][j].count(target)) {
                            parent[i][j] = {k, j};
                        }
                    }
                }
            }
        }
    }

    // Verificação do valor desejado
    if (dp[0][m - 1].count(target)) {
        cout << "1\n";
        cout << constructParentization(parent, 0, m - 1) << endl;
    } else {
        cout << "0\n";
    }

    return 0;
}
*/