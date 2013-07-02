/* ///////////////////////////////////////////////////////////////////////
 * File:		path_traits.h		
 *
 * Created:		08.06.13				
 * Updated:		08.07.06
 *
 * Brief:		path_traits class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_PLATFORM_WIN_PATH_TRAITS_H
#define EXTL_PLATFORM_WIN_PATH_TRAITS_H

/*!\file path_traits.h
 * \brief path_traits class
 */

#ifndef __cplusplus
#	error path_traits.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../win.h"
#include "../string/win_string_traits.h"
#include "../../string/string.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_BEGIN_WHOLE_NAMESPACE

template < typename_param_k C >
struct path_traits_helper_;

EXTL_TEMPLATE_SPECIALISATION
struct path_traits_helper_<e_char_t>
{
	public:
		typedef	e_char_t													char_type;
		typedef char_type													value_type;
		typedef value_type*													pointer;
		typedef value_type const*											const_pointer;
		typedef value_type&													reference;
		typedef value_type const&											const_reference;
		typedef	path_traits_helper_<char_type>								class_type;
		typedef win_string_traits<char_type, std_char_traits<char_type> >	string_traits_type;
		typedef	DWORD														size_type;
		typedef	e_ptrdiff_t													difference_type;
		typedef	e_int_t														int_type;
		typedef	e_bool_t													bool_type;
		typedef	HINSTANCE													module_type;
		typedef	HANDLE														handle_type;
		typedef	DWORD														code_type;

	public:
		static char_type path_sep()
		{
			return ';';
		}
		static char_type path_name_sep()
		{
			return '\\';
		}
		static const_pointer pattern_all()
		{
			return "*.*";
		}

		static const_pointer dot()
		{
			return ".";
		}
		static const_pointer dotdot()
		{
			return "..";
		}

		static bool_type is_path_name_sep(char_type ch)
		{
			return '\\' == ch || '/' == ch;
		}
		static bool_type is_dots(const_pointer dir)
		{
			EXTL_ASSERT(string_traits_type::length(dir) >= 1);
			return  dir[0] == '.' && (dir[1] == '\0' || 
				(string_traits_type::length(dir) >= 2 && dir[1] == '.' && dir[2] == '\0'));
		}
		static bool_type is_unc_path(const_pointer path)
		{
			if (string_traits_type::length(path) < 2) return e_false_v;
			return ('\\' == path[0] && '\\' == path[1]);
		}
		static bool_type is_unc_root(const_pointer path)
		{
			return is_unc_path(path) && '\0' == path[2];
		}
		static bool_type is_rooted_drive(const_pointer path)
		{
			return has_rooted_drive(path) && '\0' == path[3];
		}
		static bool_type is_absolute_path(const_pointer path)
		{
			return is_unc_path(path) || has_rooted_drive(path);
		}
		
		static bool_type has_rooted_drive(const_pointer path)
		{
			if (string_traits_type::length(path) < 3) return e_false_v;
			else return e_w_isalpha(path[0]) && (L':' == path[1]) && is_path_name_sep(path[2]);
		}
};

EXTL_TEMPLATE_SPECIALISATION
struct path_traits_helper_<e_wchar_t>
{
	public:
		typedef	e_wchar_t													char_type;
		typedef char_type													value_type;
		typedef value_type*													pointer;
		typedef value_type const*											const_pointer;
		typedef value_type&													reference;
		typedef value_type const&											const_reference;
		typedef	path_traits_helper_<char_type>								class_type;
		typedef win_string_traits<char_type, std_char_traits<char_type> >	string_traits_type;
		typedef	DWORD														size_type;
		typedef	e_ptrdiff_t													difference_type;
		typedef	e_int_t														int_type;
		typedef	e_bool_t													bool_type;
		typedef	HINSTANCE													module_type;
		typedef	HANDLE														handle_type;
		typedef	DWORD														code_type;

	public:
		static char_type path_sep()
		{
			return L';';
		}
		static char_type path_name_sep()
		{
			return L'\\';
		}
		static const_pointer pattern_all()
		{
			return L"*.*";
		}

		static const_pointer dot()
		{
			return L".";
		}
		static const_pointer dotdot()
		{
			return L"..";
		}

