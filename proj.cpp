#include <cstdio>
#include <vector>
#include <list>
#include <iostream>
using namespace std;

int N, M, target;
vector<vector<int>> tableRef;
vector<int> sequence;

void readInput() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cin >> tableRef[i][j];
    }
    for (int i = 0; i < M; i++)
        cin >> sequence[i];
    cin >> target;

}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    readInput();

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