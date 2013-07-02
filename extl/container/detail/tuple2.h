/* ///////////////////////////////////////////////////////////////////////
 * File:		tuple2.h		
 *
 * Created:		08.07.21		
 * Updated:		08.07.24
 *
 * Brief: tuple2 class - compress empty type
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_DETAIL_TUPLE2_H
#define EXTL_CONTAINER_DETAIL_TUPLE2_H

/*!\file tuple2.h
 * \brief tuple2 class
 */
#ifndef __cplusplus
#	error tuple2.h need be supported by c++.
#endif

#ifndef EXTL_CONTAINER_TUPLE2_SUPPORT
#	error tuple2.h is not supported by current compiler.
#endif
/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../../algorithm/algorithm.h"

#ifdef EXTL_TYPE_TRAITS_CALL_TRAITS_SUPPORT
#	include "../../type/traits/call_traits.h"
#endif

/*#ifdef EXTL_TYPE_TRAITS_IS_SAME_SUPPORT
#	include "../../type/traits/is_same.h"
#endif*/

#ifdef EXTL_TYPE_TRAITS_IS_EMPTY_SUPPORT
#	include "../../type/traits/is_empty.h"
#endif

/*#ifdef EXTL_TYPE_TRAITS_REMOVE_CV_SUPPORT
#	include "../../type/traits/remove_cv.h"
#endif*/

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

template<	typename_param_k H = e_null_t
		,	typename_param_k T = e_null_t
		>
struct tuple2;

// Compress the size of tuple2
#if defined(EXTL_TYPE_TRAITS_IS_SAME_SUPPORT) && \
		defined(EXTL_TYPE_TRAITS_IS_EMPTY_SUPPORT) && \
			/*defined(EXTL_TYPE_TRAITS_REMOVE_CV_SUPPORT) &&*/ \
				defined(EXTL_MEMBER_TEMPLATE_CLASS_SUPPORT)

/* note: 
 * H == T , H and T are both empty
 * We must store an instatnce of H or T because &get_head() != &get_tail()
 *
 * H == T , H or T are not empty
 * We need store an instatnce of H or T

 * H == T , neither H nor T are empty
 * We need store instatnces of H and T
 *
 * So we remove specialization about is_same == e_true_v 
 */
template<	e_bool_t is_same
		,	e_bool_t is_head_empty
		,	e_bool_t is_tail_empty
		>
struct tuple2_impl
{
	template<	typename_param_k H
			,	typename_param_k T
			>
	struct impl
	{
		public:
			typedef impl														class_type;
			typedef H															head_type;
			typedef T															tail_type;
			typedef typename_type_k call_traits<head_type>::param_type			head_param_type;
			typedef typename_type_k call_traits<head_type>::reference			head_reference;
			typedef typename_type_k call_traits<head_type>::const_reference		head_const_reference;
			typedef typename_type_k call_traits<tail_type>::param_type			tail_param_type;
			typedef typename_type_k call_traits<tail_type>::reference			tail_reference;
			typedef typename_type_k call_traits<tail_type>::const_reference		tail_const_reference;
	
		private:
			head_type															m_head;
			tail_type															m_tail;

		public:
			impl() 
				: m_head(), m_tail() {}

			explicit_k impl(head_param_type h) 
				: m_head(h), m_tail() {}

			impl(head_param_type h, tail_param_type t) 
				: m_head(h), m_tail(t) {}

			impl(class_type const& rhs) 
				: m_head(rhs.m_head), m_tail(rhs.m_tail) {}

			template<	typename_param_k T0
					,	typename_param_k T1
					,	typename_param_k T2
					,	typename_param_k T3
					,	typename_param_k T4
					,	typename_param_k T5
					,	typename_param_k T6
					,	typename_param_k T7
					,	typename_param_k T8
					,	typename_param_k T9
					>
			impl(T0& t0, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, T9& t9)
				: m_head(t0), m_tail(t1, t2, t3, t4, t5, t6, t7, t8, t9, cnull()) 
			{}

		public:
			void swap(class_type& rhs)
			{
				std_swap(m_head, rhs.m_head);
				std_swap(m_tail, rhs.m_tail);
			}
			class_type& operator =(class_type const& rhs)
			{
				class_type(rhs).swap(*this);
				return *this;
			}

