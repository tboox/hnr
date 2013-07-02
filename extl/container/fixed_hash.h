/* ///////////////////////////////////////////////////////////////////////
 * File:		fixed_hash.h		
 *
 * Created:		08.08.29			
 * Updated:		08.08.29
 *
 * Brief: fixed_hash class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_FIXED_HASH_H
#define EXTL_CONTAINER_FIXED_HASH_H

/*!\file fixed_hash.h
 * \brief fixed_hash class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../memory/buffer.h"
#include "../algorithm/algorithm.h"
#include "../string/string_base.h"
#include "basic_list.h"
#include "basic_pair.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_FIXED_HASH_DEFAULT_TABLE_SIZE	256

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::deatil namespace 
 */
EXTL_DETAIL_BEGIN_NAMESPACE

// hash_value_helper
template<typename_param_k _InIt>
EXTL_INLINE e_size_t hash_value_range(_InIt first, _InIt last)
{
	e_size_t v = 2166136261U;
	while (first != last)
		v = 16777619U * v ^ e_size_t(*first++);
	return (v);
}

EXTL_INLINE e_size_t hash_value_helper(e_char_t const* key)
{
	return hash_value_range(key, key + std_strlen(key) * sizeof(e_char_t));
}

EXTL_INLINE e_size_t hash_value_helper(e_wchar_t const* key)
{
	return hash_value_range(key, key + std_strlen(key) * sizeof(e_wchar_t));
}

EXTL_INLINE e_size_t hash_value_helper(e_size_t const& key)
{
	return (key ^ 0xdeadbeef);
}

template<	typename_param_k	S
		,	typename_param_k	Map 
		,	typename_param_k	B 
		>
EXTL_INLINE e_size_t hash_value_helper(string_base<S, Map, B> const& key)
{
	return hash_value_range(key.c_str(), key.c_str() + key.size());
}

// compare_helper
EXTL_INLINE e_int_t compare_helper(e_char_t const* lhs, e_char_t const* rhs)
{
	return std_strcmp(lhs, rhs);
}

EXTL_INLINE e_int_t compare_helper(e_wchar_t const* lhs, e_wchar_t const* rhs)
{
	return std_strcmp(lhs, rhs);
}

template<	typename_param_k	S
		,	typename_param_k	Map 
		,	typename_param_k	B 
		>
EXTL_INLINE e_int_t compare_helper(string_base<S, Map, B> const& lhs, string_base<S, Map, B> const& rhs)
{
	return lhs.compare(rhs);
}

EXTL_INLINE e_int_t compare_helper(e_size_t const& lhs, e_size_t const& rhs)
{
	return (lhs > rhs)? 1 : ((lhs < rhs)? -1 : 0);
}

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::deatil namespace 
 */
EXTL_DETAIL_END_NAMESPACE

template<	typename_param_k Key
		,	e_size_t TABLE_SIZE
		>
struct hash_key_traits
{
	typedef Key			key_type;
	typedef e_int_t		int_type;
	typedef e_size_t	size_type;

	static int_type compare(key_type const& lhs, key_type const& rhs)
	{
		return EXTL_NS_DETAIL(compare_helper)(lhs, rhs);
	}
	static size_type hash_value(key_type const& key)
	{
		return EXTL_NS_DETAIL(hash_value_helper)(key) % TABLE_SIZE;
	}
};
/*!brief fixed_hash class
 *
 * \param Key The key type
 * \param Map The mapped type
 * \param TABLE_SIZE The size of the hash table
 * \param Kt The key traits type
 * \param A The allocator type
 *
 * \ingroup extl_group_container
 *
 * <pre>
 * [empty]
 *
 * index:           0        1        3       ...     ...                n
 * hash_table: |--------|--------|--------|--------|--------|--------|--------|
 *                 |_____________________________________________________|
 *                       |
 *                     -----    
 * list:              | end | -> NULL
 *                     -----  
 *
 * [non-empty]
 *
 * index:           0        1        3       ...     ...                n
 * hash_table: |--------|--------|--------|--------|--------|--------|--------|
 *                 |_________|        |_______|        |_________________|
 *                      |                 |                   |
 *                    -----             -----               -----
 * list:             |     |    ==>    |     | ==> ... ... | end | -> NULL
 *                    -----             -----               -----
 *
 * [full]
 *
 * index:           0        1        3       ...     ...                n
 * hash_table: |--------|--------|--------|--------|--------|--------|--------|
 *                 |          |                                           |
 *                 |          |                                           |
 *               -----      -----       -----                           -----
 * list:        |     | => |     | ==> |     |          ... ...        | end | -> NULL
 *               -----      -----       -----                           -----
 * </pre>
 */
