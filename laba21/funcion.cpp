#include "funcion.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <vector>

// Считать целое число
int Check::readInt(const char* text){
    using namespace std;

    int x;

    while(true){
        cout << text;

        if(cin >> x){
            return x;
        }

        cout << "Ошибка ввода. Введите целое число.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Считать целое число не меньше minValue
int Check::readIntMin(const char* text, int minValue){
    using namespace std;

    while(true){
        int x = readInt(text);

        if(x >= minValue){
            return x;
        }

        cout << "Число должно быть >= " << minValue << ".\n";
    }
}

// Считать целое число в диапазоне
int Check::readIntRange(const char* text, int left, int right){
    using namespace std;

    while(true){
        int x = readInt(text);

        if(x >= left && x <= right){
            return x;
        }

        cout << "Число должно быть в диапазоне [" << left << "; " << right << "].\n";
    }
}

// Создать пустой граф
Graph::Graph() : n(0){
}

// Проверить, пустой ли граф
bool Graph::empty() const{
    return n == 0;
}

// Получить количество вершин
int Graph::size() const{
    return n;
}

// Заполнить граф с клавиатуры
bool Graph::fillKeyboard(int maxN){
    using namespace std;

    n = Check::readIntRange("Количество вершин: ", 1, maxN);
    a.assign(n, vector<int>(n, 0));

    cout << "Введите матрицу смежности:\n";

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            a[i][j] = Check::readIntRange("0 или 1: ", 0, 1);
        }
    }

    return true;
}

// Заполнить граф из файла
bool Graph::fillFile(const std::string& fileName, int maxN){
    using namespace std;

    ifstream fin(fileName);

    if(!fin.is_open()){
        return false;
    }

    if(!(fin >> n) || n < 1 || n > maxN){
        return false;
    }

    a.assign(n, vector<int>(n, 0));

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(!(fin >> a[i][j])){
                return false;
            }

            if(a[i][j] != 0){
                a[i][j] = 1;
            }
        }
    }

    return true;
}

// Заполнить граф случайно
bool Graph::fillRandom(int maxN, bool directed){
    using namespace std;

    n = Check::readIntRange("Количество вершин: ", 1, maxN);
    a.assign(n, vector<int>(n, 0));

    static bool seeded = false;
    if(!seeded){
        srand((unsigned)time(nullptr));
        seeded = true;
    }

    if(directed){
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                if(i != j){
                    a[i][j] = rand() % 2;
                }
            }
        }
    }
    else{
        for(int i = 0; i < n; ++i){
            for(int j = i + 1; j < n; ++j){
                int value = rand() % 2;
                a[i][j] = value;
                a[j][i] = value;
            }
        }
    }

    cout << "Сгенерированная матрица:\n";
    print();

    return true;
}

// Вывести матрицу смежности
void Graph::print() const{
    using namespace std;

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cout << a[i][j] << ' ';
        }
        cout << '\n';
    }
}

// Обход в ширину, расстояния в ребрах
std::vector<int> Graph::bfs(int start) const{
    std::vector<int> dist(n, -1);
    std::queue<int> q;

    dist[start] = 0;
    q.push(start);

    while(!q.empty()){
        int v = q.front();
        q.pop();

        for(int to = 0; to < n; ++to){
            if(a[v][to] != 0 && dist[to] == -1){
                dist[to] = dist[v] + 1;
                q.push(to);
            }
        }
    }

    return dist;
}

// Graf2: построить матрицу инцидентности
void Graph::writeIncidenceMatrix(const std::string& fileName) const{
    using namespace std;

    vector<pair<int, int> > edges;

    for(int i = 0; i < n; ++i){
        for(int j = i; j < n; ++j){
            if(a[i][j] != 0){
                edges.push_back(make_pair(i, j));
            }
        }
    }

    ofstream fout(fileName);

    if(!fout.is_open()){
        cout << "Не удалось открыть выходной файл\n";
        return;
    }

    fout << n << ' ' << edges.size() << '\n';

    for(int i = 0; i < n; ++i){
        for(size_t e = 0; e < edges.size(); ++e){
            int value = 0;

            if(edges[e].first == i || edges[e].second == i){
                value = 1;
            }

            fout << value << ' ';
        }
        fout << '\n';
    }

    cout << "Матрица инцидентности записана в файл: " << fileName << '\n';
}

