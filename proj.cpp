#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;

void readInput(int* N, int* M, int* target, vector<vector<int>> &tableRef, vector<vector<vector<int>>> &tableCalculated) {
    cin >> *N >> *M;
    tableRef.resize(*N, vector<int>(*N));
    for (int i = 0; i < *N; i++) {
        for (int j = 0; j < *N; j++)
            cin >> tableRef[i][j];
    }
    tableCalculated.resize(*M, vector<vector<int>>(*M, vector<int>()));
    for (int i = 0; i < *M; i++) {
        int num;
        cin >> num;
        tableCalculated[i][i].insert(tableCalculated[i][i].end(), {num, 0, 0, 0});
    }
    cin >> *target;
}

bool calculate(int N, int M, int target, vector<vector<vector<int>>> &tableCalculated, vector<vector<int>>& tableRef) {
    for (int len = 2; len <= M; len++) {    // Cria subsequencias da sequencia inicial com todos os tamanhos possiveis desde 2 ate M
        for (int i = 0; (i + len) <= M; i++) {    // Obtem o valor inicial e verifica se o tamanho excede o tamanho da sequencia inicial
            int f = i + len - 1;    // Obtem o valor final da subsequencia
            vector<int> usedResults(N, false);    // Cria um vetor temporario para verificar se os valores ja foram inseridos na tableCalculated
            for (int k = f; k > i; k--) {    // Avalia todos os pontos possiveis para dividir a subsequencia
                if (tableCalculated[i][f].size() / 4 >= static_cast<size_t>(N)) continue;    // Verifica se ja existe todos os resultados possiveis
                size_t sizeLeft = tableCalculated[i][k - 1].size();
                size_t sizeRight = tableCalculated[k][f].size();  
                for (size_t valLeft = 0; valLeft < sizeLeft; valLeft += 4) {          
                    for (size_t valRight = 0; valRight < sizeRight; valRight += 4) {
                        int res = tableRef[tableCalculated[i][k-1][valLeft] - 1][tableCalculated[k][f][valRight] - 1];    // Ve qual o valor correspondente da tableRef
                        if (usedResults[res - 1] == false) {
                            tableCalculated[i][f].insert(tableCalculated[i][f].end(), {res, k, static_cast<int>(valLeft), static_cast<int>(valRight)});    // Adiciona a tableCalculated o resultado, o ponto de divisao da subsequencia e o indice dos resultados utilizados
                            usedResults[res - 1] = true;    // Marca que o resultado ja foi verificado                    
                            if (len == M && res == target) return true; // Verifica se o res da ultima linha é aquele que se quer obter
                        } 
                    }
                }                 
            }
        }
    }
    return false;
}

string printResult(int i, int j, int valIndice, vector<vector<vector<int>>> &tableCalculated) {
    if (i == j)
        return to_string(tableCalculated[i][j][0]);
    else{
        int k = tableCalculated[i][j][valIndice + 1];
        int v1 = tableCalculated[i][j][valIndice + 2];
        int v2 = tableCalculated[i][j][valIndice + 3];
        return "(" + printResult(i, k - 1, v1, tableCalculated) + " " + printResult(k, j, v2, tableCalculated) + ")";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, M, target;
    vector<vector<int>> tableRef;
    vector<vector<vector<int>>> tableCalculated;

    readInput(&N, &M, &target, tableRef, tableCalculated);

    if (M == 1)
        (tableCalculated[0][0][0] == target) ? (cout << "1\n" << to_string(tableCalculated[0][0][0]) << endl) : cout << "0\n";    // Imprime o valor da sequencia sem parenteses se ela so tiver um valor
    else if (calculate(N, M, target, tableCalculated, tableRef))
        cout << "1\n" << printResult(0, M-1, tableCalculated[0][M-1].size() - 4, tableCalculated) << endl;
    else
        cout << "0\n";

    return 0;
}