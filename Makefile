CXX=clang++
CXXFLAGS=-O2 -std=c++11 -stdlib=libc++ -Wall
LDFLAGS=-O2 -stdlib=libc++

trie_test : trie_test.o
	$(CXX) $(LDFLAGS) -o trie_test trie_test.o
trie_test.o : trie_test.cpp trie.h
	$(CXX) $(CXXFLAGS) -c -o trie_test.o trie_test.cpp
clean :
	rm -f trie trie_test.o;
