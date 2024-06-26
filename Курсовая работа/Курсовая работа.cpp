#include <iostream>
#include <string>
#include <fstream>
using namespace std;
void menu() {
    cout << "\tРАБОТА СО СТУДЕНТАМИ\n";
    cout << "1 - Добавление студента\n";
    cout << "2 - Удаление студента\n";
    cout << "3 - Редактирование данных студента\n";
    cout << "4 - Вывести информацию о студенте\n";
    cout << "5 - Вывести информацию о всех студентах\n";
    cout << "\n\tРАБОТА С ГРУППАМИ\n";
    cout << "6 - Добавление группы студентов\n";
    cout << "7 - Удаление группы студентов\n";
    cout << "8 - Редактирование номера группы\n";
    cout << "9 - Вывести информацию о студентах группы\n";
    cout << "10 - Вывод списка студентов группы, содержащей максимальное количество хорошистов и отличников\n";
    cout << "\n\tРАБОТА С ФАЙЛАМИ\n";
    cout << "11 - Файловый ввод данных о студентах\n";
    cout << "12 - Файловый вывод данных о студентах\n";
    cout << "\n\tЗАВЕРШЕНИЕ РАБОТЫ\n";
    cout << "13 - Очищение базы данных\n";
    cout << "0 - Завершение работы программы\n\n";
}
void redactMenu() {
    cout << "\n1 - Изменить ФИО\n";
    cout << "2 - Изменить группу\n";
    cout << "3 - Изменить оценки\n";
    cout << "4 - Изменить стипендию\n";
    cout << "5 - Изменить номер зачетной книжки\n\n";
    cout << "Выбор: ";
}
void filterMenu() {
    cout << "\n1 - Фильтрация по ФИО\n";
    cout << "2 - Фильтровать по группе\n";
    cout << "3 - Фильтровать по оценкам\n";
    cout << "4 - Фильтровать по стипендии\n";
    cout << "5 - Фильтровать по номеру зачетной книжки\n\n";
    cout << "Выбор: ";
}

int id = 0;

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

