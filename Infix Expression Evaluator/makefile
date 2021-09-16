Project5: main.o MyStack.o Token.o TokenReader.o
	g++ -o Project5 main.o MyStack.o Token.o TokenReader.o

main.o: main.cpp MyStack.h Token.h TokenReader.h
	g++ -c main.cpp

MyStack.o: MyStack.cpp MyStack.h
	g++ -c MyStack.cpp

Token.o: Token.cpp Token.h
	g++ -c Token.cpp

TokenReader.o: TokenReader.cpp Token.h TokenReader.h
	g++ -c TokenReader.cpp

clean:
	rm main.o MyStack.o Token.o TokenReader.o Project5
