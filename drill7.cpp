#include "std_lib_facilities.h"

// user defined type to hold name-value pair for use in calculator

struct Token {
char kind;
double value;
string name;
Token(char ch) :kind(ch), value(0) { }    
Token(char ch, double val) :kind(ch), value(val) { }
Token(char ch, string n) :kind(ch), name(n) { }
};

//user defined type that handles retrieving items from input

class Token_stream {
bool full;
Token buffer;
public:
     Token_stream() :full(0), buffer(0) { }
     
      Token get();
      void unget(Token t) { buffer = t; full = true; }

      void ignore(char);
};

// I had to identify both square root and power and some strings

const char let = 'L';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char squareR = 's';
const char findPow = 'p';
const string declKey = "#";
const string quitKey = "quit";
const string sqrtKey = "sqrt";
const string powKey = "pow";

//Evaluate each char in the stream and determine what it is 

Token Token_stream::get()
{

if (full) //check if we already have a token ready
{ 
  full = false; 
  return buffer; 
}
char ch;
cin >> ch; 
switch (ch) 
{
  case '(': case ')': case '+': case '-':
  case '*': case '/': case '%': case ';':
  case '=': case ',':
   return Token(ch);     //let each char represent itself
  case '.':
  case '0': case '1': case '2': case '3':
  case '4': case '5': case '6': case '7':
  case '8': case '9':
  { cin.unget();      //this helps to put digit back into the input stream
   double val;
   cin >> val;       //this is to read a floating-point number
   return Token{ number, val };  //return number or decimal with a value, put back into buffer
  }
 
  //allow user defined variables if user types #

  case '#':
   return Token(let);
  default:

   //you only do this if ch is a letter
   if (isalpha(ch)) 
   {
    string s;
    s += ch;

    //although there are still chars in cin, read them into s
    while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) 
     s += ch;
    cin.unget();

    //if string is equal to other commands that are defined below, return them
    if (s == declKey) 
     return Token(let);
    if (s == quitKey) 
     return Token(quit);
    if (s == sqrtKey)
     return Token(squareR);
    if (s == powKey)
     return Token(findPow);
    return Token(name, s);
   }

   //if the char does not fit any of these parameters return an error message
   error("Bad token");
}
}


//discard characters from c
//c represents the kind of token
void Token_stream::ignore(char c)
{
//look in the buffer
if (full && c == buffer.kind) 
{
  full = false;
  return;
}
full = false;
// search input
char ch;
while (cin >> ch)
  if (ch == c) return;
}

struct Variable 
{
string name;
double value;
Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> names; 
//return the value of the Variable named s
double get_value(string s, double val)
{
for (int i = 0; i < names.size(); ++i)
{
  if (names[i].name == s)
{
  return names[i].value;
  }
 }
error("get: undefined name ", s);
}

//set the Variable named s to d
void set_value(string s, double d)
{

for (int i = 0; i <= names.size(); ++i)
  if (names[i].name == s) 
  {
   names[i].value = d;
   return;
  }
error("set: undefined name ", s);
}

//find out if the variable was already declared
bool is_declared(string s)
{

for (int i = 0; i < names.size(); ++i)
{

  if (names[i].name == s) 
   return true;
}
return false;
}

//read in values that are accepted for first time use
double primary()
{
//get character from stream
Token t = ts.get();
switch (t.kind) 
{
  //solve "(expression)"
  case '(':
  {
   double d = expression();
   t = ts.get();
   checkForChar(t, ')');
   return d;
  }
  //solve "-primary"
  case '-':
   return -primary();
 //solve "number"
  case number:
   return t.value;
  //solve "let name = value"
  case name:
   return get_value(t.name, 0);
    //solve "sqrt(expression)"
  case squareR:
  {
   //get next char after 'sqrt' if not '(' then error  
   t = ts.get();
   checkForChar(t, '(');

   //if expression is less than 0 print an error
   double d = expression();
   if (d < 0)
    error("Cannot squareroot negative integers");
   //get next char after expression, if not ')' then error
   t = ts.get();
   checkForChar(t, ')');
   // return square root of the expression taken from the tokenstream
   return sqrt(d);
  }
  //solve "pow(expression, expression)"
  case findPow:
  {
   //get next char after 'pow' if not '(' then error  
   t = ts.get();
   checkForChar(t, '(');

   //get the expression after '('
   double d = expression();

   //get next char after 'expression' if not ',' then error  
   t = ts.get();
   checkForChar(t, ',');

   //get the expression after ','
   double i = expression();

   //get next char after expression, if not ')' then error
   t = ts.get();
   checkForChar(t, ')');

   // return expression using pow() from <cmath>
   return pow(d, i);
  }
  default:
   error("primary expected");
}
}
//read in values that would normally come after a primary

double term()
{
double left = primary();
while (true) 
{
  Token t = ts.get();
  switch (t.kind) 
  {
   case '*':
    left *= primary();
    break;
   case '/':
   {
    double d = primary();
    if (d == 0) 
     error("divide by zero");
    left /= d;
    break;
   }
   case '%':
   {
    double d = primary();
    if (d == 0)
     error("%:divide by zero");
    left = fmod(left, d);
    break;
   }
   default:
    ts.unget(t);
    return left;
  }
}
}

double expression()
{

double left = term();
while (true) 
{
  Token t = ts.get();
  switch (t.kind) 
  {
   case '+':
    left += term();
    break;
   case '-':
    left -= term();
    break;
   default:
    ts.unget(t);
    return left;
  }
}
}

//check for name definition errors
double declaration()
{
Token t = ts.get();
if (t.kind != 'a') 
  error("name expected in declaration");
string name = t.name;
if (is_declared(name)) 
  error(name, " declared twice");
Token t2 = ts.get();
if (t2.kind != '=') 
  error("= missing in declaration of ", name);
double d = expression();
names.push_back(Variable(name, d));
return d;
}

double statement()
{
Token t = ts.get();
switch (t.kind) 
{
  case let:
   return declaration();
  default:
   ts.unget(t);
   return expression();
}
}
void clean_up_mess()
{
ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

void calculate()
{
while (true) try 
{
  cout << prompt;
  Token t = ts.get();
  while (t.kind == print) 
   t = ts.get();       //you have to discard all 'prints'
  if (t.kind == quit) 
   return;
  ts.unget(t);
  cout << result << statement() << endl;
}
catch (exception& e) 
{
  cerr << e.what() << endl;
  clean_up_mess();
}
}

int main()
try {
define_name("pi", 3.1415926535);
define_name("e", 2.7182818284);
define_name("k", 1000);
calculate();
return 0;
}
catch (exception& e) {
cerr << "exception: " << e.what() << endl;
char c;
while (cin >> c && c != ';');
return 1;
}
catch (...) {
cerr << "exception\n";
char c;
while (cin >> c && c != ';');
return 2;
}