			head_reference get_head()					{ return m_head;	}
			head_const_reference get_head() const		{ return m_head;	}

			tail_reference get_tail()					{ return m_tail;	}
			tail_const_reference get_tail() const		{ return m_tail;	}

			void set_head(head_param_type h)			{ m_head = h;		}
			void set_tail(tail_param_type t)			{ m_tail = t;		}

	};
};

EXTL_TEMPLATE_SPECIALISATION
struct tuple2_impl<e_false_v, e_true_v, e_false_v>
{
	template<	typename_param_k H
			,	typename_param_k T
			>
	struct impl	
		: H/*protected remove_cv<H>:type*/
	{
		public:
			typedef impl														class_type;
			typedef H															head_type;
			typedef T															tail_type;
			typedef typename_type_k call_traits<head_type>::param_type			head_param_type;
			typedef typename_type_k call_traits<head_type>::reference			head_reference;
			typedef typename_type_k call_traits<head_type>::const_reference		head_const_reference;
			typedef typename_type_k call_traits<tail_type>::param_type			tail_param_type;
			typedef typename_type_k call_traits<tail_type>::reference			tail_reference;
			typedef typename_type_k call_traits<tail_type>::const_reference		tail_const_reference;

		private:
			tail_type															m_tail;

		public:
			impl() 
				: head_type(), m_tail() {}

			explicit_k impl(head_param_type h) 
				: head_type(h), m_tail() {}

			impl(head_param_type h, tail_param_type t) 
				: head_type(h), m_tail(t) {}

			impl(class_type const& rhs) 
				: head_type(static_cast<head_type const&>(rhs)), m_tail(rhs.m_tail) {}

			template<	typename_param_k T0
					,	typename_param_k T1
					,	typename_param_k T2
					,	typename_param_k T3
					,	typename_param_k T4
					,	typename_param_k T5
					,	typename_param_k T6
					,	typename_param_k T7
					,	typename_param_k T8
					,	typename_param_k T9
					>
			impl(T0& t0, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, T9& t9)
				: head_type(t0), m_tail(t1, t2, t3, t4, t5, t6, t7, t8, t9, cnull()) 
			{}

		public:
			void swap(class_type& rhs)
			{
				std_swap(m_tail, rhs.m_tail);
			}
			class_type& operator =(class_type const& rhs)
			{
				class_type(rhs).swap(*this);
				return *this;
			}

			head_reference get_head()				{ return *this;	}
			head_const_reference get_head() const	{ return *this;	}

			tail_reference get_tail()				{ return m_tail;	}
			tail_const_reference get_tail() const	{ return m_tail;	}

			void set_head(head_param_type )			{}
			void set_tail(tail_param_type t)		{ m_tail = t;		}
	};
};

EXTL_TEMPLATE_SPECIALISATION
struct tuple2_impl<e_false_v, e_false_v, e_true_v>
{
	template<	typename_param_k H
			,	typename_param_k T
			>
	struct impl	
		: /*protected remove_cv<T>:type*/T
	{
		public:
			typedef impl														class_type;
			typedef H															head_type;
			typedef T															tail_type;
			typedef typename_type_k call_traits<head_type>::param_type			head_param_type;
			typedef typename_type_k call_traits<head_type>::reference			head_reference;
			typedef typename_type_k call_traits<head_type>::const_reference		head_const_reference;
			typedef typename_type_k call_traits<tail_type>::param_type			tail_param_type;
			typedef typename_type_k call_traits<tail_type>::reference			tail_reference;
			typedef typename_type_k call_traits<tail_type>::const_reference		tail_const_reference;

		private:
			head_type															m_head;

		public:
			impl() 
				: m_head(), tail_type() {}

			explicit_k impl(head_param_type h) 
				: m_head(h), tail_type() {}

			impl(head_param_type h, tail_param_type t) 
				: m_head(h), tail_type(t) {}

			impl(class_type const& rhs) 
				: m_head(rhs.m_head), tail_type(static_cast<tail_type const&>(rhs)) {}

			template<	typename_param_k T0
					,	typename_param_k T1
					,	typename_param_k T2
					,	typename_param_k T3
					,	typename_param_k T4
					,	typename_param_k T5
					,	typename_param_k T6
					,	typename_param_k T7
					,	typename_param_k T8
					,	typename_param_k T9
					>
			impl(T0& t0, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, T9& t9)
				: m_head(t0), tail_type(t1, t2, t3, t4, t5, t6, t7, t8, t9, cnull()) 
			{}

		public:
			void swap(class_type& rhs)
			{
				std_swap(m_head, rhs.m_head);
			}
			class_type& operator =(class_type const& rhs)
			{
				class_type(rhs).swap(*this);
				return *this;
			}

			head_reference get_head()				{ return m_head;	}
			head_const_reference get_head() const	{ return m_head;	}

			tail_reference get_tail()				{ return *this;		}
			tail_const_reference get_tail() const	{ return *this;		}

			void set_head(head_param_type h)		{ m_head = h;		}
			void set_tail(tail_param_type )			{}
	};
};

