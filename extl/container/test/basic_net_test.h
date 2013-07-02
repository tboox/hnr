/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_net_test.h		
 *
 * Created:		08.12.02			
 * Updated:		08.12.02
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONTAINER_BASIC_NET_TEST_H
#define EXTL_CONTAINER_BASIC_NET_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * unit_test namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(basic_net_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
static int basic_net_test()
{
	/* ///////////////////////////////////////////////////////////////////////
	 * directed net test
	 * 
	 *  /------------->1<-------------\
	 * 0 <------------' '------------->2
	 * |                               |
	 * '-------------->3<--------------'
	 */
	EXTL_TEST_TRACE(_T("directed net test:"));
	typedef basic_net<e_true_v, int, int>			directed_net_type;
	directed_net_type								directed_net(10);

	EXTL_ASSERT(directed_net.max_nodes_size() == 10);
	EXTL_ASSERT(directed_net.max_arcs_size() == 100);

	directed_net.insert_node(0);
	directed_net.insert_node(1);
	directed_net.insert_node(2);
	directed_net.insert_arc(0, 1);
	directed_net.insert_arc(1, 0);
	directed_net.insert_arc(2, 1);
	directed_net.insert_arc(1, 2);
	directed_net.insert_arc(0, 3);
	directed_net.insert_arc(2, 3);
	
	EXTL_ASSERT(directed_net.nodes_size() == 4);
	EXTL_ASSERT(directed_net.arcs_size() == 6);

	EXTL_ASSERT(directed_net.in_degree(0) == 1);
	EXTL_ASSERT(directed_net.out_degree(0) == 2);
	EXTL_ASSERT(directed_net.degree(0) == 3);

	EXTL_ASSERT(directed_net.in_degree(1) == 2);
	EXTL_ASSERT(directed_net.out_degree(1) == 2);
	EXTL_ASSERT(directed_net.degree(1) == 4);

	EXTL_ASSERT(directed_net.in_degree(2) == 1);
	EXTL_ASSERT(directed_net.out_degree(2) == 2);
	EXTL_ASSERT(directed_net.degree(2) == 3);

	EXTL_ASSERT(directed_net.in_degree(3) == 2);
	EXTL_ASSERT(directed_net.out_degree(3) == 0);
	EXTL_ASSERT(directed_net.degree(3) == 2);

	EXTL_TEST_TRACE(_T("\nnode iterator test:"));
	for (directed_net_type::const_node_iterator pn = directed_net.node_begin(); pn != directed_net.node_end(); ++pn)
	{
		EXTL_TEST_TRACE(_T("node:%d"), *pn);
	}

	EXTL_TEST_TRACE(_T("\nreverse node iterator test:"));
	for (directed_net_type::const_reverse_node_iterator rpn = directed_net.node_rbegin(); rpn != directed_net.node_rend(); ++rpn)
	{
		EXTL_TEST_TRACE(_T("node:%d"), *rpn);
	}

	EXTL_TEST_TRACE(_T("\narc iterator test:"));
	for (directed_net_type::const_arc_iterator pa = directed_net.arc_begin(); pa != directed_net.arc_end(); ++pa)
	{
		EXTL_TEST_TRACE(_T("arc:%d->%d"), (*pa).first(), (*pa).second());
	}

	EXTL_TEST_TRACE(_T("\nreverse arc iterator test:"));
	for (directed_net_type::const_reverse_arc_iterator rpa = directed_net.arc_rbegin(); rpa != directed_net.arc_rend(); ++rpa)
	{
		EXTL_TEST_TRACE(_T("arc:%d->%d"), (*rpa).first(), (*rpa).second());
	}

	EXTL_TEST_TRACE(_T("\nout-adjacent node iterator(id = 1) test:"));
	for (directed_net_type::const_out_adjnode_iterator poan = directed_net.out_adjnode_begin(1); poan != directed_net.out_adjnode_end(1); ++poan)
	{
		EXTL_TEST_TRACE(_T("node:%d"), *poan);
	}
	EXTL_TEST_TRACE(_T("\nreverse out-adjacent node iterator(id = 1) test:"));
	for (directed_net_type::const_reverse_out_adjnode_iterator rpoan = directed_net.out_adjnode_rbegin(1); rpoan != directed_net.out_adjnode_rend(1); ++rpoan)
	{
		EXTL_TEST_TRACE(_T("node:%d"), *rpoan);
	}

	EXTL_TEST_TRACE(_T("\nin-adjacent node iterator(id = 1) test:"));
	for (directed_net_type::const_in_adjnode_iterator pian = directed_net.in_adjnode_begin(1); pian != directed_net.in_adjnode_end(1); ++pian)
	{
		EXTL_TEST_TRACE(_T("node:%d"), *pian);
	}
	EXTL_TEST_TRACE(_T("\nreverse in-adjacent node iterator(id = 1) test:"));
	for (directed_net_type::const_reverse_in_adjnode_iterator rpian = directed_net.in_adjnode_rbegin(1); rpian != directed_net.in_adjnode_rend(1); ++rpian)
	{
		EXTL_TEST_TRACE(_T("node:%d"), *rpian);
	}

	/* after remove_node(1)
	 * 
	 *  
	 * 0                               2
	 * |                               |
	 * '-------------->3<--------------'
	 */
	directed_net.remove_node(1);

	EXTL_ASSERT(directed_net.nodes_size() == 3);
	EXTL_ASSERT(directed_net.arcs_size() == 2);

	EXTL_ASSERT(directed_net.in_degree(0) == 0);
	EXTL_ASSERT(directed_net.out_degree(0) == 1);
	EXTL_ASSERT(directed_net.degree(0) == 1);

	EXTL_ASSERT(!directed_net.node_exists(1));
	EXTL_ASSERT(!directed_net.arc_exists(0, 1));
	EXTL_ASSERT(!directed_net.arc_exists(1, 0));
	EXTL_ASSERT(!directed_net.arc_exists(1, 2));
	EXTL_ASSERT(!directed_net.arc_exists(2, 1));

	EXTL_ASSERT(directed_net.in_degree(2) == 0);
	EXTL_ASSERT(directed_net.out_degree(2) == 1);
	EXTL_ASSERT(directed_net.degree(2) == 1);

	EXTL_ASSERT(directed_net.in_degree(3) == 2);
	EXTL_ASSERT(directed_net.out_degree(3) == 0);
	EXTL_ASSERT(directed_net.degree(3) == 2);

	/* after remove_arc(0, 3)
	 * 
	 *  
	 * 0                               2
	 *                                 |
	 *                 3<--------------'
	 */
	directed_net.remove_arc(0, 3);

	EXTL_ASSERT(directed_net.nodes_size() == 3);
	EXTL_ASSERT(directed_net.arcs_size() == 1);

	EXTL_ASSERT(directed_net.in_degree(0) == 0);
	EXTL_ASSERT(directed_net.out_degree(0) == 0);
	EXTL_ASSERT(directed_net.degree(0) == 0);

	EXTL_ASSERT(!directed_net.node_exists(1));
	EXTL_ASSERT(!directed_net.arc_exists(0, 1));
	EXTL_ASSERT(!directed_net.arc_exists(1, 0));
	EXTL_ASSERT(!directed_net.arc_exists(1, 2));
	EXTL_ASSERT(!directed_net.arc_exists(2, 1));
	EXTL_ASSERT(!directed_net.arc_exists(0, 3));

	EXTL_ASSERT(directed_net.in_degree(2) == 0);
	EXTL_ASSERT(directed_net.out_degree(2) == 1);
	EXTL_ASSERT(directed_net.degree(2) == 1);

	EXTL_ASSERT(directed_net.in_degree(3) == 1);
	EXTL_ASSERT(directed_net.out_degree(3) == 0);
	EXTL_ASSERT(directed_net.degree(3) == 1);

	directed_net.clear();

	EXTL_ASSERT(directed_net.nodes_size() == 0);
	EXTL_ASSERT(directed_net.arcs_size() == 0);

	/* ///////////////////////////////////////////////////////////////////////
	 * indirected net test
	 * 
	 *  /--------------1--------------\
	 * 0                               2
	 * |                               |
	 * '---------------3---------------'
	 */
	EXTL_TEST_TRACE(_T("\nindirected net test:"));
	typedef basic_net<e_false_v, int, int>			indirected_net_type;
	indirected_net_type								indirected_net(10);

	EXTL_ASSERT(indirected_net.max_nodes_size() == 10);
	EXTL_ASSERT(indirected_net.max_arcs_size() == 55);	// 10 * 11 / 2

	indirected_net.insert_node(0);
	indirected_net.insert_node(1);
	indirected_net.insert_node(2);
	indirected_net.insert_arc(0, 1);
	indirected_net.insert_arc(2, 1);
	indirected_net.insert_arc(1, 2);
	indirected_net.insert_arc(0, 3);
	indirected_net.insert_arc(2, 3);

	EXTL_ASSERT(indirected_net.nodes_size() == 4);
	EXTL_ASSERT(indirected_net.arcs_size() == 4);

	EXTL_ASSERT(indirected_net.degree(0) == 2);
	EXTL_ASSERT(indirected_net.degree(1) == 2);
	EXTL_ASSERT(indirected_net.degree(2) == 2);
	EXTL_ASSERT(indirected_net.degree(3) == 2);

	EXTL_TEST_TRACE(_T("\nnode iterator test:"));
	for (indirected_net_type::const_node_iterator ipn = indirected_net.node_begin(); ipn != indirected_net.node_end(); ++ipn)
	{
		EXTL_TEST_TRACE(_T("node:%d"), *ipn);
	}

	EXTL_TEST_TRACE(_T("\nreverse node iterator test:"));
	for (indirected_net_type::const_reverse_node_iterator ripn = indirected_net.node_rbegin(); ripn != indirected_net.node_rend(); ++ripn)
	{
		EXTL_TEST_TRACE(_T("node:%d"), *ripn);
	}

	EXTL_TEST_TRACE(_T("\narc iterator test:"));
	for (indirected_net_type::const_arc_iterator ipa = indirected_net.arc_begin(); ipa != indirected_net.arc_end(); ++ipa)
	{
		EXTL_TEST_TRACE(_T("arc:%d-%d"), (*ipa).first(), (*ipa).second());
	}

	EXTL_TEST_TRACE(_T("\nreverse arc iterator test:"));
	for (indirected_net_type::const_reverse_arc_iterator ripa = indirected_net.arc_rbegin(); ripa != indirected_net.arc_rend(); ++ripa)
	{
		EXTL_TEST_TRACE(_T("arc:%d-%d"), (*ripa).first(), (*ripa).second());
	}

	EXTL_TEST_TRACE(_T("\nadjacent node iterator(id = 1) test:"));
	for (indirected_net_type::const_adjnode_iterator ipian = indirected_net.adjnode_begin(1); ipian != indirected_net.adjnode_end(1); ++ipian)
	{
		EXTL_TEST_TRACE(_T("node:%d"), *ipian);
	}
	EXTL_TEST_TRACE(_T("\nreverse adjacent node iterator(id = 1) test:"));
	for (indirected_net_type::const_reverse_adjnode_iterator ripian = indirected_net.adjnode_rbegin(1); ripian != indirected_net.adjnode_rend(1); ++ripian)
	{
		EXTL_TEST_TRACE(_T("node:%d"), *ripian);
	}

	/* after remove_node(1)
	 * 
	 *  
	 * 0                               2
	 * |                               |
	 * '---------------3---------------'
	 */
	indirected_net.remove_node(1);

	EXTL_ASSERT(indirected_net.nodes_size() == 3);
	EXTL_ASSERT(indirected_net.arcs_size() == 2);

	EXTL_ASSERT(indirected_net.degree(0) == 1);
	EXTL_ASSERT(indirected_net.degree(2) == 1);
	EXTL_ASSERT(indirected_net.degree(3) == 2);

	EXTL_ASSERT(!indirected_net.node_exists(1));
	EXTL_ASSERT(!indirected_net.arc_exists(0, 1));
	EXTL_ASSERT(!indirected_net.arc_exists(1, 0));
	EXTL_ASSERT(!indirected_net.arc_exists(2, 1));

	/* after remove_arc(0, 3)
	 * 
	 *  
	 * 0                               2
	 *                                 |
	 *                 3---------------'
	 */
	indirected_net.remove_arc(0, 3);

	EXTL_ASSERT(indirected_net.nodes_size() == 3);
	EXTL_ASSERT(indirected_net.arcs_size() == 1);

	EXTL_ASSERT(indirected_net.degree(0) == 0);
	EXTL_ASSERT(indirected_net.degree(2) == 1);
	EXTL_ASSERT(indirected_net.degree(3) == 1);

	EXTL_ASSERT(!indirected_net.node_exists(1));
	EXTL_ASSERT(!indirected_net.arc_exists(0, 1));
	EXTL_ASSERT(!indirected_net.arc_exists(1, 0));
	EXTL_ASSERT(!indirected_net.arc_exists(2, 1));
	EXTL_ASSERT(!indirected_net.arc_exists(0, 3));

	indirected_net.clear();

	EXTL_ASSERT(indirected_net.nodes_size() == 0);
	EXTL_ASSERT(indirected_net.arcs_size() == 0);
	

	return 0;
}
int basic_net_test_ret = basic_net_test();

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(basic_net_test)
EXTL_END_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONTAINER_BASIC_NET_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

