#include "functions.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
void create_tests() {
    using namespace std;

    ofstream f1("f9.bin", ios::binary);
    double d9[] = {1.1, 2.2, 3.3, 4.4, 10.5}; 
    for(double d : d9) f1.write((char*)&d, sizeof(double));
    f1.close();

    ofstream f2("f32.bin", ios::binary);
    int i32[] = {1, 2, 3, 100, 200, 300};
    for(int i : i32) f2.write((char*)&i, sizeof(int));
    f2.close();

    double v1[] = {9.0, 6.0}, v2[] = {8.0, 5.0}, v3[] = {7.0, 4.0};
    ofstream s1("s1.bin", ios::binary), s2("s2.bin", ios::binary), s3("s3.bin", ios::binary);
    for(double d : v1) s1.write((char*)&d, sizeof(double));
    for(double d : v2) s2.write((char*)&d, sizeof(double));
    for(double d : v3) s3.write((char*)&d, sizeof(double));
    s1.close(); s2.close(); s3.close();

    cout << "Тестовые бинарные файлы (f9.bin, f32.bin, s1.bin, s2.bin, s3.bin) созданы!" << endl;
}

void print_file_double(std::string name) {
    using namespace std;
    ifstream in(name, ios::binary);
    if (!in) { cout << "Файл не открыт!" << endl; return; }
    double val;
    cout << "Содержимое " << name << ": ";
    while (in.read((char*)&val, sizeof(double))) {
        cout << val << " ";
    }
    cout << endl;
    in.close();
}

void print_file_int(std::string name) {
    using namespace std;
    ifstream in(name, ios::binary);
    if (!in) { cout << "Файл не открыт!" << endl; return; }
    int val;
    cout << "Содержимое " << name << ": ";
    while (in.read((char*)&val, sizeof(int))) {
        cout << val << " ";
    }
    cout << endl;
    in.close();
}

void file9(){
    using namespace std;
    string f_exist, f_new;
    cout << "Введите имя существующего файла: ";
    cin >> f_exist;
    cout << "Введите имя нового файла: ";
    cin >> f_new;

    ifstream in(f_exist, ios::binary);
    if (!in) {
        cout << "Ошибка открытия файла!" << endl;
        return;
    }
    double first, last;

    if (!in.read((char*)&first, sizeof(double))) {
        cout << "Файл пуст!" << endl;
        return;
    }

    in.seekg(-(int)sizeof(double), ios::end); 
    
    if (!in.read((char*)&last, sizeof(double))) {
        last = first;
    }

    in.close();

    ofstream out(f_new, ios::binary);
    if (out) {
        out.write((char*)&last, sizeof(double));  
        out.write((char*)&first, sizeof(double)); 
        out.close();
        cout << "Готово! Записаны числа: " << last << " и " << first << endl;
    }
    print_file_double(f_exist);
    print_file_double(f_new);
}

void file32(){
    using namespace std;
    string fname;
    cout << "Введите имя файла: ";
    cin >> fname;

    cout << "Файл до удаления половины" << endl;
    print_file_int(fname);

    ifstream in(fname, ios::binary);
    if (!in){
        cout << "Файл не найден!" << endl;
        return;
    }
        vector<int> buffer;
        int val;
        while(in.read((char*)&val, sizeof(int))){
            buffer.push_back(val);
        }
        in.close();
        ofstream out(fname, ios::binary | ios::trunc);
        for(size_t i = buffer.size() / 2; i < buffer.size(); i++){
            out.write((char*)&buffer[i], sizeof(int));

        }
        out.close();
        cout << "Файл после удаления первой половины" << endl;
        print_file_int(fname); 

}

void file51() {
    using namespace std;

    string s1, s2, s3, s4;
    cout << "Введите имена 3-х исходных файлов и финальный: ";
    cin >> s1 >> s2 >> s3 >> s4;

    ifstream f1(s1, ios::binary);
    ifstream f2(s2, ios::binary);
    ifstream f3(s3, ios::binary);
    ofstream out(s4, ios::binary);
    print_file_double(s1);
    print_file_double(s2);
    print_file_double(s3);
    print_file_double(s4);

    double v1, v2, v3;
    bool has1 = bool(f1.read((char*)&v1, sizeof(double)));
    bool has2 = bool(f2.read((char*)&v2, sizeof(double)));
    bool has3 = bool(f3.read((char*)&v3, sizeof(double)));

    while (has1 || has2 || has3) {
        double max_val;
        if (has1 && (!has2 || v1 >= v2) && (!has3 || v1 >= v3)) {
            max_val = v1;
            out.write((char*)&max_val, sizeof(double));
            has1 = bool(f1.read((char*)&v1, sizeof(double)));
        } 
        else if (has2 && (!has3 || v2 >= v3)) {
            max_val = v2;
            out.write((char*)&max_val, sizeof(double));
            has2 = bool(f2.read((char*)&v2, sizeof(double)));
        } 
        else if (has3) {
            max_val = v3;
            out.write((char*)&max_val, sizeof(double));
            has3 = bool(f3.read((char*)&v3, sizeof(double)));
        }
    }

    f1.close(); f2.close(); f3.close(); out.close();

    cout << "Файлы проанализированы и объединены по убыванию." << endl;
    print_file_double(s4); 
}
int term(std::string& s){
    int last = s.back() - '0';
    s.pop_back();

    if(!s.empty() && s.back() == '*'){
        s.pop_back();
        return term(s) * last;
    }
    return last;
}

int Pl_or_mi(std::string s) {
    using namespace std;
    size_t plus = s.find_last_of('+');
    size_t minus = s.find_last_of('-');
    
    int opPos = -1;
    if (plus != string::npos || minus != string::npos) {
        if (plus == string::npos) opPos = (int)minus;
        else if (minus == string::npos) opPos = (int)plus;
        else opPos = (int)max(plus, minus);
    }

    if (opPos == -1) return term(s);

    char sign = s[opPos];
    string leftPart = s.substr(0, opPos);
    string rightPart = s.substr(opPos + 1);

    if (sign == '+') return Pl_or_mi(leftPart) + Pl_or_mi(rightPart);
    return Pl_or_mi(leftPart) - term(rightPart);
}

void recur15(){
    using namespace std;
    string expr;
    cout << "Введите выражение (цифры и знаки +, -, *): ";
    cin >> expr;
    cout << "Результат вычисления: " << Pl_or_mi(expr) << endl;
}