EXTL_TEMPLATE_SPECIALISATION
struct tuple2_impl<e_false_v, e_true_v, e_true_v>
{
	template<	typename_param_k H
			,	typename_param_k T
			>
	struct impl	
		: /*protected remove_cv<H>:type*/H
		//, /*protected remove_cv<T>:type*/T
	{
		public:
			typedef impl														class_type;
			typedef H															head_type;
			typedef T															tail_type;
			typedef typename_type_k call_traits<head_type>::param_type			head_param_type;
			typedef typename_type_k call_traits<head_type>::reference			head_reference;
			typedef typename_type_k call_traits<head_type>::const_reference		head_const_reference;
			typedef typename_type_k call_traits<tail_type>::param_type			tail_param_type;
			typedef typename_type_k call_traits<tail_type>::reference			tail_reference;
			typedef typename_type_k call_traits<tail_type>::const_reference		tail_const_reference;

		public:
			impl() 
				: head_type(), tail_type() {}

			explicit_k impl(head_param_type h) 
				: head_type(h), tail_type() {}

			impl(head_param_type h, tail_param_type t) 
				: head_type(h), tail_type(t) {}

			impl(class_type const& rhs) 
				: head_type(static_cast<head_type const&>(rhs)), tail_type(static_cast<tail_type const&>(rhs)) {}

			template<	typename_param_k T0
					,	typename_param_k T1
					,	typename_param_k T2
					,	typename_param_k T3
					,	typename_param_k T4
					,	typename_param_k T5
					,	typename_param_k T6
					,	typename_param_k T7
					,	typename_param_k T8
					,	typename_param_k T9
					>
			impl(T0& t0, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, T9& t9)
				: head_type(t0), tail_type(t1, t2, t3, t4, t5, t6, t7, t8, t9, cnull()) 
			{}

		public:
			void swap(class_type& ){}
			class_type& operator =(class_type const& )	{return *this;		}

			head_reference get_head()					{ return *this;		}
			head_const_reference get_head() const		{ return *this;		}

			tail_reference get_tail()					{ return *this;		}
			tail_const_reference get_tail() const		{ return *this;		}

			void set_head(head_param_type )	{}
			void set_tail(tail_param_type )	{}
	};
};

template<	typename_param_k H
		,	typename_param_k T
		>