		static bool_type is_path_name_sep(char_type ch)
		{
			return L'\\' == ch || L'/' == ch;
		}
		static bool_type is_dots(const_pointer dir)
		{
			EXTL_ASSERT(string_traits_type::length(dir) >= 1);
			return  dir[0] == L'.' && (dir[1] == L'\0' || 
				(string_traits_type::length(dir) >= 2 && dir[1] == L'.' && dir[2] == L'\0'));
		}
		static bool_type is_unc_path(const_pointer path)
		{
			if (string_traits_type::length(path) < 2) return e_false_v;
			return (L'\\' == path[0] && L'\\' == path[1]);
		}
		static bool_type is_unc_root(const_pointer path)
		{
			return is_unc_path(path) && L'\0' == path[2];
		}
		static bool_type is_rooted_drive(const_pointer path)
		{
			return has_rooted_drive(path) && L'\0' == path[3];
		}
		static bool_type is_absolute_path(const_pointer path)
		{
			return is_unc_path(path) || has_rooted_drive(path);
		}

		static bool_type has_rooted_drive(const_pointer path)
		{
			if (string_traits_type::length(path) < 3) return e_false_v;
			else return e_w_isalpha(path[0]) && (L':' == path[1]) && is_path_name_sep(path[2]);
		}
		
};
/*!\brief path_traits class
 *
 * \param C The character type
 *
 * \ingroup extl_group_filesystem
 */
template < typename_param_k C >
struct path_traits 
{
	///	\name Types
	///	@{
	public:
		typedef	C																char_type;
		typedef char_type														value_type;
		typedef value_type*														pointer;
		typedef value_type const*												const_pointer;
		typedef value_type&														reference;
		typedef value_type const&												const_reference;
		typedef	path_traits<char_type>											class_type;
		typedef win_string_traits<char_type, std_char_traits<char_type> >		string_traits_type;
		typedef path_traits_helper_<char_type>									path_traits_helper;
		typedef	DWORD															size_type;
		typedef	e_ptrdiff_t														difference_type;
		typedef	e_int_t															int_type;
		typedef	e_bool_t														bool_type;
		typedef	HINSTANCE														module_type;
		typedef	HANDLE															handle_type;
		typedef	DWORD															code_type;
		typedef HANDLE															file_handle_type;
		typedef FARPROC															far_proc_type;
		typedef basic_attached_string	<	char_type
										,	1 + EXTL_MAX_PATH
										,	string_traits_type
										>										attached_string_type;
		typedef basic_stack_string		<	char_type
										,	1 + EXTL_MAX_PATH
										,	string_traits_type
										>										stack_string_type;
		typedef basic_scoped_string		<	char_type
										,	EXTL_STRING_SCOPED_STRING_DEFAULT_GROW_SIZE
										,	string_traits_type
										,	typename_type_k allocator_selector<char_type>::allocator_type
										>										scoped_string_type;
	/// @}

	#if (defined(EXTL_COMPILER_IS_MSVC) && _MSC_VER == 1200) || \
			defined(EXTL_COMPILER_IS_DMC)
		template attached_string_type;
		template stack_string_type;
		template scoped_string_type;
	#endif
		
	///	@}

	/// \name Member Constants
	/// @{
	public:
		enum
		{
			en_max_size   =   1 + EXTL_MAX_PATH       //!< The maximum length of path
		};
		enum
		{
			en_max_length   =   1 + EXTL_MAX_PATH       //!< The maximum length of path
		};
	/// @}

	/// \name Accessors
	/// @{
	public:
		/*!\brief Returns \c ';'
		 * 
		 * e.g. path1; path2; ...
		 * \note On UNIX it is ':'
		 */
		static char_type path_sep();

		/*!\brief Returns \c '\\'
		 *
		 * e.g. "root\\dir\\"
		 * On UNIX it is '/'
		 */
		static char_type path_name_sep();

		/*!\brief Returns the wildcard pattern that represents all possible matches
		 *
		 * \note On Win32 it is '*.*'
		 */
		static const_pointer pattern_all();

		/// Returns \c "."
		static const_pointer dot();
		/// Returns \c ".."
		static const_pointer dotdot();

