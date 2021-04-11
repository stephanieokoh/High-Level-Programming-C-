#include “std_lib_facilities.h”

//——————————————————————————

// ERROR1.syntax class Token {
class Token {
public:
char kind;        
double value;     
Token(char ch)    
:kind(ch), value(0) { }
Token(char ch, double val)    
:kind(ch), value(val) { }
};

//——————————————————————————

class Token_stream {
public:
Token_stream();  
Token get();      
void putback(Token t);    
private:
bool full;        
Token buffer;     
};

//——————————————————————————

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
:full(false), buffer(0)    
{
}

//——————————————————————————

// The putback() member function puts its argument back into the Token_stream’s buffer:
void Token_stream::putback(Token t)
{
if (full) error(“putback() into a full buffer”);
buffer = t;      
full = true;      
}

//——————————————————————————

// ERROR2 - syntax Token get()
Token Token_stream::get()
{
if (full) {     
// remove token from buffer
full=false;
return buffer;
}

char ch;
cin >> ch;    
switch (ch) {
case ‘=’:    // for “print”
case ‘x’:    // for “quit”
case ‘(‘: case ‘)’: case ‘+’: case ‘-‘: case ‘*’: case ‘/’:
return Token(ch);        
case ‘.’:
case ‘0’: case ‘1’: case ‘2’: case ‘3’: case ‘4’:
// ERROR3 logic case ‘5’: case ‘6’: case ‘7’: case ‘9’:
case ‘5’: case ‘6’: case ‘7’: case’8′: case ‘9’:
{
cin.putback(ch);        
double val;
cin >> val;             
return Token(‘8’,val);   
}
default:
error(“Bad token”);
}
}

//——————————————————————————

Token_stream ts;       

//——————————————————————————

double expression();   

//——————————————————————————
// deal with numbers and parentheses
double primary()
{
Token t = ts.get();
switch (t.kind) {
case ‘(‘:    
{
double d = expression();
t = ts.get();
// ERROR4 - syntax if (t.kind != ‘)’) error(“‘)’ expected);
if (t.kind != ‘)’) error(“‘)’ expected”);
return d;
}
case ‘8’:           
return t.value; 
default:
error(“primary expected”);
}
}
//——————————————————————————

// deal with *, /, and %
double term()
{
double left = primary();
Token t = ts.get();       

while(true) {
switch (t.kind) {
case ‘*’:
left *= primary();
t = ts.get();
// ERROR5 - logic no break;
break;
case ‘/’:
{
double d = primary();
if (d == 0) error(“divide by zero”);
left /= d;
t = ts.get();
break;
}
default:
ts.putback(t);     
return left;
}
}
}

//——————————————————————————

// deal with + and –
double expression()
{
// ERROR6 - syntax double left = term(;      
double left = term();      
Token t = ts.get();        

while(true) {
switch(t.kind) {
case ‘+’:
left+ = term();   
t = ts.get();
break;
case ‘-‘:
// ERROR7 - logic left += term();    
left- = term();    
t = ts.get();
break;
default:
ts.putback(t);     
return left;       
}
}
}

//——————————————————————————

int main()
try
{
cout << “Welcome to our simple calculator.n”
<< “Please enter expressions using floating-point numbers.n”
<< “(We have  +, -, *, /, and () )n”
<< “Evaluate the expression with = at the end. Enter x to quit.n”;

// ERROR8 syntax No val variable declared
double val = 0;
while (cin) {
Token t = ts.get();

if (t.kind == ‘x’) break; // ‘q’ for quit
if (t.kind == ‘=’) {      // ‘;’ for “print now”
cout << “=” << val << ‘n’;
}
else {
ts.putback(t);
val = expression();
}
}
keep_window_open();
}
catch (exception& e) {
cerr << “error: ” << e.what() << ‘n’;
keep_window_open();
return 1;
}
catch (…) {
cerr << “Oops: unknown exception!n”;
keep_window_open();
return 2;
}

//——————————————————————————
