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
                    if (count1 % 2 == 0) {    // Verifica se o val1 é um valor calculado ou um k
                        for (int val2 : tableCalculated[k][f]) {
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
string printResult(int i, int j, int k, vector<vector<vector<int>>> &tableCalculated, int val) {
    if (i == j)
        return to_string(tableCalculated[i][j][0]);
    else if (i == (j - 1))
        return "(" + printResult(i, i, 0, tableCalculated)  + " " + printResult(j, j, 0, tableCalculated) + ")";
    else {
        for (int indice = 0;  : tableCalculated[i][j])


        return "(" + printResult(i, k-1, novo_k, tableCalculated) + " )" + printResult(k, j, novo_k2, tableCalculated);
    }
}
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