		/// The maximum length of path
		static size_type max_length();
		/// The maximum length of path
		static size_type max_size();
	/// @}

	/// \name Enumeration
	/// @{
	public:
		/// The path entry enumeration information type
		struct path_entry_type
		{
			private:
				typedef typename_type_k stack_string_type::buffer_type	buffer_type;

			public:
				/// enumeration flag
				enum enum_flag
				{
					en_direction_rev = 1			//!< reverse direction - default direction: positive  

				,	en_filter_dot = 2				//!< filter out \c '.'
				,	en_filter_dotdot = 4			//!< filter out \c '..'
				,	en_filter_rooted_drive = 8		//!< filter out rooted drive e.g. \c "C:"
				,	en_filter_filename = 16			//!< filter out filename e.g. \c "filename.txt"

					/// enumerate all entries in the positive direction
				,	en_enum_all = 0
					/// enumerate all directory entries in the positive direction
				,	en_enum_dir = en_enum_all | en_filter_rooted_drive | en_filter_filename 
					/// enumerate all entries in the negative direction
				,	en_enum_all_rev = en_enum_all | en_direction_rev
					/// enumerate all directory entries in the negative direction
				,	en_enum_dir_rev = en_enum_dir | en_direction_rev
				};
				/// Enumeration flag Type
				typedef enum_flag										enum_flag_type;

			/// \name Members
			/// @{
			private:
				size_type												m_pos;
				size_type												m_next_pos;
				enum_flag_type											m_flag;
				buffer_type												m_path;
			/// @}

			private:
				friend struct path_traits<C>;

			public:
				/// The Constructor
				explicit_k path_entry_type(enum_flag_type flag = en_enum_all)
					: m_pos(string_traits_type::fof())
					, m_next_pos(string_traits_type::fof())
					, m_flag(flag)
				{
				}
			/// \name Attributes
			/// @{
			public:
				const_pointer name() const	{ return m_path.is_empty()? string_traits_type::empty() : &m_path[m_pos];	}
				size_type size() const		{ return (NULL != name())? string_traits_type::length(name()) : 0;			}
				size_type pos() const		{ return m_pos;																}
				size_type flag() const		{ return m_flag;															}
			/// @}

			/// \name Operators
			/// @{
			public:
				bool_type operator ==(path_entry_type const& rhs) const
				{
					return pos() == rhs.pos() && flag() == rhs.flag() &&
						!string_traits_type::compare_nocase(name(), rhs.name());
				}
			/// @}
				
		};
		/*!\brief Starts enumerating entries from the path
		 *
		 * \code
			typedef path_traits<e_tchar_t>::path_entry_type path_entry_type;
			path_entry_type ei(path_entry_type::enum_flag::en_enum_all);
			if (path_traits<e_tchar_t>::entry_enum_start(_T("C:\\dir1\\file.txt"), ei))
			{
				do
				{
					e_t_printf(_T("name:%s  size:%d\n"), ei.name(), ei.size());
				}
				while (path_traits<e_tchar_t>::entry_enum(ei));

				path_traits<e_tchar_t>::entry_enum_stop(ei);
			}
		 * \endcode 
		 */
		static bool_type entry_enum_start(const_pointer path, size_type size, path_entry_type& ei);
		/// Starts enumerating entries from the path
		static bool_type entry_enum_start(const_pointer path, path_entry_type& ei);
		/// Enumerates entries from the path
		static bool_type entry_enum(path_entry_type& ei);
		/// Stops enumerating entries from the path
		static void entry_enum_stop(path_entry_type& ei);
	/// @}

	private:
		static bool_type entry_enum_start_impl(const_pointer path, size_type size, path_entry_type& ei);
		static bool_type entry_enum_impl(path_entry_type& ei);

		static bool_type entry_reverse_enum_start_impl(const_pointer path, size_type size, path_entry_type& ei);
		static bool_type entry_reverse_enum_impl(path_entry_type& ei);