struct tuple2 
	: tuple2_impl	<	(is_same<H, T>::value)
					,	(is_empty<H>::value)
					,	(is_empty<T>::value)
					>::template_qual_k impl<H, T>
{
	public:
		typedef typename_type_k tuple2_impl	<	(is_same<H, T>::value)
											,	(is_empty<H>::value)
											,	(is_empty<T>::value)
											>::template_qual_k impl<H, T>	base_type;
	public:
		typedef tuple2														class_type;
		typedef H															head_type;
		typedef T															tail_type;
		typedef typename_type_k call_traits<head_type>::param_type			head_param_type;
		typedef typename_type_k call_traits<head_type>::reference			head_reference;
		typedef typename_type_k call_traits<head_type>::const_reference		head_const_reference;
		typedef typename_type_k call_traits<tail_type>::param_type			tail_param_type;
		typedef typename_type_k call_traits<tail_type>::reference			tail_reference;
		typedef typename_type_k call_traits<tail_type>::const_reference		tail_const_reference;

	public:
		tuple2() 
			: base_type() {}

		explicit_k tuple2(head_param_type h) 
			: base_type(h) {}

		tuple2(head_param_type h, tail_param_type t) 
			: base_type(h, t) {}

		tuple2(class_type const& rhs) 
			: base_type(rhs) {}

		template<	typename_param_k T0
				,	typename_param_k T1
				,	typename_param_k T2
				,	typename_param_k T3
				,	typename_param_k T4
				,	typename_param_k T5
				,	typename_param_k T6
				,	typename_param_k T7
				,	typename_param_k T8
				,	typename_param_k T9
				>
		tuple2(T0& t0, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, T9& t9)
			: base_type(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9) 
		{}

	public:
		void swap(class_type& rhs)
		{
			static_cast<base_type&>(*this).swap(rhs);
		}
		class_type& operator =(class_type const& rhs)
		{
			static_cast<base_type&>(*this) = rhs;
			return *this;
		}

		head_reference get_head()				{ return base_type::get_head();	}
		head_const_reference get_head() const	{ return base_type::get_head();	}

		tail_reference get_tail()				{ return base_type::get_tail();	}
		tail_const_reference get_tail() const	{ return base_type::get_tail();	}

		void set_head(head_param_type h)		{ base_type::set_head(h);		}
		void set_tail(tail_param_type t)		{ base_type::set_tail(t);		}
};

#elif EXTL_WORKAROUND_BORLAND(==, 0x551)

template<	typename_param_k H
		,	typename_param_k T
		>
struct tuple2
{
	public:
		typedef tuple2														class_type;
		typedef H															head_type;
		typedef T															tail_type;
		typedef typename_type_k call_traits<head_type>::param_type			head_param_type;
		typedef typename_type_k call_traits<head_type>::reference			head_reference;
		typedef typename_type_k call_traits<head_type>::const_reference		head_const_reference;
		typedef typename_type_k call_traits<tail_type>::param_type			tail_param_type;
		typedef typename_type_k call_traits<tail_type>::reference			tail_reference;
		typedef typename_type_k call_traits<tail_type>::const_reference		tail_const_reference;

	private:
		head_type															m_head;
		tail_type															m_tail;

	public:
		tuple2() 
			: m_head(), m_tail() {}

		explicit_k tuple2(head_param_type h) 
			: m_head(h), m_tail() {}

		tuple2(head_param_type h, tail_param_type t) 
			: m_head(h), m_tail(t) {}

		tuple2(class_type const& rhs) 
			: m_head(rhs.m_head), m_tail(rhs.m_tail) {}

		template<	typename_param_k T0
				,	typename_param_k T1
				,	typename_param_k T2
				,	typename_param_k T3
				,	typename_param_k T4
				,	typename_param_k T5
				,	typename_param_k T6
				,	typename_param_k T7
				,	typename_param_k T8
				,	typename_param_k T9
				>
		tuple2(T0& t0, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, T9& t9)
			: m_head(t0), m_tail(t1, t2, t3, t4, t5, t6, t7, t8, t9, cnull()) 
		{}

	public:
		void swap(class_type& rhs)
		{
			std_swap(m_head, rhs.m_head);
			std_swap(m_tail, rhs.m_tail);
		}
		class_type& operator =(class_type const& rhs)
		{
			class_type(rhs).swap(*this);
			return *this;
		}

		head_reference get_head()				{ return m_head;	}
		head_const_reference get_head() const	{ return m_head;	}

		tail_reference get_tail()				{ return m_tail;	}
		tail_const_reference get_tail() const	{ return m_tail;	}

		void set_head(head_param_type h)		{ m_head = h;		}
		void set_tail(tail_param_type t)		{ m_tail = t;		}
};
#else
template<	e_bool_t is_head_null
		,	e_bool_t is_tail_null
		>
struct tuple2_impl
{
	template<	typename_param_k H
			,	typename_param_k T
			>
	struct impl
	{
		public:
			typedef impl														class_type;
			typedef H															head_type;
			typedef T															tail_type;
			typedef typename_type_k call_traits<head_type>::param_type			head_param_type;
			typedef typename_type_k call_traits<head_type>::reference			head_reference;
			typedef typename_type_k call_traits<head_type>::const_reference		head_const_reference;
			typedef typename_type_k call_traits<tail_type>::param_type			tail_param_type;
			typedef typename_type_k call_traits<tail_type>::reference			tail_reference;
			typedef typename_type_k call_traits<tail_type>::const_reference		tail_const_reference;

