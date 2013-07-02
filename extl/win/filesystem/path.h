/* ///////////////////////////////////////////////////////////////////////
 * File:		path.h		
 *
 * Created:		08.06.24				
 * Updated:		08.06.24	
 *
 * Brief:		path class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_PLATFORM_WIN_PATH_H
#define EXTL_PLATFORM_WIN_PATH_H

/*!\file path.h
 * \brief path class
 */

#ifndef __cplusplus
#	error path.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "filesystem_traits.h"
#include "path_entry_iterator.h"
#include "../../memory/allocator_selector.h"
#include "../../string/string.h"
#include "../../utility/operators.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_BEGIN_WHOLE_NAMESPACE

/*!\brief basic_path class
 * 
 * \param C The character type
 * \param S The string type
 * \param T The filesystem_traits
 *
 * \ingroup extl_group_filesystem
 */
template<	typename_param_k C
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	typename_param_k S = typename_type_def_k filesystem_traits<C>::stack_path_string_type 
		,	typename_param_k T = filesystem_traits<C>
		
#else
		,	typename_param_k S
		,	typename_param_k T 
#endif
		>
class basic_path
#ifndef EXTL_COMPILER_IS_DMC 
// operators: != == 
	: private	operators_equal_1_2_<basic_path<C, S, T>, typename_type_k S::const_pointer
			 ,	operators_div_1_2_<basic_path<C, S, T>, typename_type_k S::const_pointer
			#ifndef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
			 ,	operators_base_< basic_path<C, S, T> >
			#endif
			> > 
