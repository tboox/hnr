/* ///////////////////////////////////////////////////////////////////////
 * File:		filesystem_traits.h		
 *
 * Created:		08.06.13				
 * Updated:		08.06.13	
 *
 * Brief:		filesystem_traits class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_PLATFORM_WIN_FILESYSTEM_TRAITS_H
#define EXTL_PLATFORM_WIN_FILESYSTEM_TRAITS_H

/*!\file filesystem_traits.h
 * \brief filesystem_traits class
 */

#ifndef __cplusplus
#	error filesystem_traits.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../win.h"
#include "path_traits.h"
#include "../string/win_string_traits.h"
#include "../system/system_traits.h"
#include "../../math/math.h" // for max_min
#include "../../container/basic_stack.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_BEGIN_WHOLE_NAMESPACE

#if defined(EXTL_COMPILER_IS_MSVC) && _MSC_VER == 1200
template < typename_param_k C >
struct stat_data_traits
{
	typedef WIN32_FIND_DATAA											stat_data_type;
	typedef BY_HANDLE_FILE_INFORMATION									fstat_data_type;
	typedef stat_data_type												find_data_type;
};
#else
template < typename_param_k C >
struct stat_data_traits;
#endif

EXTL_TEMPLATE_SPECIALISATION
struct stat_data_traits<e_char_t>
{
	typedef WIN32_FIND_DATAA											stat_data_type;
	typedef BY_HANDLE_FILE_INFORMATION									fstat_data_type;
	typedef stat_data_type												find_data_type;
};

EXTL_TEMPLATE_SPECIALISATION
struct stat_data_traits<e_wchar_t>
{
	typedef WIN32_FIND_DATAW											stat_data_type;
	typedef BY_HANDLE_FILE_INFORMATION									fstat_data_type;
	typedef stat_data_type												find_data_type;
};

template < typename_param_k C >
struct filesystem_traits_helper_;

EXTL_TEMPLATE_SPECIALISATION
struct filesystem_traits_helper_<e_char_t>
{
	public:
		typedef	e_char_t													char_type;
		typedef char_type													value_type;
		typedef value_type*													pointer;
		typedef value_type const*											const_pointer;
		typedef value_type&													reference;
		typedef value_type const&											const_reference;
		typedef	filesystem_traits_helper_<char_type>						class_type;
		typedef system_traits<char_type>									system_traits_type;
		typedef path_traits<char_type>										path_traits_type;
		typedef win_string_traits<char_type, std_char_traits<char_type> >	string_traits_type;
		typedef	DWORD														size_type;
		typedef	e_ptrdiff_t													difference_type;
		typedef	e_int_t														int_type;
		typedef	e_bool_t													bool_type;
		typedef	HANDLE														handle_type;
		typedef stat_data_traits<char_type>::stat_data_type					stat_data_type;
		typedef stat_data_traits<char_type>::fstat_data_type				fstat_data_type;
		typedef stat_data_traits<char_type>::find_data_type					find_data_type;
		typedef handle_type													file_handle_type;
		typedef	size_type													code_type;

	public:
		static bool_type CreateDirectory(const_pointer dir, LPSECURITY_ATTRIBUTES lpsa)
		{
			return FALSE != ::CreateDirectoryA(dir, lpsa);
		}

		static bool_type RemoveDirectory(const_pointer dir)
		{
			return FALSE != ::RemoveDirectoryA(dir);
		}

		static bool_type DeleteFile(const_pointer filename)
		{
			return FALSE != ::DeleteFileA(filename);
		}

		static bool_type MoveFile(const_pointer old_filenme, const_pointer new_filenme)
		{
			return FALSE != ::MoveFileA(old_filenme, new_filenme);
		}

		static bool_type CopyFile(const_pointer src_filenme, const_pointer dest_filenme, bool_type is_fail_if_exists)
		{
			return FALSE != ::CopyFileA(src_filenme, dest_filenme, is_fail_if_exists);
		}

		static file_handle_type CreateFile(const_pointer filename, size_type desired_access, size_type share_mode, LPSECURITY_ATTRIBUTES sa, size_type creation_disposition, size_type flag_and_attributes, file_handle_type template_file)
		{
			return ::CreateFileA(filename, desired_access, share_mode, sa, creation_disposition, flag_and_attributes, template_file);
		}
		static size_type GetFileAttributes(const_pointer filename)
		{
			return ::GetFileAttributesA(filename);
		}

		static bool_type SetFileAttributes(const_pointer filename, size_type attr)
		{
			return FALSE != ::SetFileAttributesA(filename, attr);
		}

		static file_handle_type FindFirstFile(const_pointer path, find_data_type *find_data)
		{
			return ::FindFirstFileA(path, find_data);
		}
	#if defined(_WIN32_WINNT) &&  _WIN32_WINNT >= 0x0400
		static file_handle_type FindFirstFileEx(const_pointer path, FINDEX_INFO_LEVELS finfo_level_id, find_data_type* find_data, FINDEX_SEARCH_OPS flags, void* search_filter, size_type additional_flags)
		{
			return ::FindFirstFileExA(path, finfo_level_id, find_data, flags, search_filter, additional_flags);
		}
	#endif /* _WIN32_WINNT >= 0x0400 */

		static bool_type FindNextFile(file_handle_type hfile, find_data_type* find_data)
		{
			return FALSE != ::FindNextFileA(hfile, find_data);
		}

		static bool_type SetCurrentDirectory(const_pointer dir)
		{
			return FALSE != ::SetCurrentDirectoryA(dir);
		}

		static size_type GetCurrentDirectory(size_type size, pointer buf)
		{
			return ::GetCurrentDirectoryA(size, buf);
		}