template<	typename_param_k Key
		,	typename_param_k Map
	#if defined(EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT) && \
			!defined(EXTL_COMPILER_IS_DMC) // DMC error: constant initializer expected
		,	e_size_t TABLE_SIZE = EXTL_FIXED_HASH_DEFAULT_TABLE_SIZE
		,	typename_param_k Kt = hash_key_traits<Key, TABLE_SIZE>
		,	typename_param_k A	= typename_type_def_k allocator_selector<Map>::allocator_type 
	#else
		,	e_size_t TABLE_SIZE
		,	typename_param_k Kt
		,	typename_param_k A
	#endif
		>
class fixed_hash
{
	/// \name Types
	/// @{
	public:
		typedef fixed_hash															class_type;
		typedef Key																	key_type;
		typedef Map																	mapped_type;
		typedef basic_pair<key_type, mapped_type>									value_type;
		typedef A																	allocator_type;
		typedef Kt																	key_traits_type;
		typedef basic_list	<	value_type
						#ifdef EXTL_MEMORY_ALLOCATOR_REBIND_SUPPORT
							,	typename_type_k A::template_qual_k rebind<value_type>::other_type
						#else
							,	typename_type_k allocator_selector<value_type>::allocator_type
						#endif
							,	typename_type_k memory_traits_selector<value_type>::memory_traits_type
							,	typename_type_k initialiser_selector<value_type>::initialiser_type
							>														list_type;
		typedef typename_type_k list_type::iterator									iterator;
		typedef typename_type_k list_type::const_iterator							const_iterator;
		typedef typename_type_k list_type::reverse_iterator							reverse_iterator;
		typedef typename_type_k list_type::const_reverse_iterator					const_reverse_iterator;
		typedef iterator															local_iterator;
		typedef const_iterator														const_local_iterator;
		typedef basic_pair<iterator, iterator>										iterator_pair;
		typedef basic_pair<const_iterator, const_iterator>							const_iterator_pair;
		
		typedef typename_type_k list_type::reference								reference;
		typedef typename_type_k list_type::const_reference							const_reference;
		typedef typename_type_k list_type::size_type								size_type;
		typedef typename_type_k list_type::bool_type								bool_type;
		typedef typename_type_k list_type::difference_type							difference_type;
		typedef typename_type_k buffer_selector<const_iterator>::buffer_type		table_type;
		typedef typename_type_k table_type::index_type								index_type;
	/// @}

	/// \name Members
	/// @{
	private:
		list_type																	m_list;
		table_type																	m_table;
	/// @}

	/// \name Enumerators
	/// @{
	private:
		enum { en_table_real_size = TABLE_SIZE + 1 };	// index_0 , index_1... , index_n, index_end
	/// @}

	/// \name Constructors
	/// @{
	public:
		fixed_hash()
			: m_list(), m_table(en_table_real_size)	
		{
			clear();
			EXTL_ASSERT(is_valid());
		}
		fixed_hash(class_type const& rhs)
			: m_list(rhs.m_list), m_table(rhs.m_table)
		{
			clear();
			EXTL_ASSERT(is_valid());
		}
	/// @}

	/// \name Iterators
	/// @{
	public:
		const_iterator			begin() const			{ return m_list.begin();	}
		iterator				begin()					{ return m_list.begin();	}
		const_iterator			end() const				{ return m_list.end();		}
		iterator				end()					{ return m_list.end();		}

		const_reverse_iterator	rbegin() const			{ return m_list.rbegin();	}
		reverse_iterator		rbegin()				{ return m_list.rbegin();	}
		const_reverse_iterator	rend() const			{ return m_list.rend();		}
		reverse_iterator		rend()					{ return m_list.rend();		}

		const_local_iterator	begin(index_type bucket_index) const;
		local_iterator			begin(index_type bucket_index);
		const_local_iterator	end(index_type bucket_index) const;
		local_iterator			end(index_type bucket_index);
	/// @}

	/// \name Attributes
	/// @{
	public:
		size_type			count(key_type const& key) const;
		size_type			bucket_size(index_type bucket_index) const;
		size_type			max_size() const			{ return m_list.max_size();			}
		size_type			table_size() const			{ return TABLE_SIZE;				}
		size_type			max_bucket_count() const	{ return table_size();				}
		size_type			bucket_count() const		{ return table_size();				}
		size_type			size() const				{ return m_list.size();				}
		bool_type			is_empty() const			{ return m_list.is_empty();			}
		bool_type			empty() const				{ return is_empty();				}
	/// @}