	/// \name Attributes
	/// @{
	public:
		///Returns \c true if the character is \c '/' or \c '\\' 
		static bool_type is_path_name_sep(char_type ch);
		///Returns \c true if the character is \c '/' or \c '\\' 
		static bool_type is_path_sep(char_type ch);
		/// Returns \c true if \c dir is \c "." or \c ".."
		static bool_type is_dots(const_pointer dir);
		/// Returns \c true if \c path is is \c "\\\\..."
		static bool_type is_unc_path(const_pointer path);
		/// Returns \c true if \c path is is \c "\\\\" + '\\0'
		static bool_type is_unc_root(const_pointer path);
		/// Returns \c true if \c path is an absolute path
		static bool_type is_absolute_path(const_pointer path);
		/// Returns \c true if \c path is \c "C:\\" + '\\0'
		static bool_type is_rooted_drive(const_pointer path);

		/// Returns \c true if \c dir has trailing path name separator
		static bool_type has_sep_end(const_pointer dir);
		/// Returns \c true if \c path has rooted drive
		static bool_type has_rooted_drive(const_pointer path);
	/// @}

	/// \name Mutators
	/// @{
	public:
		/// Appends a path name separator to \c dir if one does not exist
		static const_pointer push_sep(pointer path) { return push_sep(path, (NULL != path)? string_traits_type::length(path) : 0);	}
		/// Appends a path name separator to \c dir if one does not exist
		static const_pointer push_sep(pointer path, size_type size);
		/// \brief Removes the path name separator from the end of \c dir, if it has it
		/// \note Does not trim the separator character from the root designator
		static const_pointer pop_sep(pointer path) { return pop_sep(path, (NULL != path)? string_traits_type::length(path) : 0);	}
		/// \brief Removes the path name separator from the end of \c dir, if it has it
		/// \note Does not trim the separator character from the root designator
		static const_pointer pop_sep(pointer path, size_type size);


		/// Appends the contents
		static const_pointer push(pointer dest, size_type dest_size, const_pointer src, size_type src_size, bool_type is_push_sep = e_false_v);
		/// Appends the contents
		static const_pointer push(pointer dest, size_type dest_size, const_pointer src, bool_type is_push_sep = e_false_v);
		/// Appends the contents
		static const_pointer push(pointer dest, const_pointer src, bool_type is_push_sep = e_false_v);
		/// Removes the last path element from the path
		static const_pointer pop(pointer path, size_type size, bool_type is_pop_sep = e_true_v);
		/// Removes the last path element from the path
		static const_pointer pop(pointer path, bool_type is_pop_sep = e_true_v);

		/// Appends an extensible name 
		static const_pointer push_ext_name(pointer dest, size_type dest_size, const_pointer src, size_type src_size);
		/// Appends an extensible name 
		static const_pointer push_ext_name(pointer dest, size_type dest_size, const_pointer src);
		/// Appends an extensible name 
		static const_pointer push_ext_name(pointer dest, const_pointer src);
		/// Removes the extensible name from the path
		static const_pointer pop_ext_name(pointer path, size_type size, bool_type is_pop_dot = e_true_v);
		/// Removes the extensible name from the path
		static const_pointer pop_ext_name(pointer path, bool_type is_pop_dot = e_true_v);
	/// @}

	/// \name Algorithms
	/// @{
	public:
		/// Finds a path name separator
		static size_type find_sep(const_pointer path, size_type size, size_type pos = 0);
		/// Finds a path name separator
		static size_type find_sep(const_pointer path)	{ return find_sep(path, (NULL != path)? string_traits_type::length(path) : 0);	}
		/// Reversely finds a path name separator
		static size_type rfind_sep(const_pointer path, size_type size, size_type rpos = 0);
		/// Reversely finds a path name separator
		static size_type rfind_sep(const_pointer path)	{ return rfind_sep(path, (NULL != path)? string_traits_type::length(path) : 0);	}
	
	/// @}
	
};
/* ///////////////////////////////////////////////////////////////////////
 * Macro
 */

/* Template declaration */
#ifdef EXTL_PATH_TRAITS_TEMPLATE_DECL
#	undef EXTL_PATH_TRAITS_TEMPLATE_DECL
#endif

#define EXTL_PATH_TRAITS_TEMPLATE_DECL	template< typename_param_k C >

/* Class qualification */
#ifdef EXTL_PATH_TRAITS_QUAL
#	undef EXTL_PATH_TRAITS_QUAL
#endif

#define EXTL_PATH_TRAITS_QUAL				path_traits<C>

