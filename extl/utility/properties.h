/* ///////////////////////////////////////////////////////////////////////
 * File:		properties.h		
 *
 * Created:		08.04.01				
 * Updated:		08.05.05	
 *
 * Brief: The Properties Library
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_UTILITY_PROPERTIES_H
#define EXTL_UTILITY_PROPERTIES_H

/*!\file properties.h
 * \brief The Properties Library
 *
 * [Note]
 * 1. Methods name: 
 * get_ + property name + const
 * set_ + property name
 *
 * 2. EXTL_EXTERNAL_PROPERTY_GET
 * Used in printf will be undefined 
 * undefined: printf("...",obj.property_value)
 * safe: printf("%d",static_cast<int>(obj.property_value))
 *
 * [Compatibility]
 * VC6.0: EXTL_STATIC_EXTERNAL_PROPERTY_### is not supported
 */
#ifndef __cplusplus
#	error properties.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h" 
#include "offset_of.h"

#if !defined(EXTL_UTILITY_PROPERTIES_SUPPORT)
#	error  properties.h	is not supported current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#ifdef EXTL_PROPERTY_DEFINE_OFFSET
#	undef EXTL_PROPERTY_DEFINE_OFFSET
#endif

#ifdef EXTL_EXTERNAL_PROPERTY_DEFINE_BEGIN
#	undef EXTL_EXTERNAL_PROPERTY_DEFINE_BEGIN
#endif

#ifdef EXTL_EXTERNAL_PROPERTY_DEFINE_END
#	undef EXTL_EXTERNAL_PROPERTY_DEFINE_END
#endif

#ifdef EXTL_EXTERNAL_PROPERTY_GET
#	undef EXTL_EXTERNAL_PROPERTY_GET
#endif

/* //////////////////////////////////////////////////////////////////// */
/* EXTERNAL_PROPERTY:
 * EXTL_EXTERNAL_PROPERTY_DEFINE_BEGIN(C)		
 * EXTL_EXTERNAL_PROPERTY_GET(R, P)				
 * EXTL_EXTERNAL_PROPERTY_SET(R, P)				
 * EXTL_EXTERNAL_PROPERTY_GETSET(RG, RS, P)		
 * EXTL_EXTERNAL_PROPERTY_DEFINE_END()			
 * R: The reference type
 * P: The property name
 */ 
#if defined(EXTL_PROPERTY_SUPPORT)

/* ///////////////////////////////////////////////////////////////////////
 * Using compiler extensiblity
 */

#	define EXTL_EXTERNAL_PROPERTY_DEFINE_BEGIN(C)								
#	define EXTL_EXTERNAL_PROPERTY_DEFINE_END()		

