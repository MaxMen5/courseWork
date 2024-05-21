#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int toint(string str) {
    int* arr = new int[str.size()];
    for (int i = 0; i < str.size(); i++) {
        arr[i] = str[i] - 48;
    }
    int num = 0, k = 0;
    for (int i = str.size() - 1; i >= 0; i--, k++) {
        num += arr[i] * pow(10, k);
    }
    return num;
}
int* tointarr(string str) {
    int arr[5] = {}, k = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] != ' ') {
            arr[k] = str[i] - 48;
            k++;
        }
    }
    return arr;
}
void menu() {
    cout << "1 - Консольный ввод данных о студентах\n";
    cout << "2 - Консольный вывод данных о студентах\n";
    cout << "3 - Файловый ввод данных о студентах\n";
    cout << "4 - Файловый вывод данных о студентах\n";
    cout << "5 - Удаление студента\n";
    cout << "6 - Добавление группы студентов\n";
    cout << "7 - Удаление группы студентов\n";
    cout << "8 - Вывод списка студентов группы, содержащей максимальное количество хорошистов и отличников\n";
    cout << "9 - Очищение базы данных\n";
    cout << "0 - Завершение работы программы\n\n";
}

struct Group {
    int group = 0;
    int best = 0;
};
struct Info {
    string name = "";
    int group = 0;
    int marks[5] = {};
    int stipa = 0;
    string mail = "";
    bool best = false;
};
template <typename T>
struct Node {
    T info;
    Node* next = nullptr;
    Node* prev = nullptr;
};
template <typename T>
struct List {
    int counting = 0;
    int position = 0;
    Node<T>* now = nullptr;
    Node<T>* first = nullptr;
    Node<T>* last = nullptr;

    void toIndex(int index) {
        if (abs(index - position) > (counting - 1 - index)) {
            now = last;
            position = counting - 1;
        }
        else if (abs(index - position) > index) {
            now = first;
            position = 0;
        }
        if (index > position) { for (int i = 0; i < index - position; i++) { now = now->next; } }
        else { for (int i = 0; i < position - index; i++) { now = now->prev; } }
        position = index;
    }

    void add(T info) {
        Node<T>* node = new Node<T>();
        node->info = info;
        if (counting == 0) {
            first = node;
            last = node;
            now = node;
        }
        else {
            node->prev = last;
            last->next = node;
            last = node;
        }
        counting++;
    }

    void removeAt(int index) {
        if (index < 0 || index >= counting) { throw 0; }
        toIndex(index);
        Node<T>* del = now;
        if (last == first) {
            clear();
            return;
        }
        if (del == last) {
            last = last->prev;
            last->next = nullptr;
            now = last;
            position--;
        }
        else if (del == first) {
            first = first->next;
            first->prev = nullptr;
            now = first;
        }
        else {
            now = now->next;
            del->next->prev = del->prev;
            del->prev->next = del->next;
        }
        delete del;
        counting--;
    }

    T elementAt(int index) {
        if (index < 0 || index >= counting) { throw 0; }
        toIndex(index);
        return now->info;
    }

    int count() { return counting; }

    void clear() {
        int kol = counting;
        for (int i = 0; i < kol; i++) {
            Node<T>* del = first;
            first = first->next;
            delete del;
        }
        last = nullptr;
        now = nullptr;
        position = 0;
        counting = 0;
    }
};

void fileInput(List<Info>& list) {
    Info info;
    ifstream input;
    input.open("input.txt");
    string str;
    int number = 0;
    double sred = 0;
    int* arr;
    while (getline(input, str)) {
        number++;
        switch (number) {
        case 1:
            info.name = str;
            break;
        case 2:
            info.group = toint(str);
            break;
        case 3:
            arr = tointarr(str);
            for (int i = 0; i < 5; i++) {
                info.marks[i] = arr[i];
                sred += arr[i];
            }
            if (sred / 5 > 3.5) { info.best = true; }
        case 4:
            info.stipa = toint(str);
            break;
        case 5:
            info.mail = str;
            list.add(info);
            number = 0;
        }
    }
    input.close();
}
void fileOutput(List<Info> list) {
    ofstream output;
    output.open("output.txt");
    for (int i = 0; i < list.count(); i++) {
        Info info = list.elementAt(i);
        output << info.name << endl;
        output << info.group << endl;
        for (int j = 0; j < 5; j++) { output << info.marks[j] << " "; }
        output << endl << info.stipa << endl;
        output << info.mail << endl;
    }
    output.close();
}