#endif
{
	/// \name Types
	/// @{
	public:
		typedef C																		char_type;
		typedef S																		string_type;
		typedef T																		filesystem_traits_type;
		typedef basic_path<C, S, T>														class_type;
		typedef char_type																value_type;
		typedef value_type*																pointer;
		typedef value_type const*														const_pointer;
		typedef value_type&																reference;
		typedef value_type const&														const_reference;
		typedef typename_type_k string_type::string_traits_type							string_traits_type;
		typedef typename_type_k filesystem_traits_type::path_traits_type				path_traits_type;
		typedef typename_type_k filesystem_traits_type::system_traits_type				system_traits_type;
		typedef typename_type_k filesystem_traits_type::size_type						size_type;
		typedef typename_type_k filesystem_traits_type::bool_type						bool_type;
		typedef const_path_entry_iterator<char_type, path_traits<char_type> >			const_entry_iterator;
		typedef const_reverse_path_entry_iterator<char_type, path_traits<char_type> >	const_reverse_entry_iterator;
		typedef	typename_type_k const_entry_iterator::path_entry_type					path_entry_type;
		typedef	typename_type_k const_entry_iterator::enum_flag_type					enum_flag_type;
	/// @}

	public:
	#if defined(EXTL_COMPILER_IS_DMC) 
		EXTL_OPERATORS_EQUAL_1_2_(class_type const&, const_pointer)
		// EXTL_OPERATORS_DIV_1_2_(class_type const&, const_pointer)
		
		friend class_type operator/(class_type const& lhs, class_type const& rhs)
		{ basic_path<C, S, T> ret(lhs); ret /= rhs; return ret;	}
		friend class_type operator/(class_type const& lhs, const_pointer rhs)
		{ basic_path<C, S, T> ret(lhs); ret /= rhs; return ret;	}
		friend class_type operator/(const_pointer lhs, class_type const& rhs)
		{ basic_path<C, S, T> ret(lhs); ret /= rhs; return ret;	}	// _left_2
	#endif

	/// \name Constructors
	/// @{
	public:
		basic_path()
			: m_path()
		{
		}
		explicit_k basic_path(const_pointer path)
			: m_path(path)
		{
		}
		basic_path(const_pointer path, size_type size)
			: m_path(path, size)
		{
		}
		basic_path(class_type const& path)
			: m_path(path.m_path)
		{
		}

	#ifdef EXTL_MEMBER_TEMPLATE_CTOR_OVERLOAD_DISCRIMINATED_SUPPORT
		template< typename_param_k S1 >
		explicit_k basic_path(S1 const& s)
			: m_path(c_strptr(s), c_strlen(s))
		{
		}
	#endif
	/// @}

	/// \name Operators
	/// @{
	public:
		class_type& operator =(const_pointer rhs)		{ m_path.assign(rhs); return *this;			}
		class_type& operator =(class_type const& rhs)	{ m_path.assign(rhs.m_path); return *this;	}
	#ifdef EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT
		template< typename_param_k S1 >
		class_type& operator =(S1 const& rhs)			{ return operator =(c_strptr(rhs));	}
	#endif

		/// Equivalent to push()
		class_type& operator /=(const_pointer rhs)		{ return push(rhs);	}
		/// Equivalent to push()
		class_type& operator /=(class_type rhs)			{ return push(rhs);	}
		/// Equivalent to push()
	#ifdef EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT
		template< typename_param_k S1 >
		class_type& operator /=(S1 const& rhs)			{ return push(c_strptr(rhs));	}
	#endif

		bool_type operator ==(const_pointer rhs) const		{ return equal(rhs);	}
		bool_type operator ==(class_type const& rhs) const	{ return equal(rhs);	}
	#ifdef EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT
		template< typename_param_k S1 >
		bool_type operator ==(S1 const& rhs)				{ return equal(c_strptr(rhs));	}
	#endif
	/// @}

	/// \name Attributes
	/// @{
	public:
		/// Returns the the pointer the storage of the path
		pointer data()					{ return m_path.data();		}
		/// Returns the the pointer the storage of the path
		const_pointer data() const		{ return m_path.data();		}
		/// Returns the c-style string type of the path
		const_pointer c_str() const		{ return m_path.c_str();	}
		/// Returns the length of the path
		size_type length() const		{ return m_path.length();	}
		/// Returns the length of the path
		size_type size() const			{ return length();			}
		/// Returns \c true if the path is empty
		bool_type is_empty() const		{ return m_path.is_empty();	}
		/// Returns \c true if the path is empty
		bool_type empty() const			{ return is_empty();		}
		
		/// The maximum length of path
		static size_type max_length()			{ return path_traits_type::max_length();	}
		/// The maximum length of path
		static size_type max_size()				{ return max_length();	}
		/// Returns a path separator
		static char_type path_sep()				{ return path_traits_type::path_sep();	}
		/// Returns a path name separator
		static char_type path_name_sep()		{ return path_traits_type::path_name_sep();	}
		/// Returns the wildcard pattern that represents all possible matches
		static const_pointer pattern_all()		{ return path_traits_type::pattern_all();	}

		/// Returns \c true if the path represents an existing file system entry
		bool_type exists() const			{ return filesystem_traits_type::file_exists(c_str());	}
		/// Returns \c true if the path is \c "." or \c ".."
		bool_type is_dots() const			{ return path_traits_type::is_dots(c_str());	}
		/// Returns \c true if the path is is \c "\\\\..."
		bool_type is_unc_path() const		{ return path_traits_type::is_unc_path(c_str());	}
		/// Returns \c true if the path is is \c "\\\\" + '\\0'
		bool_type is_unc_root() const		{ return path_traits_type::is_unc_root(c_str());	}
		/// Returns \c true if the path is rooted
		bool_type is_rooted_drive() const	{ return path_traits_type::is_rooted_drive(c_str());	}
		/// Returns \c true if the path is absolute
		bool_type is_absolute_path() const	{ return path_traits_type::is_absolute_path(c_str());	}

		/// Returns \c true if the path  has trailing path name separator
		bool_type has_sep_end() const		{ return path_traits_type::has_sep_end(c_str());	}
		/// Returns \c true if the path  has rooted drive
		bool_type has_rooted_drive() const	{ return path_traits_type::has_rooted_drive(c_str());	}

		/*!\brief Returns the file name of the path
		 *
		 * e.g. "C:\\dir\\file.txt" return "file.txt"
		 * e.g. "C:\\dir"			return "dir"
		 * e.g. "C:\\dir\\"			return ""
		 */
		const_pointer get_file_name() const;

		/// Returns the extensible name of the path
		const_pointer get_ext_name() const;

		/// Returns the title name of the path
		const_pointer get_title_name() const;
	/// @}

	/// \name Mutators
	/// @{
	public:
		/// Appends a path name separator if one does not exist
		class_type& push_sep();
		/// \brief Removes the path name separator from the end of the path, if it has it
		/// \note Does not trim the separator character from the root designator
		class_type& pop_sep();


		/// Removes the last path element from the path
		class_type& pop(bool_type is_pop_sep = e_true_v);
		/// Appends the contents of \c rhs to the path
		class_type& push(const_pointer rhs, bool_type is_push_sep = e_false_v);
		/// Appends the contents of \c rhs to the path
		class_type& push(class_type const& rhs, bool_type is_push_sep = e_false_v);	
	#ifdef EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT
		/// Appends the contents of \c rhs to the path
		template< typename_param_k S1 >
		class_type& push(S1 const& rhs, bool_type is_push_sep = e_false_v)	{ push(c_strptr(rhs), is_push_sep);	}
	#endif
		

		/// Removes the extensible name from the path
		class_type& pop_ext_name(bool_type is_pop_dot = e_true_v);
		/// Appends an extensible name 
		class_type& push_ext_name(const_pointer rhs);
		/// Appends an extensible name 
		class_type& push_ext_name(class_type const& rhs);
	#ifdef EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT
		/// Appends an extensible name 
		template< typename_param_k S1 >
		class_type& push_ext_name(S const& rhs)	{ push_ext_name(c_strptr(rhs));	}
	#endif

		/// Makes a relative path
		class_type& make_relative_path();
		/// Makes a absolute path
		class_type& make_absolute_path();
		/// Makes a current directory
		class_type& make_current_directory();
		

		/// Clears all contents
		void clear()	{ m_path.clear(); }
		/// Swaps the contents 
		class_type&	swap(class_type& other) { m_path.swap(other.m_path); return *this;	}
	/// @}

	/// \name Comparison
	/// @{
	public:
		/// Return \c true if this->c_str() == rhs (case-insensitive)
		bool_type equal(const_pointer rhs) const		{ return 0 == m_path.compare_nocase(rhs);	}
		/// Return \c true if this->c_str() == rhs (case-insensitive)
		bool_type equal(string_type const& rhs) const	{ return 0 == m_path.compare_nocase(rhs);	}
		/// Return \c true if this->c_str() == rhs (case-insensitive)
		bool_type equal(class_type const& rhs) const	{ return equal(rhs.m_path);					}
	#ifdef EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT
		/// Return \c true if this->c_str() == rhs (case-insensitive)
		template< typename_param_k S1 >
		bool_type equal(S1 const& rhs) const			{ return equal(c_strptr(rhs));				}
	#endif
	/// @}

	/// \name Others
	/// @{
	public:
		/// Makes path
		static class_type make_path(const_pointer path)	{ return class_type(path);	}
	#ifdef EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT
		/// Makes path
		template< typename_param_k S1 >
		static class_type make_path(S1 const& path)		{ return class_type(c_strptr(path));	}
	#endif
	/// @}

	/// \name Accessors
	/// @{
	public:
		/// Returns reference at the given index
		reference operator[](size_type index)
		{
			return const_cast<reference>(static_cast<class_type const&>(*this).operator[](index));
		}
		/// Returns const reference at the given index
		const_reference operator[](size_type index) const
		{
			EXTL_ASSERT(index < length());
			return m_path[index];
		}
		/// Returns reference at the given index and throws index_error() if index >= length() 
		reference at(size_type index)
		{
			return const_cast<reference>(static_cast<class_type const&>(*this).at(index));
		}
		/// Returns const reference at the given index and throws index_error() if index >= length() 
		const_reference at(size_type index) const
		{
			EXTL_ASSERT(index < length());
			EXTL_ASSERT_THROW(index < length(), index_error("out of range"));
			return m_path[index];
		}
	/// @}

	/// \name Path entry iterator
	/// @{
	public:
		const_entry_iterator entry_begin(enum_flag_type flag = path_entry_type::en_enum_all) const	
		{ 
			return const_entry_iterator(c_str(), flag);	
		}
		const_entry_iterator entry_end() const		
		{ 
			return const_entry_iterator();	
		}
		const_reverse_entry_iterator entry_rbegin(enum_flag_type flag = path_entry_type::en_enum_all_rev) const	
		{ 
			return const_reverse_entry_iterator(c_str(), flag);	
		}
		const_reverse_entry_iterator entry_rend() const		
		{ 
			return const_reverse_entry_iterator();	
		}
	/// @}

	/// \name Members
	/// @{
	private:
		string_type			m_path;
	/// @}
};
/* ///////////////////////////////////////////////////////////////////////
 * Macro
 */