// Graf7: общие города для двух штаб-квартир
void Graph::printCommonCities(int k1, int k2, int l) const{
    using namespace std;

    vector<int> d1 = bfs(k1 - 1);
    vector<int> d2 = bfs(k2 - 1);
    int maxEdges = l + 1;
    bool found = false;

    cout << "Города: ";

    for(int i = 0; i < n; ++i){
        if(d1[i] != -1 && d2[i] != -1 && d1[i] <= maxEdges && d2[i] <= maxEdges){
            cout << i + 1 << ' ';
            found = true;
        }
    }

    if(!found){
        cout << -1;
    }

    cout << '\n';
}

// Graf8: города, где кратчайший путь имеет не меньше L пересадок
void Graph::printCitiesFromKWithMinTransfers(int k, int l) const{
    using namespace std;

    vector<int> dist = bfs(k - 1);
    bool found = false;

    cout << "Города: ";

    for(int i = 0; i < n; ++i){
        if(i == k - 1 || dist[i] == -1){
            continue;
        }

        int transfers = dist[i] - 1;

        if(transfers >= l){
            cout << i + 1 << ' ';
            found = true;
        }
    }

    if(!found){
        cout << -1;
    }

    cout << '\n';
}
// Выбрать способ заполнения графа
static bool fillGraph3Ways(Graph& g, int maxN, bool directed){
    using namespace std;

    int mode = Check::readIntRange("Заполнение: 1-клавиатура, 2-файл, 3-случайно: ", 1, 3);

    if(mode == 1){
        return g.fillKeyboard(maxN);
    }

    if(mode == 2){
        string fileName;
        cout << "Имя файла: ";
        cin >> fileName;
        return g.fillFile(fileName, maxN);
    }

    return g.fillRandom(maxN, directed);
}

// Задание 1: Graf2
void Graf2(){
    using namespace std;

    Graph g;

    if(!fillGraph3Ways(g, 50, false)){
        cout << "Ошибка заполнения графа\n";
        return;
    }

    cout << "Матрица смежности:\n";
    g.print();

    string outFileName;
    cout << "Имя выходного файла: ";
    cin >> outFileName;

    g.writeIncidenceMatrix(outFileName);
}

// Задание 2: Graf7
void Graf7(){
    using namespace std;

    Graph g;

    if(!fillGraph3Ways(g, 25, false)){
        cout << "Ошибка заполнения графа\n";
        return;
    }

    int k1 = Check::readIntRange("K1: ", 1, g.size());
    int k2 = Check::readIntRange("K2: ", 1, g.size());

    while(k2 == k1){
        cout << "K1 и K2 должны быть разными.\n";
        k2 = Check::readIntRange("K2: ", 1, g.size());
    }

    int l = Check::readIntMin("L пересадок: ", 0);

    g.printCommonCities(k1, k2, l);
}

// Задание 3: Graf8
void Graf8(){
    using namespace std;

    Graph g;

    if(!fillGraph3Ways(g, 15, true)){
        cout << "Ошибка заполнения графа\n";
        return;
    }

    int k = Check::readIntRange("K: ", 1, g.size());
    int l = Check::readIntMin("L пересадок: ", 0);

    g.printCitiesFromKWithMinTransfers(k, l);
}

// Котик после завершения программы
void printCat(){
    using namespace std;

    cout << " /\\_/\\\\\n";
    cout << "( o.o )\n";
    cout << " > ^ <\n";
}