	/// \name Static Methods
	/// @{
	public:
		static size_type	hash_value(key_type const& key) { return key_traits_type::hash_value(key);	}
		static size_type	bucket(key_type const& key) 	{ return hash_value(key);					}
	/// @}

	/// \name Mutators
	/// @{
	public:
		void		clear()									{ m_list.clear(); init();			}
		void		swap(class_type& rhs);
		class_type&	operator=(class_type& rhs);
	/// @}

	/// \name Insert 
	/// @{
	public:
		iterator insert(value_type const& value);
		iterator insert(key_type const& key, mapped_type const& mapped_value);
	/// @}

	/// \name Erase 
	/// @{
	public:
		size_type	erase(key_type const& key);
		iterator	erase(const_iterator pos);
		iterator	erase(const_iterator first, const_iterator last);
	/// @}

	/// \name Find 
	/// @{
	public:
		const_iterator		find(key_type const& key) const;
		iterator			find(key_type const& key);

		const_iterator		lower_bound(key_type const& key) const;
		iterator			lower_bound(key_type const& key);

		const_iterator		upper_bound(key_type const& key) const;
		iterator			upper_bound(key_type const& key);

		const_iterator_pair	equal_range(key_type const& key) const;
		iterator_pair		equal_range(key_type const& key);
	/// @}

	/// \name Accessors
	/// @{
	public:
		mapped_type&		operator[](key_type const& key);
		mapped_type&		at(key_type const& key);
	/// @}

	/// \name Allocator
	/// @{
	public:
		allocator_type		allocator() const				{ return allocator_type();				}
	/// @}

	/// \name Others
	/// @{
	private:
		void				init()							{ m_table.assign(end(), table_size());	}
		static iterator		make_iter(const_iterator it)	{ return list_type::make_iter(it);		}
		bool_type			is_valid() const;
	/// @}
	
};
/* ///////////////////////////////////////////////////////////////////////
 * Macro
 */

/* Template declaration */
#ifdef EXTL_FIXED_HASH_TEMPLATE_DECL
#	undef EXTL_FIXED_HASH_TEMPLATE_DECL
#endif

#define EXTL_FIXED_HASH_TEMPLATE_DECL			\
template<	typename_param_k Key					\
		,	typename_param_k Map					\
		,	e_size_t TABLE_SIZE					\
		,	typename_param_k Kt					\
		,	typename_param_k A					\
		>

/* Class qualification */
#ifdef EXTL_FIXED_HASH_QUAL
#	undef EXTL_FIXED_HASH_QUAL
#endif

#define EXTL_FIXED_HASH_QUAL	fixed_hash<Key, Map, TABLE_SIZE, Kt, A>

/* Class qualification */
#ifdef EXTL_FIXED_HASH_RET_QUAL
#	undef EXTL_FIXED_HASH_RET_QUAL
#endif

#define EXTL_FIXED_HASH_RET_QUAL(ret_type)	\
					typename_type_ret_k EXTL_FIXED_HASH_QUAL::ret_type \
					EXTL_FIXED_HASH_QUAL
/* ///////////////////////////////////////////////////////////////////////
 * Implemention
 */
EXTL_FIXED_HASH_TEMPLATE_DECL
inline void EXTL_FIXED_HASH_QUAL::swap(class_type& rhs)
{
	EXTL_ASSERT(is_valid());
	if (this != &rhs)
	{
		m_list.swap(rhs.m_list); 
		m_table.swap(rhs.m_table);	
	}
	EXTL_ASSERT(is_valid());
}

EXTL_FIXED_HASH_TEMPLATE_DECL
inline EXTL_FIXED_HASH_RET_QUAL(class_type&)::operator=(class_type& rhs)
{
	class_type(rhs).swap(*this);
	return *this;
}

EXTL_FIXED_HASH_TEMPLATE_DECL
inline EXTL_FIXED_HASH_RET_QUAL(iterator)::lower_bound(key_type const& key) 
{
	return make_iter(static_cast<class_type const&>(*this).lower_bound(key));
}

