// Notebook.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include<vector>
#include<algorithm>
#include<functional>

using namespace std;
class NoteBook
{
public:
    vector<string> Tags;
private:

    string Author;//автор
    string Name;//название
    string Text;//текст
    int Day;//время создания
    int Month;
    int Year;
    int ChangedDay; //время изменения
    int ChangedMonth;
    int ChangedYear;


public:

    NoteBook() {
        Tags = { "тэг" };
        Author = "неизвестен";
        Name = "Заметка";
        Text = "заметка";
        Day = 1;
        Month = 1;
        Year = 2022;

    }
    NoteBook(string author, string name, string text, vector<string>tags) {
        Tags = tags;
        Author = author;
        Name = name;
        Text = text;

        SYSTEMTIME st;
        GetSystemTime(&st);
        Day = st.wDay;
        Month = st.wMonth;
        Year = st.wYear;
    }
    NoteBook(string author, string name, string text, vector<string>tags, int day, int month, int year)
    {
        Tags = tags;
        Author = author;
        Name = name;
        Text = text;
        Day = day;
        Month = month;
        Year = year;
    }
    string GetAuthor()
    {
        return Author;
    }
    string GetName()
    {
        return Name;
    }
    string GetText()
    {
        return Text;
    }
    vector<string> GetTags() {
        return Tags;
    }
    void SetAuthor(string author)
    {
        Author = author;
    }
    void SetName(string name)
    {
        Name = name;
    }
    void SetText(string text)
    {
        Text = text;
    }
    void SetTags(vector<string> tags) {
        Tags = tags;
    }

    void ShowNote()
    {
        cout << "Название заметки: " << GetName() << endl;
        cout << "Автор заметки:" << GetAuthor() << endl;
        cout << "Текст заметки: " << endl;
        cout << GetText() << endl;
        cout << "Тэги:" << endl;
        for (int i = 0; i < Tags.size(); i++) {
            cout << Tags[i] << " ";
        }
        cout << endl;
    }

    int GetDay() {
        return Day;
    }
    int GetMonth() {
        return Month;
    }
    int GetYear() {
        return Year;
    }
    void SetChangedTimeAndDate() {
        SYSTEMTIME st;
        GetSystemTime(&st);
        ChangedDay = st.wDay;
        ChangedMonth = st.wMonth;
        ChangedYear = st.wYear;
    }



};

ostream& operator<<(ostream& input, NoteBook& note)//перегрузка оператора << 
{
    for (int i = 0; i < note.Tags.size(); i++) {
        input << note.Tags[i] << " ";
    }
    input << "#";
    input << "\n";
    input << note.GetAuthor() << "\n" << note.GetName() << "\n" << note.GetText();
    input << "\n";
    input << note.GetDay() << "/" << note.GetMonth() << "/" << note.GetYear();

    return input;

}


