#pragma once
#include <functional>
#include <iterator>
#include <deque>
#include <type_traits>
#include <ctime>
#include <cstdlib>
#define MAX_LEVEL 16

template<typename T>
 class sl_node {
public:
	sl_node()=default;
	sl_node(T _node_value, int max_level):node_value(_node_value),contain_value(true){
		
		make_levels(max_level);

	};
	sl_node(int level, sl_node* _default_ptr) {
		ptrs.resize(level);
		for (int i = 0; i < level; i++)
		{
			ptrs[i] = _default_ptr;
		}
		contain_value = false;
	};
	sl_node(const sl_node& another) :contain_value(another.contain_value), node_value(another.node_value)
	{
		ptrs.resize(another.ptrs.size());
	};
	~sl_node(){ ptrs.clear(); };
	bool operator==(const sl_node& node) const
	{
		if (node_value==node.node_value && ptrs.size() == node.ptrs.size()) return true;
		return false;
	};
	bool operator!=(const sl_node& node) const
	{
		return !(*this == node);
	}
	
	void make_levels(int max_level) {
		ptrs.push_front(nullptr);
		while (rand() % 2 + 1 != 2 && (int)ptrs.size() < max_level) {
			ptrs.push_front(nullptr);
		}
	};
	bool contain_value{false};
	T node_value{};
	std::deque<sl_node<T>*> ptrs;
};