/* Template declaration */
#ifdef EXTL_BASIC_PATH_TEMPLATE_DECL
#	undef EXTL_BASIC_PATH_TEMPLATE_DECL
#endif

#define EXTL_BASIC_PATH_TEMPLATE_DECL	template<	typename_param_k C	\
												,	typename_param_k S	\
												,	typename_param_k T	\
												>

/* Class qualification */
#ifdef EXTL_BASIC_PATH_QUAL
#	undef EXTL_BASIC_PATH_QUAL
#endif

#define EXTL_BASIC_PATH_QUAL				basic_path<C, S, T>

/* Class qualification */
#ifdef EXTL_BASIC_PATH_RET_QUAL
#	undef EXTL_BASIC_PATH_RET_QUAL
#endif

#define EXTL_BASIC_PATH_RET_QUAL(ret_type)	\
					typename_type_ret_k EXTL_BASIC_PATH_QUAL::ret_type \
					EXTL_BASIC_PATH_QUAL

/* ///////////////////////////////////////////////////////////////////////
 * Implemention
 */
EXTL_BASIC_PATH_TEMPLATE_DECL
inline EXTL_BASIC_PATH_RET_QUAL(class_type&)::push_sep()
{
	EXTL_ASSERT(NULL != data());

	/* Maybe path_name_sep() is '\\' or '/',
	 * so ensure_push_back(path_name_sep()) isn't used. 
	 */
	if(!path_traits_type::is_path_name_sep(*--m_path.end())) 
		m_path.push_back(path_traits_type::path_name_sep());

	return *this;
}
EXTL_BASIC_PATH_TEMPLATE_DECL
inline EXTL_BASIC_PATH_RET_QUAL(class_type&)::pop_sep()
{
	EXTL_ASSERT(NULL != data());

	if(is_rooted_drive()) return *this;
	if(is_unc_root()) return *this;

	/* Maybe path_name_sep() is '\\' or '/',
	 * so ensure_pop_back(path_name_sep()) isn't used. 
	 */
	if(path_traits_type::is_path_name_sep(*--m_path.end())) 
		m_path.pop_back();

	return *this;
}

