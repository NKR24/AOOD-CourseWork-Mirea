#include <iostream>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <fstream>

using namespace  std;

using Pages = std::set<size_t>;

class TermManager {
private:
    map<string, Pages> terms; // [термин, страницы]
public:
    TermManager() = default; // Создание пустого предметного указателя

    void AddTerm(const string& term) {
        terms[term];
    }

    void AddRef(const string& term, size_t page) {
        terms[term].insert(page);
    }

    void ChangePage(const string& term, size_t page_prew, size_t new_val) {
        terms[term].erase(page_prew);
        terms[term].insert(new_val);
    }

    // Поиск по предметному указателю
    const Pages& getPages(const string& term) const {
        return terms.at(term);
    }

    friend void PrintTermManager(ostream& out, const TermManager& tm);
};

void PrintTermManager(ostream& out, const TermManager& tm) {
    for (const auto& [term, pages] : tm.terms) {
        out << term << " ";
        for (const auto& page : pages) {
            out << " " << page;
        }
        out << "\n";
    }
}

void WriteToFile(const string& path, const TermManager& tm) {
    ofstream out(path);
    PrintTermManager(out, tm);
    out.close();
}

Pages ParsePages(istream& is) {
    Pages p;
    for (size_t page; is >> page;) {
        p.insert(page);
    }
    return p;
}

int main() {
    setlocale(0, "Russian");
    cout << "========================================================\n";
    cout << "Reading from console, enter query_count\n";
    cout << "Adding test\n" << "Enter query count\n";
    int query_count;

    cin >> query_count;
    TermManager tm;
    // создание пустого предметного указателя
   // чтение
    for (int q = 0; q < query_count; q++) {
        string term;
        cin >> term;
        size_t page;
        cin >> page;
        // добавление элементов к
        tm.AddTerm(term);  // добавит просто значение, но страницу не добавит
        tm.AddRef(term, page);  // добавит термин, если его не было раньше, добавит страницу к существующему термину, если термин уже есть
    }
a:
    int choice = 0;
    cout << "1. Поиск" << endl;
    cout << "2. Изменить значение" << endl;
    cout << "3. Прочитать файл" << endl;
    cout << "4. Выход" << endl;
    cin >> choice;

    switch (choice)
    {
    case 1: {
        WriteToFile("output.txt", tm);      // вывод в файл
        PrintTermManager(cout, tm);
        cout << "========================================================\n";
        cout << "Searching test\n" << "Enter query count\n";
        cin >> query_count;

        for (int q = 0; q < query_count; q++) {
            cout << "searching term: \n";
            string term;
            cin >> term;

            try {
                const Pages found_value = tm.getPages(term);
                for (size_t element : found_value) {
                    cout << element << " ";
                }
                cout << endl;
            }
            catch (...) {
                cout << "not found!\n";
            }
        }
        goto a;
        break;

    }
    case 2: {
        cout << "========================================================\n";
        cout << "Change term test\n";

        cout << "Searching test\n" << "Enter query count\n";
        cin >> query_count;

        for (int q = 0; q < query_count; q++) {
            cout << "searching term: \n";
            string term;
            cin >> term;
            size_t last_v, new_v;
            cout << "enter last value\n";
            cin >> last_v;
            cout << "enter new value\n";
            cin >> new_v;
            tm.ChangePage(term, last_v, new_v);
        }
        PrintTermManager(cout, tm);
        goto a;
        break;
    }
    case 3: {
        cout << "========================================================\n";
        cout << "Reading from file\n";

        ifstream is("output.txt");
        TermManager tm; // создание пустого предметного указателя
        for (string line; getline(is, line);) {
            istringstream ss(line);

            string term;
            ss >> term;

            for (auto val : ParsePages(ss)) {
                tm.AddRef(term, val);
            }

        }
        goto a;
        break;
    }
    case 4: {
        ifstream is("output.txt");
        PrintTermManager(cout, tm);
        cout << "Incorrect input" << endl;
        is.close();
        return 0;
    }
    }
}
