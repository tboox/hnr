/* ///////////////////////////////////////////////////////////////////////
 * File:		properties_test.h		
 *
 * Created:		08.04.01			
 * Updated:		08.05.05
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_UTILITY_PROPERTIES_TEST_H
#define EXTL_UTILITY_PROPERTIES_TEST_H

#ifndef EXTL_UTILITY_PROPERTIES_H
#	error This file must be included of properties.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
class external_propery_test
{
	public:
		typedef int								value_type;
		typedef external_propery_test			class_type;
	
	public:
		external_propery_test(value_type v)
			: m_value(v)
		{
		}
	
	public:
		value_type get_Value1() const
		{
			return m_value;
		}
		void set_Value2(value_type value)
		{
			m_value = value;
		}
		value_type get_Value3() const
		{
			return m_value;
		}
		void set_Value3(value_type value)
		{
			m_value = value;
		}
	/*public:
		static e_size_t get_property_start_offset()
		{
			return EXTL_OFFSET_OF(class_type, property_start_tag);
		}

	public:
		union
		{
			e_byte_t	property_start_tag;
			external_property_get< class_type, value_type const&, &class_type::get_property_start_offset, &class_type::get_Value1 > Value1;
			external_property_set< class_type, value_type, &class_type::get_property_start_offset, &class_type::set_Value2 > Value2;
			external_property_set< class_type, value_type, &class_type::get_property_start_offset, &class_type::get_Value3, &class_type::set_Value3 > Value3;
		};*/
		EXTL_EXTERNAL_PROPERTY_DEFINE_BEGIN(class_type)	
		EXTL_EXTERNAL_PROPERTY_GET(value_type, Value1)
		EXTL_EXTERNAL_PROPERTY_SET(value_type, Value2)
		EXTL_EXTERNAL_PROPERTY_GETSET(value_type, Value3)
		EXTL_EXTERNAL_PROPERTY_DEFINE_END()

		static value_type get_Value4()
		{
			return s_value;
		}
		static void set_Value5(value_type value)
		{
			s_value = value;
		}
		static value_type get_Value6()
		{
			return s_value;
		}
		static void set_Value6(value_type value)
		{
			s_value = value;
		}
		
		/*static static_external_property_get<value_type, &class_type::get_Value4> Value4;
		static static_external_property_set<value_type, &class_type::set_Value5> Value5;
		static static_external_property_getset<value_type, value_type, &class_type::get_Value6, &class_type::set_Value6> Value6;
		*/

	#if !defined(EXTL_COMPILER_IS_MSVC) || _MSC_VER > 1200
		EXTL_STATIC_EXTERNAL_PROPERTY_DECLARE_BEGIN(class_type)	
		EXTL_STATIC_EXTERNAL_PROPERTY_GET(value_type, Value4)
		EXTL_STATIC_EXTERNAL_PROPERTY_SET(value_type, Value5)
		EXTL_STATIC_EXTERNAL_PROPERTY_GETSET(value_type, Value6)
		EXTL_STATIC_EXTERNAL_PROPERTY_DECLARE_END()
	#endif

	private:
		value_type m_value;
		static value_type s_value;
};
external_propery_test::value_type external_propery_test::s_value = 10;

#if !defined(EXTL_COMPILER_IS_MSVC) || _MSC_VER > 1200
EXTL_STATIC_EXTERNAL_PROPERTY_DEFINE_GET(external_propery_test, external_propery_test::value_type, Value4)
EXTL_STATIC_EXTERNAL_PROPERTY_DEFINE_SET(external_propery_test, external_propery_test::value_type, Value5)
EXTL_STATIC_EXTERNAL_PROPERTY_DEFINE_GETSET(external_propery_test, external_propery_test::value_type, Value6)
#endif

struct properties_test
{
	properties_test()
	{
		external_propery_test epgt(10);
		/*printf("result:%d\n", epgt.Value1);*/
		/*printf("result:%d\n", static_cast<int const&>(epgt.Value1));*/

		EXTL_ASSERT(epgt.Value1 == 10);

		epgt.Value2 = 15;
		EXTL_ASSERT(epgt.Value1 == 15);

		epgt.Value3 = 20;
		EXTL_ASSERT(epgt.Value3 == 20);

	#if !defined(EXTL_COMPILER_IS_MSVC) || _MSC_VER > 1200
		EXTL_ASSERT(external_propery_test::Value4 == 10);

		external_propery_test::Value5 = 5;
		EXTL_ASSERT(external_propery_test::Value4 == 5);

		external_propery_test::Value6 = 100;
		EXTL_ASSERT(external_propery_test::Value6 == 100);
	#endif
	}
};

properties_test g_properties_test;
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_UTILITY_PROPERTIES_TEST_H */
/* //////////////////////////////////////////////////////////////////// */