EXTL_BASIC_PATH_TEMPLATE_DECL
inline EXTL_BASIC_PATH_RET_QUAL(const_pointer)::get_file_name() const
{
	size_type pos = path_traits_type::rfind_sep(m_path.c_str(), m_path.size());

	if(string_type::fof() != pos)
	{
		EXTL_ASSERT(pos <= length());
		return m_path.c_str() + pos + 1;
	}
	else return string_traits_type::empty();
}
EXTL_BASIC_PATH_TEMPLATE_DECL
inline EXTL_BASIC_PATH_RET_QUAL(const_pointer)::get_ext_name() const
{
	size_type pos = m_path.rfind(char_type('.'));
	if(string_type::fof() != pos)
	{
		EXTL_ASSERT(pos <= length());
		return m_path.c_str() + pos + 1;
	}
	else return string_traits_type::empty();
}

EXTL_BASIC_PATH_TEMPLATE_DECL
inline EXTL_BASIC_PATH_RET_QUAL(const_pointer)::get_title_name() const
{
	string_type s(get_file_name());
	if(s.is_empty()) return string_traits_type::empty();
	
	size_type pos = s.rfind(char_type('.'));
	if(string_type::fof() != pos) s.resize(pos);
	return s.c_str();
}

EXTL_BASIC_PATH_TEMPLATE_DECL
inline EXTL_BASIC_PATH_RET_QUAL(class_type&)::push(const_pointer rhs, bool_type is_push_sep)
{
	EXTL_ASSERT(NULL != rhs);
	if (NULL == rhs) return *this;
	if (string_traits_type::is_empty(rhs)) return *this;
	if (path_traits_type::has_rooted_drive(rhs)) m_path.assign(rhs);
	else 
	{
		if (!is_empty()) push_sep();
		m_path.append(rhs);
	}
	if (is_push_sep) push_sep();
	return *this;
}
// The function isn't forwarded to push(const_pointer, bool_type) for the efficiency of string operation
EXTL_BASIC_PATH_TEMPLATE_DECL
inline EXTL_BASIC_PATH_RET_QUAL(class_type&)::push(class_type const& rhs, bool_type is_push_sep)
{
	EXTL_ASSERT(!rhs.is_empty());
	if (rhs.is_empty()) return *this;
	if (rhs.has_rooted_drive()) m_path.assign(rhs.m_path);
	else 
	{
		if (!is_empty()) push_sep();
		m_path.append(rhs.m_path);
	}
	if (is_push_sep) push_sep();
	return *this;
}