EXTL_FIXED_HASH_TEMPLATE_DECL
inline EXTL_FIXED_HASH_RET_QUAL(const_iterator)::lower_bound(key_type const& key) const
{
	size_type hash_index = hash_value(key);
	EXTL_ASSERT(hash_index < table_size());

	for (const_iterator p = m_table[hash_index]; p != m_table[hash_index + 1]; ++p)
	{
		if (!key_traits_type::compare(key, (*p).first()))
			return p;
	}
	return end();
}

EXTL_FIXED_HASH_TEMPLATE_DECL
inline EXTL_FIXED_HASH_RET_QUAL(iterator)::upper_bound(key_type const& key)
{
	return make_iter(static_cast<class_type const&>(*this).upper_bound(key));
}

EXTL_FIXED_HASH_TEMPLATE_DECL
inline EXTL_FIXED_HASH_RET_QUAL(const_iterator)::upper_bound(key_type const& key) const
{
	size_type hash_index = hash_value(key);
	EXTL_ASSERT(hash_index < table_size());

	for (const_iterator p = m_table[hash_index + 1]; p != m_table[hash_index];)
	{
		if (!key_traits_type::compare(key, (*--p).first()))
			return ++p;
	}
	return end();
}

EXTL_FIXED_HASH_TEMPLATE_DECL
inline EXTL_FIXED_HASH_RET_QUAL(const_iterator_pair)::equal_range(key_type const& key) const
{
	return const_iterator_pair(lower_bound(key), upper_bound(key));
}

EXTL_FIXED_HASH_TEMPLATE_DECL
inline EXTL_FIXED_HASH_RET_QUAL(iterator_pair)::equal_range(key_type const& key)
{
	return iterator_pair(lower_bound(key), upper_bound(key));
}

EXTL_FIXED_HASH_TEMPLATE_DECL
inline EXTL_FIXED_HASH_RET_QUAL(const_iterator)::find(key_type const& key) const
{
	return lower_bound(key);
}

EXTL_FIXED_HASH_TEMPLATE_DECL
inline EXTL_FIXED_HASH_RET_QUAL(iterator)::find(key_type const& key)
{
	return lower_bound(key);
}

EXTL_FIXED_HASH_TEMPLATE_DECL
inline EXTL_FIXED_HASH_RET_QUAL(size_type)::count(key_type const& key) const
{
	const_iterator_pair p = equal_range(key);
	return std_distance(p.first(), p.second());
}

EXTL_FIXED_HASH_TEMPLATE_DECL
inline EXTL_FIXED_HASH_RET_QUAL(size_type)::bucket_size(index_type bucket_index) const
{
	return std_distance(begin(bucket_index), end(bucket_index));
}

EXTL_FIXED_HASH_TEMPLATE_DECL
inline EXTL_FIXED_HASH_RET_QUAL(mapped_type&)::at(key_type const& key)
{
	iterator p = find(key);

	if (p == end()) 
		p = insert(key, mapped_type());

	return (*p).second();
}

EXTL_FIXED_HASH_TEMPLATE_DECL
inline EXTL_FIXED_HASH_RET_QUAL(mapped_type&)::operator[](key_type const& key)
{
	return at(key);
}

EXTL_FIXED_HASH_TEMPLATE_DECL
inline EXTL_FIXED_HASH_RET_QUAL(bool_type)::is_valid() const
{
	if (m_table.size() != table_size()) return e_false_v;
	if (0 == m_list.size())
	{
		for (size_type i = 0; i < m_table.size(); ++i)
		{
			if (m_table[i] != m_list.end()) return e_false_v;
		}
	}

	return e_true_v;
}

EXTL_FIXED_HASH_TEMPLATE_DECL
inline EXTL_FIXED_HASH_RET_QUAL(iterator)::insert(value_type const& value)
{
	EXTL_ASSERT(is_valid());

	size_type hash_index = hash_value(value.first());
	EXTL_ASSERT(hash_index < table_size());

	const_iterator pos = m_table[hash_index];
	const_iterator new_pos = m_list.insert(pos, value);

	// update iterators in hash table 
	do
	{
		if (m_table[hash_index] == pos) m_table[hash_index] = new_pos;

	} while (--hash_index);

	EXTL_ASSERT(is_valid());
	return make_iter(new_pos);
}

EXTL_FIXED_HASH_TEMPLATE_DECL
inline EXTL_FIXED_HASH_RET_QUAL(iterator)::insert(key_type const& key, mapped_type const& mapped_value)
{
	return insert(value_type(key, mapped_value));
}

