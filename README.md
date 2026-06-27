# Dumblang

## How to use:

Inside **src/lexer/** run the following command:  

**compile:**  
``g++ g++ main.cpp lexer.cpp token.cpp filereader.cpp -o main ``

**run:**  
``./main``

You will be met with the following output:
```
1. Enter code file path
2. Write code directly.

Input:
```
If you enter **1**, you will be met with the following output:
```
1. Enter code file path
2. Write code directly.

Input: 1
Enter the code file path:
```
If you want to use one of the code files from the **test/** folder, you need to enter the file name as such:  

`../../test/file_name.dumblang`

If you want to use your own files, you need to have your code written in a file with the extension **.dumblang**  and enter the full file path.

If you enter **2**, you will be met with the following output:
```
1. Enter code file path
2. Write code directly.

Input: 2
Write your code. When you're done, enter a new line and press: CTRL+D
```
In this case, you can directly write code in the console which will then be passed to the Lexer to tokenize. 

**NOTE:** Since this project isn't a text editor, navigating with arrow keys are not working.

When you are done writing code, make sure to enter a new line and press **CTRL+D** to signal the EOF as such:
```
1. Enter code file path
2. Write code directly.

Input: 2
Write your code. When you're done, enter a new line and press: CTRL+D

int x = 3;
int y = 100;

if (x <= y) {
    print("Y is bigger than X");
}
// CTRL+D                     <-----------------
```

Once you press **CTRL+D**, you should instantly get the tokenized output.  

Heres 2 sample outputs showcasing the program's functionality for cases **1** and **2**:

**Case 1:**
```
1. Enter code file path
2. Write code directly.

Input: 1
Enter the code file path: ../../test/main.dumblang
Lexeme: int      TokenType: int
Lexeme: x        TokenType: Ident
Lexeme: =        TokenType: Equals
Lexeme: 3        TokenType: Integer Literal
Lexeme: ;        TokenType: Semicolon
Lexeme: double   TokenType: double
Lexeme: d        TokenType: Ident
Lexeme: =        TokenType: Equals
Lexeme: 2.3      TokenType: Double Literal
Lexeme: ;        TokenType: Semicolon
Lexeme: string   TokenType: string
Lexeme: a        TokenType: Ident
Lexeme: =        TokenType: Equals
Lexeme: Hello    TokenType: String Literal
Lexeme: ;        TokenType: Semicolon
Lexeme: while    TokenType: while
Lexeme: (        TokenType: LeftParentheses
Lexeme: true     TokenType: Ident
Lexeme: )        TokenType: RightParentheses
Lexeme: {        TokenType: LeftBrace
Lexeme: print    TokenType: Ident
Lexeme: (        TokenType: LeftParentheses
Lexeme: a        TokenType: Ident
Lexeme: )        TokenType: RightParentheses
Lexeme: ;        TokenType: Semicolon
Lexeme: }        TokenType: RightBrace
```
**Case 2:**
```
1. Enter code file path
2. Write code directly.

Input: 2
Write your code. When you're done, enter a new line and press: CTRL+D

string fruit = "Apple";
double a = 2.3

if (fruit.length() >= 120) {
    print("Woah!");
}
Lexeme: string   TokenType: string
Lexeme: fruit    TokenType: Ident
Lexeme: =        TokenType: Equals
Lexeme: Apple    TokenType: String Literal
Lexeme: ;        TokenType: Semicolon
Lexeme: double   TokenType: double
Lexeme: a        TokenType: Ident
Lexeme: =        TokenType: Equals
Lexeme: 2.3      TokenType: Double Literal
Lexeme: if       TokenType: if
Lexeme: (        TokenType: LeftParentheses
Lexeme: fruit    TokenType: Ident
Lexeme: .        TokenType: Dot
Lexeme: length   TokenType: Ident
Lexeme: (        TokenType: LeftParentheses
Lexeme: )        TokenType: RightParentheses
Lexeme: >=       TokenType: GreaterThanOrEquals
Lexeme: 120      TokenType: Integer Literal
Lexeme: )        TokenType: RightParentheses
Lexeme: {        TokenType: LeftBrace
Lexeme: print    TokenType: Ident
Lexeme: (        TokenType: LeftParentheses
Lexeme: Woah!    TokenType: String Literal
Lexeme: )        TokenType: RightParentheses
Lexeme: ;        TokenType: Semicolon
Lexeme: }        TokenType: RightBrace
```