		static bool_type drive_exists(char_type drive_char)
		{
			size_type const drives_mask = ::GetLogicalDrives();
			return 0 != ((0x01 << (string_traits_type::to_upper(drive_char) - 'A')) & drives_mask);
		}

		static size_type get_drive_type(char_type drive_char)
		{
			char_type drive[] = { '?', ':', '\\', '\0' };
			drive[0] = drive_char;
			return ::GetDriveTypeA(drive);
		}
};

EXTL_TEMPLATE_SPECIALISATION
struct filesystem_traits_helper_<e_wchar_t>
{
	public:
		typedef	e_wchar_t													char_type;
		typedef char_type													value_type;
		typedef value_type*													pointer;
		typedef value_type const*											const_pointer;
		typedef value_type&													reference;
		typedef value_type const&											const_reference;
		typedef	filesystem_traits_helper_<char_type>						class_type;
		typedef system_traits<char_type>									system_traits_type;
		typedef path_traits<char_type>										path_traits_type;
		typedef win_string_traits<char_type, std_char_traits<char_type> >	string_traits_type;
		typedef	DWORD														size_type;
		typedef	e_ptrdiff_t													difference_type;
		typedef	e_int_t														int_type;
		typedef	e_bool_t													bool_type;
		typedef	HANDLE														handle_type;
		typedef stat_data_traits<char_type>::stat_data_type					stat_data_type;
		typedef stat_data_traits<char_type>::fstat_data_type				fstat_data_type;
		typedef stat_data_traits<char_type>::find_data_type					find_data_type;
		typedef handle_type													file_handle_type;
		typedef	size_type													code_type;

	public:
		static bool_type CreateDirectory(const_pointer dir, LPSECURITY_ATTRIBUTES lpsa)
		{
			return FALSE != ::CreateDirectoryW(dir, lpsa);
		}

		static bool_type RemoveDirectory(const_pointer dir)
		{
			return FALSE != ::RemoveDirectoryW(dir);
		}

		static bool_type DeleteFile(const_pointer filename)
		{
			return FALSE != ::DeleteFileW(filename);
		}

		static bool_type MoveFile(const_pointer old_filenme, const_pointer new_filenme)
		{
			return FALSE != ::MoveFileW(old_filenme, new_filenme);
		}

		static bool_type CopyFile(const_pointer src_filenme, const_pointer dest_filenme, bool_type is_fail_if_exists)
		{
			return FALSE != ::CopyFileW(src_filenme, dest_filenme, is_fail_if_exists);
		}

		static file_handle_type CreateFile(const_pointer filename, size_type desired_access, size_type share_mode, LPSECURITY_ATTRIBUTES sa, size_type creation_disposition, size_type flag_and_attributes, file_handle_type template_file)
		{
			return ::CreateFileW(filename, desired_access, share_mode, sa, creation_disposition, flag_and_attributes, template_file);
		}
		static size_type GetFileAttributes(const_pointer filename)
		{
			return ::GetFileAttributesW(filename);
		}

		static bool_type SetFileAttributes(const_pointer filename, size_type attr)
		{
			return FALSE != ::SetFileAttributesW(filename, attr);
		}

		static file_handle_type FindFirstFile(const_pointer path, find_data_type* find_data)
		{
			return ::FindFirstFileW(path, find_data);
		}

	#if defined(_WIN32_WINNT) &&  _WIN32_WINNT >= 0x0400
		static file_handle_type FindFirstFileEx(const_pointer path, FINDEX_INFO_LEVELS finfo_level_id, find_data_type* find_data, FINDEX_SEARCH_OPS flags, void* search_filter, size_type additional_flags)
		{
			return ::FindFirstFileExW(path, finfo_level_id, find_data, flags, search_filter, additional_flags);
		}
	#endif /* _WIN32_WINNT >= 0x0400 */

		static bool_type FindNextFile(file_handle_type hfile, find_data_type* find_data)
		{
			return FALSE != ::FindNextFileW(hfile, find_data);
		}
		
		static bool_type SetCurrentDirectory(const_pointer dir)
		{
			return FALSE != ::SetCurrentDirectoryW(dir);
		}

		static size_type GetCurrentDirectory(size_type size, pointer buf)
		{
			return ::GetCurrentDirectoryW(size, buf);
		}
		static bool_type drive_exists(char_type drive_char)
		{
			size_type const drives_mask = ::GetLogicalDrives();
			return 0 != ((0x01 << (string_traits_type::to_upper(drive_char) - L'A')) & drives_mask);
		}

		static size_type get_drive_type(char_type drive_char)
		{
			char_type drive[] = { L'?', L':', L'\\', L'\0' };
			drive[0] = drive_char;
			return ::GetDriveTypeW(drive);
		}
};

/*!\brief filesystem_traits class
 *
 * \param C The character type
 *
 * \ingroup extl_group_filesystem
 */