EXTL_FIXED_HASH_TEMPLATE_DECL
inline EXTL_FIXED_HASH_RET_QUAL(iterator)::erase(const_iterator pos)
{
	EXTL_ASSERT(is_valid());

	size_type hash_index = hash_value((*pos).first());
	EXTL_ASSERT(hash_index < table_size());

	EXTL_ASSERT(pos != end());

	// update iterators in hash table 
	do
	{
		if (m_table[hash_index] == pos) ++m_table[hash_index];

	} while (--hash_index);

	return m_list.erase(pos);
}

EXTL_FIXED_HASH_TEMPLATE_DECL
inline EXTL_FIXED_HASH_RET_QUAL(iterator)::erase(const_iterator first, const_iterator last)
{
	EXTL_ASSERT(is_valid());

	if (first == begin() && last == end())
	{
		clear();
		EXTL_ASSERT(is_valid());
		return begin();
	}
	else
	{
		while (first != last) erase(first++);

		EXTL_ASSERT(is_valid());
		return make_iter(first);
	}
}

EXTL_FIXED_HASH_TEMPLATE_DECL
inline EXTL_FIXED_HASH_RET_QUAL(size_type)::erase(key_type const& key)
{
	EXTL_ASSERT(is_valid());

	iterator_pair p = equal_range(key);
	size_type num = std_distance(p.first(), p.second());
	erase(p.first(), p.second());

	EXTL_ASSERT(is_valid());
	return num;
}
EXTL_FIXED_HASH_TEMPLATE_DECL
inline EXTL_FIXED_HASH_RET_QUAL(const_local_iterator)::begin(index_type bucket_index) const
{
	if (bucket_index < table_size()) 
		return m_table[bucket_index];
	else return end();

}
EXTL_FIXED_HASH_TEMPLATE_DECL
inline EXTL_FIXED_HASH_RET_QUAL(local_iterator)::begin(index_type bucket_index)
{
	return make_iter(static_cast<class_type const&>(*this).begin(bucket_index));
}
EXTL_FIXED_HASH_TEMPLATE_DECL
inline EXTL_FIXED_HASH_RET_QUAL(const_local_iterator)::end(index_type bucket_index) const
{
	if (bucket_index < table_size()) 
		return m_table[bucket_index + 1];
	else return end();
}
EXTL_FIXED_HASH_TEMPLATE_DECL
inline EXTL_FIXED_HASH_RET_QUAL(local_iterator)::end(index_type bucket_index)
{
	return make_iter(static_cast<class_type const&>(*this).end(bucket_index));
}
/* /////////////////////////////////////////////////////////////////////////
 * swapping
 */

#if defined(EXTL_FUNCTION_TEMPLATE_NON_TYPE_PARAM_SUPPORT)

EXTL_FIXED_HASH_TEMPLATE_DECL
EXTL_INLINE void swap(EXTL_FIXED_HASH_QUAL& lhs, EXTL_FIXED_HASH_QUAL& rhs)
{
	lhs.swap(rhs);
}

EXTL_FIXED_HASH_TEMPLATE_DECL
EXTL_INLINE typename_type_ret_k EXTL_FIXED_HASH_QUAL::
size_type get_size(EXTL_FIXED_HASH_QUAL const& h)
{
	return h.size();
}

#endif

/* //////////////////////////////////////////////////////////////////// */
#undef EXTL_FIXED_HASH_TEMPLATE_DECL
#undef EXTL_FIXED_HASH_QUAL
#undef EXTL_FIXED_HASH_RET_QUAL

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * std::swap 
 */
#if !defined(EXTL_NO_STL) && \
		!defined(EXTL_NO_NAMESPACE) && \
			defined(EXTL_FUNCTION_TEMPLATE_NON_TYPE_PARAM_SUPPORT)

/* ::std namespace */
EXTL_STD_BEGIN_NAMESPACE

template<	typename_param_k Key					
		,	typename_param_k Map					
		,	EXTL_NS(e_size_t) TABLE_SIZE					
		,	typename_param_k Kt					
		,	typename_param_k A					
		>
EXTL_INLINE void swap(EXTL_NS(fixed_hash)<Key, Map, TABLE_SIZE, Kt, A>& lhs, 
						EXTL_NS(fixed_hash)<Key, Map, TABLE_SIZE, Kt, A>& rhs)
{
	lhs.swap(rhs);
}
/* ::std namespace */
EXTL_STD_END_NAMESPACE
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_FIXED_HASH_H */
/* //////////////////////////////////////////////////////////////////// */
