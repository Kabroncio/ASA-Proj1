#include <cstdio>
#include <vector>
#include <list>
#include <iostream>
using namespace std;

int N, M, target;
vector<vector<int>> tableRef;
vector<vector<vector<int>>> tableCalculated;

void readInput() {
    cin >> N >> M;
    tableRef.resize(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cin >> tableRef[i][j];
    }
    tableCalculated.resize(M, vector<vector<int>>(M, vector<int>(M)));
    for (int i = 0; i < M; i++) {
        cin >> tableCalculated[i][i][0];
        tableCalculated[i][i][1] = 0;
    }
    cin >> target;
}

void calculate() {
    for (int len = 2; len < M; len++) {
        for (int i = 0; (i + len) < M; i++) {
            int f = i + len - 1;
            for (int k = f; k > i; k--) {
                int res = tableRef[tableCalculated[i][k - 1][0]][tableCalculated[k][f][0]];
                tableCalculated[i][f].push_back(res);
                //tableCalculated[i][f].push_back(k);
            }
        }
    }
}

// 2 2 2 2 1 3
// 0 1 2 3 4 5

void printTableCalculated() {
    cout << "TableCalculated:\n";
    for (int i = 0; i < M; i++) {
        for (int f = i; f < M; f++) {
            cout << "Interval [" << (i+1) << ", " << (f+1) << "]: ";
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

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    readInput();
    calculate();
    printTableCalculated();

    return 0;
}













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