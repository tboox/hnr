/* ///////////////////////////////////////////////////////////////////////
 * File:		fixed_marray_impl.h		
 *
 * Created:		08.08.05			
 * Updated:		08.08.05
 *
 * Brief: fixed_marray_impl class - fixed multiple dimension array
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_DETAIL_FIXED_MARRAY_IMPL_H
#define EXTL_CONTAINER_DETAIL_FIXED_MARRAY_IMPL_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"
#include "../../algorithm/algorithm.h"
/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#if !defined(EXTL_MEMBER_TEMPLATE_CLASS_SUPPORT)  
#	error extl::fixed_marray_impl is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_FIXED_MARRAY_CURRENT_MAX_DIM	4

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_BEGIN_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

template<e_size_t N>
struct fixed_marray_impl
{
	template<	typename_param_k T
			,	typename_param_k D
			,	typename_param_k RD
			>
	struct impl;
};

EXTL_TEMPLATE_SPECIALISATION
struct fixed_marray_impl<1>
{
	template<	typename_param_k T
			,	typename_param_k D
			,	typename_param_k RD
			>
	struct impl
	{
		public:
			typedef D																	derived_type;
			typedef impl																class_type;
			typedef T																	value_type;
			typedef T*																	pointer;
			typedef T const*															const_pointer;
			typedef T&																	reference;
			typedef T const&															const_reference;
			typedef e_size_t															size_type;
			typedef size_type															index_type;
			typedef e_bool_t															bool_type;
			typedef e_int_t																int_type;
			typedef e_ptrdiff_t															difference_type;
			typedef reference															reduced_dimension_type;
			typedef const_reference														const_reduced_dimension_type;

		private:
			index_type			m_d0;

		private:																							
			derived_type& get_derive()				{ return static_cast<derived_type&>(*this);			}	
			derived_type const& get_derive() const	{ return static_cast<derived_type const&>(*this);	}
	
		protected:
			impl()
				: m_d0(0)
			{}
			impl(index_type d0, index_type , index_type , index_type )
				: m_d0(d0)
			{}
			impl(class_type const& rhs) 
				: m_d0(rhs.m_d0)
			{}
			class_type& operator =(class_type const& rhs)
			{
				m_d0 = rhs.m_d0;
				return *this;
			}

		protected:
			void swap(class_type& rhs)
			{
				std_swap(m_d0, rhs.m_d0);
			}

		public:
			index_type dim0() const { return m_d0;	}

		public:
			// at_unchecked
			reference		at_unchecked(index_type i0)
			{
				return const_cast<reference>(static_cast<class_type const&>(*this).at_unchecked(i0));
			}
			const_reference	at_unchecked(index_type i0) const
			{
				EXTL_ASSERT(!get_derive().is_empty());
				EXTL_MESSAGE_ASSERT	(	i0 < this->dim0() 
									,	"out of range");
				return get_derive().data()[i0];
			}
			// at
			reference		at(index_type i0)
			{
				return const_cast<reference>(static_cast<class_type const&>(*this).at(i0));
			}
			const_reference	at(index_type i0) const
			{
				EXTL_ASSERT_THROW	(	i0 < this->dim0() 
									,	index_error("out of range"));
				return at_unchecked(i0);
			}
		
		
	};
};

EXTL_TEMPLATE_SPECIALISATION
struct fixed_marray_impl<2>
{
	template<	typename_param_k T
			,	typename_param_k D
			,	typename_param_k RD
			>
	struct impl
	{
		public:
			typedef D																	derived_type;
			typedef RD																	reduced_dimension_type;
			typedef reduced_dimension_type const										const_reduced_dimension_type;
			typedef impl																class_type;
			typedef T																	value_type;
			typedef T*																	pointer;
			typedef T const*															const_pointer;
			typedef T&																	reference;
			typedef T const&															const_reference;
			typedef e_size_t															size_type;
			typedef size_type															index_type;
			typedef e_bool_t															bool_type;
			typedef e_int_t																int_type;
			typedef e_ptrdiff_t															difference_type;

		private:
			index_type			m_d0;
			index_type			m_d1;

		private:																							
			derived_type& get_derive()				{ return static_cast<derived_type&>(*this);			}	
			derived_type const& get_derive() const	{ return static_cast<derived_type const&>(*this);	}

		protected:
			impl()
				: m_d0(0), m_d1(0)
			{}
			impl(index_type d0, index_type d1, index_type , index_type )
				: m_d0(d0), m_d1(d1)
			{}
			impl(class_type const& rhs) 
				: m_d0(rhs.m_d0), m_d1(rhs.m_d1)
			{}
			class_type& operator =(class_type const& rhs)
			{
				m_d0 = rhs.m_d0;
				m_d1 = rhs.m_d1;
				return *this;
			}

		protected:
			void swap(class_type& rhs)
			{
				std_swap(m_d0, rhs.m_d0);
				std_swap(m_d1, rhs.m_d1);
			}

		public:
			index_type dim0() const { return m_d0;	}
			index_type dim1() const { return m_d1;	}

		public:
			// at_unchecked
			reference		at_unchecked(index_type i0, index_type i1)
			{
				return const_cast<reference>(static_cast<class_type const&>(*this).at_unchecked(i0, i1));
			}
			const_reference	at_unchecked(index_type i0, index_type i1) const
			{
				EXTL_ASSERT(!get_derive().is_empty());
				EXTL_MESSAGE_ASSERT	(	i0 < this->dim0() &&
										i1 < this->dim1() 
									,	"out of range");
				return get_derive().data()[(i0 * dim1()) + i1];
			}
			reduced_dimension_type			at_unchecked(index_type i0)
			{
				EXTL_ASSERT(!get_derive().is_empty());
				EXTL_MESSAGE_ASSERT	(	i0 < this->dim0() 
									,	"out of range");
				return reduced_dimension_type(get_derive().data() + i0 * dim1(), dim1());
			}
			const_reduced_dimension_type	at_unchecked(index_type i0) const
			{
				EXTL_ASSERT(!get_derive().is_empty());
				EXTL_MESSAGE_ASSERT	(	i0 < this->dim0() 
									,	"out of range");
				return const_reduced_dimension_type(get_derive().data() + i0 * dim1(), dim1());
			}

			// at
			reference		at(index_type i0, index_type i1)
			{
				return const_cast<reference>(static_cast<class_type const&>(*this).at(i0, i1));
			}
			const_reference	at(index_type i0, index_type i1) const
			{
				EXTL_ASSERT_THROW	(	i0 < this->dim0() &&
										i1 < this->dim1() 
									,	index_error("out of range"));
				return at_unchecked(i0, i1);
			}
			reduced_dimension_type			at(index_type i0)
			{
				EXTL_ASSERT_THROW	(	i0 < this->dim0() 
									,	index_error("out of range"));
				return at_unchecked(i0);
			}
			const_reduced_dimension_type	at(index_type i0) const
			{
				EXTL_ASSERT_THROW	(	i0 < this->dim0() 
									,	index_error("out of range"));
				return at_unchecked(i0);
			}
	};
};

EXTL_TEMPLATE_SPECIALISATION
struct fixed_marray_impl<3>
{
	template<	typename_param_k T
			,	typename_param_k D
			,	typename_param_k RD
			>
	struct impl
	{
		public:
			typedef D																	derived_type;
			typedef RD																	reduced_dimension_type;
			typedef reduced_dimension_type const										const_reduced_dimension_type;
			typedef impl																class_type;
			typedef T																	value_type;
			typedef T*																	pointer;
			typedef T const*															const_pointer;
			typedef T&																	reference;
			typedef T const&															const_reference;
			typedef e_size_t															size_type;
			typedef size_type															index_type;
			typedef e_bool_t															bool_type;
			typedef e_int_t																int_type;
			typedef e_ptrdiff_t															difference_type;

		private:
			index_type			m_d0;
			index_type			m_d1;
			index_type			m_d2;

		private:																							
			derived_type& get_derive()				{ return static_cast<derived_type&>(*this);			}	
			derived_type const& get_derive() const	{ return static_cast<derived_type const&>(*this);	}

		protected:
			impl()
				: m_d0(0), m_d1(0), m_d2(0)
			{}
			impl(index_type d0, index_type d1, index_type d2, index_type )
				: m_d0(d0), m_d1(d1), m_d2(d2)
			{}
			impl(class_type const& rhs) 
				: m_d0(rhs.m_d0), m_d1(rhs.m_d1), m_d2(rhs.m_d2)
			{}
			class_type& operator =(class_type const& rhs)
			{
				m_d0 = rhs.m_d0;
				m_d1 = rhs.m_d1;
				m_d2 = rhs.m_d2;
				return *this;
			}

		protected:
			void swap(class_type& rhs)
			{
				std_swap(m_d0, rhs.m_d0);
				std_swap(m_d1, rhs.m_d1);
				std_swap(m_d2, rhs.m_d2);
			}

		public:
			index_type dim0() const { return m_d0;	}
			index_type dim1() const { return m_d1;	}
			index_type dim2() const { return m_d2;	}
		
		public:
			// at_unchecked
			reference		at_unchecked(index_type i0, index_type i1, index_type i2)
			{
				return const_cast<reference>(static_cast<class_type const&>(*this).at_unchecked(i0, i1, i2));
			}
			const_reference	at_unchecked(index_type i0, index_type i1, index_type i2) const
			{
				EXTL_ASSERT(!get_derive().is_empty());
				EXTL_MESSAGE_ASSERT	(	i0 < this->dim0() &&
										i1 < this->dim1() &&
										i2 < this->dim2() 
									,	"out of range");
				return get_derive().data()[((i0 * dim1()) + i1) * dim2() + i2];
			}
			reduced_dimension_type			at_unchecked(index_type i0)
			{
				EXTL_ASSERT(!get_derive().is_empty());
				EXTL_MESSAGE_ASSERT	(	i0 < this->dim0() 
									,	"out of range");
				return reduced_dimension_type(get_derive().data() + i0 * dim1(), dim1());
			}
			const_reduced_dimension_type	at_unchecked(index_type i0) const
			{
				EXTL_ASSERT(!get_derive().is_empty());
				EXTL_MESSAGE_ASSERT	(	i0 < this->dim0() 
									,	"out of range");
				return const_reduced_dimension_type(get_derive().data() + i0 * dim1() * dim2(), dim1(), dim2());
			}
			// at
			reference		at(index_type i0, index_type i1, index_type i2)
			{
				return const_cast<reference>(static_cast<class_type const&>(*this).at(i0, i1, i2));
			}
			const_reference	at(index_type i0, index_type i1, index_type i2) const
			{
				EXTL_ASSERT_THROW	(	i0 < this->dim0() &&
										i1 < this->dim1() &&
										i2 < this->dim2() 
									,	index_error("out of range"));
				return at_unchecked(i0, i1, i2);
			}
			reduced_dimension_type			at(index_type i0)
			{
				EXTL_ASSERT_THROW	(	i0 < this->dim0() 
									,	index_error("out of range"));
				return at_unchecked(i0);
			}
			const_reduced_dimension_type	at(index_type i0) const
			{
				EXTL_ASSERT_THROW	(	i0 < this->dim0() 
									,	index_error("out of range"));
				return at_unchecked(i0);
			}
		
	};
};

EXTL_TEMPLATE_SPECIALISATION
struct fixed_marray_impl<4>
{
	template<	typename_param_k T
			,	typename_param_k D
			,	typename_param_k RD
			>
	struct impl
	{
		public:
			typedef D																	derived_type;
			typedef RD																	reduced_dimension_type;
			typedef reduced_dimension_type const										const_reduced_dimension_type;
			typedef impl																class_type;
			typedef T																	value_type;
			typedef T*																	pointer;
			typedef T const*															const_pointer;
			typedef T&																	reference;
			typedef T const&															const_reference;
			typedef e_size_t															size_type;
			typedef size_type															index_type;
			typedef e_bool_t															bool_type;
			typedef e_int_t																int_type;
			typedef e_ptrdiff_t															difference_type;
			
		private:
			index_type			m_d0;
			index_type			m_d1;
			index_type			m_d2;
			index_type			m_d3;	

		private:																							
			derived_type& get_derive()				{ return static_cast<derived_type&>(*this);			}	
			derived_type const& get_derive() const	{ return static_cast<derived_type const&>(*this);	}

		protected:
			impl()
				: m_d0(0), m_d1(0), m_d2(0), m_d3(0)
			{}
			impl(index_type d0, index_type d1, index_type d2, index_type d3)
				: m_d0(d0), m_d1(d1), m_d2(d2), m_d3(d3)
			{}
			impl(class_type const& rhs) 
				: m_d0(rhs.m_d0), m_d1(rhs.m_d1), m_d2(rhs.m_d2), m_d3(rhs.m_d3)
			{}
			class_type& operator =(class_type const& rhs)
			{
				m_d0 = rhs.m_d0;
				m_d1 = rhs.m_d1;
				m_d2 = rhs.m_d2;
				m_d3 = rhs.m_d3;
				return *this;
			}

		protected:
			void swap(class_type& rhs)
			{
				std_swap(m_d0, rhs.m_d0);
				std_swap(m_d1, rhs.m_d1);
				std_swap(m_d2, rhs.m_d2);
				std_swap(m_d3, rhs.m_d3);
			}
		
		public:
			index_type dim0() const { return m_d0;	}
			index_type dim1() const { return m_d1;	}
			index_type dim2() const { return m_d2;	}
			index_type dim3() const { return m_d3;	}

		public:
			// at_unchecked
			reference		at_unchecked(index_type i0, index_type i1, index_type i2, index_type i3)
			{
				return const_cast<reference>(static_cast<class_type const&>(*this).at_unchecked(i0, i1, i2, i3));
			}
			const_reference	at_unchecked(index_type i0, index_type i1, index_type i2, index_type i3) const
			{
				EXTL_ASSERT(!get_derive().is_empty());
				EXTL_MESSAGE_ASSERT	(	i0 < this->dim0() &&
										i1 < this->dim1() &&
										i2 < this->dim2() &&
										i3 < this->dim3()
									,	"out of range");
				return get_derive().data()[(((i0 * dim1()) + i1) * dim2() + i2) * dim3() + i3];
			}
			reduced_dimension_type			at_unchecked(index_type i0)
			{
				EXTL_ASSERT(!get_derive().is_empty());
				EXTL_MESSAGE_ASSERT	(	i0 < this->dim0() 
									,	"out of range");
				return reduced_dimension_type(get_derive().data() + i0 * dim1(), dim1());
			}
			const_reduced_dimension_type	at_unchecked(index_type i0) const
			{
				EXTL_ASSERT(!get_derive().is_empty());
				EXTL_MESSAGE_ASSERT	(	i0 < this->dim0() 
									,	"out of range");
				return const_reduced_dimension_type(get_derive().data() + i0 * dim1() * dim2() * dim3(), dim1(), dim2(), dim3());
			}

			// at
			reference		at(index_type i0, index_type i1, index_type i2, index_type i3)
			{
				return const_cast<reference>(static_cast<class_type const&>(*this).at(i0, i1, i2, i3));
			}
			const_reference	at(index_type i0, index_type i1, index_type i2, index_type i3) const
			{
				EXTL_ASSERT_THROW	(	i0 < this->dim0() &&
										i1 < this->dim1() &&
										i2 < this->dim2() &&
										i3 < this->dim3()
									,	index_error("out of range"));
				return at_unchecked(i0, i1, i2, i3);
			}
			reduced_dimension_type			at(index_type i0)
			{
				EXTL_ASSERT_THROW	(	i0 < this->dim0() 
									,	index_error("out of range"));
				return at_unchecked(i0);
			}
			const_reduced_dimension_type	at(index_type i0) const
			{
				EXTL_ASSERT_THROW	(	i0 < this->dim0() 
									,	index_error("out of range"));
				return at_unchecked(i0);
			}
	};
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_DETAIL_END_NAMESPACE
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_DETAIL_FIXED_MARRAY_IMPL_H */
/* //////////////////////////////////////////////////////////////////// */