		private:
			head_type															m_head;
			tail_type															m_tail;

		public:
			impl() 
				: m_head(), m_tail() {}

			explicit_k impl(head_param_type h) 
				: m_head(h), m_tail() {}

			impl(head_param_type h, tail_param_type t) 
				: m_head(h), m_tail(t) {}

			impl(class_type const& rhs) 
				: m_head(rhs.m_head), m_tail(rhs.m_tail) {}

			template<	typename_param_k T0
					,	typename_param_k T1
					,	typename_param_k T2
					,	typename_param_k T3
					,	typename_param_k T4
					,	typename_param_k T5
					,	typename_param_k T6
					,	typename_param_k T7
					,	typename_param_k T8
					,	typename_param_k T9
					>
			impl(T0& t0, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, T9& t9)
				: m_head(t0), m_tail(t1, t2, t3, t4, t5, t6, t7, t8, t9, cnull()) 
			{}

		public:
			void swap(class_type& rhs)
			{
				std_swap(m_head, rhs.m_head);
				std_swap(m_tail, rhs.m_tail);
			}
			class_type& operator =(class_type const& rhs)
			{
				class_type(rhs).swap(*this);
				return *this;
			}

			head_reference get_head()				{ return m_head;	}
			head_const_reference get_head() const	{ return m_head;	}

			tail_reference get_tail()				{ return m_tail;	}
			tail_const_reference get_tail() const	{ return m_tail;	}

			void set_head(head_param_type h)		{ m_head = h;		}
			void set_tail(tail_param_type t)		{ m_tail = t;		}
	};
};
EXTL_TEMPLATE_SPECIALISATION
struct tuple2_impl<e_true_v, e_false_v>
{
	template<	typename_param_k H
			,	typename_param_k T
			>
	struct impl	
	{
		public:
			typedef impl														class_type;
			typedef e_null_t													head_type;
			typedef T															tail_type;
			typedef typename_type_k call_traits<head_type>::param_type			head_param_type;
			typedef typename_type_k call_traits<head_type>::reference			head_reference;
			typedef typename_type_k call_traits<head_type>::const_reference		head_const_reference;
			typedef typename_type_k call_traits<tail_type>::param_type			tail_param_type;
			typedef typename_type_k call_traits<tail_type>::reference			tail_reference;
			typedef typename_type_k call_traits<tail_type>::const_reference		tail_const_reference;

		private:
			tail_type															m_tail;

		public:
			impl() 
				: m_tail() {}

			explicit_k impl(head_param_type ) 
				: m_tail() {}

			impl(head_param_type , tail_param_type t) 
				: m_tail(t) {}

			impl(class_type const& rhs) 
				: m_tail(rhs.m_tail) {}

			template<	typename_param_k T0
					,	typename_param_k T1
					,	typename_param_k T2
					,	typename_param_k T3
					,	typename_param_k T4
					,	typename_param_k T5
					,	typename_param_k T6
					,	typename_param_k T7
					,	typename_param_k T8
					,	typename_param_k T9
					>
			impl(T0& , T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, T9& t9)
				: m_tail(t1, t2, t3, t4, t5, t6, t7, t8, t9, cnull()) 
			{}

		public:
			void swap(class_type& rhs)
			{
				std_swap(m_tail, rhs.m_tail);
			}
			class_type& operator =(class_type const& rhs)
			{
				class_type(rhs).swap(*this);
				return *this;
			}

			head_reference get_head()				{ return cnull();	}
			head_const_reference get_head() const	{ return cnull();	}

			tail_reference get_tail()				{ return m_tail;	}
			tail_const_reference get_tail() const	{ return m_tail;	}

			void set_head(head_param_type )			{}
			void set_tail(tail_param_type t)		{ m_tail = t;		}

	};
};

