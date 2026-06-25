how to use (for now):

1. go to the test directory and write code to main.dumblang.
2. go to the src directory and run the following command:
3. g++ main.cpp lexer.cpp token.cpp filereader.cpp -o main && ./main ../../test/FILENAMEHERE.dumblang


if you haven't changed the filename (main.dumblang)
g++ main.cpp lexer.cpp token.cpp filereader.cpp -o main && ./main ../../test/main.dumblang


if you want to compile first:

compile:
g++ main.cpp lexer.cpp token.cpp filereader.cpp -o main

run:
./main ../../test/main.dumblang