template <typename Key,
	typename Value,
	typename Compare = std::less<Key>,
	typename Alloc = std::allocator<std::pair<const Key, Value> > >
	class skip_list {

	typedef std::pair<const Key, Value> node_value;
	Compare cmp;																	
	Alloc _alloc;
	size_t count;

	sl_node<node_value> nil{};	   
	sl_node<node_value> start{};
public:
 		template<bool is_const>   
		class __sklist_iterator final {
			typename std::conditional <is_const, const sl_node<node_value>*, sl_node<node_value>* > ::type node = nullptr;
		public:
			friend class skip_list;
			using iterator_category = std::forward_iterator_tag;
			using value_type = node_value;
			using pointer = node_value*;
			using reference = node_value&;
			using const_reference = const node_value&;
			__sklist_iterator() = default;
			__sklist_iterator(typename std::conditional<is_const, const sl_node<node_value>&, sl_node<node_value>&>::type _node) { node = &_node; };
			__sklist_iterator(typename std::conditional<is_const, const __sklist_iterator&&, __sklist_iterator&&>::type other)
			{
				std::swap(node, other.node);
			}
			__sklist_iterator &operator=( __sklist_iterator&& another)
			{
				std::swap(node, another.node);	   //std::swap
				return *this;
			}
			__sklist_iterator &operator=(__sklist_iterator& another)
			{
				node = std::move(another.node);
				return *this;
			}
			__sklist_iterator<is_const>& operator ++()				//++it 
			{																						 
				
				node = node->ptrs[0];
				return (*this);
			};
 			__sklist_iterator<is_const> operator++(int)
 			{
				sklist_iterator tmp = *this;
				node = node->ptrs[0];
				return tmp;
 			}
 
			bool operator ==(const __sklist_iterator<is_const>& it) const { return node == (it.node); };
			bool operator !=(const __sklist_iterator<is_const>& it) const { return !(node == (it.node)); };

			typename std::conditional <is_const, const_reference, reference >::type operator*() { return node->node_value; }
		};
	using sklist_iterator =__sklist_iterator<false>;
	using const_sklist_iterator =const __sklist_iterator<true>;

	//constructors & distructors
	skip_list();
	explicit skip_list(const Compare &comp, const Alloc &a = Alloc());
	skip_list(const skip_list &another);
	skip_list(skip_list&& another)
	{
		std::swap(start, another.start);
		std::swap(nil, another.nil);
		count = another.count;
		std::swap(cmp, another.cmp);
		std::swap(_alloc, another._alloc);
		another.count = 0;
	}
	~skip_list() { clear(); };
	
	//operators
	skip_list &operator=(const skip_list &another);
	
   //iterator methods
	auto begin(){ return sklist_iterator(*start.ptrs[0]); };
	auto end() { return sklist_iterator(nil); };
	const_sklist_iterator cbegin() const { return const_sklist_iterator(*start.ptrs[0]);};
	const_sklist_iterator cend() const { return const_sklist_iterator(nil); };
	
	//size_methods
	bool empty() const { return count == 0; };
	size_t size() const { return count; };
	
	//read methods
	sklist_iterator find(const Key &key);
	const_sklist_iterator cfind(const Key &key) const
	{
		int level = MAX_LEVEL;
		for (auto it = const_sklist_iterator(start); it != cend();) {
			if (level == 0) break;
			if (it.node->ptrs[level - 1]->contain_value == false) level--;
			else {
				if (it.node->ptrs[level - 1]->node_value.first == key) return const_sklist_iterator(*it.node->ptrs[level - 1]);
				if (cmp(key, it.node->ptrs[level - 1]->node_value.first) == false)
				{
					it.node = it.node->ptrs[level - 1];
					
				}
				else level--;
			}
		}
		return cend();
	};
    Value &operator[](const Key &key);
	const Value &operator[](const Key &key) const;
	Value &at(const Key &key);
	const Value &at(const Key &key) const;
	
	//insert
	std::pair<sklist_iterator, bool> insert(const node_value& v);

	//erase
	void erase(const Key &key);
	void erase(sklist_iterator& position);
	void erase(sklist_iterator& first, sklist_iterator& last);
	void clear();
	void swap(skip_list &another);
};
  template <typename Key, typename Value, typename Compare, typename Alloc>
  skip_list<Key, Value, Compare, Alloc>::skip_list(const skip_list& another) :nil(MAX_LEVEL, nullptr), start(MAX_LEVEL, &nil), cmp(another.cmp), _alloc(another._alloc), count(another.count)
  {
	  if (another.count > 0) {
		  sl_node<node_value>* anothers_node = another.start.ptrs[0];
		  sl_node<node_value>* tmp = &start;
		  for (size_t j = 0; j < another.count; j++) {
			  sl_node<node_value>* copied_node = new sl_node<node_value>(*anothers_node);
			  copied_node->ptrs[0] = &nil;
			  tmp->ptrs[0] = copied_node;
			  anothers_node = anothers_node->ptrs[0];
			  tmp = tmp->ptrs[0];
		  }
		  sl_node<node_value>* next;
		  for (size_t j = 1; j < MAX_LEVEL; j++)
		  {
			  tmp = &start;

			  while (tmp != &nil) {
				  next = tmp->ptrs[0];
				  if (next->ptrs.size() >= j + 1)
				  {
					  tmp->ptrs[j] = next;
				  }
				  else {
					  while (next->ptrs.size() < j + 1 && next != &nil) next = next->ptrs[0];
					  tmp->ptrs[j] = next;
				  }
				  tmp = tmp->ptrs[j];
			  }
		  }
	  }
  }

 template <typename Key, typename Value, typename Compare, typename Alloc>
 void skip_list<Key, Value, Compare, Alloc>::clear()
 {
	 if (count != 0 && start.ptrs[0]!=nullptr) {
		 sl_node<node_value>*  tmp = start.ptrs[0];
		 sl_node<node_value>* next;
		 for (size_t i = 0; i < count; i++)
		 {
			 next = tmp->ptrs[0];
			 if (next == nullptr) break;
			 //tmp->ptrs.clear();
			 delete tmp;
			 tmp = next;

		 }
	 }
	 count = 0;
  	for(int i = 0; i<MAX_LEVEL;i++)
  	{
		start.ptrs[i] = &nil;
  	}
 }

template <typename K, typename V, typename C, typename A>
bool operator==(const skip_list<K, V, C, A> &x, const skip_list<K, V, C, A> &y) {
	if (x.empty() && y.empty()) return true;
	if (x.size() != y.size()) return false;
	auto it_y = y.cbegin();
	for (auto it_x = x.cbegin(); it_x != x.cend();)
	{
		if (it_y == y.cend()) return false;
		if (it_x.operator*()!=it_y.operator*()) return false;
		++it_y;
		++it_x;
	}
	return true;
}

