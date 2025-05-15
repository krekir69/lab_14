#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Файлы по умолчанию
const string INPUT_FILE = "input.txt";
const string MATRIX_FILE = "matrix.txt";
const string LIST_FILE = "adjlist.txt";
const string LISTSM_FILE = "LISTSM_FILE.txt";

// Упр.1:  Матрица смежности
void buildMatrix(const string& inFile, const string& outFile) {
    ifstream fin(inFile);
    ofstream fout(outFile);
    if (!fin && !fout) {
        cout << " Ошибка открытия файла\n";
        return;
    }

    int n, m, i, j, k;
    fin >> n >> m;   
    int** M = new int* [n];
    for (i = 0; i < n; i++) {
        M[i] = new int[n];
        for (j = 0; j < n; j++) M[i][j] = 0;
    }

    for (k = 0; k < m; k++) {
        fin >> i >> j;
        if (i >= 0 && i < n && j >= 0 && j < n) {
            M[i][j] = 1;
            M[j][i] = 1;
        }
    }

    fout << n << " " << n << "\n";
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fout << M[i][j] << (j + 1 < n ? ' ' : '\n');
        }
        delete[] M[i];
    }
    delete[] M;
    cout << "[1] Матрица смежности записана в " << outFile << "\n";
}

// Упр.2: из матрицы смежности строим списки смежных вершин
void buildAdjList(const string& inFile, const string& outFile) {
    ifstream fin(inFile);
    ofstream fout(outFile);
    if (!fin && !fout) {
        cout << " Ошибка открытия файла\n";
        return;
    }

    int n, cols;
    fin >> n >> cols;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < cols; ++j) {
            int x;
            fin >> x;
            if (x == 1) {
                adj[i].push_back(j ); 
            }
        }
    }

    fout << n << "\n";
    for (int i = 0; i < n; ++i) {
        fout << adj[i].size();
        for (int v : adj[i]) fout << ' ' << v;
        fout << "\n";
    }
    cout << "[Упр.2] Списки смежности записаны в " << outFile << "\n";
}

// Упр.3: из списка смежности формируем последовательность рёбер
void buildEdgeSequence(const string& inFile, const string& outFile) {
    ifstream fin(inFile);
    ofstream fout(outFile);
    if (!fin && !fout) {
        cout << " Ошибка открытия файла\n";
        return;
    }

    int n;
    fin >> n;
    if (fin.fail() && n <= 0) {
        cout << "[Упр.3] Ошибка чтения числа вершин из " << inFile << endl;
        return;
    }

    vector<pair<int, int>> edges;
    for (int u = 0; u < n; ++u) {
        int len;
        fin >> len;
        for (int k = 0; k < len; ++k) {
            int v;
            fin >> v;
            if (u <= v) edges.emplace_back(u, v);
        }
    }

    fout << edges.size() << "\n";
    for (auto& e : edges) {
        fout << e.first << " " << e.second << "\n";
    }
    cout << "[Упр.3] Последовательность рёбер записана в " << outFile << "\n";
}

int main() {
    setlocale(LC_ALL, "Ru"); 
    
            buildMatrix(INPUT_FILE, MATRIX_FILE);
            buildAdjList(MATRIX_FILE, LIST_FILE);
            buildEdgeSequence(LIST_FILE, LISTSM_FILE);
           
        

    return 0;
}