#	define EXTL_EXTERNAL_PROPERTY_GET(R, P)										\
					EXTL_PROPERTY_GET(R, P, get_##P);

#	define EXTL_EXTERNAL_PROPERTY_SET(R, P)										\
					EXTL_PROPERTY_SET(R, P, set_##P);

#	define EXTL_EXTERNAL_PROPERTY_GETSET(R, P)									\
					EXTL_PROPERTY_GETSET(R, P, get_##P, set_##P);

#else /* EXTL_PROPERTY_SUPPORT */
#	if !defined(EXTL_COMPILER_IS_BORLAND)
/* ///////////////////////////////////////////////////////////////////////
 * Using union to compress them because every null-member will occupy one-byte space
 * 
	union
	{
		e_byte_t	property_start_tag;				
		external_property_get< ... > Value1;	
		external_property_get< ... > Value2;
		......
	};
 *
 */
#	define EXTL_PROPERTY_DEFINE_OFFSET(C)										\
		static e_size_t get_property_start_offset()								\
		{																		\
			return EXTL_OFFSET_OF(C, property_start_tag);						\
		}

#	define EXTL_EXTERNAL_PROPERTY_DEFINE_BEGIN(C)								\
		typedef	C	container_external_property_type;							\
		EXTL_PROPERTY_DEFINE_OFFSET(C)											\
		union																	\
		{																		\
			e_byte_t	property_start_tag;										\

#	define EXTL_EXTERNAL_PROPERTY_DEFINE_END()									};	

#	define EXTL_EXTERNAL_PROPERTY_GET(R, P)										\
		EXTL_NS(external_property_get)											\
		<																		\
			container_external_property_type									\
		,	R																	\
		,	&container_external_property_type::get_property_start_offset		\
		,	&container_external_property_type::get_##P							\
		>	P;

#	define EXTL_EXTERNAL_PROPERTY_SET(R, P)										\
		EXTL_NS(external_property_set)											\
		<																		\
			container_external_property_type									\
		,	R																	\
		,	&container_external_property_type::get_property_start_offset		\
		,	&container_external_property_type::set_##P							\
		>	P;

#	define EXTL_EXTERNAL_PROPERTY_GETSET(R, P)									\
		EXTL_NS(external_property_getset)										\
		<																		\
			container_external_property_type									\
		,	R																	\
		,	R																	\
		,	&container_external_property_type::get_property_start_offset		\
		,	&container_external_property_type::get_##P							\
		,	&container_external_property_type::set_##P							\
		>	P;

#	else
/* ///////////////////////////////////////////////////////////////////////
 * [Note]
 * BCC:
 * Every property will occupy one-byte space 
 * because the property with operator= can not be the member of union type
 *
	static e_size_t get_property_Value1_start_offset(){...}
	external_property_get< ... > Value1;	
	static e_size_t get_property_Value2_start_offset(){...}
	external_property_get< ... > Value2;
	......
 *
 */

#	define EXTL_PROPERTY_DEFINE_OFFSET(C, P)									\
		static e_size_t get_property_##P##_start_offset()						\
		{																		\
			return EXTL_OFFSET_OF(C, P);										\
		}

#	define EXTL_EXTERNAL_PROPERTY_DEFINE_BEGIN(C)								\
		typedef	C	container_external_property_type;				

#	define EXTL_EXTERNAL_PROPERTY_DEFINE_END()								

#	define EXTL_EXTERNAL_PROPERTY_GET(R, P)										\
		EXTL_PROPERTY_DEFINE_OFFSET(container_external_property_type, P)		\
		EXTL_NS(external_property_get)											\
		<																		\
			container_external_property_type									\
		,	R																	\
		,	&container_external_property_type::get_property_##P##_start_offset	\
		,	&container_external_property_type::get_##P							\
		>	P;

#	define EXTL_EXTERNAL_PROPERTY_SET(R, P)										\
		EXTL_PROPERTY_DEFINE_OFFSET(container_external_property_type, P)		\
		EXTL_NS(external_property_set)											\
		<																		\
			container_external_property_type									\
		,	R																	\
		,	&container_external_property_type::get_property_##P##_start_offset	\
		,	&container_external_property_type::set_##P							\
		>	P;

#	define EXTL_EXTERNAL_PROPERTY_GETSET(R, P)									\
		EXTL_PROPERTY_DEFINE_OFFSET(container_external_property_type, P)		\
		EXTL_NS(external_property_getset)										\
		<																		\
			container_external_property_type									\
		,	R																	\
		,	&container_external_property_type::get_property_##P##_start_offset	\
		,	&container_external_property_type::get_##P							\
		,	&container_external_property_type::set_##P							\
		>	P;

#	endif /* !defined(EXTL_COMPILER_IS_BORLAND) */
#endif /* EXTL_PROPERTY_SUPPORT */

/*  ///////////////////////////////////////////////////////////////////////
 * STATIC_EXTERNAL_PROPERTY:
 * EXTL_STATIC_EXTERNAL_PROPERTY_DECLARE_BEGIN(C)			
 * EXTL_STATIC_EXTERNAL_PROPERTY_GET(R, P)						
 * EXTL_STATIC_EXTERNAL_PROPERTY_SET(R, P)					
 * EXTL_STATIC_EXTERNAL_PROPERTY_GETSET(RG, RS, P)			
 * EXTL_STATIC_EXTERNAL_PROPERTY_DECLARE_END()					
 *
 * EXTL_STATIC_EXTERNAL_PROPERTY_DEFINE_GET(R, P)						
 * EXTL_STATIC_EXTERNAL_PROPERTY_DEFINE_SET(R, P)					
 * EXTL_STATIC_EXTERNAL_PROPERTY_DEFINE_GETSET(RG, RS, P)				
 *
 * R: The reference type
 * P: The property name
 */

#define EXTL_STATIC_EXTERNAL_PROPERTY_DECLARE_BEGIN(C)							\
		typedef	C	container_static_external_property_type;		

#define EXTL_STATIC_EXTERNAL_PROPERTY_DECLARE_END()							
	
#if defined(EXTL_COMPILER_IS_MSVC) && _MSC_VER == 1200
#	define EXTL_STATIC_EXTERNAL_PROPERTY_GET(R, P)								\
		static EXTL_NS(static_external_property_get)							\
		<																		\
			R																	\
		,	&get_##P															\
		>	P;
#	define EXTL_STATIC_EXTERNAL_PROPERTY_SET(R, P)								\
		static EXTL_NS(static_external_property_set)							\
		<																		\
			R																	\
		,	&set_##P															\
		>	P;

#	define EXTL_STATIC_EXTERNAL_PROPERTY_GETSET(R, P)							\
		static EXTL_NS(static_external_property_getset)							\
		<																		\
			R																	\
		,	R																	\
		,	&get_##P															\
		,	&set_##P															\
		>	P;
#else /* defined(EXTL_COMPILER_IS_MSVC) && _MSC_VER == 1200 */
#	define EXTL_STATIC_EXTERNAL_PROPERTY_GET(R, P)								\
		static EXTL_NS(static_external_property_get)							\
		<																		\
			R																	\
		,	&container_static_external_property_type::get_##P					\
		>	P;

#	define EXTL_STATIC_EXTERNAL_PROPERTY_SET(R, P)								\
		static EXTL_NS(static_external_property_set)							\
		<																		\
			R																	\
		,	&container_static_external_property_type::set_##P					\
		>	P;


#	define EXTL_STATIC_EXTERNAL_PROPERTY_GETSET(R, P)							\
		static EXTL_NS(static_external_property_getset)							\
		<																		\
			R																	\
		,	R																	\
		,	&container_static_external_property_type::get_##P					\
		,	&container_static_external_property_type::set_##P					\
		>	P;

#endif /* defined(EXTL_COMPILER_IS_MSVC) && _MSC_VER == 1200 */

#define EXTL_STATIC_EXTERNAL_PROPERTY_DEFINE_GET(C, R, P)						\
		EXTL_NS(static_external_property_get)									\
		<																		\
			R																	\
		,	&C::get_##P															\
		>	C::P;

#define EXTL_STATIC_EXTERNAL_PROPERTY_DEFINE_SET(C, R, P)						\
		EXTL_NS(static_external_property_set)									\
		<																		\
			R																	\
		,	&C::set_##P															\
		>	C::P;

#define EXTL_STATIC_EXTERNAL_PROPERTY_DEFINE_GETSET(C, R, P)					\
		EXTL_NS(static_external_property_getset)								\
		<																		\
			R																	\
		,	R																	\
		,	&C::get_##P															\
		,	&C::set_##P															\
		>	C::P;
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_BEGIN_NAMESPACE 
EXTL_DETAIL_BEGIN_NAMESPACE 

/* ///////////////////////////////////////////////////////////////////////
 * Details
 */
template< e_bool_t R, e_bool_t W, e_bool_t S >
struct property_base
{
    enum { is_read		=	R	};
    enum { is_write		=	W	};	
    enum { is_static	=	S	};	
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_DETAIL_END_NAMESPACE
/*!\brief External property
 *
 * \param C: The container type 
 * \param R: The reference type
 * \param offset_func_ptr: The function pointer to caculate property offset
 * \param get_func_ptr: The function pointer to access property value
 *
 * \ingroup extl_group_utility
 */
template<	typename_param_k C							
		,	typename_param_k R							
		,	e_size_t (*offset_func_ptr)()					
		,	R (C::*get_func_ptr)() const				
		>
class external_property_get
	: public EXTL_NS_DETAIL(property_base)< e_true_v, e_false_v, e_false_v >
{
	public:
		typedef R															reference;		
		typedef C															container_type;	
		typedef external_property_get<C, R, offset_func_ptr, get_func_ptr>	class_type;

	public:
		operator reference() const
		{
			return get();
		}
		reference get() const
		{
			/* Caculates the offset of the property within the container */
			e_size_t offset = (*offset_func_ptr)(); 
			/* Gets the pointer to the container  */
			container_type* container = (container_type *)((e_byte_t*)this - offset);
			/* Invokes the get method */
			return (container->*get_func_ptr)();
		}
	private:
		/* Protect from modifying the property value */
		class_type& operator=(reference); /* BORLAND: Can not be used in union type */
};
/*!\brief External property
 *
 * \param C: The container type 
 * \param R: The reference type
 * \param offset_func_ptr: The function pointer to caculate property offset
 * \param set_func_ptr: The function pointer to modify property value
 *
 * \ingroup extl_group_utility
 */
template<	typename_param_k C							
		,	typename_param_k R							
		,	e_size_t (*offset_func_ptr)()					
		,	void (C::*set_func_ptr)(R)						
		>
class external_property_set
	: public EXTL_NS_DETAIL(property_base)< e_false_v, e_true_v, e_false_v >
{
	public:
		typedef R															reference;		
		typedef C															container_type;	
		typedef external_property_set<C, R, offset_func_ptr, set_func_ptr>	class_type;

	public:
		void set(reference value)
		{
			/* Caculates the offset of the property within the container */
			e_size_t offset = (*offset_func_ptr)(); 
			/* Gets the pointer to the container  */
			container_type* container = (container_type *)((e_byte_t*)this - offset);
			/* Invokes the set method */
			(container->*set_func_ptr)(value);
		}
	
		class_type& operator=(reference value)
		{
			set(value);
			return *this;
		}
};
/*!\brief External property
 *
 * \param C The container type 
 * \param RS The reference type of the get-property
 * \param RG The reference type of the set-property
 * \param offset_func_ptr The function pointer to caculate property offset
 * \param get_func_ptr The function pointer to access property value
 * \param set_func_ptr The function pointer to modify property value
 *
 * \ingroup extl_group_utility
 */
template<	typename_param_k C							
		,	typename_param_k RG							
		,	typename_param_k RS							
		,	e_size_t (*offset_func_ptr)()						
		,	RG (C::*get_func_ptr)() const					
		,	void (C::*set_func_ptr)(RS)						
		>
class external_property_getset
	: public EXTL_NS_DETAIL(property_base)< e_true_v, e_true_v, e_false_v >
{
	public:
		typedef RG															get_reference_type;			
		typedef RS															set_reference_type;			
		typedef C															container_type;	
		typedef external_property_getset
										<
											C
										,	RG
										,	RS
										,	offset_func_ptr
										,	get_func_ptr
										,	set_func_ptr
										>									class_type;

	public:
		operator get_reference_type() const
		{
			return get();
		}

		class_type& operator=(set_reference_type value) 
		{
			set(value);
			return *this;
		}

		get_reference_type get() const
		{
			e_size_t offset = (*offset_func_ptr)(); 
			container_type* container = (container_type *)((e_byte_t*)this - offset);
			return (container->*get_func_ptr)();
		}
		void set(set_reference_type value)
		{
			e_size_t offset = (*offset_func_ptr)(); 
			container_type* container = (container_type *)((e_byte_t*)this - offset);
			(container->*set_func_ptr)(value);
		}
};
/*!\brief Static external property
 *
 * \param R The reference type
 * \param get_func_ptr The function pointer to access property value
 *
 * \ingroup extl_group_utility
 */
template<	typename_param_k R						
		,	R (*get_func_ptr)(void)							
		>
class static_external_property_get
	: public EXTL_NS_DETAIL(property_base)< e_true_v, e_false_v, e_true_v >
{
	public:
		typedef R														reference;			
		typedef static_external_property_get<R, get_func_ptr>			class_type;

	public:
		operator reference() const
		{
			return get();
		}
		reference get() const
		{
			return (*get_func_ptr)();
		}
	private:
		class_type& operator=(reference); 
};
/*!\brief Static external property
 *
 * \param R The reference type of the set-property
 * \param set_func_ptr The function pointer to modify property value
 *
 * \ingroup extl_group_utility
 */
template<	typename_param_k R							
		,	void (*set_func_ptr)(R)							
		>
class static_external_property_set
	: public EXTL_NS_DETAIL(property_base)< e_false_v, e_true_v, e_true_v >
{
	public:
		typedef R														reference;			
		typedef static_external_property_set<R, set_func_ptr>			class_type;

	public:
		void set(reference value)
		{
			(*set_func_ptr)(value);
		}
	
		class_type& operator=(reference value) 
		{
			set(value);
			return *this;
		}
};
/*!\brief Static external property
 *
 * \param RS The reference type of the get-property
 * \param RG The reference type of the set-property
 * \param get_func_ptr The function pointer to access property value
 * \param set_func_ptr The function pointer to modify property value
 *
 * \ingroup extl_group_utility
 */
template<	typename_param_k RG								
		,	typename_param_k RS								
		,	RG (*get_func_ptr)(void)							
		,	void (*set_func_ptr)(RS)						
		>
class static_external_property_getset
	: public EXTL_NS_DETAIL(property_base)< e_true_v, e_true_v, e_true_v >
{
	public:
		typedef RG																get_reference_type;	
		typedef RS																set_reference_type;	
		typedef static_external_property_getset<RG, RS, get_func_ptr, set_func_ptr>		class_type;

	public:
		operator get_reference_type() const
		{
			return get();
		}
		class_type& operator=(set_reference_type value)
		{
			set(value);
			return *this;
		}
		get_reference_type get() const
		{
			return (*get_func_ptr)();
		}
		void set(set_reference_type value)
		{
			(*set_func_ptr)(value);
		}
};
/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#ifdef EXTL_UTILITY_PROPERTIES_TEST_ENABLE
#	include "unit_test/properties_test.h"
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_UTILITY_PROPERTIES_H */
/* //////////////////////////////////////////////////////////////////// */