EXTL_BASIC_PATH_TEMPLATE_DECL
inline EXTL_BASIC_PATH_RET_QUAL(class_type&)::pop(bool_type is_pop_sep)
{
	if (is_rooted_drive()) return *this;
	if (is_unc_root()) return *this;

	size_type pos = path_traits_type::rfind_sep(m_path.c_str(), m_path.size());
	if (string_type::fof() != pos)
	{
		EXTL_ASSERT(pos <= length());

		if (!is_pop_sep) m_path.resize(pos + 1);
		else if (has_rooted_drive() && pos < 3) // Cannot remove '\\' for "C:\\dir"
			m_path.resize(pos + 1);
		else m_path.resize(pos);
	}
	return *this;
}

EXTL_BASIC_PATH_TEMPLATE_DECL
inline EXTL_BASIC_PATH_RET_QUAL(class_type&)::push_ext_name(const_pointer rhs)
{
	EXTL_ASSERT(NULL != rhs);
	if (NULL == rhs) return *this;
	if (string_traits_type::is_empty(rhs)) return *this;
	if (path_traits_type::is_path_name_sep(*--m_path.end())) return *this;	// for "C:dir\\"
	EXTL_ASSERT(!path_traits_type::has_rooted_drive(rhs));

	m_path.ensure_push_back(char_type('.'));
	m_path.append(rhs);
	
	return *this;
}
// The function isn't forwarded to push_ext_name(const_pointer) for the efficiency of string operation
EXTL_BASIC_PATH_TEMPLATE_DECL
inline EXTL_BASIC_PATH_RET_QUAL(class_type&)::push_ext_name(class_type const& rhs)
{
	EXTL_ASSERT(!rhs.is_empty());
	if (rhs.is_empty()) return *this;
	if (path_traits_type::is_path_name_sep(*--m_path.end())) return *this;	// for "C:dir\\"
	EXTL_ASSERT(!rhs.has_rooted_drive());

	m_path.ensure_push_back(char_type('.'));
	m_path.append(rhs.m_path);
	
	return *this;
}

EXTL_BASIC_PATH_TEMPLATE_DECL
inline EXTL_BASIC_PATH_RET_QUAL(class_type&)::pop_ext_name(bool_type is_pop_dot)
{
	if (is_rooted_drive()) return *this;
	if (is_unc_root()) return *this;

	size_type pos = m_path.rfind(char_type('.'));
	if (string_type::fof() != pos)
	{
		EXTL_ASSERT(pos <= length());

		if (!is_pop_dot) m_path.resize(pos + 1);
		else m_path.resize(pos);
	}
	return *this;

}

