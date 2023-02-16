//=======================================================================
// Copyright 2012
// Authors: David Doria
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#include <boost/graph/directed_graph.hpp> // A subclass to provide reasonable arguments to adjacency_list for a typical directed graph
#include <boost//graph/graph_traits.hpp>
#include <vector>
#include <string.h>
#include <iostream>
#include <boost/graph/graph_utility.hpp>

#include <memory>
#include "boost/graph/random.hpp"
#include <random>
#include "rsdTopoGraph2.h"
#include "rsdTopoGraph.h"


using namespace boost;
using namespace std;
using namespace rsdTopo;

int tryDbLink();



class VertexInfo
{
public:
	VertexInfo(int i) : id(i) {}
	int id;
};



void testChild()
{
	//试验子类节点的添加方式
	netElement2 vvp0;
	netElement2 vvp1;

	rsdTopoGraph g;

	netRelation e0; e0.setIndex(0); e0.setName("e0");
	g.ensureEdge(vvp0, vvp1, e0);
}

void testOut()
{
	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS
		, netElement, netRelation > Graph;
	Graph g;
	const std::string base_filename{ "save_graph_to_dot_test_empty_directed_graph" };
	const std::string dot_filename{ base_filename + ".dot" };
	std::ofstream f(dot_filename);
	boost::write_graphviz(f, g);
}

void testGraph()
{

	//testOut();
	//testChild();
	//初始化节点
	netElement vp0("0"); vp0.setIndex(0); vp0.setName("a");
	netElement vp1("1"); vp1.setIndex(1); vp1.setName("b");
	netElement vp2("2"); vp2.setIndex(2); vp2.setName("c");
	netElement vp3("3"); vp3.setIndex(3); vp3.setName("d");
	netElement vp4("4"); vp4.setIndex(4); vp4.setName("e");

	netRelation e0("0"); e0.setIndex(0); e0.setName("e0");
	netRelation e1("1"); e1.setIndex(1); e1.setName("e1");
	netRelation e2("2"); e2.setIndex(2); e2.setName("e2");
	netRelation e3("3"); e3.setIndex(3); e3.setName("e3");
	netRelation e4("4"); e4.setIndex(4); e4.setName("e4");
	netRelation e5("5"); e5.setIndex(5); e5.setName("e5");
	netRelation e6("6"); e6.setIndex(6); e6.setName("e6");

	rsdTopoGraph g;


	g.ensureEdge(vp0, vp1, e0);
	g.ensureEdge(vp0, vp3, e1);
	g.ensureEdge(vp1, vp3, e2);
	g.ensureEdge(vp2, vp0, e3);
	g.ensureEdge(vp2, vp4, e4);
	g.ensureEdge(vp3, vp2, e5);
	g.ensureEdge(vp3, vp4, e6);


	//g.test(vp2);
	g.test(e5);
	g.test2(vp3);
	netElement newNode = vp1;
	vp1.m_name = "maoning";
	g.updateVertexElement(vp1);

	//输出dot文件
	std::string base_filename{ "rsdGraph" };
	std::string dot_filename{ base_filename + ".dot" };
	std::string svg_filename{ base_filename + ".svg" };
	//g.dotOut(dot_filename);
	g.svgOut(dot_filename, svg_filename);

	//修改后测试输出
	/*g.delNode(vp0);
	base_filename = "rsdGraph_test1";
	dot_filename = base_filename + ".dot";
	svg_filename = base_filename + ".svg";
	g.svgOut(dot_filename, svg_filename);*/


	//输出某一节点的所有出边
	/*typename boost::graph_traits<zcGudaoTopo>::out_edge_iterator ei, ei_end;
	for (auto e : make_iterator_range(out_edges(src, zcGraph)))
	{

		std::cout << zcGraph[source(e, zcGraph)].m_index << " --> "
			<< zcGraph[target(e, zcGraph)].m_index << std::endl;
	}*/

	//int dd = dow(12, 7, 2023);
}

void testDb()
{
	tryDbLink();
}
int main(int, char* [])
{

	//testGraph();
	testDb();
	


	return 0;
}


//void makeGraph1(zcGudaoTopo& zcGraph)
//{
//	vertexPropSample vp0(0, "a");
//	vertexPropSample vp1(1, "b");
//	vertexPropSample vp2(2, "c");
//	vertexPropSample vp3(3, "d");
//	vertexPropSample vp4(4, "e");
//
//
//
//	//定义节点描述器
//	typedef boost::graph_traits<zcGudaoTopo>::vertex_descriptor zcVertex;
//
//
//
//	//添加节点
//	zcVertex pt0 = add_vertex(vp0, zcGraph);
//	zcVertex pt1 = add_vertex(vp1, zcGraph);
//	zcVertex pt2 = add_vertex(vp2, zcGraph);
//	zcVertex pt3 = add_vertex(vp3, zcGraph);
//	zcVertex pt4 = add_vertex(vp4, zcGraph);
//
//	//添加有向边
//	add_edge(pt0, pt1, zcGraph);
//	add_edge(pt0, pt3, zcGraph);
//	add_edge(pt1, pt3, zcGraph);
//	add_edge(pt2, pt0, zcGraph);
//	add_edge(pt2, pt4, zcGraph);
//	add_edge(pt3, pt2, zcGraph);
//	add_edge(pt3, pt4, zcGraph);
//}







	/*typedef boost::directed_graph<> Graph;
	Graph g;
	boost::graph_traits< Graph >::vertex_descriptor v0 = g.add_vertex();
	boost::graph_traits< Graph >::vertex_descriptor v1 = g.add_vertex();

	g.add_edge(v0, v1);

	boost::graph_traits<Graph>::edge_descriptor e;
	bool b = is_selfloop(e,g);


	int vertex_index = 2;
	boost::graph_traits<Graph>::vertex_descriptor v = boost::vertex(vertex_index, g);*/



	//rsdTopoGraph<> map;

	//Map map; // load the map
	//graph_traits< Map >::vertex_descriptor v00;
	//v00=add_vertex(map);
	//Map::vertex_descriptor v1 = *vertices(map).first;
	//Map::vertex_descriptor v2 = vertex(0,map);
	/*map[v].name = "Troy";
	map[v].population = 49170;
	map[v].zipcodes.push_back(12180);
	*/

	//map[graph_bundle].name = "United States";
	//map[graph_bundle].use_right = true;
	//map[graph_bundle].use_metric = false;




