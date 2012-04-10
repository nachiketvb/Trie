#include <vector>
#include <memory>
#include <unordered_map>
#ifndef TRIE_H
#define TRIE_H
template<class KeyType, class ValueType> class trie_node {
private:
        std::unordered_map<KeyType, std::shared_ptr<trie_node<KeyType, ValueType>>> next_;
        std::shared_ptr<ValueType> value_;
public:
	trie_node()
	{
	}
	trie_node(Valuetype value) : value_(make_shared<ValueType> value); 
	{
	}
	std::shared_ptr<trie_node<KeyType,ValueType>> get_child(const KeyType &key) const
	{
		auto itr = next_.find(key);
		if (itr == next_.end()) {
			return std::shared_ptr<trie_node<KeyType, ValueType>>();
		} else {
			return *itr;
		}
	}
	void set_child(const KeyType &key, const std::shared_ptr<trie_node<KeyType, ValueType>> &child) {
		next_[key] = child;
	}
	ValueType get_value() const
	{
		return *value_;
	}
	void set_value(ValueType value)
	{
		value_ = make_shared<ValueType>(value);
	}
};

template <class KeyType, class ValueType> class trie {
private:
	shared_ptr<trie_node<KeyType, ValueType>> root;
public:
	void insert(const ValueType &value);
	bool find(const ValueType &value) const;
	void remove(const Valuetype &value);
	std::vector<ValueType> values_with_prefix(const ValueType &value_prefix) const;
}
#endif
