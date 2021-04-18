#include "std_lib_facilities.h"
/* 9.4.1
struct Date {
    int y;
    int m;
    int d;
};
	
void init_day(Date& dd, int y, int m, int d)
{
    if (m < 1 || m > 12) error("invalid month");
    if (d < 1 || d > 31) error("impossible day");
	
    dd.y = y;
    dd.m = m;
    dd.d = d;
}
	
void add_day(Date& dd, int n)
{
    dd.d += n;
    if (dd.d > 31) dd.d %= 31;
}
	
ostream& operator<<(ostream& os, const Date& d)
{
    return os << '(' << d.y << ',' << d.m << ',' << d.d << ')';	
}
	
int main()
{
    Date today;	
    init_day(today, 1978, 6, 25);
	

    Date tomorrow = today;
    add_day(tomorrow, 1);
    cout << today << '\n'
         << tomorrow << '\n';
    //Date bad_day;
    //init_day(bad_day, 2004, 13, -5);
}
*/
	
/* 9.4.2
struct Date {
    int y, m, d;                    // year, month, day
    Date(int y, int m, int d);      // check for valid date and initialize	
    void add_day(int n);            // increase the Date by n days
};
	
Date::Date(int yy, int mm, int dd)
     :y{yy}, m{mm}, d{dd}

{
    if (m < 1 || 12 < m) error("invalid month");
    if (d < 1 || 31 < d) error("impossible day");
}
	
void Date::add_day(int n)
{
    d += n;
    if (d > 31) d %= 31;
}
	
ostream& operator<<(ostream& os, const Date& d)
{
    return os << '(' << d.y << ',' << d.m << ',' << d.d << ')';
}
	
int main()
try {
    Date today(1978, 6, 25);
    Date tomorrow = today;
    tomorrow.add_day(1);
    cout << today << '\n'
         << tomorrow << '\n';

    //Date bad_day(2004, 13, -5);
}

catch(exception& e) {
    cerr << e.what() << '\n';
    return 1;
}
catch(...) {
    cerr << "unknown error" << '\n';
    return 2;
}
*/
	
/* 9.4.3
class Date {
    int y, m, d;
public:
    Date(int y, int m, int d);      // check for valid date and initialize
    void add_day(int n);            // increase the Date by n days
    int month() const { return m; }
    int day() const { return d; }
    int year() const { return y; }
};
	
Date::Date(int yy, int mm, int dd)
     :y{yy}, m{mm}, d{dd}
{
    if (m < 1 || 12 < m) error("invalid month");
    if (d < 1 || 31 < d) error("impossible day");
}

void Date::add_day(int n)
{
    d += n;
    if (d > 31) d %= 31;
}
	
ostream& operator<<(ostream& os, const Date& d)
{
    return os << '(' << d.year()	
              << ',' << d.month()
              << ',' << d.day() << ')';
}
	
int main()
try {
    Date today(1978, 6, 25);
    Date tomorrow = today;
    tomorrow.add_day(1);

    cout << today << '\n'	
         << tomorrow << '\n';

    //Date bad_day(2004, 13, -5);
}

catch(exception& e) {
    cerr << e.what() << '\n';
    return 1;
}
	
catch(...) {
    cerr << "unknown error" << '\n';
    return 2;
}
*/
	
// 9.7.1
/*
enum class Month {
   jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

vector<string> month_tbl = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

ostream& operator<<(ostream& os, Month m)
{
    return os << month_tbl[int(m)];
}

class Date {
    int y;
    Month m;
	
    int d;
public:
    Date(int y, Month m, int d);
    void add_day(int n);
    
    int year() const {
     return y; 
    }
    
    Month month() const {
     return m;
      }
    int day() const {
     return d; 
     }
};
	
Date::Date(int yy, Month mm, int dd)
     :y{yy}, m{mm}, d{dd}
{
    if (d < 1 || 31 < d) error("impossible day");
}
	
void Date::add_day(int n)
{
    d += n;
    if (d > 31) d %= 31;
}
	
ostream& operator<<(ostream& os, const Date& d)
{
    return os << '(' << d.year()
              << ',' << d.month()
              << ',' << d.day() << ')';
}
	
int main()
try {
    Date today(1978, Month::jun, 25);
    Date tomorrow = today;
    tomorrow.add_day(1);
	
    cout << today << '\n'
	 << tomorrow << '\n';
	
    //Date bad_day(2004, 13, -5);
	
}
catch(exception& e) {
    cerr << e.what() << '\n';
    return 1;
}
catch(...) {
    cerr << "unknown error" << '\n';
    return 2;

}
*/

//9.7.4
enum class Month {
    jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

vector<string> months {
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};

ostream& operator<<(ostream& os, Month m)
{
	return os << months[int(m)-1];
}

class Date{
    int y, d;
    Month m;
public:
    Date(int y, Month m, int d);
    void add_day(int n);
    void add_month(int n);
    void add_year(int n);
    Month month() const {return m;};
    int day() const {return d;};
    int year() const {return y;};
};

Date::Date (int yy, Month mm, int dd) {
    if(yy < 0 || dd < 0 || dd > 31 || int(mm) < 1 || int(mm) > 12) error("invalid date!");
    y = yy;
    m = mm;
    d = dd;
}

void Date::add_day(int n) {
    d += n;
    int im = int(m);
    for (;d > 31;)
    {
        d -= 31;
        ++im;
    }
    for (;im > 12;)
    {
        im -= 12;
        ++y;
    }
    for (;d < 1;)
    {
        d += 31;
        --im;
    }
    for (;im < 1;)
    {
        im += 12;
        --y;
    }
    m = Month(im);
}

void Date::add_month(int n) {

    int im = int(m);
    im += n;
    for (;im > 12;)
    {
        im -= 12;
        ++y;
    }
    for (;im < 1;)
    {
        im += 12;
        --y;
    }
    m = Month(im);
}

void Date::add_year(int n) {
    y += n;
}

ostream& operator<<(ostream& os, Date& dd)
{
    return os << dd.year() << ' '
              << dd.month() << ' '
              << dd.day();
}

int main() {

    Date today{1978, Month::jun, 25};
    Date tommorow {today};
    tommorow.add_day(1);
    //today.add_month(38); output "1981 August 25"
    cout << today << endl;
    cout << tommorow << endl;
    //Date t_1{2006, 17, -9}; will not compile
    /*
    Date t_2{2021, Month::dec, 31};
    t_2.add_day(1);
    cout << t_2 << endl;
    output "2022 January 1"
    */
    return 0;
}
