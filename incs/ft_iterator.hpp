/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 11:57:54 by mroux             #+#    #+#             */
/*   Updated: 2021/07/25 18:56:00 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTITERATOR_HPP
#define FTITERATOR_HPP
#include <iostream>
namespace ft
{
	//------------- TAGS -------------//
	struct input_iterator_tag
	{
	}; // Input Iterator
	struct output_iterator_tag
	{
	}; // Output Iterator
	struct forward_iterator_tag
	{
	}; // Forward Iterator
	struct bidirectional_iterator_tag
	{
	}; // Bidirectional Iterator
	struct random_access_iterator_tag
	{
	}; // Random-access Iterator

	//------------- TRAITS -------------//
	template <class Iter>
	class iterator_traits
	{
	public:
		typedef typename Iter::difference_type difference_type;
		typedef typename Iter::value_type value_type;
		typedef typename Iter::pointer pointer;
		typedef typename Iter::reference reference;
		typedef typename Iter::iterator_category iterator_category;
	};

	template <class T>
	class iterator_traits<T *>
	{
	public:
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template <class T>
	class iterator_traits<const T *>
	{
	public:
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T *pointer;
		typedef const T &reference;
		typedef random_access_iterator_tag iterator_category;
	};

	//template<class Iter> class iterator_traits<enable_if<is_integral<Iter>::value> >{};  // possibilité d'utiliser quelque chose comme ça ?
	template <>
	class iterator_traits<int>
	{
	}; //to resolve error: type 'int' cannot be used prior to '::' because it has no members => silencing all
	template <>
	class iterator_traits<char>
	{
	};
	template <>
	class iterator_traits<double>
	{
	};
	template <>
	class iterator_traits<std::string>
	{
	};
	template <>
	class iterator_traits<unsigned int>
	{
	};
	template <>
	class iterator_traits<long>
	{
	};
	template <>
	class iterator_traits<long long>
	{
	};
	template <>
	class iterator_traits<short int>
	{
	};
	template <>
	class iterator_traits<bool>
	{
	};
	template <>
	class iterator_traits<unsigned long>
	{
	};
	template <>
	class iterator_traits<unsigned long long>
	{
	};

	//------------- ITERATOR -------------//
	template <class Category, class T, class Distance = ptrdiff_t,
			  class Pointer = T *, class Reference = T &>
	struct iterator
	{
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};

	//------------- REVERSE ITERATOR -------------//
	template <class Iter>
	class ConstReverseIterator;

	template <class Iter, class ConstIter>
	class ReverseIterator
	{
	public:
		typedef Iter iterator_type;
		typedef ConstIter const_iterator_type;
		typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;
		typedef typename ft::iterator_traits<Iter>::value_type value_type;
		typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iter>::pointer pointer;
		typedef typename ft::iterator_traits<Iter>::reference reference;

		ReverseIterator() { _current = iterator_type(); };
		ReverseIterator(iterator_type it) { _current = it; };
		ReverseIterator(ReverseIterator<iterator_type, const_iterator_type> const &rev_it) { _current = rev_it._current; };

		operator ConstReverseIterator<const_iterator_type>() const { return ConstReverseIterator<const_iterator_type>(const_iterator_type(_current)); };

		ReverseIterator &operator=(ReverseIterator const &other)
		{
			_current = other._current;
			return (*this);
		};
		ReverseIterator &operator++()
		{
			_current--;
			return *this;
		};
		ReverseIterator operator++(int)
		{
			ReverseIterator retval = *this;
			++(*this);
			return retval;
		}
		ReverseIterator &operator--()
		{
			_current++;
			return *this;
		};
		ReverseIterator operator--(int)
		{
			ReverseIterator retval = *this;
			--(*this);
			return retval;
		}
		ReverseIterator operator+(int n) const
		{
			ReverseIterator rit = *this;
			rit._current -= n;
			return rit;
		};
		ReverseIterator operator-(int n) const
		{
			ReverseIterator rit = *this;
			rit._current += n;
			return rit;
		};
		ReverseIterator operator+=(int n)
		{
			_current -= n;
			return *this;
		}
		ReverseIterator operator-=(int n)
		{
			_current += n;
			return *this;
		}
		difference_type operator-(ReverseIterator other) { return -(_current - other._current); }

		template <class Iterator, class ConstIterator>
		friend bool operator==(const ReverseIterator<Iterator, ConstIterator> &lhs,
							   const ReverseIterator<Iterator, ConstIterator> &rhs);
		template <class Iterator, class ConstIterator>
		friend bool operator<(const ReverseIterator<Iterator, ConstIterator> &lhs,
							  const ReverseIterator<Iterator, ConstIterator> &rhs);
		template <class Iterator, class ConstIterator>
		friend bool operator==(const ConstReverseIterator<ConstIterator> &lhs,
							   const ReverseIterator<Iterator, ConstIterator> &rhs);

		typename iterator_type::value_type &operator[](difference_type n) { return *(_current - 1 - n); }
		typename iterator_type::value_type const &operator[](difference_type n) const { return *(_current - 1 - n); }
		typename iterator_type::value_type &operator*()
		{
			iterator_type tmp = _current;
			tmp--;
			return *tmp;
		};
		typename iterator_type::value_type const &operator*() const
		{
			iterator_type tmp = _current;
			tmp--;
			return *tmp;
		};
		typename iterator_type::value_type *operator->()
		{
			iterator_type tmp = _current;
			tmp--;
			return &(*tmp);
		};
		typename iterator_type::value_type const *operator->() const
		{
			iterator_type tmp = _current;
			tmp--;
			return &(*tmp);
		};

	private:
		iterator_type base() { return _current; };
		iterator_type _current;
	};

	template <class Iterator, class ConstIterator>
	bool operator==(const ReverseIterator<Iterator, ConstIterator> &lhs,
					const ReverseIterator<Iterator, ConstIterator> &rhs)
	{
		return (lhs._current == rhs._current);
	}

	template <class Iterator, class ConstIterator>
	bool operator!=(const ReverseIterator<Iterator, ConstIterator> &lhs,
					const ReverseIterator<Iterator, ConstIterator> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class Iterator, class ConstIterator>
	bool operator<(const ReverseIterator<Iterator, ConstIterator> &lhs,
				   const ReverseIterator<Iterator, ConstIterator> &rhs)
	{
		return (lhs._current > rhs._current);
	}

	template <class Iterator, class ConstIterator>
	bool operator<=(const ReverseIterator<Iterator, ConstIterator> &lhs,
					const ReverseIterator<Iterator, ConstIterator> &rhs)
	{
		return !(lhs > rhs);
	}

	template <class Iterator, class ConstIterator>
	bool operator>(const ReverseIterator<Iterator, ConstIterator> &lhs,
				   const ReverseIterator<Iterator, ConstIterator> &rhs)
	{
		return (rhs < lhs);
	}

	template <class Iterator, class ConstIterator>
	bool operator>=(const ReverseIterator<Iterator, ConstIterator> &lhs,
					const ReverseIterator<Iterator, ConstIterator> &rhs)
	{
		return !(lhs < rhs);
	}

	//------------- CONST REVERSE ITERATOR -------------//
	template <class Iter>
	class ConstReverseIterator
	{
	public:
		typedef Iter iterator_type;
		typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;
		typedef typename ft::iterator_traits<Iter>::value_type value_type;
		typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iter>::pointer pointer;
		typedef typename ft::iterator_traits<Iter>::reference reference;

		ConstReverseIterator() { _current = iterator_type(); };
		ConstReverseIterator(iterator_type it) { _current = it; };
		ConstReverseIterator(ConstReverseIterator<iterator_type> const &rev_it) { _current = rev_it._current; };

		ConstReverseIterator &operator=(ConstReverseIterator const &other)
		{
			_current = other._current;
			return (*this);
		};
		ConstReverseIterator &operator++()
		{
			_current--;
			return *this;
		};
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator retval = *this;
			++(*this);
			return retval;
		}
		ConstReverseIterator &operator--()
		{
			_current++;
			return *this;
		};
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator retval = *this;
			--(*this);
			return retval;
		}
		ConstReverseIterator operator+(int n) const
		{
			ConstReverseIterator rit = *this;
			rit._current -= n;
			return rit;
		};
		ConstReverseIterator operator-(int n) const
		{
			ConstReverseIterator rit = *this;
			rit._current += n;
			return rit;
		};
		difference_type operator-(ConstReverseIterator other) { return -(_current - other._current); }
		ConstReverseIterator operator+=(int n)
		{
			_current -= n;
			return *this;
		}
		ConstReverseIterator operator-=(int n)
		{
			_current += n;
			return *this;
		}

		template <class Iterator>
		friend bool operator==(const ConstReverseIterator<Iterator> &lhs,
							   const ConstReverseIterator<Iterator> &rhs);
		template <class Iterator>
		friend bool operator<(const ConstReverseIterator<Iterator> &lhs,
							  const ConstReverseIterator<Iterator> &rhs);
		template <class Iterator, class ConstIterator>
		friend bool operator==(const ConstReverseIterator<ConstIterator> &lhs,
							   const ReverseIterator<Iterator, ConstIterator> &rhs);

			typename iterator_type::value_type const &
			operator[](difference_type n) const
		{
			return *(_current - 1 - n);
		}
		typename iterator_type::value_type const &operator*() const
		{
			iterator_type tmp = _current;
			tmp--;
			return *tmp;
		};

		typename iterator_type::value_type const *operator->() const
		{
			iterator_type tmp = _current;
			tmp--;
			return &(*tmp);
		};

	private:
		iterator_type base() { return _current; };
		iterator_type _current;
	};

	// ============= const reverse iterator comparaison non member overloads ==========
	template <class Iterator>
	bool operator==(const ConstReverseIterator<Iterator> &lhs,
					const ConstReverseIterator<Iterator> &rhs)
	{
		return (lhs._current == rhs._current);
	}

	template <class Iterator>
	bool operator!=(const ConstReverseIterator<Iterator> &lhs,
					const ConstReverseIterator<Iterator> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class Iterator>
	bool operator<(const ConstReverseIterator<Iterator> &lhs,
				   const ConstReverseIterator<Iterator> &rhs)
	{
		return (lhs._current > rhs._current);
	}

	template <class Iterator>
	bool operator<=(const ConstReverseIterator<Iterator> &lhs,
					const ConstReverseIterator<Iterator> &rhs)
	{
		return !(lhs > rhs);
	}

	template <class Iterator>
	bool operator>(const ConstReverseIterator<Iterator> &lhs,
				   const ConstReverseIterator<Iterator> &rhs)
	{
		return (rhs < lhs);
	}

	template <class Iterator>
	bool operator>=(const ConstReverseIterator<Iterator> &lhs,
					const ConstReverseIterator<Iterator> &rhs)
	{
		return !(lhs < rhs);
	}


	// ================ reverse iterator / const reverse iterator comparaison non member overloads ==============
	template <class Iterator, class ConstIterator>
	bool operator ==(const ConstReverseIterator<ConstIterator> &lhs,
					const ReverseIterator<Iterator, ConstIterator> &rhs)
	{
		return lhs._current == rhs._current;
	}
	template <class Iterator, class ConstIterator>
	bool operator !=(const ConstReverseIterator<ConstIterator> &lhs,
					const ReverseIterator<Iterator, ConstIterator> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class Iterator, class ConstIterator>
	bool operator <(const ConstReverseIterator<ConstIterator> &lhs,
					const ReverseIterator<Iterator, ConstIterator> &rhs)
	{
		return (lhs._current > rhs._current);
	}
	template <class Iterator, class ConstIterator>
	bool operator >=(const ConstReverseIterator<ConstIterator> &lhs,
					const ReverseIterator<Iterator, ConstIterator> &rhs)
	{
		return !(lhs < rhs);
	}
	template <class Iterator, class ConstIterator>
	bool operator >(const ConstReverseIterator<ConstIterator> &lhs,
					const ReverseIterator<Iterator, ConstIterator> &rhs)
	{
		return (rhs < lhs);
	}
	template <class Iterator, class ConstIterator>
	bool operator <=(const ConstReverseIterator<ConstIterator> &lhs,
					const ReverseIterator<Iterator, ConstIterator> &rhs)
	{
		return !(lhs > rhs);
	}
}

#endif