vector <int> GetPreviousDay(int day, int month, int year) {//определие предыдущего дня
    vector<int> PreviousDay;
    if (day == 1) {
        if (month == 2 || month == 4 || month == 6 || month == 9 || month == 11) {
            day = 31;
            month = month - 1;
        }

        else if (month == 1) {
            day = 31;
            month = 12;
            year = year - 1;
        }
        else if (month == 3) {
            if (year % 4 == 0)
                day = 29;
            else
                day = 28;
            month = month - 1;

        }
        else {
            day = 30;
            month = month - 1;
        }
    }
    else {
        day = day - 1;
    }
    PreviousDay.push_back(day);
    PreviousDay.push_back(month);
    PreviousDay.push_back(year);
    return PreviousDay;
}
int main()
{
    vector<NoteBook> Notes;
    NoteBook n;
    string author;
    string tag;
    vector<string> tags;
    string name;
    string text;
    ifstream file;
    int day;
    int month;
    int year;
    string nothing;
    file.open("Сохранение.txt");
    if (file.is_open()) {
        while (!file.eof())
        {
            string tag;
            while ((file >> tag) && (tag != "#")) {
                tags.push_back(tag);
            }
            getline(file, author);
            getline(file, name);
            getline(file, text);

            file >> day;
            file >> month;
            file >> year;

            Notes.push_back(NoteBook(author, name, text, tags, day, month, year));
            tags.clear();

        }
        file.close();
    }
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int number = -1;
    cout << "Введите цифру для действия с заметкой:\n 1-создание новой заметки \n 2-изменение заметки \n 3-поиск заметки \n 4-сортировка заметок \n 5-подсчет статистики по заметкам \n 0-завершение программы" << endl;
    while (number != 0) {

        cin >> number;
        switch (number) {
        case 1:
        {
            string text;
            string name;
            string author;
            string stop = "";
            vector<string> tags;
            string tag;
            cout << "-------------Создание заметки-------------" << endl;
            cout << "Введите автрора заметки:";
            cin.ignore();
            getline(cin, author);
            cout << "Введите название заметки(название не может содержать пробелы):";

            getline(cin, name);
            cout << "Введите текст заметки:";

            getline(cin, text);
            cout << "Введите тэги(вводите через пробел,по окончании ввода введите стоп):";
            while (stop != "стоп") {
                cin >> tag;
                if (tag == "стоп") {
                    stop = "стоп";
                    break;
                }
                tags.push_back(tag);
            }
            sort(tags.begin(), tags.end());

            NoteBook* note;
            note = new NoteBook(author, name, text, tags);

            Notes.push_back(*note);
            fstream file;
            string path = name + ".txt";
            file.open(path, fstream::in | fstream::app);
            if (!file.is_open())
            {
                cout << "Невозможно создать заметку!";
            }
            else
            {

                file << *note << "\n";
            }
            file.close();
            fstream file1;
            string path1 = "Сохранение.txt";
            file1.open(path1, fstream::in | fstream::app);
            file1 << *note << "\n";
            file1.close();
            for (vector<NoteBook>::iterator it = Notes.begin(); it != Notes.end(); it++) {
                cout << "Заметка " << endl;
                cout << "--------------------" << endl;
                it->ShowNote();
                cout << "------------------------------------" << endl;

            }
            break;
        }
        case 2:
        {
            string name;
            string choose;

            cout << "-------------Изменение заметки-------------" << endl;
            cout << "Введите название заметки, которую вы хотите изменить:";
            cin >> name;
            string path = name + ".txt";
            cout << endl;
            auto FindName = find_if(Notes.begin(), Notes.end(), [name](NoteBook n)
                {
                    return (n.GetName() == name);
                });
            cin.ignore();
            if (FindName == Notes.end()) {
                cout << "Такой заметки не существует!";
                break;
            }
            else {
                FindName->ShowNote();
                cout << "Как вы хотите изменить заметку?" << endl;
                cout << "Изменить автора?Введите да либо нет" << endl;
                cin >> choose;
                string author;
                if (choose == "да") {
                    cin >> author;
                    FindName->SetAuthor(author);
                }
                else if (choose == "нет") {
                    author = FindName->GetAuthor();
                }
                cout << "Изменить текст?Введите да либо нет" << endl;
                cin >> choose;
                string text;
                if (choose == "да") {
                    cin >> text;
                    FindName->SetText(text);
                }
                else if (choose == "нет") {
                    text = FindName->GetText();
                }
                cout << "Изменить тэги?Введите да либо нет" << endl;
                cin >> choose;
                vector<string> tags;
                if (choose == "да") {
                    string tag;
                    string stop = "";
                    cout << "Введите тэги(вводите через пробел,по окончании ввода введите стоп):";
                    while (stop != "стоп") {
                        cin >> tag;
                        if (tag == "стоп") {
                            stop = "стоп";
                            break;
                        }
                        tags.push_back(tag);
                    }
                    FindName->SetTags(tags);
                }
                else if (choose == "нет") {
                    tags = FindName->GetTags();
                }
                FindName->SetChangedTimeAndDate();
                NoteBook* n = new NoteBook(author, name, text, tags);
                fstream file1;
                fstream file;

                file.open(path, fstream::in);
                file.clear();

                if (!file.is_open())
                {
                    cout << "Невозможно изменить заметку!";
                }
                else
                {


                    file << *n << "\n";

                }
                file.close();
                file1.open("Сохранение.txt", fstream::in);
                file1 << *n << "\n";
                file1.close();
            }


            break;
        }
        case 3:
        {
            int number;
            cout << "-------------Поиск заметки--------------: " << endl;

            cout << "По какому парамету вы хотите найти заметку?" << endl;
            cout << "Введите, по каком параметру Вы хотите искать заметки: 1 - по автору, 2- по тэгам, 3 - по дате создания" << endl;
            cin >> number;
            if (number == 1) {
                cout << "Введите имя автора, которого вы хотите найти: " << endl;
                string author;
                cin >> author;
                vector <NoteBook> AuthorSearch;
                copy_if(Notes.begin(), Notes.end(), back_inserter(AuthorSearch), [author](NoteBook& n1) {
                    return(n1.GetAuthor() == author);
                    });
                int i = 1;

                for (vector<NoteBook>::iterator it = AuthorSearch.begin(); it != AuthorSearch.end(); it++) {
                    cout << "Заметка " << i << endl;
                    cout << "--------------------" << endl;
                    it->ShowNote();
                    cout << "------------------------------------" << endl;
                    i++;
                }
            }
            else if (number == 2) {
                cout << "Введите тэги,по которым вы хотите найти заметку: " << endl;
                vector <string> tags;
                string tag;
                string stop = "";
                while (stop != "стоп") {
                    cin >> tag;
                    if (tag == "стоп") {
                        stop = "стоп";
                        break;
                    }
                    tags.push_back(tag);
                }
                sort(tags.begin(), tags.end());
                vector <NoteBook> TagSearch;
                copy_if(Notes.begin(), Notes.end(), back_inserter(TagSearch), [tags](NoteBook& n1) {
                    for (int i = 0; i < tags.size(); i++) {
                        return(n1.Tags[i] == tags[i]);
                    }
                    });
                int i = 1;

                for (vector<NoteBook>::iterator it = TagSearch.begin(); it != TagSearch.end(); it++) {
                    cout << "Заметка " << i << endl;
                    cout << "--------------------" << endl;
                    it->ShowNote();
                    cout << "------------------------------------" << endl;
                    i++;
                }


            }
            else if (number == 3) {
                cout << "Введите по какому папаметру вы хотите осуществлять поиск: 1-поиск по дате создания, 2-вывод заметок за последние 3 дня" << endl;
                int n = 0;
                cin >> n;
                if (n == 1) {
                    cout << "---------------Поиск заметок по дате-----------------" << endl;
                    int day;
                    int month;
                    int year;
                    cout << "Введите дату создаия заметки(вводите числа):" << endl;
                    cout << "Введите день: " << endl;
                    cin >> day;
                    cout << "Введите месяц: " << endl;
                    cin >> month;
                    cout << "Введите год: " << endl;
                    cin >> year;

                    vector <NoteBook>  DateSearch;
                    copy_if(Notes.begin(), Notes.end(), back_inserter(DateSearch), [day, month, year](NoteBook& n1) {

                        return(n1.GetDay() == day && n1.GetMonth() == month && n1.GetYear() == year);

                        });
                    int i = 1;

                    for (vector<NoteBook>::iterator it = DateSearch.begin(); it != DateSearch.end(); it++) {
                        cout << "Заметка " << i << endl;
                        cout << "--------------------" << endl;
                        it->ShowNote();
                        cout << "------------------------------------" << endl;
                        i++;
                    }
                }
                else if (n == 2) {
                    cout << "---------------Вывод заметок за последние 3 дня-----------------" << endl;
                    SYSTEMTIME st;
                    GetSystemTime(&st);
                    int day = st.wDay;
                    int month = st.wMonth;
                    int year = st.wYear;
                    vector <NoteBook>  DateSearch;
                    cout << "Заметки за " << day << "/" << month << "/" << year << endl;
                    copy_if(Notes.begin(), Notes.end(), back_inserter(DateSearch), [day, month, year](NoteBook& n1) {

                        return(n1.GetDay() == day && n1.GetMonth() == month && n1.GetYear() == year);

                        });
                    int i = 1;
                    for (vector<NoteBook>::iterator it = DateSearch.begin(); it != DateSearch.end(); it++) {
                        cout << "Заметка " << i << endl;
                        cout << "--------------------" << endl;
                        it->ShowNote();
                        cout << "------------------------------------" << endl;
                        i++;
                    }
                    DateSearch.clear();
                    vector<int>Previous1;
                    Previous1 = GetPreviousDay(day, month, year);
                    day = Previous1[0];
                    month = Previous1[1];
                    year = Previous1[2];

                    cout << "Заметки за " << day << "/" << month << "/" << year << endl;
                    copy_if(Notes.begin(), Notes.end(), back_inserter(DateSearch), [day, month, year](NoteBook& n1) {

                        return(n1.GetDay() == day && n1.GetMonth() == month && n1.GetYear() == year);

                        });

                    for (vector<NoteBook>::iterator it = DateSearch.begin(); it != DateSearch.end(); it++) {
                        cout << "Заметка " << i << endl;
                        cout << "--------------------" << endl;
                        it->ShowNote();
                        cout << "------------------------------------" << endl;
                        i++;
                    }
                    DateSearch.clear();
                    vector<int>Previous2;
                    Previous2 = GetPreviousDay(day, month, year);
                    day = Previous2[0];
                    month = Previous2[1];
                    year = Previous2[2];
                    cout << "Заметки за " << day << "/" << month << "/" << year << endl;
                    copy_if(Notes.begin(), Notes.end(), back_inserter(DateSearch), [day, month, year](NoteBook n1) {

                        return(n1.GetDay() == day && n1.GetMonth() == month && n1.GetYear() == year);

                        });

                    for (vector<NoteBook>::iterator it = DateSearch.begin(); it != DateSearch.end(); it++) {
                        cout << "Заметка " << i << endl;
                        cout << "--------------------" << endl;
                        it->ShowNote();
                        cout << "------------------------------------" << endl;
                        i++;
                    }

                }


            }
            else {
                cout << "Неверный ввод!";
                break;
            }
            break;

        }
        case 4:
        {
            int n;
            cout << "-------------Сортировка заметок-------------- " << endl;
            cout << "По какому парамету вы хотите сортировать заметки?" << endl;
            cout << "Введите, по каком параметру Вы хотите сортировать заметки: 1 - по автору, 2-по названию" << endl;
            cin >> n;
            if (n == 1) {
                cout << "Сортировка по возрастанию или по убыванию? Введите + для сортировки по возрастанию, введите - для сортировки по убыванию." << endl;
                string symbol;
                cin >> symbol;
                if (symbol == "+") {
                    cout << "Сортировка заметок по автору(по возрастанию)" << endl;
                    cout << "----------------------------------------" << endl;
                    sort(Notes.begin(), Notes.end(), [](NoteBook n1, NoteBook n2) {
                        return n1.GetAuthor() < n2.GetAuthor();
                        });
                    for (vector<NoteBook>::iterator it = Notes.begin(); it != Notes.end(); it++) {
                        it->ShowNote();
                    }
                }
                else if (symbol == "-") {
                    cout << "Сортировка заметок по автору(по убыванию)" << endl;
                    cout << "----------------------------------------" << endl;
                    sort(Notes.begin(), Notes.end(), [](NoteBook& n1, NoteBook& n2) {
                        return n1.GetAuthor() > n2.GetAuthor();
                        });
                    for (vector<NoteBook>::iterator it = Notes.begin(); it != Notes.end(); it++) {
                        it->ShowNote();
                    }
                }
                else {
                    cout << "Неверный ввод" << endl;
                    break;
                }

            }
            if (n == 2) {
                cout << "Сортировка по возрастанию или по убыванию? Введите + для сортировки по возрастанию, введите - для сортировки по убыванию." << endl;
                string symbol;
                cin >> symbol;
                if (symbol == "+") {
                    cout << "Сортировка заметок по названию(по возрастанию)" << endl;
                    cout << "----------------------------------------" << endl;
                    sort(Notes.begin(), Notes.end(), [](NoteBook n1, NoteBook n2) {
                        return n1.GetName() < n2.GetName();
                        });
                }
                else if (symbol == "-") {
                    cout << "Сортировка заметок по названию(по убыванию)" << endl;
                    cout << "----------------------------------------" << endl;
                    sort(Notes.begin(), Notes.end(), [](NoteBook n1, NoteBook n2) {
                        return n1.GetName() > n2.GetName();
                        });
                }
                else {
                    cout << "Неверный ввод" << endl;
                    break;
                }

            }
            else {
                cout << "Неверный ввод" << endl;
                break;
            }
            break;
        }
        case 5:
        {
            cout << "--------------------Подсчет статистики-----------------------" << endl;
            cout << "По какому параметру вы хотите посмотреть статистику? 1-по авторам, 2 - по тэгам.";
            int number;
            cin >> number;
            if (number == 1) {
                cout << "Введите имя автора, по которому вы хотите посмотреть статистику: " << endl;
                string author;
                cin >> author;
                vector <NoteBook> AuthorSearch;
                copy_if(Notes.begin(), Notes.end(), back_inserter(AuthorSearch), [author](NoteBook n1) {
                    return(n1.GetAuthor() == author);
                    });
                cout << AuthorSearch.size();
            }

            else if (number == 2) {
                cout << "Введите тэги,по которым вы хотите посмотреть статистику: " << endl;
                vector <string> tags;
                string tag;
                string stop = "";
                while (stop != "стоп") {
                    cin >> tag;
                    if (tag == "стоп") {
                        stop = "стоп";
                        break;
                    }
                    tags.push_back(tag);
                }
                sort(tags.begin(), tags.end());
                vector <NoteBook> TagSearch;
                copy_if(Notes.begin(), Notes.end(), back_inserter(TagSearch), [tags](NoteBook n1) {
                    for (int i = 0; i < tags.size(); i++) {
                        return(n1.Tags[i] == tags[i]);
                    }
                    });
                cout << TagSearch.size();
            }
            else {
                cout << ("Неверный ввод!");
                break;
            }
            break;

        }
        case 0:
        {

            break;
        }
        }
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
