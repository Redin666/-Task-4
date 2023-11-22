#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <codecvt>
#include <locale>
#include <Windows.h>

using namespace std;

#pragma pack(push, 1)
typedef struct
{
    int ID;
    string Name;
    string Surname;
    string Patronymic;
    string sex;
    int course;
    string Department;
    int group;
    int mark;
} University;
#pragma pack(pop)


void addStudent(string fileInput, University university)
{
    setlocale(LC_ALL, "rus UTF-8");
    cin.ignore();

    ifstream inputFile("C:\\Users\\ASUS\\Desktop\\Таск\\C++\\Task 4\\x64\\Debug\\" + fileInput + ".txt");
    int maxID = 0;
    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string idStr;
        getline(iss, idStr, '|');
        int id = stoi(idStr);
        if (id > maxID) {
            maxID = id;
        }
    }
    inputFile.close();

    university.ID = maxID + 1;

    cout << "Введите имя студента: ";
    getline(cin, university.Name);
    cout << "Фамилия: ";
    cin >> university.Surname;
    cout << "Отчество: ";
    cin >> university.Patronymic;
    cout << "Пол: ";
    cin >> university.sex;
    cout << "Курс: ";
    cin >> university.course;
    cout << "Кафедра: ";
    cin >> university.Department;
    cout << "Группа: ";
    cin >> university.group;
    cout << "Оценка: ";
    cin >> university.mark;

    ofstream outputFile("C:\\Users\\ASUS\\Desktop\\Таск\\C++\\Task 4\\x64\\Debug\\" + fileInput + ".txt", ios::app);

    if (!outputFile) {
        cout << "Ошибка! Мы не смогли прочитать TXT файл";
        return;
    }
    else {
        outputFile << university.ID << '|' << university.Name << '|'
            << university.Surname << '|'
            << university.Patronymic << '|'
            << university.sex << '|'
            << university.course << '|'
            << university.Department << '|'
            << university.group << '|'
            << university.mark << endl;
        cout << "Студент добавлен" << endl;
        outputFile.close();
    }
}

void listStudent(string fileInput, University university)
{
    ifstream inputFile("C:\\Users\\ASUS\\Desktop\\Таск\\C++\\Task 4\\x64\\Debug\\" + fileInput + ".txt");
    if (!inputFile.is_open()) {
        cout << "Ошибка! Не удалось открыть файл." << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);

        getline(iss, line, '|');
        university.ID = stoi(line);
        getline(iss, university.Name, '|');
        getline(iss, university.Surname, '|');
        getline(iss, university.Patronymic, '|');
        getline(iss, university.sex, '|');
        iss >> university.course;
        iss.ignore();
        getline(iss, university.Department, '|');
        iss >> university.group;
        iss.ignore();
        iss >> university.mark;
        iss.ignore();

        cout << "ID: " << university.ID << endl;
        cout << "Имя: " << university.Name << endl;
        cout << "Фамилия: " << university.Surname << endl;
        cout << "Отчество: " << university.Patronymic << endl;
        cout << "Пол: " << university.sex << endl;
        cout << "Курс: " << university.course << endl;
        cout << "Кафедра: " << university.Department << endl;
        cout << "Группа: " << university.group << endl;
        cout << "Оценка: " << university.mark << endl;
        cout << "-------------------------" << endl;
    }

    inputFile.close();
}


void filterStudent(string fileInput, University university)
{
    ifstream inputFile("C:\\Users\\ASUS\\Desktop\\Таск\\C++\\Task 4\\x64\\Debug\\" + fileInput + ".txt");
    if (!inputFile.is_open()) {
        cout << "Ошибка! Не удалось открыть файл." << endl;
        return;
    }

    int filterCourse;
    cout << "Выбирите курс: ";
    cin >> filterCourse;

    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);

        getline(iss, line, '|');
        university.ID = stoi(line);
        getline(iss, university.Name, '|');
        getline(iss, university.Surname, '|');
        getline(iss, university.Patronymic, '|');
        getline(iss, university.sex, '|');
        iss >> university.course;
        iss.ignore();
        getline(iss, university.Department, '|');
        iss >> university.group;
        iss.ignore();
        iss >> university.mark;
        iss.ignore();

        if (university.course == filterCourse) {
            cout << "ID: " << university.ID << endl;
            cout << "Имя: " << university.Name << endl;
            cout << "Фамилия: " << university.Surname << endl;
            cout << "Отчество: " << university.Patronymic << endl;
            cout << "Пол: " << university.sex << endl;
            cout << "Курс: " << university.course << endl;
            cout << "Кафедра: " << university.Department << endl;
            cout << "Группа: " << university.group << endl;
            cout << "Оценка: " << university.mark << endl;
            cout << "-------------------------" << endl;
        }
    }

    inputFile.close();
}

