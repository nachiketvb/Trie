#include"trie.h"
#include<iostream>
#include<string>

using namespace std;

int main(int argc, char*argv[])
{
	trie<char, string> words;
	words.insert("aa");
	words.insert("ab");
	words.insert("aabb");
	words.insert("abab");
	words.insert("Hello World!");
	cout << words.find("aa") << endl;
	cout << words.find("aaa") << endl;
	cout << words.find("a") << endl;
	cout << words.find("ab") << endl;
	cout << words.find("aba") << endl;
	cout << words.find("Hello World") << endl;
	cout << words.find("Hello World!") << endl;
	cout << words.find("") << endl;
	vector<string> a_strings = words.containers_with_prefix("a");
	for (auto &i : a_strings) {
		cout << i << " ";
	}
	cout << "count =" << words.num_containers_with_prefix("a") << endl;
	vector<string> empty_strings = words.containers_with_prefix("");
	for (auto &i : empty_strings) {
		cout << i << " ";
	}
	cout << "count =" << words.num_containers_with_prefix("") << endl;
	vector<string> ab_strings = words.containers_with_prefix("ab");
	for (auto &i : ab_strings) {
		cout << i << " ";
	}
	cout << "count =" << words.num_containers_with_prefix("ab") << endl;
	vector<string> aa_strings = words.containers_with_prefix("aa");
	for (auto &i : aa_strings) {
		cout << i << " ";
	}
	cout << "count =" << words.num_containers_with_prefix("aa") << endl;
	vector<string> b_strings = words.containers_with_prefix("b");
	for (auto &i : b_strings) {
		cout << i << " ";
	}
	cout << "count =" << words.num_containers_with_prefix("b") << endl;
	vector<string> Hello_strings = words.containers_with_prefix("Hello");
	for (auto &i : Hello_strings) {
		cout << i << " ";
	}
	cout << "count =" << words.num_containers_with_prefix("Hello") << endl;
	vector<string> Hello_World_strings = words.containers_with_prefix("Hello World!");
	for (auto &i : Hello_World_strings) {
		cout << i << " ";
	}
	cout << "count =" << words.num_containers_with_prefix("Hello World") << endl;
	vector<string> Hello_only_strings = words.containers_with_prefix("Hello!");
	for (auto &i : Hello_only_strings) {
		cout << i << " ";
	}
	cout << "count =" << words.num_containers_with_prefix("Hello!") << endl;
	return 0;
}