struct Group {
    int group = 0;
    int best = 0;
};
struct Info {
    string name = "";
    int group = 0;
    int marks[5] = {};
    int stipa = 0;
    int booknumber = 0;
    int id = 0;
    bool best = true;
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

Info input() {
    Info info;
    string name1, name2, name3;
    cout << "Введите ФИО студента: ";
    cin >> name1 >> name2 >> name3;
    info.name = name1 + " " + name2 + " " + name3;
    cout << "Введите группу студента: ";
    cin >> info.group;
    cout << "Введите оценки студента: ";
    for (int i = 0; i < 5; i++) {
        cin >> info.marks[i];
        if (info.marks[i] < 4) { info.best = false; }
    }
    cout << "Введите размер стипендии студента: ";
    cin >> info.stipa;
    cout << "Введите номер зачетной книжки студента: ";
    cin >> info.booknumber;
    id++;
    info.id = id;
    return info;
}
void out(Info info) {
    cout << "\nФИО студента: " << info.name;
    cout << "\nГруппа студента: " << info.group;
    cout << "\nОценки студента: ";
    for (int i = 0; i < 5; i++) { cout << info.marks[i] << " "; }
    cout << "\nСтипендия студента : " << info.stipa;
    cout << "\nНомер зачетной книжки студента: " << info.booknumber;
    cout << "\nID студента: " << info.id << "\n";
}
Info inputGroup(int group) {
    Info info;
    string name1, name2, name3;
    cout << "Введите ФИО студента: ";
    cin >> name1 >> name2 >> name3;
    info.name = name1 + " " + name2 + " " + name3;
    info.group = group;
    cout << "Введите оценки студента: ";
    for (int i = 0; i < 5; i++) {
        cin >> info.marks[i];
        if (info.marks[i] < 4) { info.best = false; }
    }
    cout << "Введите размер стипендии студента: ";
    cin >> info.stipa;
    cout << "Введите номер зачетной книжки студента: ";
    cin >> info.booknumber;
    id++;
    info.id = id;
    return info;
}
Group inputGroup1(Info info) {
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

/*2*/void deleteStudent(List<Info>& list) {
    cout << "\nВведите ID удаляемого студента: ";
    bool isStudent = false;
    int num;
    cin >> num;
    for (int i = 0; i < list.count(); i++) {
        if (list.elementAt(i).id == num) {
            list.removeAt(i);
            isStudent = true;
            break;
        }
    }
    if (!isStudent) { cout << "Нет студента с таким ID!\n"; }
}
/*3*/void redactStudent(List<Info>& list) {
    bool isStudent = false;
    cout << "\nВведите ID студента: ";
    int num;
    cin >> num;
    for (int i = 0; i < list.count(); i++) {
        if (list.elementAt(i).id == num) {
            redactMenu();
            isStudent = true;
            Info newinfo = list.elementAt(i);
            string fio, fio1, fio2;
            cin >> num;
            switch (num) {
            case 1:
                cout << "Введите новое ФИО: ";
                cin >> fio >> fio1 >> fio2;
                fio = fio + " " + fio1 + " " + fio2;
                newinfo.name = fio;
                break;
            case 2:
                cout << "Введите новую группу: ";
                cin >> num;
                newinfo.group = num;
                break;
            case 3:
                cout << "Введите новые оценки: ";
                newinfo.best = true;
                for (int i = 0; i < 5; i++) {
                    cin >> newinfo.marks[i];
                    if (newinfo.marks[i] < 4) { newinfo.best = false; }
                }
                break;
            case 4:
                cout << "Введите новый размер стипендии: ";
                cin >> num;
                newinfo.stipa = num;
                break;
            case 5:
                cout << "Введите новый номер зачетной книжки: ";
                cin >> num;
                newinfo.booknumber = num;
                break;
            }
            list.removeAt(i);
            list.add(newinfo);
            break;
        }
    }
    if (!isStudent) { cout << "Нет студента с таким ID!\n"; }
}
/*4*/void infoStudent(List<Info> list) {
    filterMenu();
    bool isStudent = false, marks;
    int choice;
    int arr[5], arr1[5];
    string name1, name2, name3;
    cin >> choice;
    switch (choice) {
    case 1:
        cout << "Введите ФИО: ";
        cin >> name1 >> name2 >> name3;
        name1 = name1 + " " + name2 + " " + name3;
        for (int i = 0; i < list.count(); i++) {
            if (list.elementAt(i).name == name1) {
                out(list.elementAt(i));
                isStudent = true;
            }
        }
        if (!isStudent) { cout << "Нет студента с таким ФИО!\n"; }
        break;
    case 2:
        cout << "Введите группу: ";
        cin >> choice;
        for (int i = 0; i < list.count(); i++) {
            if (list.elementAt(i).group == choice) {
                out(list.elementAt(i));
                isStudent = true;
            }
        }
        if (!isStudent) { cout << "Нет группы с таким номером!\n"; }
        break;
    case 3:
        cout << "Введите оценки: ";
        for (int i = 0; i < 5; i++) { cin >> arr[i]; }
        for (int i = 0; i < list.count(); i++) {
            marks = true;
            for (int j = 0; j < 5; j++) {
                if (arr[j] != list.elementAt(i).marks[j]) { marks = false; }
            }
            if (marks) {
                out(list.elementAt(i));
                isStudent = true;
            }
        }
        if (!isStudent) { cout << "Нет студентов с такими оценками!\n"; }
        break;
    case 4:
        cout << "Введите размер стипендии: ";
        cin >> choice;
        for (int i = 0; i < list.count(); i++) {
            if (list.elementAt(i).stipa == choice) {
                out(list.elementAt(i));
                isStudent = true;
            }
        }
        if (!isStudent) { cout << "Нет студентов с такой стипендией!\n"; }
        break;
    case 5:
        cout << "Введите номер зачетной книжки: ";
        cin >> choice;
        for (int i = 0; i < list.count(); i++) {
            if (list.elementAt(i).booknumber == choice) {
                out(list.elementAt(i));
                isStudent = true;
            }
        }
        if (!isStudent) { cout << "Нет студентов с таким номером зачетной книжки!\n"; }
        break;
    }
}
/*5*/void infoAllStudent(List<Info> list) {
    if (list.count() == 0) {
        cout << "В потоке нет ни одного студента!\n";
        return;
    }
    for (int i = 0; i < list.count(); i++) { out(list.elementAt(i)); }
}
/*6*/void addGroup(List<Info>& list) {
    int group;
    cout << "Введите номер группы: ";
    cin >> group;
    while (true) {
        list.add(inputGroup(group));
        cout << "\n1 - Продолжить добавление\n";
        cout << "2 - Закончить\n";
        cout << "Выбор: ";
        int choice;
        cin >> choice;
        if (choice == 2) { break; }
    }
}
/*7*/void deleteGroup(List<Info>& list) {
    int group;
    bool isGroup = false;
    cout << "Введите группу: ";
    cin >> group;
    for (int i = 0; i < list.count(); i++) {
        if (list.elementAt(i).group == group) { 
            list.removeAt(i);
            isGroup = true;
        }
    }
    if (!isGroup) { cout << "Нет группы с таким номером!\n"; }
}
/*8*/void redactGroup(List<Info>& list) {
    int oldnum, newnum;
    bool isGroup = false;
    cout << "Введите номер группы, который хотите поменять: ";
    cin >> oldnum;
    cout << "Введите новый номер для этой группы: ";
    cin >> newnum;
    for (int i = 0; i < list.count(); i++) {
        if (list.elementAt(i).group == oldnum) {
            Info newinfo = list.elementAt(i);
            newinfo.group = newnum;
            list.removeAt(i);
            i--;
            list.add(newinfo);
            isGroup = true;
        }
    }
    if (!isGroup) { cout << "Нет группы с таким номером!\n"; }
}
/*9*/void infoGroup(List<Info> list) {
    int group;
    bool isGroup = false;
    cout << "Введите группу: ";
    cin >> group;
    for (int i = 0; i < list.count(); i++) {
        if (list.elementAt(i).group == group) { 
            out(list.elementAt(i));
            isGroup = true;
        }
    }
    if (!isGroup) { cout << "Нет группы с таким номером!\n"; }
}
/*10*/void bestGroup(List<Info> list) {
    List<Group> dellist, newlist;
    bool isBest = false;
    for (int i = 0; i < list.count(); i++) { dellist.add(inputGroup1(list.elementAt(i))); }
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
            isBest = true;
        }
    }

