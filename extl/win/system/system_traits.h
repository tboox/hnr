/* ///////////////////////////////////////////////////////////////////////
 * File:		system_traits.h		
 *
 * Created:		08.06.13				
 * Updated:		08.06.13	
 *
 * Brief:		system_traits class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_PLATFORM_WIN_SYSTEM_TRAITS_H
#define EXTL_PLATFORM_WIN_SYSTEM_TRAITS_H

/*!\file system_traits.h
 * \brief system_traits class
 */

#ifndef __cplusplus
#	error system_traits.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../win.h"
#include "../string/win_string_traits.h"
#include "../filesystem/path_traits.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_BEGIN_WHOLE_NAMESPACE

template < typename_param_k C >
struct system_traits_helper_;

EXTL_TEMPLATE_SPECIALISATION
struct system_traits_helper_<e_char_t>
{
	public:
		typedef	e_char_t													char_type;
		typedef char_type													value_type;
		typedef value_type*													pointer;
		typedef value_type const*											const_pointer;
		typedef value_type&													reference;
		typedef value_type const&											const_reference;
		typedef	system_traits_helper_<char_type>							class_type;
		typedef	DWORD														size_type;
		typedef	e_ptrdiff_t													difference_type;
		typedef	e_int_t														int_type;
		typedef	e_bool_t													bool_type;
		typedef	HINSTANCE													module_type;
		typedef	HANDLE														handle_type;
		typedef	DWORD														code_type;

	public:
		static module_type GetModuleHandle()
		{
			return ::GetModuleHandleA(NULL);
		}
		static size_type GetModuleFileName(module_type module, pointer buf, size_type size)
		{
			return ::GetModuleFileNameA(module, buf, size);
		}
		static size_type GetSystemDirectory(pointer buf, size_type size)
		{
			return ::GetSystemDirectoryA(buf, size);
		}
		static size_type GetWindowsDirectory(pointer buf, size_type size)
		{
			return ::GetWindowsDirectoryA(buf, size);
		}
		static module_type LoadLibrary(const_pointer name)
		{
			return ::LoadLibraryA(name);
		}
		static size_type GetEnvironmentVariable(const_pointer name, pointer buf, size_type size)
		{
			return ::GetEnvironmentVariableA(name, buf, size);
		}
		static size_type ExpandEnvironmentStrings(const_pointer src, pointer dest, size_type size)
		{
			return ::ExpandEnvironmentStringsA(src, dest, size);
		}
};

EXTL_TEMPLATE_SPECIALISATION
struct system_traits_helper_<e_wchar_t>
{
	public:
		typedef	e_wchar_t													char_type;
		typedef char_type													value_type;
		typedef value_type*													pointer;
		typedef value_type const*											const_pointer;
		typedef value_type&													reference;
		typedef value_type const&											const_reference;
		typedef	system_traits_helper_<char_type>							class_type;
		typedef	DWORD														size_type;
		typedef	e_ptrdiff_t													difference_type;
		typedef	e_int_t														int_type;
		typedef	e_bool_t													bool_type;
		typedef	HINSTANCE													module_type;
		typedef	HANDLE														handle_type;
		typedef	DWORD														code_type;

	public:
		static module_type GetModuleHandle()
		{
			return ::GetModuleHandleW(NULL);
		}
		static size_type GetModuleFileName(module_type module, pointer buf, size_type size)
		{
			return ::GetModuleFileNameW(module, buf, size);
		}
		static size_type GetSystemDirectory(pointer buf, size_type size)
		{
			return ::GetSystemDirectoryW(buf, size);
		}
		static size_type GetWindowsDirectory(pointer buf, size_type size)
		{
			return ::GetWindowsDirectoryW(buf, size);
		}
		static module_type LoadLibrary(const_pointer name)
		{
			return ::LoadLibraryW(name);
		}
		static size_type GetEnvironmentVariable(const_pointer name, pointer buf, size_type size)
		{
			return ::GetEnvironmentVariableW(name, buf, size);
		}
		static size_type ExpandEnvironmentStrings(const_pointer src, pointer dest, size_type size)
		{
			return ::ExpandEnvironmentStringsW(src, dest, size);
		}
};
/*!\brief system_traits class
 *
 * \param C The character type
 *
 * \ingroup extl_group_system
 */
