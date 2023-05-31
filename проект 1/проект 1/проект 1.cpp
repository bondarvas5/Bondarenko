#pragma once
#include "Class_MyString.h"
class date
{
    short day, month, year;
    int* adtoi(const char* D, const char separator);//функция, конвертирующая строку в набор чисел
    const static int daytap[2][13];//массив кол-ва дней в каждом месяце невысокосного или высокосного года(соответственно)
    const static char* MonthName[13];//названия месяцев
    const static char* DayName[8];//название дней недели
public:
    static char get_separator(char* t);//функция, получающая разделительный знак
    static int checkright(int day, int month = 1, int year = 1);//проверка правильности данных
    date(int d, int m, int y);//конструктор с числами
    date();//конструктор по умолчанию
    date(const char* D, const char separator);//конструктор со строкой
    date(const date& d2);//конструктор копирования
    void output(ostream& os = cout);//вывод на экран
    int input(int d, int m, int y);//ввод числовой
    int input(const char* D, const char separator);//ввод строковой
    void assign(const date& d1);//присваивание
    int input(istream& is);
    ~date();//деструктор
    int get_day() { return day; }//получение дня
    int get_month() { return month; }//получение месяца
    int get_year() { return year; }//получение года
    int validate();//проверка правильности данных
    void set_day(int d);//замена дня
    void set_month(int m);//замена месяца
    void set_year(int y);//замена года
    void Add_days(int days);//добавление дней
    void Add_monthes(int monthes);//добавление месяцев
    void Add_years(int years);//добавление годов
    static int days_from_year(int y, int d, int m);//кол-во дней с начала года
    static date date_from_days(int d, int y);//возврат даты по кол-ву дней с начала года
    static int vis(int y)//высокосный ли?
    {
        if (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0))
            return 1;
        return 0;
    }
    char* ToPChar(const char separator = '.');//дату в строку
    static date* newdate(char* date);//строку в дату
    int equal(const date& d1);//проверка на равность
    int cmp(const date& d1);//сравнение
    void day_month(int d, int y, int* m, int* dd);//првращение года и кол-ва дней с начала года в дату
    static int between(const date& d1, const date& d2);//разница между двумя датами
    date& operator = (char* d1);//присваивание из строки в дату
    int operator <= (const date& d1) { return cmp(d1) <= 0; }//< или =?
    int operator >= (const date& d1) { return cmp(d1) >= 0; }//> или =?
    int operator > (const date& d1) { return cmp(d1) > 0; }//>?
    int operator < (const date& d1) { return cmp(d1) < 0; }//<?
    date& operator ++() { Add_days(1); return *this; }//увеличение даты на 1 день
    date& operator --() { Add_days(-1); return *this; }//уменьшение даты на 1 день
    date& operator +=(int d) { Add_days(d); return *this; }//увеличение даты на d дней
    date& operator -=(int d) { Add_days(-d); return *this; }//уменьшение даты на d дней
    friend date operator +(const date& d1, int d);//увеличение даты d1 на d дней
    friend date operator -(const date& d1, int d);//уменьшение даты d1 на d дней
    date* copy() { return new date(*this); }
    MyString ToMyString()const { return MyString("date"); }
    void dispose() { if (this != nullptr) this->~date(); }
    friend std::istream& operator>>(std::istream& i, date& d1);//ввод даты с клавиатуры
    friend std::ostream& operator<<(std::ostream& o, const date& d1) { return o << "Date: " << d1.day << '.' << d1.month << '.' << d1.year; }//вывод на эран
};