template < typename_param_k C >
struct filesystem_traits 
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
		typedef	filesystem_traits<char_type>									class_type;
		typedef system_traits<char_type>										system_traits_type;
		typedef path_traits<char_type>											path_traits_type;
		typedef win_string_traits<char_type, std_char_traits<char_type> >		string_traits_type;
		typedef filesystem_traits_helper_<char_type>							filesystem_traits_helper;
		typedef	DWORD															size_type;
		typedef	e_ptrdiff_t														difference_type;
		typedef	e_int_t															int_type;
		typedef	e_bool_t														bool_type;
		typedef	HANDLE															handle_type;
		typedef	size_type														code_type;
		typedef handle_type														file_handle_type;
		typedef typename_type_k stat_data_traits<char_type>::stat_data_type		stat_data_type;
		typedef typename_type_k stat_data_traits<char_type>::find_data_type		find_data_type;
		typedef typename_type_k stat_data_traits<char_type>::fstat_data_type	fstat_data_type;
		typedef typename_type_k path_traits_type::attached_string_type			attached_path_string_type;
		typedef typename_type_k path_traits_type::stack_string_type				stack_path_string_type;
		typedef typename_type_k path_traits_type::scoped_string_type			scoped_path_string_type;
		typedef typename_type_k path_traits_type::path_entry_type			path_entry_type;

	#ifdef EXTL_64BIT_INT_SUPPORT
		typedef e_uint64_t														file_size_type;
	#else
		typedef e_uint32_t														file_size_type;
	#endif

	///	@}

	/// \name Attributes
	/// @{
		public:
			/// Gets the size of a given file
			static file_size_type get_file_size(file_handle_type hfile);
			/// Returns \c true if a file exists
			static bool_type file_exists(const_pointer filename);

			/// Gets the information by a given path
			static bool_type get_stat(const_pointer path, stat_data_type *stat_data);
			/// Gets the information by a given file handle
			static bool_type get_fstat(file_handle_type hfile, fstat_data_type *fstat_data);

			/// Sets the file attributes by a given path
			static bool_type set_file_attr(const_pointer path, size_type attr);
			/// Gets the attributes of the file of a given path
			static size_type get_file_attr(const_pointer path);

			/// Returns \c true if the given path represents a file
			static bool_type is_file(const_pointer path);
			/// Returns \c true if the given stat info represents a file
			static bool_type is_file(stat_data_type const* stat_data);
			/// Returns \c true if the given stat info represents a file
			static bool_type is_file(fstat_data_type const* stat_data);

			/// Returns \c true if the given path represents a directory
			static bool_type is_dir(const_pointer path);
			/// Returns \c true if the given stat info represents a directory
			static bool_type is_dir(stat_data_type const* stat_data);
			/// Returns \c true if the given stat info represents a directory
			static bool_type is_dir(fstat_data_type const* stat_data);

			/// Returns \c true if the given path represents a read-only entry
			static bool_type is_readonly(const_pointer path);
			/// Returns \c true if the given stat info represents a read-only entry
			static bool_type is_readonly(stat_data_type const* stat_data);
			/// Returns \c true if the given stat info represents a read-only entry
			static bool_type is_readonly(fstat_data_type const* stat_data);

			/// Returns \c true if the given path represents a hidden entry
			static bool_type is_hidden(const_pointer path);
			/// Returns \c true if the given stat info represents a hidden entry
			static bool_type is_hidden(stat_data_type const* stat_data);
			/// Returns \c true if the given stat info represents a hidden entry
			static bool_type is_hidden(fstat_data_type const* stat_data);

			/// Returns \c true if the given path represents a normal entry
			static bool_type is_normal(const_pointer path);
			/// Returns \c true if the given stat info represents a normal entry
			static bool_type is_normal(stat_data_type const* stat_data);
			/// Returns \c true if the given stat info represents a normal entry
			static bool_type is_normal(fstat_data_type const* stat_data);

			/// Returns \c true if the given path represents a system entry
			static bool_type is_system(const_pointer path);
			/// Returns \c true if the given stat info represents a system entry
			static bool_type is_system(stat_data_type const* stat_data);
			/// Returns \c true if the given stat info represents a system entry
			static bool_type is_system(fstat_data_type const* stat_data);

			/// Gets the current directory
			static size_type get_current_directory(pointer buf, size_type size);
			/// Sets the current directory
			static bool_type set_current_directory(const_pointer dir);

			/*!\brief Gets the relative path
			 * 
			 * \note Returns the size of result path, if dest == NULL
			 */
			static size_type get_relative_path(const_pointer src, size_type src_size, pointer dest, size_type dest_size);
			/*!\brief Gets the relative path
			 * 
			 * \note Returns the size of result path, if dest == NULL
			 */
			static size_type get_relative_path(const_pointer src, pointer dest, size_type dest_size);
			/*!\brief Gets the absolute path
			 * 
			 * \note Returns the size of result path, if dest == NULL
			 */
			static size_type get_absolute_path(const_pointer src, size_type src_size, pointer dest, size_type dest_size);
			/*!\brief Gets the absolute path
			 * 
			 * \note Returns the size of result path, if dest == NULL
			 */
			static size_type get_absolute_path(const_pointer src, pointer dest, size_type dest_size);

			/// Indicates whether the given drive currently exists on the system
			static bool_type drive_exists(char_type drive_char);
			/// Gets the type of the drive
			static size_type get_drive_type(char_type drive_char);
			/// Returns \c true if the given drive is CDROM 
			static size_type is_drive_cdrom(char_type drive_char);
			/// Returns \c true if the given drive is FIXED 
			static size_type is_drive_fixed(char_type drive_char);
			/// Returns \c true if the given drive is RAMDISK 
			static size_type is_drive_ramdisk(char_type drive_char);
			/// Returns \c true if the given drive is REMOVABLE
			static size_type is_drive_removable(char_type drive_char);
			/// Returns \c true if the given drive is REMOTE
			static size_type is_drive_remote(char_type drive_char);
			/// Returns \c true if the given drive is UNKNOWN
			static size_type is_drive_unknown(char_type drive_char);
	/// @}

	/// \name File Enumeration Win32 Api
	/// @{
		public:
			/*!\brief Finds the first file or directory - Win32 Api
			 *
			 * e.g.  path: "C:\\*.*"
			 * \note path must not be directory
			 *
			 * \code
				filesystem_traits<e_tchar_t>::find_data_type fd;
				filesystem_traits<e_tchar_t>::file_handle_type hfile = 
					filesystem_traits<e_tchar_t>::find_first_file(_T("C:\\*.*"), &fd);
				if (INVALID_HANDLE_VALUE != hfile)
				{
					do
					{
						e_t_printf(_T("%s\n"), fd.cFileName);
					}
					while (filesystem_traits<e_tchar_t>::find_next_file(hfile, &fd));

					filesystem_traits<e_tchar_t>::find_file_close(hfile);
				}
			 * \endcode
			 */
			static file_handle_type find_first_file(const_pointer path, find_data_type* find_data);
		#if defined(_WIN32_WINNT) &&  _WIN32_WINNT >= 0x0400
			/// Finds the first file or directory - NT4+-only - Win32 Api
			static file_handle_type find_first_file_ex(const_pointer path, FINDEX_SEARCH_OPS flags, find_data_type *find_data);
		#endif /* _WIN32_WINNT >= 0x0400 */
			/// Finds the next file or directory - Win32 Api
			static bool_type find_next_file(file_handle_type hfile, find_data_type* find_data);
			/// Closes the handle of the file search - Win32 Api
			static void find_file_close(file_handle_type hfile);

			/// The file enumeration information type
			struct file_entry_type
			{
				public:
					/// enumeration flag
					enum enum_flag
					{
						en_filter_file = 1									//!< filter out files
					,	en_filter_dir = 2									//!< filter out directories
					,	en_filter_readonly = 4								//!< filter out readonly files
					,	en_filter_hidden = 8								//!< filter out hidden files
					,	en_filter_dots = 16									//!< filter out \c '.' or ".."

					,	en_enum_all = en_filter_dots						//!< enumeration of all file-system entries
					,	en_enum_dir = en_enum_all | en_filter_file			//!< enumeration of all directories
					,	en_enum_file = en_enum_all | en_filter_dir			//!< enumeration of all files
					};

					/// Enumeration flag Type
					typedef enum_flag						enum_flag_type;	

				/// \name Members
				/// @{
				private:
					file_handle_type						m_handle;
					find_data_type							m_data;
					enum_flag								m_flag;
				/// @}

				private:
					friend struct filesystem_traits<C>;

				public:
					/// The Constructor
					explicit_k file_entry_type(enum_flag_type flag = en_enum_all)
						: m_handle(NULL)
						, m_data(find_data_type())
						, m_flag(flag)
					{}

				/// \name Attributes
				/// @{
				public:
					file_handle_type handle() const	{ return m_handle;			}
					find_data_type data() const		{ return m_data;			}
					const_pointer filename() const	{ return m_data.cFileName;	}
					size_type flag() const			{ return m_flag;			}
					bool_type is_file() const		{ return filesystem_traits<C>::is_file(&m_data);		}
					bool_type is_dir() const		{ return filesystem_traits<C>::is_dir(&m_data);			}
					bool_type is_readonly() const	{ return filesystem_traits<C>::is_readonly(&m_data);	}
					bool_type is_hidden() const		{ return filesystem_traits<C>::is_hidden(&m_data);		}
					bool_type is_normal() const		{ return filesystem_traits<C>::is_normal(&m_data);		}
					bool_type is_system() const		{ return filesystem_traits<C>::is_system(&m_data);		}
					bool_type is_dots() const		{ return path_traits_type::is_dots(filename());			}
				/// @}
			};

			/*!\brief Starts enumerating files from the given directory - Common Interface
			 *
			 * e.g.  path: "C:\\*.*"
			 * \note path must not be directory and not be nested enumeration
			 *
			 * \code
				filesystem_traits<e_tchar_t>::file_entry_type fi;
				if (filesystem_traits<e_tchar_t>::file_enum_start(_T("C:\\*.*"), fi))
				{
					do
					{
						e_t_printf(_T("%s\n"), fi.filename());
					}
					while (filesystem_traits<e_tchar_t>::file_enum(fi));

					filesystem_traits<e_tchar_t>::file_enum_stop(fi);
				}
			 * \endcode
			 */
			static bool_type file_enum_start(const_pointer path, file_entry_type& fi);
			/// Enumerates files  - Common Interface
			static bool_type file_enum(file_entry_type& fi);
			/// Stop enumerating files  - Common Interface
			static void file_enum_stop(file_entry_type& fi);
	/// @}

	/// \name Control
	/// @{
		public:
			/// Creates a directory
			static bool_type create_directory(const_pointer dir, bool_type is_failed_if_exists = e_false_v);
			/// Deletes a directory
			static bool_type remove_directory(const_pointer dir, bool_type is_failed_if_nonempty = e_false_v);

			/// Delete a file
			static bool_type delete_file(const_pointer filename);
			/// Rename a file
			static bool_type rename_file(const_pointer old_filename, const_pointer new_filename);
			/// Copy a file
			static bool_type copy_file(const_pointer src_filename, const_pointer dest_filename, bool_type is_fail_if_exists = e_false_v);

			/// Create / open a file - Win32 Api
			static file_handle_type create_file(const_pointer filename, size_type desired_access, size_type share_mode, LPSECURITY_ATTRIBUTES sa, size_type creation_disposition, size_type flag_and_attributes, file_handle_type template_file);
			/// Closes the given file handle - Win32 Api
			static bool_type close_file(file_handle_type hfile);
	/// @}
};
/* ///////////////////////////////////////////////////////////////////////
 * Macro
 */