template < typename_param_k C >
struct system_traits
{
	///	\name Types
	///	@{
	public:
		typedef	C															char_type;
		typedef char_type													value_type;
		typedef value_type*													pointer;
		typedef value_type const*											const_pointer;
		typedef value_type&													reference;
		typedef value_type const&											const_reference;
		typedef	system_traits<char_type>									class_type;
		typedef win_string_traits<char_type, std_char_traits<char_type> >	string_traits_type;
		typedef system_traits_helper_<char_type>							system_traits_helper;
		typedef	DWORD														size_type;
		typedef	e_ptrdiff_t													difference_type;
		typedef	e_int_t														int_type;
		typedef	e_bool_t													bool_type;
		typedef	HINSTANCE													module_type;
		typedef	HANDLE														handle_type;
		typedef	DWORD														code_type;
		typedef FARPROC														far_proc_type;
		typedef path_traits<char_type>										path_traits_type;
		typedef typename_type_k path_traits_type::attached_string_type		attached_path_string_type;
		

	/// \name Module Paths
	/// @{
	public:
		/// Gets the full path name of the given module
		static module_type get_current_module()
		{
			return system_traits_helper::GetModuleHandle();
		}
		/// Gets the full path name of the current module
		static size_type get_current_filename(pointer buf, size_type size)
		{
			EXTL_ASSERT(NULL != buf || 0 == size);
			return get_module_filename(get_current_module(), buf, size);
		}
		/// Gets the full path name of the directory of the current module
		static size_type get_current_module_directory(pointer buf, size_type size)
		{
			EXTL_ASSERT(NULL != buf || 0 == size);
			return get_module_directory(get_current_module(), buf, size);
		}
		/// Gets the full path name of the given module
		static size_type get_module_filename(module_type module, pointer buf, size_type size)
		{
			EXTL_ASSERT(NULL != buf || 0 == size);
			return system_traits_helper::GetModuleFileName(module, buf, size);
		}
		/// Gets the full path name of the directory of the given module
		static size_type get_module_directory(module_type module, pointer buf, size_type size)
		{
			EXTL_ASSERT(NULL != buf || 0 == size);
			size_type res_size = get_module_filename(module, buf, size);
			
			if(0 != res_size && NULL != buf)
			{
				attached_path_string_type attached_str(buf, res_size);
				size_type pos = attached_str.rfind(path_traits_type::path_name_sep());
				if(attached_path_string_type::fof() != pos)
				{
					attached_str.resize(pos);
					res_size = attached_str.length();
				}
			}
			return res_size;
		}
		/// Gets the full path name of the system directory
		static size_type get_system_directory(pointer buf, size_type size)
		{
			EXTL_ASSERT(NULL != buf || 0 == size);
			return system_traits_helper::GetSystemDirectory(buf, size);
		}
		/// Gets the full path name of the windows directory
		static size_type get_windows_directory(pointer buf, size_type size)
		{
			EXTL_ASSERT(NULL != buf || 0 == size);
			return system_traits_helper::GetWindowsDirectory(buf, size);
		}
	/// @}

	/// \name Dynamic Loading
	/// @{
	public:
		/// Loads the given executable module
		static module_type load_library(const_pointer name)
		{
			return system_traits_helper::LoadLibrary(name);
		}
		/// Closes the given executable module
		static bool_type free_library(module_type module)
		{
			return FALSE != ::FreeLibrary(module);
		}
		/// Gets the address of the given procedure from the library
		static far_proc_type get_proc_address(module_type module, char const* proc_name)
		{
			EXTL_ASSERT(NULL != proc_name);
			return ::GetProcAddress(module, proc_name);
		}
	/// @}

	/// \name Error
	/// @{
	public:
		/// Gets the last error
		static code_type get_last_error()
		{
			return ::GetLastError();
		}
		/// Sets the last error
		static void set_last_error(code_type er = code_type())
		{
			::SetLastError(er);
		}
	/// @}

	/// \name Kernel object control
	/// @{
	public:
		/// Closes the given handle
		static bool_type close_handle(handle_type h)
		{
			return FALSE != ::CloseHandle(h);
		}
	/// @}

	/// \name Environment
	/// @{
	public:
		/// Gets an environment variable
		static size_type get_environment_variable(const_pointer name, pointer buf, size_type size)
		{
			EXTL_ASSERT(NULL != name);
			EXTL_ASSERT(NULL != buf || 0 == size);
			return system_traits_helper::GetEnvironmentVariable(name, buf, size);
		}
		/// Expands the given environment string
		static size_type expand_environment_strings(const_pointer src, pointer dest, size_type size)
		{
			EXTL_ASSERT(NULL != src);
			EXTL_ASSERT(NULL != dest || 0 == size);
			return system_traits_helper::ExpandEnvironmentStrings(src, dest, size);
		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
#ifdef EXTL_SYSTEM_TRAITS_TEST_ENABLE
#	include "unit_test/system_traits_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WIN_SYSTEM_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