#include "Class_date.h"
#pragma warning(disable: 4996)
const int date::daytap[2][13] = { {0,31,28,31,30,31,30,31,31,30,31,30,31},{0,31,29,31,30,31,30,31,31,30,31,30,31} };
const char* date::MonthName[13] = { "Wrong","January","February","March","April","May","June","July","August","September","October","November","December" };
const char* date::DayName[8] = { "Wrong","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday" };
date::date()
{
    day = month = year = 1;//присвоение начальных значений
}
date::date(int d, int m, int y)
{//присвоение переданных значений
    day = d;
    month = m;
    year = y;
}
date::date(const date& d2)
{//присвоение значений из другой даты
    day = d2.day;
    month = d2.month;
    year = d2.year;
}
int* date::adtoi(const char* D, const char separator)
{
    char buf[5] = {}; int j = 0, k = 0, * mass = new int[3];//выделение пам¤ти под счЄтчики, массив чисел даты и массив символьный числа
    for (int i = 0; D[i] != '\0' && j < 5; i++)
    {
        if (!isdigit(D[i]) && D[i] != separator)//проверка на число или разделитель
        {
            delete[] mass;
            return nullptr;
        }
        buf[j++] = D[i];
        if (D[i] == separator || D[i + 1] == '\0')//проверка на конец числа
        {
            j = 0;
            mass[k++] = atoi(buf);
        }
    }
    return mass;
}
date::date(const char* D, const char separator)
{
    if (separator == '\0')
        exit(3);
    int* mass = adtoi(D, separator);//превращение строки в число
    if (mass == nullptr)//если строка не дата
    {
        day = month = year = 1;
    }
    else
    {//копирование
        if (checkright(mass[0], mass[1], mass[2]))//проверка на правильность
        {
            day = *mass;
            month = mass[1];
            year = mass[2];
        }
    }//освобождение динамической пам¤ти
    delete[] mass;
}
int date::checkright(int day, int month, int year)//проверка корректности введЄЄнных данных
{
    return year > 0 && month > 0 && month < 13 && day>0 && day <= daytap[vis(year)][month];
}
void date::output(ostream& os)//вывод на экран
{
    os << "Date:\n" << day << '.' << month << '.' << year << '\n';
}
int date::input(int d, int m, int y)
{//аналогично конструктору
    day = d;
    month = m;
    year = y;
    return 1;
}
int date::input(const char* D, const char separator)
{//аналогично конструктору
    int* mass = adtoi(D, separator);
    day = *mass;
    month = mass[1];
    year = mass[2];
    delete[] mass;
    return 1;
}
date::~date()
{//нет выделени¤ динамической пам¤ти
    ;
}
int date::validate()
{//проверка корректности текущей даты
    return year > 0 && month > 0 && month < 13 && day>0 && day <= daytap[vis(year)][month];
}
void date::set_day(int d)
{//установка нового дн¤ и проверка правильности
    int tmp = day;
    day = d;
    if (validate())
        return;
    day = tmp;
    std::cout << "Incorrect day!\nRepeat please.\n";
}
void date::set_month(int m)
{//установка нового мес¤ца и проверка правильности
    int tmp = month;
    month = m;
    if (validate())
        return;
    month = tmp;
    std::cout << "Incorrect month!\nRepeat please.\n";
}
void date::set_year(int y)
{//установка нового года и проверка правильности
    int tmp = year;
    year = y;
    if (validate())
        return;
    year = tmp;
    std::cout << "Incorrect year!\nRepeat please.\n";
}
int date::cmp(const date& d1)
{
    if (year != d1.year)//если не равны то возврат разницы
        return year - d1.year;
    if (day != d1.day)
        return day - d1.day;
    if (month != d1.month)
        return month - d1.month;
    return 0;//если равны то 0
}
int date::equal(const date& d1)
{//проверка двух дат поэлементно на равенство
    return cmp(d1) == 0;
}
date* date::newdate(char* dat)
{
    //if (isdigit(dat[1]))//один из возможных вариантов нахождени¤ разделител¤
    //  return date(dat, dat[2]);
    return new date(dat, get_separator(dat));
}
void date::assign(const date& d1)//присвоение значений из даты d1 в текущую дату
{
    day = d1.day;
    month = d1.month;
    year = d1.year;
}
char* date::ToPChar(const char separator)//перевод из чисел в строку
{
    char d[3]{};
    itoa(day, d, 10);
    char m[3]{};
    itoa(month, m, 10);
    char y[4]{};
    itoa(year, y, 10); int cur;
    char* tmp = new char[strlen(m) + (cur = strlen(d)) + strlen(y) + 3];
    strcpy(tmp, d);
    tmp[cur++] = separator;
    strcpy(&tmp[cur], m); cur += strlen(m);
    tmp[cur++] = separator;
    strcpy(&tmp[cur], y);
    return tmp;
}
int date::days_from_year(int d, int m, int y)//из лекций
{
    int dd = d, ye = vis(y);
    while (--m)
        dd += daytap[ye][m];
    return dd;
}
void date::day_month(int d, int y, int* m, int* dd)//из лекций
{
    *m = 1; int ye = vis(y);
    while (d > daytap[y][*m])
        d -= daytap[ye][(*m)++];
    *dd = d;
    return;
}
void date::Add_days(int d)//из лекций
{
    if (d > 0)
        while (d--)
        {
            day++;
            if (day > daytap[vis(year)][month])
            {
                day = 1; month++;
                if (month > 12)
                {
                    month = 1;
                    year++;
                }
            }
        }
    else
        while (d++)
        {
            day--;
            if (!day)
            {
                month--;
                if (!month)
                {
                    year--;
                    if (!year)
                    {
                        year = month = day = 1;
                        break;
                    }
                    month = 12;
                }
                day = daytap[vis(year)][month];
            }
        }
}
void date::Add_monthes(int m)//из лекций
{
    if (m > 0)
        while (m--)
        {
            month++;
            if (month > 12)
            {
                month = 1;
                year++;
            }
        }
    else
        while (m++)
        {
            month--;
            if (!month)
            {
                year--;
                if (!year)
                {
                    year = month = day = 1;
                    break;
                }
                month = 12;
            }
        }
    if (day > daytap[vis(year)][month])
        day = daytap[vis(year)][month];
}
void date::Add_years(int y)//аналогично лекци¤м
{
    year += y;
    if (year < 1)
    {
        year = month = day = 1;
    }
    if (day > daytap[vis(year)][month])
        day = daytap[vis(year)][month];
}
date date::date_from_days(int d, int y)
{
    int m = 1, ye = vis(y);
    if ((d > 365 && ye == 0) || d > 366)//корректность введЄнных данных
        return date();
    while (d > daytap[ye][m])//подсчЄт мес¤цев
    {
        d -= daytap[ye][m];
        m++;
    }
    return date(d, m, y);//возврат новой даты
}
int date::between(const date& d1, const date& d2)//по лекции
{
    int dd = 0;
    if (d1.year < d2.year)
    {
        vis(d1.year) ? dd += 366 : dd += 365;
        dd = dd - days_from_year(d1.day, d1.month, d1.year) + days_from_year(d2.day, d2.month, d2.year);
        int ye = d1.year + 1;
        while (ye++ < d2.year)
            vis(ye) ? dd += 366 : dd += 365;
    }
    else
    {
        vis(d2.year) ? dd += 366 : dd += 365;
        dd = dd - days_from_year(d2.day, d2.month, d2.year) + days_from_year(d1.day, d1.month, d1.year);
        int ye = d2.year + 1;
        while (ye++ < d1.year)
            vis(ye) ? dd += 366 : dd += 365;
    }
    return dd;
}
char date::get_separator(char* t)//нахождение разделительного знака
{
    for (int i = 0; t[i] != '\0'; i++)
        if (!isdigit(t[i]))
            return t[i];
    return '\0';
}
date& date::operator=(char* d1)//оператор присваивани из строки в дату
{
    char sep = get_separator(d1);
    int* t = adtoi(d1, sep);
    day = t[0]; month = t[1]; year = t[2];
    delete[] t;
    return *this;
}
date operator +(const date& d1, int d)//оператор прибавлени¤ d дней к d1 дате
{
    date tmp = d1;
    return tmp += d;
}
date operator -(const date& d1, int d)//аналогично оператору +
{
    date tmp = d1;
    return tmp -= d;
}
std::istream& operator>>(std::istream& i, date& d1)//оператор поэлементного ввода
{
    i >> d1.day >> d1.month >> d1.year;
    i.get();
    return i;
}
int date::input(istream& is)
{
    is >> day >> month >> year;
    is.get();
    return 1;
}