    for (int i = 0; i < list.count(); i++) {
        if (list.elementAt(i).group == group) {
            cout << list.elementAt(i).name << "\n";
        }
    }
    if (!isBest) { cout << "На потоке нет ни одного хорошиста или отличника!\n"; }
}
/*11*/void fileInput(List<Info>& list) {
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
            break;
        case 4:
            info.stipa = toint(str);
            break;
        case 5:
            info.booknumber = toint(str);
            id++;
            info.id = id;
            list.add(info);
            number = 0;
        }
    }
    input.close();
}
/*12*/void fileOutput(List<Info> list) {
    ofstream output;
    output.open("output.txt");
    for (int i = 0; i < list.count(); i++) {
        Info info = list.elementAt(i);
        output << info.name << endl;
        output << info.group << endl;
        for (int j = 0; j < 5; j++) { output << info.marks[j] << " "; }
        output << endl << info.stipa << endl;
        output << info.booknumber << endl;
    }
    output.close();
}

int main() {
    system("chcp 1251>NULL");
    List<Info> list;
    int par;
    while (true) {
        cout << endl;
        system("pause");
        system("cls");
        menu();
        cout << "\nВведите команду: ";
        cin >> par;
        switch (par) {
        case 1:
            list.add(input());
            break;
        case 2:
            deleteStudent(list);
            break;
        case 3:
            redactStudent(list);
            break;
        case 4:
            infoStudent(list);
            break;
        case 5:
            infoAllStudent(list);
            break;
        case 6:
            addGroup(list);
            break;
        case 7:
            deleteGroup(list);
            break;
        case 8:
            redactGroup(list);
            break;
        case 9:
            infoGroup(list);
            break;
        case 10:
            bestGroup(list);
            break;
        case 11:
            fileInput(list);
            break;
        case 12:
            fileOutput(list);
            break;
        case 13:
            list.clear();
            break;
        case 0:
            return 0;
        default:
            cout << "Некорректная команда!";
        }
    }
}   
