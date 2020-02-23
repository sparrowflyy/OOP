#pragma once
#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <exception>
#include <stdexcept>
template <class T> class SubTrie
{
public:
	SubTrie():parent(nullptr){};
	SubTrie(char _c, SubTrie<T>* _parent, std::string& _cur_key) :character(_c), node_value{ _cur_key,T() }, parent(_parent) {};
	~SubTrie()
	{
		children.clear();
	}

	char character{};
	bool hasValue = false;
	std::pair<const std::string, T> node_value;
	SubTrie<T>* parent;
	std::map<const char, std::shared_ptr<SubTrie<T>> > children;
	
								
};

template <class T> class Trie
{

	typedef T value;
	typedef const std::string key;
	typedef std::pair<key, value> node_value;
	typedef const std::pair<key, value> const_node_value;
	
    SubTrie<T>* root;
	size_t count;
	SubTrie<T>* find_first() const;
	SubTrie<T>* find_last() const;
	
public:
	Trie()
	{
		root = new SubTrie<T>();
		count = 0;						   
	};
	Trie(const Trie<T> & trie);
	~Trie()
	{
		clear();
		delete root;
	};
	
	template<bool is_const>
	class _trie_iterator final {
	friend class Trie;
	typename std::conditional<is_const, const Trie<T>&, Trie<T>&>::type  this_trie;
	std::map<const std::string, char> ex_keys;
	typename std::conditional <is_const, const SubTrie<value>*, SubTrie<value>* > ::type node = nullptr;
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = typename std::conditional < is_const,const_node_value,node_value>::type;
		using pointer = value_type*;
		using reference = value_type&;																	  
		using const_reference = const value_type&;														 
		_trie_iterator(typename std::conditional <is_const, const SubTrie<value>*, SubTrie<value>* > ::type _node,
		typename std::conditional<is_const, const Trie<T>&, Trie<T>&>::type _this_trie):this_trie(_this_trie) { node = _node;};
		~_trie_iterator() = default;
		
		_trie_iterator &operator=(_trie_iterator another)
		{
			node = std::move(another.node);
			ex_keys = std::move(another.ex_keys);
			return *this;
		}
		_trie_iterator& operator ++()
		{
			if (node == nullptr) throw std::runtime_error("Handling to end()!");
			std::string current_key = node->node_value.first;
			auto last = this_trie.find_last();
			if (node == last) {
				node = nullptr;
				return *this;
			}
			do
			{
				ex_keys[node->node_value.first];
				node = find_next(node);
			} while (!(node->hasValue && !were_before(node) && current_key < node->node_value.first));
			return *this;
		};
		_trie_iterator  operator++(int)
		{
			if (node == nullptr) throw std::runtime_error("Handling to end()!");
			_trie_iterator tmp = *this;
			++*this;
			return tmp;
		};
		typename std::conditional <is_const, const_reference, reference >::type operator*()
		{
			if (node == nullptr) throw std::runtime_error("Handling to end()!");
			return node->node_value;
		}
		bool operator ==(const _trie_iterator& it) const
		{
			if (node == nullptr && it.node == nullptr) return true;
			if (node == nullptr && it.node != nullptr) return false;
			if (node != nullptr && it.node == nullptr) return false;
			return (node->node_value.first == it.node->node_value.first);
		};
		bool operator !=(const _trie_iterator& it) const
		{
			return !(*this==it);
		};
		pointer operator->()
		{
			if (node == nullptr) throw std::runtime_error("Handling to end()!");
			return &node->node_value;
		};
		
	private:
		bool were_before(typename std::conditional <is_const, const SubTrie<value>*, SubTrie<value>* > ::type _node)
		{
			if (_node == nullptr) return false;
			return (ex_keys.find(_node->node_value.first) != ex_keys.end());
		}
		typename std::conditional <is_const, const SubTrie<value>*, SubTrie<value>* > ::type next_children(typename std::conditional <is_const, const SubTrie<value>*, SubTrie<value>* > ::type _node)
		{
			auto visited_child = std::find_if(_node->children.begin(), _node->children.end(),
			[this](typename std::conditional <is_const, const std::pair<const char, std::shared_ptr<SubTrie<T>>>&, std::pair<const char, std::shared_ptr<SubTrie<T>>>& > ::type map_node) 
			{ return (ex_keys.find(map_node.second->node_value.first) != ex_keys.end()); });
			if (visited_child == _node->children.end()) {
				return _node->children.begin()->second.get();
			}		
			for (auto next_child = visited_child;next_child!=_node->children.end();++next_child)
			{
				if (ex_keys.find(next_child->second->node_value.first) == ex_keys.end()) return next_child->second.get();
			}
			return _node->parent;
			 
		}
		typename std::conditional <is_const, const SubTrie<value>*, SubTrie<value>* > ::type find_next(typename std::conditional <is_const, const SubTrie<value>*, SubTrie<value>* > ::type _node) {
			if (_node->children.empty()) return _node->parent;
			return next_children(_node);
		}
		
	};
	using trie_iterator =_trie_iterator<false>;
	using const_trie_iterator = _trie_iterator<true>;
	
	
	
	trie_iterator begin()
	{
		if (count == 0) return end();
		return trie_iterator(find_first(), *this);
	};
	const_trie_iterator cbegin() const
	{
		if (count == 0) return cend();
		return const_trie_iterator(find_first(), *this);
	};

	trie_iterator end() { return trie_iterator(nullptr,*this); };
	const_trie_iterator cend() const { return const_trie_iterator(nullptr, *this); };

	bool empty() const { return count == 0; }; //Test whether container is empty
	size_t size() const { return count; };										  

	value& operator[] (const key& k);

	std::pair<trie_iterator, bool> insert(const key& k, const value& val);	  



	//удаление
	void erase(trie_iterator position);
	void erase(const key& k);							   
	void erase(trie_iterator first, trie_iterator last);
	void clear(); //очистить структуру
	
	void swap(Trie& trie);
	Trie<T> & operator= (const Trie & trie);			
	
	//найти элемент
	trie_iterator find(const key& k);				
	const_trie_iterator cfind(const key& k) const;

};