EXTL_TEMPLATE_SPECIALISATION
struct tuple2_impl<e_false_v, e_true_v>
{
	template<	typename_param_k H
			,	typename_param_k T
			>
	struct impl	
	{
		public:
			typedef impl														class_type;
			typedef H															head_type;
			typedef e_null_t													tail_type;
			typedef typename_type_k call_traits<head_type>::param_type			head_param_type;
			typedef typename_type_k call_traits<head_type>::reference			head_reference;
			typedef typename_type_k call_traits<head_type>::const_reference		head_const_reference;
			typedef typename_type_k call_traits<tail_type>::param_type			tail_param_type;
			typedef typename_type_k call_traits<tail_type>::reference			tail_reference;
			typedef typename_type_k call_traits<tail_type>::const_reference		tail_const_reference;

		private:
			head_type															m_head;

		public:
			impl() 
				: m_head() {}

			explicit_k impl(head_param_type h) 
				: m_head(h) {}

			impl(head_param_type h, tail_param_type ) 
				: m_head(h){}

			impl(class_type const& rhs) 
				: m_head(rhs.m_head) {}

			template<	typename_param_k T0
					,	typename_param_k T1
					,	typename_param_k T2
					,	typename_param_k T3
					,	typename_param_k T4
					,	typename_param_k T5
					,	typename_param_k T6
					,	typename_param_k T7
					,	typename_param_k T8
					,	typename_param_k T9
					>
			impl(T0& t0, T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& )
				: m_head(t0)
			{}
	
		public:
			void swap(class_type& rhs)
			{
				std_swap(m_head, rhs.m_head);
			}
			class_type& operator =(class_type const& rhs)
			{
				class_type(rhs).swap(*this);
				return *this;
			}

			head_reference get_head()				{ return m_head;	}
			head_const_reference get_head() const	{ return m_head;	}

			tail_reference get_tail()				{ return cnull();	}
			tail_const_reference get_tail() const	{ return cnull();	}

			void set_head(head_param_type h)		{ m_head = h;		}
			void set_tail(tail_param_type )			{}

	};
};

EXTL_TEMPLATE_SPECIALISATION
struct tuple2_impl<e_true_v, e_true_v>
{
	template<	typename_param_k H
			,	typename_param_k T
			>
	struct impl	
	{
		public:
			typedef impl														class_type;
			typedef e_null_t													head_type;
			typedef e_null_t													tail_type;
			typedef typename_type_k call_traits<head_type>::param_type			head_param_type;
			typedef typename_type_k call_traits<head_type>::reference			head_reference;
			typedef typename_type_k call_traits<head_type>::const_reference		head_const_reference;
			typedef typename_type_k call_traits<tail_type>::param_type			tail_param_type;
			typedef typename_type_k call_traits<tail_type>::reference			tail_reference;
			typedef typename_type_k call_traits<tail_type>::const_reference		tail_const_reference;

		public:
			impl() {}
			explicit_k impl(head_param_type ) {}
			impl(head_param_type , tail_param_type t)  {}
			impl(class_type const& rhs) {}

			template<	typename_param_k T0
					,	typename_param_k T1
					,	typename_param_k T2
					,	typename_param_k T3
					,	typename_param_k T4
					,	typename_param_k T5
					,	typename_param_k T6
					,	typename_param_k T7
					,	typename_param_k T8
					,	typename_param_k T9
					>
			impl(T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& )
			{}

		public:
			void swap(class_type& ) {}
			class_type& operator =(class_type const& )	{ return *this;	}

			head_reference get_head()					{ return cnull();	}
			head_const_reference get_head() const		{ return cnull();	}

			tail_reference get_tail()					{ return cnull();	}
			tail_const_reference get_tail() const		{ return cnull();	}

			void set_head(head_param_type )				{}
			void set_tail(tail_param_type )				{}
	};
};

template<	typename_param_k H
		,	typename_param_k T
		>