void deleteStudent(string fileInput, University university) {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");
    setlocale(LC_CTYPE, "Russian");

    locale utf8_locale(locale(), new codecvt_utf8<wchar_t>);

    ifstream inputFile("C:\\Users\\ASUS\\Desktop\\Таск\\C++\\Task 4\\x64\\Debug\\" + fileInput + ".txt");
    if (!inputFile.is_open()) {
        cout << "Ошибка! Не удалось открыть файл." << endl;
        return;
    }

    int studentIDToDelete;
    cout << "Введите ID студента, которого хотите удалить: ";
    cin >> studentIDToDelete;
    cin.ignore();

    ofstream tempFile("C:\\Users\\ASUS\\Desktop\\Таск\\C++\\Task 4\\x64\\Debug\\temp.txt");

    if (!tempFile.is_open()) {
        cout << "Ошибка! Не удалось создать временный файл." << endl;
        inputFile.close();
        return;
    }

    bool studentFound = false;
    int currentID = 1;

    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string idStr;
        getline(iss, idStr, '|');
        int id = stoi(idStr);

        if (id == studentIDToDelete) {
            studentFound = true;
            cout << "Студент с ID " << studentIDToDelete << " удален." << endl;
        }
        else {
            string updatedLine = to_string(currentID) + line.substr(idStr.length());
            tempFile << updatedLine << endl;
            currentID++;
        }
    }

    inputFile.close();
    tempFile.close();

    if (!studentFound) {
        cout << "Студент с ID " << studentIDToDelete << " не найден." << endl;
    }
    else {
        ofstream outputFile("C:\\Users\\ASUS\\Desktop\\Таск\\C++\\Task 4\\x64\\Debug\\" + fileInput + ".txt");
        ifstream tempFile("C:\\Users\\ASUS\\Desktop\\Таск\\C++\\Task 4\\x64\\Debug\\temp.txt");

        if (!outputFile.is_open() || !tempFile.is_open()) {
            cout << "Ошибка! Не удалось открыть файлы для записи." << endl;
            return;
        }

        while (getline(tempFile, line)) {
            outputFile << line << endl;
        }

        tempFile.close();
        outputFile.close();
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");
    setlocale(LC_CTYPE, "Russian");

    string fileInput;

    cout << "Напишите путь к файлу с которго нужно считать это: ";
    getline(cin, fileInput);

    ifstream inputFile("C:\\Users\\ASUS\\Desktop\\Таск\\C++\\Task 4\\x64\\Debug\\" + fileInput + ".txt");
    if (!inputFile.is_open())
    {
        cout << "Ошибка! Мы не смогли прочитать txt";
        return -1;
    }

    University university;

    cout << "-------Программа студент-------" << endl;
    int choise;
    while (true)
    {
        cout << "Выбирите фукцию которую хотите использовать" << endl;
        cout << "1. Вывести список студентов" << endl;
        cout << "2. Вывести по фильтру" << endl;
        cout << "3. Добавить студента" << endl;
        cout << "4. Удалить студента" << endl;
        cout << "5. Завершить программу" << endl;
        cin >> choise;

        switch (choise)
        {
        case 1:
            listStudent(fileInput, university);
            break;
        case 2:
            filterStudent(fileInput, university);
            break;
        case 3:
            addStudent(fileInput, university);
            break;
        case 4:
            deleteStudent(fileInput, university);
            break;
        case 5:
            return 0;
        default:
            cout << "Ошибка вода попробуйте еще раз" << endl;
        }
    }
    return 0;
}