template <typename K, typename V, typename C, typename A>
bool operator!=(const skip_list<K, V, C, A> &x, const skip_list<K, V, C, A> &y) { return  !(x == y); }

template <typename Key, typename Value, typename Compare, typename Alloc>
void skip_list<Key, Value, Compare, Alloc>::erase(sklist_iterator& first, sklist_iterator& last)
{
	sklist_iterator tmp(*first.node);
	sklist_iterator next;
  	while(tmp!=last)
  	{
		next.node = tmp.node->ptrs[0];
		erase(tmp);
		tmp = next;
  	}
	erase(last);
}

template <typename Key, typename Value, typename Compare, typename Alloc>
void skip_list<Key, Value, Compare, Alloc>::erase(sklist_iterator& position)
{
	erase(position.node->node_value.first);
}


template <typename Key, typename Value, typename Compare, typename Alloc>
typename skip_list<Key, Value, Compare, Alloc>::sklist_iterator skip_list<Key, Value, Compare, Alloc>::find(const Key& key)
{
	int level = MAX_LEVEL;
	for (auto it = sklist_iterator(start); it != end();) {
		if (level == 0) break;
		if (it.node->ptrs[level - 1]->contain_value==false) level--;
		else {
			if (it.node->ptrs[level - 1]->node_value.first == key) return sklist_iterator(*it.node->ptrs[level-1]);
			if (cmp(key,it.node->ptrs[level - 1]->node_value.first)==false)
			{
				it = sklist_iterator(*it.node->ptrs[level - 1]);
			}
			else level--;
		}
	}
	return end();
}



 template <typename Key, typename Value, typename Compare, typename Alloc>
 void skip_list<Key, Value, Compare, Alloc>::erase(const Key& key)
 {
	 sklist_iterator iter_on_victim = find(key);
	 if (iter_on_victim != end())
	 {
		 std::deque<sl_node<node_value>**> last_ptrs;
		 int level = MAX_LEVEL;
		 for (auto it = sklist_iterator(start); it != end();) {
			 if (level == 0) break;
			 if (it.node->ptrs[level - 1]->contain_value==false) {
				 last_ptrs.push_front(&it.node->ptrs[level - 1]);
				 level--;
			 }
			 else {
				 if (it.node->ptrs[level - 1]->node_value.first == key) {
					 last_ptrs.push_front(&it.node->ptrs[level - 1]);
					 while (last_ptrs.size() != MAX_LEVEL) {
						 level--;
						 while (it.node->ptrs[level - 1]->node_value.first != key) ++it/*it = it.operator++()*/;
						 last_ptrs.push_front(&it.node->ptrs[level - 1]); 
					 }
				 	sklist_iterator victim(*it.node->ptrs[level - 1]);
					for (size_t i = 0; i < victim.node->ptrs.size(); i++) *last_ptrs[i] = victim.node->ptrs[i];
					count--;
					delete (victim.node);
					 return;
				 }
				 if (cmp(key, it.node->ptrs[level - 1]->node_value.first) == false)
				 {
					 it = sklist_iterator(*it.node->ptrs[level - 1]);
				 }
				 else {
					 last_ptrs.push_front(&it.node->ptrs[level - 1]);
					 level--; 
				 }
			 }
		 }
	 }
 }

