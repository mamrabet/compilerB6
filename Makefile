CXX = g++
CXXFLAGS = -Wall -Winline -fmessage-length=0 -ggdb -fno-inline -I /home/m/mamrabet/flex/include

all : my_comp

my_comp : SyntaxTree.o SimpleC_gram.o SimpleC_lex.o Algorithms.o
	$(CXX) -o my_comp $(CXXFLAGS) SyntaxTree.o Algorithms.o SimpleC_gram.o SimpleC_lex.o /home/m/mamrabet/flex/lib/libfl.a

SyntaxTree.o : SyntaxTree.cpp SyntaxTree.h Algorithms.h
	$(CXX) -c -o SyntaxTree.o $(CXXFLAGS) SyntaxTree.cpp

Algorithms.o : Algorithms.cpp SyntaxTree.h Algorithms.h
	$(CXX) -c -o Algorithms.o $(CXXFLAGS) Algorithms.cpp

SimpleC_gram.o : SimpleC_gram.cpp SyntaxTree.h
	$(CXX) -c -o SimpleC_gram.o $(CXXFLAGS) SimpleC_gram.cpp

SimpleC_lex.o : SimpleC_lex.cpp SyntaxTree.h
	$(CXX) -c -o SimpleC_lex.o $(CXXFLAGS) SimpleC_lex.cpp

SimpleC_gram.cpp : SimpleC.yy
	bison --debug -o SimpleC_gram.cpp SimpleC.yy

SimpleC_lex.cpp : SimpleC.lex
	flex -oSimpleC_lex.cpp SimpleC.lex

clean :
	rm my_comp *.o SimpleC_gram.cpp SimpleC_lex.cpp