/* Template declaration */
#ifdef EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
#	undef EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
#endif

#define EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL	template< typename_param_k C >

/* Class qualification */
#ifdef EXTL_FILESYSTEM_TRAITS_QUAL
#	undef EXTL_FILESYSTEM_TRAITS_QUAL
#endif

#define EXTL_FILESYSTEM_TRAITS_QUAL				filesystem_traits<C>

/* Class qualification */
#ifdef EXTL_FILESYSTEM_TRAITS_RET_QUAL
#	undef EXTL_FILESYSTEM_TRAITS_RET_QUAL
#endif

#define EXTL_FILESYSTEM_TRAITS_RET_QUAL(ret_type)	\
					typename_type_ret_k EXTL_FILESYSTEM_TRAITS_QUAL::ret_type \
					EXTL_FILESYSTEM_TRAITS_QUAL
/* ///////////////////////////////////////////////////////////////////////
 * Implemention
 */
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::create_directory(const_pointer dir, bool_type is_failed_if_exists)
{
	EXTL_ASSERT(NULL != dir);
	if (file_exists(dir))
	{
		if (is_failed_if_exists) return e_false_v;
		else return e_true_v;
	}
	return filesystem_traits_helper::CreateDirectory(dir, NULL);
}

EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::remove_directory(const_pointer dir, bool_type is_failed_if_nonempty)
{
	EXTL_ASSERT(NULL != dir);
	EXTL_ASSERT(is_dir(dir));

	if (!is_failed_if_nonempty)
	{
		stack_path_string_type dir_path(dir);

		// Appends "\\"
		dir_path.ensure_push_back(path_traits_type::path_name_sep());

		file_entry_type fi;
		if (file_enum_start((dir_path + path_traits_type::pattern_all()).c_str(), fi))
		{
			do
			{
				if (fi.is_dots()) continue;

				stack_path_string_type path(dir_path);
				path += fi.filename();

				set_file_attr(path.c_str(), FILE_ATTRIBUTE_NORMAL); 
				if (fi.is_dir())
				{
					remove_directory(path.c_str(), e_false_v);
				}
				else if (fi.is_file())
				{  
					delete_file(path.c_str());
				}
			}
			while (file_enum(fi));
			file_enum_stop(fi);
		}
	}

	return filesystem_traits_helper::RemoveDirectory(dir);
}

EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::delete_file(const_pointer filename)
{
	EXTL_ASSERT(NULL != filename);
	return filesystem_traits_helper::DeleteFile(filename);
}

EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::rename_file(const_pointer old_filename, const_pointer new_filename)
{
	EXTL_ASSERT(NULL != old_filename);
	EXTL_ASSERT(NULL != new_filename);
	return filesystem_traits_helper::MoveFile(old_filename, new_filename);
}

EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::copy_file(const_pointer src_filename, const_pointer dest_filename, bool_type is_fail_if_exists)
{
	EXTL_ASSERT(NULL != src_filename);
	EXTL_ASSERT(NULL != dest_filename);
	return filesystem_traits_helper::CopyFile(src_filename, dest_filename, is_fail_if_exists);
}

EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(file_handle_type)::create_file(const_pointer filename, size_type desired_access, size_type share_mode, LPSECURITY_ATTRIBUTES sa, size_type creation_disposition, size_type flag_and_attributes, file_handle_type template_file)
{
	EXTL_ASSERT(NULL != filename);
	return filesystem_traits_helper::CreateFile(filename, desired_access, share_mode, sa, creation_disposition, flag_and_attributes, template_file);
}

EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::close_file(file_handle_type hfile)
{
	return system_traits_type::close_handle(hfile);
}

EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(file_size_type)::get_file_size(file_handle_type hfile)
{
	EXTL_ASSERT(NULL != hfile);
#ifdef EXTL_64BIT_INT_SUPPORT
	size_type high;
	size_type low = ::GetFileSize(hfile, &high);

	if (0xFFFFFFFF == low &&
		ERROR_SUCCESS != system_traits_type::get_last_error())
	{
		high = 0xFFFFFFFF;
	}

	return (static_cast<file_size_type>(high) << 32) | low;
#else
	return static_cast<file_size_type>(::GetFileSize(hfile, NULL));
#endif

}
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::file_exists(const_pointer filename)
{
	EXTL_ASSERT(NULL != filename);
	if(NULL == filename) return e_false_v;

	return 0xFFFFFFFF != filesystem_traits_helper::GetFileAttributes(filename);
}

EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::is_file(const_pointer path)
{
	EXTL_ASSERT(NULL != path);
	if(NULL == path) return e_false_v;

	size_type attr = filesystem_traits_helper::GetFileAttributes(path);
	return 0xFFFFFFFF != attr && FILE_ATTRIBUTE_DIRECTORY != (attr & FILE_ATTRIBUTE_DIRECTORY);
}

EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::is_file(stat_data_type const* stat_data)
{
	EXTL_ASSERT(NULL != stat_data);
	return FILE_ATTRIBUTE_DIRECTORY != (stat_data->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
}

EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::is_file(fstat_data_type const* stat_data)
{
	EXTL_ASSERT(NULL != stat_data);
	return FILE_ATTRIBUTE_DIRECTORY != (stat_data->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
}

EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::is_dir(const_pointer path)
{
	EXTL_ASSERT(NULL != path);
	if(NULL == path) return e_false_v;

	size_type attr = filesystem_traits_helper::GetFileAttributes(path);
	return 0xFFFFFFFF != attr && FILE_ATTRIBUTE_DIRECTORY == (attr & FILE_ATTRIBUTE_DIRECTORY);
}
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::is_dir(stat_data_type const* stat_data)
{
	EXTL_ASSERT(NULL != stat_data);
	return FILE_ATTRIBUTE_DIRECTORY == (stat_data->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
}
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::is_dir(fstat_data_type const* stat_data)
{
	EXTL_ASSERT(NULL != stat_data);
	return FILE_ATTRIBUTE_DIRECTORY == (stat_data->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
}
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::is_readonly(const_pointer path)
{
	EXTL_ASSERT(NULL != path);
	if(NULL == path) return e_false_v;

	size_type attr = filesystem_traits_helper::GetFileAttributes(path);
	return 0xFFFFFFFF != attr && FILE_ATTRIBUTE_READONLY == (attr & FILE_ATTRIBUTE_READONLY);
}
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::is_readonly(stat_data_type const* stat_data)
{
	EXTL_ASSERT(NULL != stat_data);
	return FILE_ATTRIBUTE_READONLY == (stat_data->dwFileAttributes & FILE_ATTRIBUTE_READONLY);
}
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::is_readonly(fstat_data_type const* stat_data)
{
	EXTL_ASSERT(NULL != stat_data);
	return FILE_ATTRIBUTE_READONLY == (stat_data->dwFileAttributes & FILE_ATTRIBUTE_READONLY);
}
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::is_hidden(const_pointer path)
{
	EXTL_ASSERT(NULL != path);
	if(NULL == path) return e_false_v;

	size_type attr = filesystem_traits_helper::GetFileAttributes(path);
	return 0xFFFFFFFF != attr && FILE_ATTRIBUTE_HIDDEN == (attr & FILE_ATTRIBUTE_HIDDEN);
}
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::is_hidden(stat_data_type const* stat_data)
{
	EXTL_ASSERT(NULL != stat_data);
	return FILE_ATTRIBUTE_HIDDEN == (stat_data->dwFileAttributes & FILE_ATTRIBUTE_HIDDEN);
}
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::is_hidden(fstat_data_type const* stat_data)
{
	EXTL_ASSERT(NULL != stat_data);
	return FILE_ATTRIBUTE_HIDDEN == (stat_data->dwFileAttributes & FILE_ATTRIBUTE_HIDDEN);
}
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::is_normal(const_pointer path)
{
	EXTL_ASSERT(NULL != path);
	if(NULL == path) return e_false_v;

	size_type attr = filesystem_traits_helper::GetFileAttributes(path);
	return 0xFFFFFFFF != attr && FILE_ATTRIBUTE_NORMAL == (attr & FILE_ATTRIBUTE_NORMAL);
}
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::is_normal(stat_data_type const* stat_data)
{
	EXTL_ASSERT(NULL != stat_data);
	return FILE_ATTRIBUTE_NORMAL == (stat_data->dwFileAttributes & FILE_ATTRIBUTE_NORMAL);
}
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::is_normal(fstat_data_type const* stat_data)
{
	EXTL_ASSERT(NULL != stat_data);
	return FILE_ATTRIBUTE_NORMAL == (stat_data->dwFileAttributes & FILE_ATTRIBUTE_NORMAL);
}
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::is_system(const_pointer path)
{
	EXTL_ASSERT(NULL != path);
	if(NULL == path) return e_false_v;

	size_type attr = filesystem_traits_helper::GetFileAttributes(path);
	return 0xFFFFFFFF != attr && FILE_ATTRIBUTE_SYSTEM == (attr & FILE_ATTRIBUTE_SYSTEM);
}
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::is_system(stat_data_type const* stat_data)
{
	EXTL_ASSERT(NULL != stat_data);
	return FILE_ATTRIBUTE_SYSTEM == (stat_data->dwFileAttributes & FILE_ATTRIBUTE_SYSTEM);
}
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::is_system(fstat_data_type const* stat_data)
{
	EXTL_ASSERT(NULL != stat_data);
	return FILE_ATTRIBUTE_SYSTEM == (stat_data->dwFileAttributes & FILE_ATTRIBUTE_SYSTEM);
}
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::get_stat(const_pointer path, stat_data_type *stat_data)
{
	EXTL_ASSERT(NULL != path);
	EXTL_ASSERT(NULL != stat_data);

	if(path_traits_type::is_rooted_drive(path))
	{
		stat_data->dwFileAttributes                 =   filesystem_traits_helper::GetFileAttributes(path);
		stat_data->ftCreationTime.dwLowDateTime     =   0;
		stat_data->ftCreationTime.dwHighDateTime    =   0;
		stat_data->ftLastAccessTime.dwLowDateTime   =   0;
		stat_data->ftLastAccessTime.dwHighDateTime  =   0;
		stat_data->ftLastWriteTime.dwLowDateTime    =   0;
		stat_data->ftLastWriteTime.dwHighDateTime   =   0;
		stat_data->nFileSizeHigh                    =   0;
		stat_data->nFileSizeLow                     =   0;
		for(size_type i = 0; i < 4; ++i)
		{
			stat_data->cFileName[i]             =   path[i];
			stat_data->cAlternateFileName[i]    =   path[i];
		}

		return 0xFFFFFFFF != stat_data->dwFileAttributes;
	}

	HANDLE  hfile = find_first_file(path, stat_data);

	return (INVALID_HANDLE_VALUE == hfile) ? e_false_v : (find_file_close(hfile), e_true_v);
}

EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::set_file_attr(const_pointer path, size_type attr)
{
	return filesystem_traits_helper::SetFileAttributes(path, attr);
}

EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(size_type)::get_file_attr(const_pointer path)
{
	return filesystem_traits_helper::GetFileAttributes(path);
}

EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::get_fstat(file_handle_type hfile, fstat_data_type *fstat_data)
{
	EXTL_ASSERT(INVALID_HANDLE_VALUE != hfile && NULL != hfile);
	EXTL_ASSERT(NULL != fstat_data);
	return FALSE != ::GetFileInformationByHandle(hfile, fstat_data);
}

EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(file_handle_type)::find_first_file(const_pointer path, find_data_type* find_data)
{
	EXTL_ASSERT(NULL != path);
	EXTL_ASSERT(NULL != find_data);
	
	return filesystem_traits_helper::FindFirstFile(path, find_data);
}
#if defined(_WIN32_WINNT) &&  _WIN32_WINNT >= 0x0400
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(file_handle_type)::find_first_file_ex(const_pointer path, FINDEX_SEARCH_OPS flags, find_data_type* find_data)
{
	EXTL_ASSERT(NULL != path);
	EXTL_ASSERT(NULL != find_data);
	return filesystem_traits_helper::FindFirstFileEx(path, FindExInfoStandard, find_data, flags, NULL, 0);
}
#endif /* _WIN32_WINNT >= 0x0400 */

EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::find_next_file(file_handle_type hfile, find_data_type* find_data)
{
	EXTL_ASSERT(INVALID_HANDLE_VALUE != hfile && NULL != hfile);
	EXTL_ASSERT(NULL != find_data);
	return filesystem_traits_helper::FindNextFile(hfile, find_data);
}

EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline void EXTL_FILESYSTEM_TRAITS_QUAL::find_file_close(file_handle_type hfile)
{
	EXTL_ASSERT(INVALID_HANDLE_VALUE != hfile && NULL != hfile);
	::FindClose(hfile);
}
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::file_enum_start(const_pointer path, file_entry_type& fi)
{
	EXTL_ASSERT(NULL != path);
	fi.m_handle = find_first_file(path, &fi.m_data);
	bool_type res = INVALID_HANDLE_VALUE != fi.m_handle && NULL != fi.m_handle;
	if (res)
	{
		if ((fi.flag() & file_entry_type::en_filter_file) && fi.is_file())
		{
			res = file_enum(fi);
		}
		else if ((fi.flag() & file_entry_type::en_filter_dir) && fi.is_dir())
		{
			res = file_enum(fi);
		}
		else if ((fi.flag() & file_entry_type::en_filter_readonly) && fi.is_readonly())
		{
			res = file_enum(fi);
		}
		else if ((fi.flag() & file_entry_type::en_filter_hidden) && fi.is_hidden())
		{
			res = file_enum(fi);
		}
		else if ((fi.flag() & file_entry_type::en_filter_dots) && fi.is_dots())
		{
			res = file_enum(fi);
		}

		if (!res)
		{
			file_enum_stop(fi);
		}
	}
	return res;
}
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::file_enum(file_entry_type& fi)
{
	EXTL_ASSERT(INVALID_HANDLE_VALUE != fi.m_handle && NULL != fi.m_handle);
	bool_type res = find_next_file(fi.m_handle, &fi.m_data);

	if (res)
	{
		if ((fi.flag() & file_entry_type::en_filter_file) && fi.is_file())
		{
			res = file_enum(fi);
		}
		else if ((fi.flag() & file_entry_type::en_filter_dir) && fi.is_dir())
		{
			res = file_enum(fi);
		}
		else if ((fi.flag() & file_entry_type::en_filter_readonly) && fi.is_readonly())
		{
			res = file_enum(fi);
		}
		else if ((fi.flag() & file_entry_type::en_filter_hidden) && fi.is_hidden())
		{
			res = file_enum(fi);
		}
		else if ((fi.flag() & file_entry_type::en_filter_dots) && fi.is_dots())
		{
			res = file_enum(fi);
		}
	}
	return res;
}

EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline void EXTL_FILESYSTEM_TRAITS_QUAL::file_enum_stop(file_entry_type& fi)
{
	EXTL_ASSERT(INVALID_HANDLE_VALUE != fi.m_handle && NULL != fi.m_handle);
	find_file_close(fi.m_handle);
	fi.m_handle = NULL;
}

EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(size_type)::get_current_directory(pointer buf, size_type size)
{
	return filesystem_traits_helper::GetCurrentDirectory(size, buf);
}

EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::set_current_directory(const_pointer dir)
{
	return filesystem_traits_helper::SetCurrentDirectory(dir);
}

EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(bool_type)::drive_exists(char_type drive_char)
{
	return filesystem_traits_helper::drive_exists(drive_char);
}

EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(size_type)::get_drive_type(char_type drive_char)
{
	return filesystem_traits_helper::get_drive_type(drive_char);
}

EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(size_type)::is_drive_cdrom(char_type drive_char)
{
	return DRIVE_CDROM == get_drive_type(drive_char);
}
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(size_type)::is_drive_fixed(char_type drive_char)
{
	return DRIVE_FIXED == get_drive_type(drive_char);
}
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(size_type)::is_drive_ramdisk(char_type drive_char)
{
	return DRIVE_RAMDISK == get_drive_type(drive_char);
}
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(size_type)::is_drive_removable(char_type drive_char)
{
	return DRIVE_REMOVABLE == get_drive_type(drive_char);
}
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(size_type)::is_drive_remote(char_type drive_char)
{
	return DRIVE_REMOTE == get_drive_type(drive_char);
}
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(size_type)::is_drive_unknown(char_type drive_char)
{
	return DRIVE_UNKNOWN == get_drive_type(drive_char);
}

EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(size_type)::get_absolute_path(const_pointer src, size_type src_size, pointer dest, size_type dest_size)
{
	EXTL_ASSERT(NULL != src);
	if (NULL == src || 0 == src_size) return 0;

	size_type res_size;
	if (path_traits_type::is_absolute_path(src))
	{
		if (NULL == dest)
		{
			res_size = src_size;
		}
		else
		{
			res_size = xtl_min(src_size, dest_size);
			string_traits_type::copy(dest, src, res_size);
			dest[res_size] = char_type('\0');
		}
		return res_size;
	}
	else
	{
		char_type dir_buf[path_traits_type::en_max_size];
		res_size = get_current_directory(dir_buf, path_traits_type::en_max_size);
		if (0 == res_size) return 0;

		// Enumerates path entries
		path_entry_type ei(path_entry_type::en_filter_dot);
		if (path_traits_type::entry_enum_start(src, ei))
		{
			do
			{
				// if ei.name() == ".."
				if (!string_traits_type::compare(ei.name(), path_traits_type::dotdot()))
				{
					path_traits_type::pop_sep(dir_buf);
					path_traits_type::pop(dir_buf);

				}
				else 
				{
					path_traits_type::push_sep(dir_buf);
					path_traits_type::push(dir_buf, ei.name());
				}
			}
			while (path_traits_type::entry_enum(ei));
			path_traits_type::entry_enum_stop(ei);
		}

		// Returns the result
		res_size = string_traits_type::length(dir_buf);
		res_size = xtl_min(res_size, dest_size);
		if (NULL != dest)
		{
			string_traits_type::copy(dest, dir_buf, res_size);
			dest[res_size] = char_type('\0');
		}
	}
	return res_size;
}
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(size_type)::get_absolute_path(const_pointer src, pointer dest, size_type dest_size)
{
	return get_absolute_path(src, (NULL != src)? string_traits_type::length(src) : 0, dest, dest_size);
}
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(size_type)::get_relative_path(const_pointer src, size_type src_size, pointer dest, size_type dest_size)
{
	EXTL_ASSERT(NULL != src);
	if (NULL == src || 0 == src_size) return 0;

	size_type res_size;
	if (!path_traits_type::is_absolute_path(src))
	{
		if (NULL == dest)
		{
			res_size = src_size;
		}
		else
		{
			res_size = xtl_min(src_size, dest_size);
			string_traits_type::copy(dest, src, res_size);
			dest[res_size] = char_type('\0');
		}
		return res_size;
	}
	else
	{
		char_type dir_buf[path_traits_type::en_max_size];
		res_size = get_current_directory(dir_buf, path_traits_type::en_max_size);
		if (0 == res_size) return 0;

		// Ensures to remove the last path separator
		path_traits_type::pop_sep(dir_buf);
		
		path_entry_type cur_dir_ei(path_entry_type::en_filter_dot);
		path_entry_type src_ei(path_entry_type::en_filter_dot);

		char_type res_buf[path_traits_type::en_max_size];
		res_buf[0] = char_type('\0');

		if (path_traits_type::entry_enum_start(dir_buf, cur_dir_ei) &&
			path_traits_type::entry_enum_start(src, src_ei))
		{
			do
			{
				/* Finds the position of the first different entry between dir_buf and src
				 * e.g.
				 * src:		"C:\\dir1\\dir2\\dir3\\file.txt"
				 * dir_buf:	"C:\\dir1\\dir4\\dir5\\"
				 * pos:				   |
				 */
				if (0 != string_traits_type::compare_nocase(cur_dir_ei.name(), src_ei.name()))
				{
					// e.g. push "..\\..\\"
					do
					{
						path_traits_type::push(res_buf, path_traits_type::dotdot());
					}
					while (path_traits_type::entry_enum(cur_dir_ei));

					// e.g. push "dir2\\dir3\\file.txt"
					path_traits_type::push(res_buf, &src[src_ei.pos()]);
					break;
				}

				bool_type res_cur_dir_ei = path_traits_type::entry_enum(cur_dir_ei);
				bool_type res_src_ei = path_traits_type::entry_enum(src_ei);

				/* e.g.
				 * src:		"C:\\dir1\\dir2\\dir3\\file.txt"
				 * dir_buf:	"C:\\dir1\\dir2"
				 */
				if (!res_cur_dir_ei && res_src_ei)
				{
					// e.g. push "dir3\\file.txt"
					path_traits_type::push(res_buf, &src[src_ei.pos()]);
					break;
				}
				/* e.g.
				 * src:		"C:\\dir1\\dir2"
				 * dir_buf:	"C:\\dir1\\dir2\\dir3"
				 */
				else if (res_cur_dir_ei && !res_src_ei)
				{
					// e.g. push ".."
					do
					{
						path_traits_type::push(res_buf, path_traits_type::dotdot());
					}
					while (path_traits_type::entry_enum(cur_dir_ei));
					break;
				}
				/* e.g.
				 * src:		"C:\\dir1\\dir2"
				 * dir_buf:	"C:\\dir1\\dir2"
				 */
				else if (!res_cur_dir_ei && !res_src_ei)
				{
					// push "."
					path_traits_type::push(res_buf, path_traits_type::dot());
					break;
				}
			}
			while (1);

			path_traits_type::entry_enum_stop(cur_dir_ei);
			path_traits_type::entry_enum_stop(src_ei);
		}

		// Returns the result
		res_size = string_traits_type::length(res_buf);
		res_size = xtl_min(res_size, dest_size);
		if (NULL != dest)
		{
			string_traits_type::copy(dest, res_buf, res_size);
			dest[res_size] = char_type('\0');
		}
	}
	return res_size;
}
EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
inline EXTL_FILESYSTEM_TRAITS_RET_QUAL(size_type)::get_relative_path(const_pointer src, pointer dest, size_type dest_size)
{
	return get_relative_path(src, (NULL != src)? string_traits_type::length(src) : 0, dest, dest_size);
}
/* //////////////////////////////////////////////////////////////////// */
#undef EXTL_FILESYSTEM_TRAITS_TEMPLATE_DECL
#undef EXTL_FILESYSTEM_TRAITS_QUAL
#undef EXTL_FILESYSTEM_TRAITS_RET_QUAL

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
#ifdef EXTL_FILESYSTEM_TRAITS_TEST_ENABLE
#	include "unit_test/filesystem_traits_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WIN_FILESYSTEM_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
