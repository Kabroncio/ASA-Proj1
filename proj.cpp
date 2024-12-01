#include <cstdio>
#include <vector>
#include <iostream>
#include <memory> // Para std::shared_ptr
using namespace std;

struct Values {
    int val;
    int k;
    shared_ptr<Values> prev1;
    shared_ptr<Values> prev2;
};

vector<vector<int>> tableRef;

vector<vector<vector<shared_ptr<Values>>>> readInput(int* N, int* M, int* target) {
    cin >> *N >> *M;
    tableRef.resize(*N, vector<int>(*N));
    for (int i = 0; i < *N; i++) {
        for (int j = 0; j < *N; j++)
            cin >> tableRef[i][j];
    }
    vector<vector<vector<shared_ptr<Values>>>> tableCalculated(*M, vector<vector<shared_ptr<Values>>>(*M, vector<shared_ptr<Values>>()));    for (int i = 0; i < *M; i++) {
        int num;
        cin >> num;
        auto val = make_shared<Values>(Values{num, 0, nullptr, nullptr});
        tableCalculated[i][i].push_back(val);
    }
    cin >> *target;
    
    return tableCalculated;
}

bool calculate(int N, int M, int target, vector<vector<vector<shared_ptr<Values>>>> &tableCalculated) {
    for (int len = 2; len <= M; len++) {    // Vai iterando sobre a sequencia inicial com os varios tamanhos possiveis ate M
        for (int i = 0; (i + len) <= M; i++) {  // Vai a cada linha
            int f = i + len - 1;    // Obtem o ultimo indice do termo da sequencia a ser observada
            for (int k = f; k > i; k--) {   // Vai com o K desde o penultimo elemento ate o segundo
                for (auto& val_prev1 : tableCalculated[i][k - 1]) {          
                    for (auto& val_prev2 : tableCalculated[k][f]) {
                        int res = tableRef[val_prev1->val - 1][val_prev2->val - 1];
                        // if (find(tableCalculated[i][f].begin(), tableCalculated[i][f].end(), res) == tableCalculated[i][f].end()) { //Verifica se o res ja existe
                        auto atual = make_shared<Values>(Values{res, k, val_prev1, val_prev2});
                        tableCalculated[i][f].push_back(atual);
                        if (len == M && res == target) { // Verifica se o res da ultima linha é aquele que se quer obter
                            return true;
                        }
                        
                    }        
                }   
            }
        }
    }
    return false;
}


string printResult(int i, int j, shared_ptr<Values> atual) {
    //printf("Val: %d, K: %d\n",atual->val, atual->k); //////////////////////////////////////

    if (i == j)
        return to_string(atual->val);
    
    if (i == j - 1)
        return "(" + printResult(i, i, atual->prev1) + " " + printResult(j, j, atual->prev2) + ")";
    
    return "(" + printResult(i, atual->k - 1, atual->prev1) + " " + printResult(atual->k, j, atual->prev2) + ")";
}



int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int N, M, target;

    auto tableCalculated = readInput(&N, &M, &target);

    if (calculate(N, M, target, tableCalculated)) {
        cout << "1\n";
        cout << printResult(0, M-1, tableCalculated[0][M-1].back()) << endl;
    }
    else
        cout << "0\n";
    
    // printTableCalculated(M, tableCalculated);

    return 0;
}


/*

*/

/*
void printTableCalculated(int M, const vector<vector<vector<Values>>> &tableCalculated) {
    cout << "TableCalculated:\n";

    for (int i = 0; i < M; i++) {
        for (int j = i; j < M; j++) {
            cout << "Interval [" << i << ", " << j << "]:\n";
            if (tableCalculated[i][j].empty()) {
                cout << "  Empty\n";
            } else {
                for (const auto &val : tableCalculated[i][j]) {
                    cout << "  Value: " << val.val
                         << ", k: " << val.k;

                    if (val.prev1) {
                        cout << ", Prev1: " << val.prev1->val;
                    } else {
                        cout << ", Prev1: null";
                    }

                    if (val.prev2) {
                        cout << ", Prev2: " << val.prev2->val;
                    } else {
                        cout << ", Prev2: null";
                    }

                    cout << "\n";
                }
            }
        }
    }
}
*/


/*
[[[2, 0], [1, 1], [2, 2, 1, 1], [2, 3, 2, 2, 1, 1]],
 [[2, 0], [2, 1], [2, 2]],
 [[3, 0], [3, 1]],
 [[3, 0]]]
*/