EXTL_BASIC_PATH_TEMPLATE_DECL
inline EXTL_BASIC_PATH_RET_QUAL(class_type&)::make_relative_path() 
{
	char_type buffer[path_traits_type::en_max_size];
	size_type n = filesystem_traits_type::get_relative_path(c_str(), size(), buffer, path_traits_type::en_max_size);
	m_path.assign(buffer, n);
	return *this;
}
EXTL_BASIC_PATH_TEMPLATE_DECL
inline EXTL_BASIC_PATH_RET_QUAL(class_type&)::make_absolute_path() 
{
	char_type buffer[path_traits_type::en_max_size];
	size_type n = filesystem_traits_type::get_absolute_path(c_str(), size(), buffer, path_traits_type::en_max_size);
	m_path.assign(buffer, n);
	return *this;
}
EXTL_BASIC_PATH_TEMPLATE_DECL
inline EXTL_BASIC_PATH_RET_QUAL(class_type&)::make_current_directory() 
{
	char_type buffer[path_traits_type::en_max_size];
	size_type n = filesystem_traits_type::get_current_directory(buffer, path_traits_type::en_max_size);
	m_path.assign(buffer, n);
	return *this;
}

/* /////////////////////////////////////////////////////////////////////////
 * swapping
 */
EXTL_BASIC_PATH_TEMPLATE_DECL
EXTL_INLINE void swap(EXTL_BASIC_PATH_QUAL &lhs, EXTL_BASIC_PATH_QUAL &rhs)
{
	lhs.swap(rhs);
}
/* /////////////////////////////////////////////////////////////////////////
 * shims
 */
EXTL_BASIC_PATH_TEMPLATE_DECL
EXTL_INLINE typename_type_ret_k EXTL_BASIC_PATH_QUAL::
size_type c_strlen(EXTL_BASIC_PATH_QUAL const& p)
{
	return EXTL_NS(c_strlen)(p.c_str());
}

EXTL_BASIC_PATH_TEMPLATE_DECL
EXTL_INLINE typename_type_ret_k EXTL_BASIC_PATH_QUAL::
const_pointer c_strptr(EXTL_BASIC_PATH_QUAL const& p)
{
	return p.c_str();
}

EXTL_BASIC_PATH_TEMPLATE_DECL
EXTL_INLINE typename_type_ret_k EXTL_BASIC_PATH_QUAL::
const_pointer get_ptr(EXTL_BASIC_PATH_QUAL const& p)
{
	return p.data();
}

template<	typename_param_k	St			
		,	typename_param_k	C			
		,	typename_param_k	S		
		,	typename_param_k	T			
		>
EXTL_INLINE St& operator<<(St& s, EXTL_BASIC_PATH_QUAL const& p)
{
	return s << p.c_str();
}
/* /////////////////////////////////////////////////////////////////////////
 * Types
 */
/// path_a
typedef basic_path	<	e_char_t
					,	filesystem_traits<e_char_t>::stack_path_string_type
					,	filesystem_traits<e_char_t>
					>					path_a;
/// path_w
typedef basic_path	<	e_wchar_t
					,	filesystem_traits<e_wchar_t>::stack_path_string_type
					,	filesystem_traits<e_wchar_t>
					>					path_w;
/// path
typedef basic_path	<	e_tchar_t
					,	filesystem_traits<e_tchar_t>::stack_path_string_type
					,	filesystem_traits<e_tchar_t>
					>					path;
/* //////////////////////////////////////////////////////////////////// */
#undef EXTL_BASIC_PATH_TEMPLATE_DECL
#undef EXTL_BASIC_PATH_QUAL
#undef EXTL_BASIC_PATH_RET_QUAL

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
#ifdef EXTL_PATH_TEST_ENABLE
#	include "unit_test/path_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * std::swap 
 */
#if !defined(EXTL_NO_STL) && \
		!defined(EXTL_NO_NAMESPACE)
/* ::std namespace */
EXTL_STD_BEGIN_NAMESPACE

template<	typename_param_k	C			
		,	typename_param_k	S		
		,	typename_param_k	T			
		>
EXTL_INLINE void swap(EXTL_NS(EXTL_NS_PLATFORM(EXTL_NS_WIN(basic_path)))<C, S, T> const& lhs, 
						EXTL_NS(EXTL_NS_PLATFORM(EXTL_NS_WIN(basic_path)))<C, S, T> const& rhs)
{
    lhs.swap(rhs);
}
/* ::std namespace */
EXTL_STD_END_NAMESPACE
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WIN_PATH_H */
/* //////////////////////////////////////////////////////////////////// */