template <class T>
Trie<T>& Trie<T>::operator=(const Trie& trie)
{
	clear();
	for (auto it = trie.cbegin(); it != trie.cend(); ++it)
	{
		insert(it.node->node_value.first, it.node->node_value.second);
	}
	return *this;
}

 template <class T>
 Trie<T>::Trie(const Trie<T>& trie)
 {
	 root = new SubTrie<T>();
	 count = 0;
 	for(auto it = trie.cbegin();it!=trie.cend();++it)
 	{
		insert(it.node->node_value.first, it.node->node_value.second);
 	}
 }

template <class T>
void Trie<T>::swap(Trie& trie)
{
	std::swap(root, trie.root);
	const int another_count = trie.count;
	trie.count = count;
	count = another_count;
	
}


template <class T>
void Trie<T>::clear()
{
	if (count == 0) return;
	erase(begin(), end());
}


template <class T>
typename Trie<T>::value& Trie<T>::operator[](key& k)
{
	auto iter = find(k);
	if (iter == end())
	{
		std::pair<trie_iterator, bool> inserted = insert(k,value());
		if (inserted.second == true) return inserted.first.node->node_value.second;
	}
	return iter.node->node_value.second;
}


 template <class T>
 void Trie<T>::erase(trie_iterator position)
 {
	 erase(position.node->node_value.first);
 }

template <class T>
void Trie<T>::erase(trie_iterator first, trie_iterator last)
{
	if (first.node == nullptr) return;
	auto temp = first;
	for (auto it = first;it!=last;)
	{
		++temp;
		erase(it);
		if (temp.node == nullptr) break;
		it.node = temp.node;
	}
	if (last!=end()) erase(last);
}


template <class T>
std::pair<typename Trie<T>::trie_iterator, bool> Trie<T>::insert(const key& k, const value& val)
{
	auto element = find(k);
	if(element!=end())
	{
		element->second = val;
		return { element,false };
	}
	size_t size = k.size();
	SubTrie<T>* temp = root;
	for (size_t i = 0; i < size; i++) {
		if (i == size - 1)
		{
			if (temp->children.find(k[i]) != temp->children.end())
			{
				temp = temp->children[k[i]].get();
				temp->hasValue = true;
				temp->node_value.second = val;
				count++;
				return { trie_iterator(temp,*this), true };
			}
			
			std::string cur_key = k.substr(0, i + 1);
			auto new_children = std::make_shared<SubTrie<T>>(k[i], temp, cur_key);
			(new_children)->hasValue = true;
			(new_children)->node_value.second = val;
			temp->children.insert({ k[i],new_children });
			count++;
			return { trie_iterator(new_children.get(),*this), true };
			
		}
		if (temp->children.find(k[i]) == temp->children.end())
		{
			std::string cur_key = k.substr(0, i + 1);
			auto new_children = std::make_shared<SubTrie<T>>(k[i], temp, cur_key);
			temp->children.insert({ k[i],(new_children) });
			temp = temp->children[k[i]].get();
			
		}
		else temp = temp->children.find(k[i])->second.get();
	}
	return {end(),false};
}
template <class T>
typename Trie<T>::trie_iterator Trie<T>::find(const key& k)
{
	size_t size = k.size();
	SubTrie<T>* temp= root;
	for (size_t i = 0; i < size; i++) {
		if (i == size - 1)
		{
			if (temp->children.find(k[i]) != temp->children.end())
			{
				temp = temp->children[k[i]].get();
				if(temp->hasValue == true) return trie_iterator(temp, *this);
				return end();
				
			}
			return end();
		}
		if (temp->children.find(k[i]) == temp->children.end())
		{
			return end();
		}
		temp = temp->children.find(k[i])->second.get();
	}
	return end();
}
template <class T>
typename Trie<T>::const_trie_iterator Trie<T>::cfind(const key& k) const
{
	
	size_t size = k.size();
	SubTrie<T>* temp = root;
	for (size_t i = 0; i < size; i++) {
		if (i == size - 1)
		{
			if (temp->children.find(k[i]) != temp->children.end())
			{
				temp = temp->children[k[i]].get();
				if (temp->hasValue == true) return const_trie_iterator(temp, *this);
				return cend();

			}
			return cend();
		}
		if (temp->children.find(k[i]) == temp->children.end())
		{
			return cend();
		}
		temp = temp->children.find(k[i])->second.get();
	}
	return cend();
}


template <class T>
void Trie<T>::erase(const key& k)
{
	auto victim = find(k);
	if (victim == end()) return;
	if (!victim.node->children.empty())
	{
		victim.node->hasValue = false;
		count--;
		return;
	}
	SubTrie<T>* temp = victim.node;
	SubTrie<T>* parent;
	while (temp->children.empty()) {
		parent = temp->parent;
		parent->children.erase(temp->character);
		if (parent == root) break;
		temp = parent;
	}
	count--;
}

template <class T>
SubTrie<T>* Trie<T>::find_last() const
{
	if (count == 0) return root;
	auto temp = root->children.rbegin()->second;

	while (!temp->children.empty())
	{
		temp = temp->children.rbegin()->second;
	}
	return temp.get();
}
template <class T>
SubTrie<T>* Trie<T>::find_first() const
{
	if (count == 0) return root;
	auto temp = root->children.begin()->second;
	while (!temp->hasValue)
	{
		temp = temp->children.begin()->second;
	}
	return temp.get();
}




