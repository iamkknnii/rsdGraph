//=======================================================================
// Copyright 2012
// Authors: David Doria
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#include <boost/graph/directed_graph.hpp> // A subclass to provide reasonable arguments to adjacency_list for a typical directed graph
#include <boost/graph/graph_traits.hpp>
#include <vector>
#include <string.h>
#include <iostream>
#include <boost/graph/graph_utility.hpp>
#include <boost/range/algorithm.hpp >

#include <memory>
#include "boost/graph/random.hpp"
#include <random>
#include "rsdTopoGraph2.h"
#include "rsdTopoGraph.h"


#include <boost/graph/adjacency_list.hpp>

#include <boost/graph/iteration_macros.hpp>
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


struct netVertex{
	int id;
	std::string name;
};
struct netEdge {
	int length;
	std::string level;
};

// 定义图类型
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS,
	netVertex, netEdge> Graph;
// 深度优先搜索的回调函数
//struct dfs_callback : public boost::default_dfs_visitor
//{
//	std::vector<int>& result;
//	const Graph& g;
//
//	dfs_callback(std::vector<int>& res, const Graph& graph)
//		: result(res), g(graph) {}
//
//	// 检查当前节点的所有出边的捆绑属性
//	void discover_vertex(Graph::vertex_descriptor v, const Graph& g) const
//	{
//		typename boost::graph_traits<Graph>::edge_iterator ei, ei_end;
//		for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
//		{
//			//for (auto e : out_edges(v, g)) 
//			{
//				auto rel = g[*ei];
//				if (rel.level == "高速" && rel.length < 100)
//				{
//					auto neighbor = boost::target(*ei, g);
//					result.push_back(neighbor);
//					dfs_callback callback(result, g);
//					boost::depth_first_search(g, boost::visitor(callback), boost::root_vertex(neighbor));
//				}
//			}
//		}
//	}
//
//};

// 定义一个自定义访问者
struct my_visitor : default_dfs_visitor
{
	static std::vector<int> visited_nodes; // 存储已访问节点的数组
	int target_edge_property = 100; // 目标边属性的值
	template <typename Vertex, typename Graph>
	 void discover_vertex(Vertex u, const Graph& g) 
	{
		// 将访问到的节点添加到visited_nodes数组中
		 
		visited_nodes.push_back(u);
	}

	 //template <typename Vertex, typename Graph>
	 //void initialize_vertex(Vertex u, const Graph& g)
	 //{
		// return;
	 //}
	

	template <typename Edge, typename Graph>
	void examine_edge(Edge e, const Graph& g) const
	{
		return;
		// 检查当前遍历到的边的属性是否符合条件
		/*if (g[e].length < target_edge_property)
		{
			
			return false;
		}*/
	}
};

// 在定义结构体外部初始化visited_nodes数组
std::vector<int> my_visitor::visited_nodes;

	int main(int, char* [])
	{
		Graph g;
		auto v1 = boost::add_vertex(netVertex{ 0, "A" }, g);
		auto v2 = boost::add_vertex(netVertex{ 1, "B" }, g);
		auto v3 = boost::add_vertex(netVertex{ 2, "C" }, g);
		auto v4 = boost::add_vertex(netVertex{ 3, "D" }, g);
		auto v5 = boost::add_vertex(netVertex{ 4, "E" }, g);
		auto v6 = boost::add_vertex(netVertex{ 5, "F" }, g);
		auto v7 = boost::add_vertex(netVertex{ 6, "G" }, g);
		auto v8 = boost::add_vertex(netVertex{ 7, "H" }, g);
		auto v9 = boost::add_vertex(netVertex{ 8, "I" }, g);

		boost::add_edge(v1, v2, netEdge{ 100, "普通" }, g);
		boost::add_edge(v1, v5, netEdge{ 50, "高速" }, g);
		boost::add_edge(v2, v3, netEdge{ 80, "普通" }, g);
		boost::add_edge(v2, v6, netEdge{ 120, "高速" }, g);
		boost::add_edge(v3, v4, netEdge{ 150, "普通" }, g);
		boost::add_edge(v3, v7, netEdge{ 90, "高速" }, g);
		boost::add_edge(v4, v8, netEdge{ 200, "高速" }, g);
		boost::add_edge(v5, v6, netEdge{ 70, "普通" }, g);
		boost::add_edge(v5, v9, netEdge{ 100, "高速" }, g);
		boost::add_edge(v6, v7, netEdge{ 130, "普通" }, g);
		boost::add_edge(v7, v8, netEdge{ 180, "普通" }, g);
		boost::add_edge(v8, v9, netEdge{ 150, "高速" }, g);
		// 从起始节点 v2 出发搜索
// 		std::vector<int> result;
// 		dfs_callback callback(result, g);
// 		boost::depth_first_search(g, boost::visitor(callback), boost::root_vertex(v2));
// 		// 输出结果
// 		std::cout << "Search results:" << std::endl;
// 		for (auto node : result)
// 		{
// 			std::cout << "Node " << g[node].name << std::endl;
// 		}

		//testGraph();
		//testDb();

		 // 定义一个自定义访问者对象
		my_visitor vis;

		//// 使用DFS算法遍历图形，并使用自定义访问者处理每个节点
		   // 使用DFS算法遍历图形，并使用自定义访问者处理每个节点
		depth_first_search(g, visitor(vis).root_vertex(v2));

		// 输出存储的节点
		std::cout << "Visited nodes: ";
		for (int node : my_visitor::visited_nodes) {
			std::cout << node << " ";
		}
		std::cout << std::endl;
	
	
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




