#include <vector>
#include <memory>
#include <unordered_map>
#include <algorithm>
#ifndef TRIE_H
#define TRIE_H

template<class KeyType, class ContainerType>
class trie;

template<class KeyType, class ContainerType>
class trie_node {
private:
	friend class trie<KeyType, ContainerType>;
        std::unordered_map<KeyType, std::shared_ptr<trie_node<KeyType, ContainerType>>> next_;
	bool complete_;
public:
	trie_node():complete_(false)
	{
	}
	std::shared_ptr<trie_node<KeyType,ContainerType>> get_child(const KeyType &key) const
	{
		auto itr = next_.find(key);
		if (itr == next_.end()) {
			return std::shared_ptr<trie_node<KeyType, ContainerType>>();
		} else {
			return itr->second;
		}
	}
	void set_child(const KeyType &key) {
		next_[key] = std::make_shared<trie_node<KeyType, ContainerType>>();
	}
	bool is_complete() const
	{
		return complete_;
	}
	void set_complete(const bool &complete)
	{
		complete_ = complete;
	}
};

template <class KeyType, class ContainerType>
class trie {
private:
	std::shared_ptr<trie_node<KeyType, ContainerType>> root_;
	void get_child_containers_(std::shared_ptr<trie_node<KeyType, ContainerType>>, std::vector<ContainerType>&, ContainerType) const;
	unsigned int get_num_child_containers_(std::shared_ptr<trie_node<KeyType, ContainerType>>) const;
public:
	trie() {
		root_ = std::make_shared<trie_node<KeyType, ContainerType>>();
		root_->set_complete(false); 
	}
	void insert(const ContainerType &container);
	bool find(const ContainerType &container) const;
	void remove(const ContainerType &container);
	std::vector<ContainerType> containers_with_prefix(const ContainerType &container_prefix) const;
	unsigned int num_containers_with_prefix(const ContainerType &container_prefix) const;
};

template<class KeyType, class ContainerType>
void trie<KeyType, ContainerType>::get_child_containers_(std::shared_ptr<trie_node<KeyType, ContainerType>> current_node, std::vector<ContainerType> &result, ContainerType container_prefix) const
{
	if (current_node->is_complete()) {
		result.push_back(container_prefix);
	}
	for (auto &i : current_node->next_) {
		if (i.second.get() != nullptr) {
			container_prefix.push_back(i.first);
			get_child_containers_(i.second, result, container_prefix);
			container_prefix.pop_back();
		}
	}
}

template<class KeyType, class ContainerType>
unsigned int trie<KeyType, ContainerType>::get_num_child_containers_(std::shared_ptr<trie_node<KeyType, ContainerType>> current_node) const
{
	unsigned count = 0;
	if (current_node->is_complete()) {
		count = 1;
	}
	for (auto &i : current_node->next_) {
		if (i.second.get() != nullptr) {
			count += get_num_child_containers_(i.second);
		}
	}
	return count;
}

	
template<class KeyType, class ContainerType>
void trie<KeyType, ContainerType>::insert(const ContainerType &container)
{
	auto current_node = root_;
	auto i = begin(container);
	while (i != end(container)) {
		auto j = current_node->get_child(*i);
		if (j.get() == nullptr) {
			break;
		}
		current_node = j;
		++i;
	}
	while (i != end(container)) {
		current_node->set_child(*i);
		current_node = current_node->get_child(*i);
		++i;
	}
	current_node->set_complete(true);
}

template<class KeyType, class ContainerType>
bool trie<KeyType, ContainerType>::find(const ContainerType &container) const
{
	auto current_node = root_;
	for (auto &i: container) {
		auto j = current_node->get_child(i);
		if (j.get() == nullptr) {
			return false;
		}
		current_node = j;
	}
	if (current_node->is_complete()) {
		return true;
	} else {
		return false;
	}
}

template<class KeyType, class ContainerType>
std::vector<ContainerType> trie<KeyType, ContainerType>::containers_with_prefix(const ContainerType &container_prefix) const
{
	std::vector<ContainerType> result;
	auto current_node = root_;
	for (auto &i: container_prefix) {
		auto j = current_node->get_child(i);
		if (j.get() == nullptr) {
			return result;
		}
		current_node = j;
	}
	get_child_containers_(current_node, result, container_prefix);
	return result;
}

template<class KeyType, class ContainerType>
unsigned int trie<KeyType, ContainerType>::num_containers_with_prefix(const ContainerType &container_prefix) const
{
	auto current_node = root_;
	for (auto &i: container_prefix) {
		auto j = current_node->get_child(i);
		if (j.get() == nullptr) {
			return 0;
		}
		current_node = j;
	}
	return get_num_child_containers_(current_node);
}

#endif