struct tuple2 
	: tuple2_impl	<	(is_null_type<H>::value)
					,	(is_null_type<T>::value)
					>::template_qual_k impl<H, T>
{
	public:
		typedef typename_type_k tuple2_impl	<	(is_null_type<H>::value)
											,	(is_null_type<T>::value)
											>::template_qual_k impl<H, T>	base_type;
	public:
		typedef tuple2														class_type;
		typedef H															head_type;
		typedef T															tail_type;
		typedef typename_type_k call_traits<head_type>::param_type			head_param_type;
		typedef typename_type_k call_traits<head_type>::reference			head_reference;
		typedef typename_type_k call_traits<head_type>::const_reference		head_const_reference;
		typedef typename_type_k call_traits<tail_type>::param_type			tail_param_type;
		typedef typename_type_k call_traits<tail_type>::reference			tail_reference;
		typedef typename_type_k call_traits<tail_type>::const_reference		tail_const_reference;

	public:
		tuple2() 
			: base_type() {}

		explicit_k tuple2(head_param_type h) 
			: base_type(h) {}

		tuple2(head_param_type h, tail_param_type t) 
			: base_type(h, t) {}

		tuple2(class_type const& rhs) 
			: base_type(rhs) {}

		template<	typename_param_k T0
				,	typename_param_k T1
				,	typename_param_k T2
				,	typename_param_k T3
				,	typename_param_k T4
				,	typename_param_k T5
				,	typename_param_k T6
				,	typename_param_k T7
				,	typename_param_k T8
				,	typename_param_k T9
				>
		tuple2(T0& t0, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, T9& t9)
			: base_type(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9) 
		{}

	public:
		void swap(class_type& rhs)
		{
			static_cast<base_type&>(*this).swap(rhs);
		}
		class_type& operator =(class_type const& rhs)
		{
			static_cast<base_type&>(*this) = rhs;
			return *this;
		}

		head_reference get_head()				{ return base_type::get_head();	}
		head_const_reference get_head() const	{ return base_type::get_head();	}

		tail_reference get_tail()				{ return base_type::get_tail();	}
		tail_const_reference get_tail() const	{ return base_type::get_tail();	}

		void set_head(head_param_type h)		{ base_type::set_head(h);		}
		void set_tail(tail_param_type t)		{ base_type::set_tail(t);		}
};
#endif /* defined(EXTL_TYPE_TRAITS_IS_SAME_SUPPORT) && \
			defined(EXTL_TYPE_TRAITS_IS_EMPTY_SUPPORT) && \
				defined(EXTL_MEMBER_TEMPLATE_CLASS_SUPPORT) */


#ifdef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT
template<typename_param_k H>
struct tuple2<H, e_null_t>
{
	public:
		typedef tuple2														class_type;
		typedef H															head_type;
		typedef e_null_t													tail_type;
		typedef typename_type_k call_traits<head_type>::param_type			head_param_type;
		typedef typename_type_k call_traits<head_type>::reference			head_reference;
		typedef typename_type_k call_traits<head_type>::const_reference		head_const_reference;
		typedef typename_type_k call_traits<tail_type>::param_type			tail_param_type;
		typedef typename_type_k call_traits<tail_type>::reference			tail_reference;
		typedef typename_type_k call_traits<tail_type>::const_reference		tail_const_reference;

	private:
		head_type															m_head;

	public:
		tuple2() 
			: m_head() {}

		explicit_k tuple2(head_param_type h) 
			: m_head(h) {}

		tuple2(head_param_type h, tail_param_type ) 
			: m_head(h){}

		tuple2(class_type const& rhs) 
			: m_head(rhs.m_head) {}

		template<	typename_param_k T0
				,	typename_param_k T1
				,	typename_param_k T2
				,	typename_param_k T3
				,	typename_param_k T4
				,	typename_param_k T5
				,	typename_param_k T6
				,	typename_param_k T7
				,	typename_param_k T8
				,	typename_param_k T9
				>
		tuple2(T0& t0, T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& )
			: m_head(t0)
		{}

	public:
		void swap(class_type& rhs)
		{
			std_swap(m_head, rhs.m_head);
		}
		class_type& operator =(class_type const& rhs)
		{
			class_type(rhs).swap(*this);
			return *this;
		}

		head_reference get_head()				{ return m_head;	}
		head_const_reference get_head() const	{ return m_head;	}

		tail_reference get_tail()				{ return cnull();	}
		tail_const_reference get_tail() const	{ return cnull();	}

		void set_head(head_param_type h)		{ m_head = h;		}
		void set_tail(tail_param_type )			{}
};

#endif /* !defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_DETAIL_END_NAMESPACE
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /*  EXTL_CONTAINER_DETAIL_TUPLE2_H */
/* //////////////////////////////////////////////////////////////////// */