Info inputGr(int group) {
    Info info;
    double sred = 0;
    string name1, name2, name3;
    cout << "Введите ФИО студента: ";
    cin >> name1 >> name2 >> name3;
    info.name = name1 + " " + name2 + " " + name3;
    info.group = group;
    cout << "Введите оценки студента: ";
    for (int i = 0; i < 5; i++) {
        cin >> info.marks[i];
        sred += info.marks[i];
    }
    if (sred / 5 > 3.5) { info.best = true; }
    cout << "Введите размер стипендии студента: ";
    cin >> info.stipa;
    cout << "Введите почту студента: ";
    cin >> info.mail;
    return info;
}
void addGroup(List<Info> &list) {
    int group, kol;
    cout << "Введите группу добавляемых студентов: ";
    cin >> group;
    cout << "Введите количество добавляемых студентов: ";
    cin >> kol;
    for (int i = 0; i < kol; i++) {
        list.add(inputGr(group));
    }
}

Info input() {
    Info info;
    double sred = 0;
    string name1, name2, name3;
    cout << "Введите ФИО студента: ";
    cin >> name1 >> name2 >> name3;
    info.name = name1 + " " + name2 + " " + name3;
    cout << "Введите группу студента: ";
    cin >> info.group;
    cout << "Введите оценки студента: ";
    for (int i = 0; i < 5; i++) {
        cin >> info.marks[i];
        sred += info.marks[i];
    }
    if (sred / 5 > 3.5) { info.best = true; }
    cout << "Введите размер стипендии студента: ";
    cin >> info.stipa;
    cout << "Введите почту студента: ";
    cin >> info.mail;
    return info;
}
void out(Info info) {
    cout << "\nФИО студента: " << info.name;
    cout << "\nГруппа студента: " << info.group;
    cout << "\nОценки студента: ";
    for (int i = 0; i < 5; i++) { cout << info.marks[i] << " "; }
    cout << "\nСтипендия студента : " << info.stipa;
    cout << "\nПочта студента: " << info.mail << "\n";
}

void delStud(List<Info> &list) {
    string name1, name2, name3;
    cout << "Введите ФИО студента: ";
    cin >> name1 >> name2 >> name3;
    name1 = name1 + " " + name2 + " " + name3;
    for (int i = 0; i < list.count(); i++) {
        if (list.elementAt(i).name == name1) {
            list.removeAt(i);
            break;
        }
    }
}
void delGroup(List<Info> &list) {
    int group;
    cout << "Введите группу: ";
    cin >> group;
    for (int i = 0; i < list.count(); i++) {
        if (list.elementAt(i).group == group) { list.removeAt(i); }
    }
}

Group inputGroup(Info info) {
    Group group;
    group.group = info.group;
    group.best = info.best;
    return group;
}
Group inputGroup2(int num, int kol) {
    Group group;
    group.group = num;
    group.best = kol;
    return group;
}
void bestGroup(List<Info> list) {
    List<Group> dellist, newlist;
    for (int i = 0; i < list.count(); i++) { dellist.add(inputGroup(list.elementAt(i))); }
    while (dellist.count() != 0) {
        int kol = dellist.elementAt(0).best;
        int num = dellist.elementAt(0).group;
        for (int i = 1; i < dellist.count(); i++) {
            if (dellist.elementAt(0).group == dellist.elementAt(i).group) {
                kol += dellist.elementAt(i).best;
                dellist.removeAt(i);
                i--;
            }
        }
        newlist.add(inputGroup2(num, kol));
        dellist.removeAt(0);
    }

    int group = 0, best = 0;
    for (int i = 0; i < newlist.count(); i++) {
        if (newlist.elementAt(i).best > best) {
            group = newlist.elementAt(i).group;
            best = list.elementAt(i).best;
        }
    }

    for (int i = 0; i < list.count(); i++) {
        if (list.elementAt(i).group == group) {
            cout << list.elementAt(i).name << "\n";
        }
    }
}

int main() {
    system("chcp 1251>NULL");
    menu();
    List<Info> list;
    int par;
    while (true) {
        cout << "\nВведите команду: ";
        cin >> par;
        switch (par) {
        case 1:
            list.add(input());
            break;
        case 2:
            for (int i = 0; i < list.count(); i++) { out(list.elementAt(i)); }
            break;
        case 3:
            fileInput(list);
            break;
        case 4:
            fileOutput(list);
            break;
        case 5:
            delStud(list);
            break;
        case 6:
            addGroup(list);
            break;
        case 7:
            delGroup(list);
            break;
        case 8:
            bestGroup(list);
            break;
        case 9:
            list.clear();
            break;
        case 0:
            return 0;
        default:
            cout << "Некорректная команда!";
        }
    }
}