template <typename Key, typename Value, typename Compare, typename Alloc>
std::pair<typename skip_list<Key, Value, Compare, Alloc>::sklist_iterator, bool> skip_list<Key, Value, Compare, Alloc>::insert(const node_value& v)
{
	auto found = find(v.first);
	if (found != end()) return { sklist_iterator(*found.node), false };
	if (count == 0)
	{
		sl_node<node_value>* new_node = new sl_node<node_value>(v, MAX_LEVEL);
		for (int i = 0; i < (int)new_node->ptrs.size(); i++)
		{
			new_node->ptrs[i] = start.ptrs[i];
			start.ptrs[i] = new_node;
		}
		count++;
		return std::make_pair(sklist_iterator(*new_node), true);
	}
	int level = MAX_LEVEL;
	std::deque<sl_node<node_value>**> last_ptrs;
	for (auto it = sklist_iterator(start); it != end();) {
		if (it.node->ptrs[level - 1]->contain_value==false && level!=1) {
			last_ptrs.push_front(&it.node->ptrs[level - 1]);
			level--;
		}
		else {
			if (level==1)														
				{
				if (it.node->ptrs[0]->contain_value == true) {
					while (cmp(v.first, it.node->ptrs[0]->node_value.first) == false)
					{
						/*it = it.operator++();*/
						++it;
						if (it.node->ptrs[0]->contain_value == false) break;
					}
				}
					sl_node<node_value>* new_node = new sl_node<node_value>(v, MAX_LEVEL);
					for (size_t i = 0; i < new_node->ptrs.size(); i++)
					{
						if (i < it.node->ptrs.size()) {								 
							new_node->ptrs[i] = it.node->ptrs[i];
							it.node->ptrs[i] = new_node;
						}
						else {
							new_node->ptrs[i] = *last_ptrs[i-1];
							*last_ptrs[i-1] = new_node;
						}
					}
				
					count++;
					return std::make_pair(sklist_iterator(*new_node), true);
				}
			if (cmp(v.first, it.node->ptrs[level - 1]->node_value.first)==true) {
				last_ptrs.push_front(&it.node->ptrs[level - 1]);
				level--;
																																																								
			}
			//else it=it.operator++();
			else it = sklist_iterator(*it.node->ptrs[level-1]);
			}
		}
	return std::make_pair(end(), false);
}

 template <typename Key, typename Value, typename Compare, typename Alloc>
 Value& skip_list<Key, Value, Compare, Alloc>::operator[](const Key& key)
 {
	 sklist_iterator iter = find(key);
	if (iter==end())
	{
		std::pair<sklist_iterator, bool> inserted= insert(node_value(key, Value()));
		if (inserted.second == true) return inserted.first.node->node_value.second;
	}
	 return iter.node->node_value.second;
 }
template <typename Key, typename Value, typename Compare, typename Alloc>
const Value& skip_list<Key, Value, Compare, Alloc>::operator[](const Key& key) const
{
	auto iter = cfind(key);
	if (iter == cend()) throw key;
	return iter.node->node_value.second;
}

 template <typename Key, typename Value, typename Compare, typename Alloc>
 Value& skip_list<Key, Value, Compare, Alloc>::at(const Key& key)
 {
	sklist_iterator iter = find(key);
	if (iter == end()) throw key;
	return iter.operator*().second;
 }
  template <typename Key, typename Value, typename Compare, typename Alloc>
  const Value& skip_list<Key, Value, Compare, Alloc>::at(const Key& key) const
  {
	  auto iter = this->cfind(key);
	  if (iter == this->cend()) throw key;
	  return (*iter).second;
  	
  }

template <typename Key, typename Value,																					 //operator =
	typename Compare,
	typename Alloc>
	skip_list<Key,Value,Compare,Alloc> &skip_list<Key, Value, Compare, Alloc>::operator=(const skip_list &another){
	this->clear(); 
	start.ptrs = another.start.ptrs;
	count = another.count;
	cmp = another.cmp;
	_alloc = another._alloc;
	return *this;
}
template <typename Key, typename Value, typename Compare, typename Alloc>
void skip_list<Key, Value, Compare, Alloc>::swap(skip_list& another)
{
	int another_count = another.count;
	std::deque<sl_node<node_value>*> another_ptrs(another.start.ptrs);
	another.start.ptrs = start.ptrs;
	another.count = count;
	start.ptrs = another_ptrs;				 
	count = another_count;
}


template <typename Key, typename Value,					//default constructor of skip list
	typename Compare,
	typename Alloc>
	skip_list<Key, Value, Compare, Alloc>::skip_list():nil(MAX_LEVEL,nullptr),start(MAX_LEVEL,&nil) {
	srand(time(nullptr));
	count = 0;
}
template <typename Key, typename Value,
	typename Compare,																			//explicit construcor of skip_list
	typename Alloc>
	skip_list<Key, Value, Compare, Alloc>::skip_list(const Compare &comp, const Alloc &a) {
	cmp = comp;
	_alloc = a;
	skip_list<Key,Value,Compare,Alloc>::skip_list();
}

