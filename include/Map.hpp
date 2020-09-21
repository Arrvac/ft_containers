#ifndef MAP_HPP
# define MAP_HPP
# include <memory>
# include <functional>
# include <limits>
# include "MapIterator.hpp"

namespace ft
{
	template <class Key, class T, class Compare=std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T> > >
	class Map
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef std::pair<const key_type, mapped_type> value_type;
			typedef Compare key_compare;
			typedef Alloc allocator_type;
			typedef T& reference;
			typedef const T& const_reference;
			typedef T* pointer;
			typedef const T* const_pointer;
			typedef unsigned long size_type;
			typedef BNode<key_type, mapped_type>* node;
			typedef MapIterator<key_type, mapped_type> iterator;
			class value_compare
			{
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {};
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					};
			};
		private:
			allocator_type _allocator;
			key_compare _comp;
			node _root;
			node _end;
			size_type _length;
			node _new_node(key_type key, mapped_type value, node parent)
			{
				node el = new BNode<key_type, mapped_type>();
				el->pair = std::make_pair(key, value);
				el->right = 0;
				el->left = 0;
				el->parent = parent;
				return (el);
			};
			void _init_tree(void)
			{
				_root = _new_node(key_type(), mapped_type(), 0);
				_end = _new_node(key_type(), mapped_type(), 0);
				_end->left = _root;
				_length = 0;
			};
			void _free_tree(node n)
			{
				if (n->right)
					_free_tree(n->right);
				if (n->left)
					_free_tree(n->left);
				delete n;
			};
			node _insert_node(node n, key_type key, mapped_type value)
			{
				if (key < n->pair.first)
				{
					if (!n->left)
					{
						n->left = _new_node(key, value, n);
						return (n->left);
					}
					else
						return (_insert_node(n->left, key, value));
				}
				else
				{
					if (!n->right)
					{
						n->right = _new_node(key, value, n);
						return (n->right);
					}
					else
						return(_insert_node(n->right, key, value));
				}
			};
			node _find(node n, key_type key)
			{
				node tmp;
				if (n->pair.first == key)
					return (n);
				if (n->right)
				{
					if ((tmp = _find(n->right, key)))
						return (tmp);
				}
				if (n->left)
				{
					if ((tmp = _find(n->left, key)))
						return (tmp);
				}
				return (0);
			};
		public:
			explicit Map(const key_compare &comp = key_compare(), const allocator_type alloc = allocator_type())
			: _allocator(alloc), _comp(comp)
			{
				_init_tree();
			};
			template <class InputIterator>
			Map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type alloc = allocator_type())
			: _allocator(alloc), _comp(comp)
			{
				_init_tree();
				insert(first, last);
			};
			Map(const Map<Key, T> &other)
			{
				_init_tree();
				*this = other;
			};
			~Map(void)
			{
				_free_tree(_root);	
			};
			Map &operator=(const Map<Key, T> &other)
			{
				(void)other;
				clear();
				insert(other.begin(), other.end());
				return (*this);
			};
			iterator begin(void)
			{
				node n = _root;
				if (!n->left && !n->right)
					return (end());
				if (!n->left && n->right)
					n = n->right;
				while (n->left)
					n = n->left;
				return (iterator(n));
			};
			iterator begin(void) const
			{
				node n = _root;
				if (!n->left && !n->right)
					return (end());
				if (!n->left && n->right)
					n = n->right;
				while (n->left)
					n = n->left;
				return (iterator(n));
			};
			iterator end(void)
			{
				return (iterator(_end));
			};
			iterator end(void) const
			{
				return (iterator(_end));
			};
			// reverse_iterator rbegin(void)
			// {};
			// const_reverse_iterator rbegin(void) const
			// {};
			// reverse_iterator rend(void)
			// {};
			// const_reverse_iterator rend(void) const
			// {};
			bool empty(void) const
			{
				return (_length == 0);
			};
			size_type size(void) const
			{
				return (_length);
			};
			size_type max_size(void) const
			{
				return (std::numeric_limits<size_type>::max() / sizeof(node));
			};
			mapped_type &operator[](const key_type& k)
			{
				iterator tmp = find(k);
				if (tmp != end())
					return tmp->second;
				++_length;
				return (insert(std::make_pair(k, mapped_type())).first->second);
			};
			std::pair<iterator, bool> insert(const value_type &value)
			{
				iterator tmp;
				if ((tmp = find(value.first)) != end())
				{
					tmp->second = value.second;
					return (std::make_pair(tmp, false));
				}
				++_length;
				return (make_pair(iterator(_insert_node(_root, value.first, value.second)), true));
			};
			iterator insert(iterator position, const value_type &value)
			{
				iterator tmp;
				if ((tmp = find(value.first)) != end())
				{
					tmp->second = value.second;
					return (std::make_pair(tmp, false));
				}
				++_length;
				return (make_pair(iterator(_insert_node(position.node(), value.first, value.second)), true));
			};
			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					insert(*first);
					first++;
				}
			};
			// void erase(iterator position)
			// {};
			// size_type erase(const key_type &value)
			// {};
			// void erase(iterator first, iterator last)
			// {};
			void swap(Map &x)
			{
				ft::swap(_length, x._length);
				ft::swap(_root, x._root);
			};
			void clear(void)
			{
				if (_root->right)
					_free_tree(_root->right);
				if (_root->left)
					_free_tree(_root->left);
				_root->right = 0;
				_root->left = 0;
				_length = 0;
			};
			key_compare key_comp(void) const
			{
				return (_comp);
			};
			value_compare value_comp(void) const
			{
				return (this->value_compare);
			};
			iterator find(const key_type &value)
			{
				node tmp = _find(_root, value);
				if (tmp)
					return (iterator(tmp));
				return (end());
			};
			// const_iterator find(const key_type &value) const
			// {};
			size_type count(const key_type &value) const
			{
				size_t c = 0;
				iterator it = begin();

				while (it != end())
				{
					if (it->first == value)
						++c;
					++it;
				}
				return (c);
			};
			// iterator lower_bound(const key_type &value)
			// {};
			// const_iterator lower_bound(const key_type &k) const
			// {};
			// iterator upper_bound(const key_type &k)
			// {};
			// const_iterator upper_bound(const key_type &k) const
			// {};
			// std::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
			// {};
			// std::pair<const_iterator, const_iterator> equal_range(const key_type &k)
			// {};
	};
};

#endif