/* Class qualification */
#ifdef EXTL_PATH_TRAITS_RET_QUAL
#	undef EXTL_PATH_TRAITS_RET_QUAL
#endif

#define EXTL_PATH_TRAITS_RET_QUAL(ret_type)	\
					typename_type_ret_k EXTL_PATH_TRAITS_QUAL::ret_type \
					EXTL_PATH_TRAITS_QUAL
/* ///////////////////////////////////////////////////////////////////////
 * Implemention
 */
EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(char_type)::path_sep()
{
	return path_traits_helper::path_sep();
}

EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(char_type)::path_name_sep()
{
	return path_traits_helper::path_name_sep();
}

EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(bool_type)::is_path_name_sep(char_type ch)
{
	return path_traits_helper::is_path_name_sep(ch);
}

EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(bool_type)::is_path_sep(char_type ch)
{
	return path_sep() == ch;
}

EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(bool_type)::is_dots(const_pointer dir)
{
	EXTL_ASSERT(NULL != dir);
	return path_traits_helper::is_dots(dir);
}

EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(bool_type)::is_unc_path(const_pointer path)
{
	EXTL_ASSERT(NULL != path);
	return path_traits_helper::is_unc_path(path);
}

EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(bool_type)::is_unc_root(const_pointer path)
{
	EXTL_ASSERT(NULL != path);
	return path_traits_helper::is_unc_root(path);
}

EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(bool_type)::is_absolute_path(const_pointer path)
{
	EXTL_ASSERT(NULL != path);
	return path_traits_helper::is_absolute_path(path);
}

EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(bool_type)::is_rooted_drive(const_pointer path)
{
	EXTL_ASSERT(NULL != path);
	return path_traits_helper::is_rooted_drive(path);
}

EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(bool_type)::has_sep_end(const_pointer dir)
{
	EXTL_ASSERT(NULL != dir);
	attached_string_type attached_dir(dir);
	return !attached_dir.is_empty() && is_path_name_sep(*--attached_dir.end());
}
EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(bool_type)::has_rooted_drive(const_pointer path)
{
	EXTL_ASSERT(NULL != path);
	return path_traits_helper::has_rooted_drive(path);
}

EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(const_pointer)::push_sep(pointer path, size_type size)
{
	EXTL_ASSERT(NULL != path);

	/* Maybe path_name_sep() is '\\' or '/',
	 * so ensure_push_back(path_name_sep()) isn't used. 
	 */
	attached_string_type attached_path(path, size);
	if(!is_path_name_sep(attached_path.back())) 
		attached_path.push_back(path_name_sep());

	return path;
}

EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(const_pointer)::pop_sep(pointer path, size_type size)
{
	EXTL_ASSERT(NULL != path);
	if(is_rooted_drive(path)) return path;
	if(is_unc_root(path)) return path;

	/* Maybe path_name_sep() is '\\' or '/',
	 * so ensure_pop_back(path_name_sep()) isn't used. 
	 */
	attached_string_type attached_path(path, size);
	if(is_path_name_sep(attached_path.back())) 
		attached_path.pop_back();

	return path;
}
EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(size_type)::max_length()
{
	return en_max_size;
}
EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(size_type)::max_size()
{
	return en_max_size;
}

EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(const_pointer)::pattern_all()
{
	return path_traits_helper::pattern_all();
}
EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(size_type)::find_sep(const_pointer path, size_type size, size_type pos)
{
	EXTL_ASSERT(NULL != path);
	size_type p = string_traits_type::fof();

	if(NULL == path || 0 == size) 
		return p;

	if(is_rooted_drive(path)) return p;

	for (size_type i = pos; i < size; ++i)
	{
		// '\\' or '/'
		if (is_path_name_sep(path[i]))
		{
			p = i;
			break;
		}
	}

	return p;
}
EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(size_type)::rfind_sep(const_pointer path, size_type size, size_type rpos)
{
	EXTL_ASSERT(NULL != path);
	size_type p = string_traits_type::fof();

	if(NULL == path || 0 == size) 
		return p;

	if(is_rooted_drive(path)) return p;

	for (size_type i = size - rpos; i > 0; --i)
	{
		// '\\' or '/'
		if (is_path_name_sep(path[i - 1]))
		{
			p = i - 1;
			break;
		}
	}
	return p;
}

EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(const_pointer)::push(pointer dest, size_type dest_size, const_pointer src, size_type src_size, bool_type is_push_sep)
{
	EXTL_ASSERT(NULL != src);
	if (NULL == src) return dest;
	if (string_traits_type::is_empty(src)) return dest;

	attached_string_type path(dest, dest_size);
	if (has_rooted_drive(src)) path.assign(src, src_size);
	else 
	{
		// push_sep(dest, dest_size);
		if(!path.is_empty() && !is_path_name_sep(path.back())) 
			path.push_back(path_name_sep());

		path.append(src, src_size);
	}
	if (is_push_sep) 
	{
		// push_sep(dest, dest_size);
		if(!is_path_name_sep(*--path.end())) 
			path.push_back(path_name_sep());
	}
	return dest;
}

EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(const_pointer)::push(pointer dest, size_type dest_size, const_pointer src, bool_type is_push_sep)
{
	return push(dest, dest_size, src, (NULL != src)? string_traits_type::length(src) : 0, is_push_sep);
}
EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(const_pointer)::push(pointer dest, const_pointer src, bool_type is_push_sep)
{
	return push(dest, (NULL != dest)? string_traits_type::length(dest) : 0, src, is_push_sep);
}
EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(const_pointer)::pop(pointer path, size_type size, bool_type is_pop_sep)
{
	if (is_rooted_drive(path)) return path;
	if (is_unc_root(path)) return path;

	size_type pos = rfind_sep(path, size);
	if (string_traits_type::fof() != pos)
	{
		EXTL_ASSERT(pos <= size);

		if (!is_pop_sep) path[pos + 1] = char_type('\0');
		else if (has_rooted_drive(path) && pos < 3) // Cannot remove '\\' for "C:\\dir"
			path[pos + 1] = char_type('\0');
		else path[pos] = char_type('\0');
	}
	return path;
}

EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(const_pointer)::pop(pointer path, bool_type is_pop_sep)
{
	return pop(path, (NULL != path)? string_traits_type::length(path) : 0, is_pop_sep);
}

EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(const_pointer)::push_ext_name(pointer dest, size_type dest_size, const_pointer src, size_type src_size)
{
	EXTL_ASSERT(!string_traits_type::is_empty(src));
	if (string_traits_type::is_empty(src)) return dest;

	attached_string_type path(dest, dest_size);
	if (is_path_name_sep(*--path.end())) return dest;	// for "C:dir\\"
	EXTL_ASSERT(!has_rooted_drive(src));

	path.ensure_push_back(char_type('.'));
	path.append(src, src_size);
	
	return dest;
}
EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(const_pointer)::push_ext_name(pointer dest, size_type dest_size, const_pointer src)
{
	return push_ext_name(dest, dest_size, src, (NULL != src)? string_traits_type::length(src) : 0);
}
EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(const_pointer)::push_ext_name(pointer dest, const_pointer src)
{
	return push_ext_name(dest, (NULL != dest)? string_traits_type::length(dest) : 0, src);
}
EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(const_pointer)::pop_ext_name(pointer path, size_type size, bool_type is_pop_dot)
{
	if (is_rooted_drive(path)) return path;
	if (is_unc_root(path)) return path;

	attached_string_type path_str(path, size);
	size_type pos = path_str.rfind(char_type('.'));
	if (string_traits_type::fof() != pos)
	{
		EXTL_ASSERT(pos <= size);

		if (!is_pop_dot) path[pos + 1] = char_type('\0');
		else path[pos] = char_type('\0');
	}
	return path;
}

EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(const_pointer)::pop_ext_name(pointer path, bool_type is_pop_dot)
{
	return pop_ext_name(path, (NULL != path)? string_traits_type::length(path) : 0, is_pop_dot);
}
EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(const_pointer)::dot()
{
	return path_traits_helper::dot();
}
EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(const_pointer)::dotdot()
{
	return path_traits_helper::dotdot();
}
EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(bool_type)::entry_enum_start_impl(const_pointer path, size_type size, path_entry_type& ei)
{
	EXTL_ASSERT(NULL != path);
	if (NULL == path || 0 == size) return e_false_v;

	// + '\0', the type of m_path is buffer_type
	ei.m_path.assign(path, size + 1);

	// Filters out path name separators
	ei.m_pos = 0;
	while (ei.m_pos < ei.m_path.size() && is_path_name_sep(path[ei.m_pos])) ++ei.m_pos;

	// Finds the end of the first entry
	size_type pos = find_sep(path, size, ei.m_pos);
 
	if (string_traits_type::fof() != pos)
	{
		// Filters out path name separators
		ei.m_path[pos++] = char_type('\0');
		while (pos < ei.m_path.size() && is_path_name_sep(path[pos]))
		{
			ei.m_path[pos] = char_type('\0');
			++pos;
		}
		ei.m_next_pos = pos;
	}
	else
	{
		ei.m_next_pos = ei.m_path.size();
	}

	EXTL_ASSERT(NULL != ei.name());

	// Filters out rooted drive
	if ((ei.flag() & path_entry_type::en_filter_rooted_drive) &&
		string_traits_type::eq(ei.name()[1], char_type(':')))
	{
		return entry_enum(ei);
	}

	// Filters out "."
	if (ei.flag() & path_entry_type::en_filter_dot)
	{
		while (!string_traits_type::compare(ei.name(), dot()))
		{
			return entry_enum(ei);
		}
	}

	// Filters out ".."
	if (ei.flag() & path_entry_type::en_filter_dotdot)
	{
		while (!string_traits_type::compare(ei.name(), dotdot()))
		{
			return entry_enum(ei);
		}
	}

	return e_true_v;
}
EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(bool_type)::entry_reverse_enum_start_impl(const_pointer path, size_type size, path_entry_type& ei)
{
	EXTL_ASSERT(NULL != path);
	if (NULL == path || 0 == size) return e_false_v;

	// + '\0', the type of m_path is buffer_type
	ei.m_path.assign(path, size + 1);

	// Filters out path name separators
	size_type pos = ei.m_path.size();
	while (pos > 0 && is_path_name_sep(path[pos - 1])) 
	{
		ei.m_path[pos - 1] = char_type('\0');
		--pos;
	}
	// the path like this: "\\\\..."
	if (0 == pos) return e_false_v; 

	// Reversely finds the begin of the first entry
	ei.m_next_pos = rfind_sep(path, size, size - (1 + pos));

	if (string_traits_type::fof() != ei.m_next_pos)
		ei.m_pos = ei.m_next_pos + 1;
	else ei.m_pos = 0;

	/* Filters out filename
	 * e.g. Filters out "filename.txt" if the path is "C:\\dir\\filename.txt" 
	 * e.g. Filters out "dir2" if the path is "C:\\dir\\dir2" 
	 * e.g. Filters out "" if the path is "C:\\dir\\dir2\\" 
	 */
	if (ei.flag() & path_entry_type::en_filter_filename)
	{
		if (!is_path_name_sep(path[size]))
			return entry_enum(ei);
	}

	// Filters out '.'
	if (ei.flag() & path_entry_type::en_filter_dot)
	{
		while (!string_traits_type::compare(ei.name(), dot()))
		{
			return entry_enum(ei);
		}
	}

	// Filters out ".."
	if (ei.flag() & path_entry_type::en_filter_dotdot)
	{
		while (!string_traits_type::compare(ei.name(), dotdot()))
		{
			return entry_enum(ei);
		}
	}

	return e_true_v;

}
EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(bool_type)::entry_enum_start(const_pointer path, size_type size, path_entry_type& ei)
{
	bool_type res;
	if (ei.flag() & path_entry_type::en_direction_rev)
		res = entry_reverse_enum_start_impl(path, size, ei);
	else res = entry_enum_start_impl(path, size, ei);

	if (!res) entry_enum_stop(ei);
	return res;
}
EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(bool_type)::entry_enum_start(const_pointer path, path_entry_type& ei)
{
	return entry_enum_start(path, (NULL != path)? string_traits_type::length(path) : 0, ei);
}
EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(bool_type)::entry_enum_impl(path_entry_type& ei)
{
	if (ei.m_path.size() == ei.m_next_pos) return e_false_v;

	// Finds the end of this entry
	size_type pos = find_sep(ei.m_path.data(), ei.m_path.size(), ei.m_next_pos);
	
	if (string_traits_type::fof() != pos)
	{
		// Filters out path name separators
		ei.m_path[pos++] = char_type('\0');
		while (pos < ei.m_path.size() && is_path_name_sep(ei.m_path[pos]))
		{
			ei.m_path[pos] = char_type('\0');
			++pos;
		}
		ei.m_pos = ei.m_next_pos;
		ei.m_next_pos = pos;
	}
	else
	{
		/* Filters out filename
		 * e.g. Filters out "filename.txt" if the path is "C:\\dir\\filename.txt" 
		 * e.g. Filters out "dir2" if the path is "C:\\dir\\dir2" 
		 * e.g. Filters out "" if the path is "C:\\dir\\dir2\\" 
		 */
		if (ei.flag() & path_entry_type::en_filter_filename) 
			return e_false_v;

		ei.m_pos = ei.m_next_pos;
		ei.m_next_pos = ei.m_path.size();
	}

	EXTL_ASSERT(NULL != ei.name());

	// Filters out '.'
	if (ei.flag() & path_entry_type::en_filter_dot)
	{
		while (!string_traits_type::compare(ei.name(), dot()))
		{
			return entry_enum(ei);
		}
	}

	// Filters out ".."
	if (ei.flag() & path_entry_type::en_filter_dotdot)
	{
		while (!string_traits_type::compare(ei.name(), dotdot()))
		{
			return entry_enum(ei);
		}
	}

	return e_true_v;
}
EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(bool_type)::entry_reverse_enum_impl(path_entry_type& ei)
{
	if (string_traits_type::fof() == ei.m_next_pos) return e_false_v;

	// Filters out path name separators
	size_type pos = ei.m_next_pos + 1;
	while (pos > 0 && is_path_name_sep(ei.m_path[pos - 1])) 
	{
		ei.m_path[pos - 1] = char_type('\0');
		--pos;
	}
	// the path like this: "\\\\..."
	if (0 == pos) return e_false_v; 

	// Reversely finds the begin of the first entry
	ei.m_next_pos = rfind_sep(ei.m_path.data(), ei.m_path.size(), ei.m_path.size() - (1 + pos));

	if (string_traits_type::fof() != ei.m_next_pos)
		ei.m_pos = ei.m_next_pos + 1;
	else ei.m_pos = 0;

	// Filters out rooted drive
	if ((ei.flag() & path_entry_type::en_filter_rooted_drive) &&
		string_traits_type::eq(ei.name()[1], char_type(':')))
	{
		return entry_enum(ei);
	}

	// Filters out '.'
	if (ei.flag() & path_entry_type::en_filter_dot)
	{
		while (!string_traits_type::compare(ei.name(), dot()))
		{
			return entry_enum(ei);
		}
	}

	// Filters out ".."
	if (ei.flag() & path_entry_type::en_filter_dotdot)
	{
		while (!string_traits_type::compare(ei.name(), dotdot()))
		{
			return entry_enum(ei);
		}
	}

	return e_true_v;
}
EXTL_PATH_TRAITS_TEMPLATE_DECL
inline EXTL_PATH_TRAITS_RET_QUAL(bool_type)::entry_enum(path_entry_type& ei)
{
	if (ei.flag() & path_entry_type::en_direction_rev)
		return entry_reverse_enum_impl(ei);
	else return entry_enum_impl(ei);
}
EXTL_PATH_TRAITS_TEMPLATE_DECL
inline void EXTL_PATH_TRAITS_QUAL::entry_enum_stop(path_entry_type& ei)
{
	ei.m_path.clear();
	ei.m_pos = string_traits_type::fof();
	ei.m_next_pos = string_traits_type::fof();
	ei.m_flag = path_entry_type::en_enum_all;
}
/* //////////////////////////////////////////////////////////////////// */
#undef EXTL_PATH_TRAITS_TEMPLATE_DECL
#undef EXTL_PATH_TRAITS_QUAL
#undef EXTL_PATH_TRAITS_RET_QUAL

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
#ifdef EXTL_PATH_TRAITS_TEST_ENABLE
#	include "unit_test/path_traits_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WIN_PATH_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
