
#pragma once
//=======================================================================
// Copyright 2022
// Authors: Maoning
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>



#include <map>
#include <set>
#include <utility>
#include <vector>
#include <string>
#include <iostream>


#include "make_bundle_writer.h"


using namespace boost;
using namespace std;

//网络层次枚举
enum zcNetWorkLevel
{
	Macro = 0,    //宏观层次
	Meso = 1,     //中观层次
	Micro = 2,    //微观层次
	Nano = 3,       //细节

};

//股道关系连通类型枚举
enum zcNetNavigablity
{
	BOTH = 0,        //双联接
	SINGLE = 1,     //单联接
	NONE = 99,   //非物理连通

};


//节点示例
class netElement
{
public:
	//好像必须写缺省构造函数

	string m_ID;
	int    m_index;
	string m_name;
	int    m_type;

	//最好用成员初始化表
	netElement(
		const std::string& uID = "",
		const std::string& name = "",
		const int type = 0.0,
		const int index = 0.0
	) :  m_ID(uID), m_name(name), m_type(type), m_index(index)
	{
	}

	void setIndex(int myIndex)
	{
		m_index = myIndex;

	}

	void setName(string name)
	{
		m_name = name;
	}


	bool operator ==(const netElement& vertex)
	{
		if (m_ID == vertex.m_ID)
		{
			return true;
		}

		return false;
	}
};

class netElement2 : public netElement
{
public:
	string myID;
};

//边关系示例
class netRelation
{
public:
	netRelation(
		const std::string& uID = "",
		const std::string& name = "",
		const int type = 0.0,
		const int index = 0.0
	) :  m_ID(uID), m_name(name), m_type(type), m_index(index)
	{
	}
	//好像必须写缺省构造函数

	void setName(string name)
	{
		m_name = name;

	}

	void setIndex(int myIndex)
	{
		m_index = myIndex;

	}

	string m_ID;
	int    m_index;
	string m_name;
	int    m_type;

	bool operator ==(const netRelation& edge)
	{
		if (m_ID == edge.m_ID)
		{
			return true;
		}

		return false;
	}
};

namespace rsdTopo
{
	// 站场拓扑图基类模板
	class rsdTopoGraph
	{
	public:
		rsdTopoGraph()

		{
			networkLevel = zcNetWorkLevel::Micro;
		}
		rsdTopoGraph(int nLevel)

		{
			networkLevel = nLevel;
		}

		using Graph = boost::adjacency_list<
			boost::vecS, boost::vecS, boost::bidirectionalS,
			netElement, netRelation >;
		/*std::shared_ptr<netElement>, std::shared_ptr<netRelation> >;*/

	//节点及边描述器
		using VertexDesc = Graph::vertex_descriptor;
		using EdgeDesc = Graph::edge_descriptor;

		//节点遍历器
		using VertexIte = boost::graph_traits<Graph>::vertex_iterator;
		//边遍历器
		using EdgeIte = boost::graph_traits<Graph>::edge_iterator;


		/*using VertexDesc = boost::graph_traits<Graph>::vertex_descriptor;
		using EdgeDesc = boost::graph_traits<Graph>::edge_descriptor;*/

		//在图中增加节点（安全有保证）

		VertexDesc ensureNode(netElement& node)
		{
			if (auto it = vertexMap_.find(node.m_name); it != vertexMap_.end())
				return it->second;

			auto descriptor = add_vertex(node, graph_);
			vertexMap_[node.m_name] = descriptor;
			vertexMap_.emplace(node.m_name, descriptor);
			return descriptor;
		}
		// 在图中增加边（安全有保证）
		EdgeDesc ensureEdge(netElement& src, netElement& dst, netRelation edge)
		{
			auto [descriptor, isnew] =
				add_edge(ensureNode(src), ensureNode(dst), std::move(edge), graph_);
			return descriptor; // 
		}
		//以节点名称为匹配删除节点（遍历map）

		bool delNode(const string nodeName)
		{
			auto it = vertexMap_.find(nodeName);
			if (it != vertexMap_.end())
			{
				auto descriptor = it->second;
				clear_vertex(descriptor, graph_);
				remove_vertex(descriptor, graph_);
				vertexMap_.erase(it);
				return true;
			}

			return false;

		}

		//以节点对象整体为匹配 删除节点（遍历graph）

		bool delNode(netElement& node)
		{
			VertexIte vi, vi_end;
			for (tie(vi, vi_end) = vertices(graph_); vi != vi_end; ++vi)
			{
				auto descriptor = *vi;
				netElement curNode = graph_[descriptor];
				//此处改为重载==后的内容
				if (curNode == node)
				{
					clear_vertex(descriptor, graph_);
					remove_vertex(descriptor, graph_);
					auto it = vertexMap_.find(curNode.m_name);
					if (it != vertexMap_.end())
					{
						vertexMap_.erase(it);
					}
					return true;
				}
			}

			return false;

		}

		bool  delEdge(netRelation& edge)

		{
			EdgeIte ei, ei_end;
			for (tie(ei, ei_end) = edges(graph_); ei != ei_end; ++ei)
			{
				auto descriptor = *ei;
				netRelation curEdge = graph_[descriptor];
				//此处改为重载==后的内容
				if (curEdge == edge)
				{
					remove_edge(descriptor, graph_);
					return true;
				}
			}

			return false;
		}

		//删除两个节点之间的边 （不一定为一条）
		bool  delEdge(netElement& srcNode, netElement& tarNode)
		{
			auto it = vertexMap_.find(srcNode.m_name);
			if (it == vertexMap_.end())
			{
				return false;
			}

			auto it2 = vertexMap_.find(tarNode.m_name);
			if (it2 == vertexMap_.end())
			{
				return false;
			}

			/*remove_edge(descriptor, *nit, graph_);*/
			auto descriptor = it->second;
			auto descriptor2 = it2->second;

			remove_edge(descriptor, descriptor2, graph_);

			//auto neighbors = adjacent_vertices(descriptor, graph_);

			/*for (auto nit = neighbors.first; nit != neighbors.second; ++nit)
			{

				netElement curNode = graph_[*nit];
				if (curNode == tarNode)
				{
					remove_edge(descriptor,*nit, graph_);
					return true;
				}
			}

			*/

			return true;
		}



		//打印输出测试函数

		void print(std::ostream& out)
		{

			print_graph(graph_, get(&netElement::m_name, graph_), out << "---邻接表表达\n");
			print_edges(graph_, get(&netElement::m_name, graph_), out << "---边集合\n");
			print_vertices(graph_, get(&netElement::m_name, graph_), out << "---点集合\n");

			//简单输出法
		/*	write_graphviz(out, graph_,
				make_label_writer(get(&netElement::m_name, graph_)),
				make_label_writer(get(&netRelation::m_name, graph_)));*/
		}


		//输出dot文件函数
		void dotOut(const std::string& filename)
		{
			std::ofstream f(filename);
			//邻接表需采用vecs ，listS会报错 
			boost::write_graphviz(f, graph_, make_bundled_vertices_writer(graph_), make_bundled_edges_writer(graph_));
		}
		//输出svg文件函数 同时输出dot文件
		void svgOut(const std::string& dot_filename, const std::string& svg_filename)
		{
			dotOut(dot_filename);
			outsvg(dot_filename, svg_filename);
		}

		int networkLevel;  //网络图的等级

	
		//更新节点的属性(ID不能变)
		bool updateVertexElement( netElement& node)
		{
			VertexDesc nodeDescriper;
			if (!hasVertex(node, nodeDescriper))
			{
				return false;
			}
			graph_[nodeDescriper] = node;
			return true;
		}
		//更新边的属性(ID不能变)
		bool updateEdgeRelation(netRelation& node)
		{
			EdgeDesc edgeDescriper;
			if (!hasEdge(node, edgeDescriper))
			{
				return false;
			}
			graph_[edgeDescriper] = node;
			return true;
		}


		//内部使用函数 主要是包括节点和边的查询 根据属性判定是否存在
		
		bool  hasVertex(netElement& node, VertexDesc& nodeDescriper)
		{

			VertexIte vi, vi_end;
			for (tie(vi, vi_end) = vertices(graph_); vi != vi_end; ++vi)
			{
				auto descriptor = *vi;
				netElement curNode = graph_[descriptor];
				//此处改为重载==后的内容
				if (curNode == node)
				{
					nodeDescriper = descriptor;
					return true;
				}
			}
			return false;
		}



		bool  hasEdge(netRelation& edge, EdgeDesc& edgeDescriper)
		{

			EdgeIte ei, ei_end;
			for (tie(ei, ei_end) = edges(graph_); ei != ei_end; ++ei)
			{
				auto descriptor = *ei;
				netRelation curEdge = graph_[descriptor];
				//此处改为重载==后的内容
				if (curEdge == edge)
				{
					edgeDescriper = descriptor;
					return true;
				}
			}
			return false;
		}


		protected:
			//内部函数使用
			//判定vertex desc是否已经存在
			bool isVertexdesc_valid(VertexDesc desc) const
			{
				if constexpr (std::is_integral_v<VertexDesc>)
				{
					return desc >= 0 && desc < num_vertices(graph_);
				}
				else
				{
					auto vds = vertices(graph_);
					return std::count(vds.first, vds.second, desc);
				}
			}

			//判定edge desc是否已经存在
			bool isEdgedesc_valid(EdgeDesc desc) const
			{

				auto eds = edges(graph_);
				return std::count(eds.first, eds.second, desc);

			}

	public:
		void  test(netRelation& node)
		{
			EdgeDesc discrpiter;
			if (!hasEdge(node, discrpiter))
			{
				return;
			}
			if (isEdgedesc_valid(discrpiter))
			{
				netRelation  myNode = graph_[discrpiter];
			}
			
			return;
		}

		void  test2(netElement& node)
		{
			
			VertexDesc discrpiter;
			if (!hasVertex(node, discrpiter))
			{
				return;
			}
			if (isVertexdesc_valid(discrpiter))
			{
				netElement myNode = graph_[discrpiter];
			}

			return;
		}


	private:

		//节点名称加节点索引的map
		std::map<std::string, VertexDesc>             vertexMap_;
		Graph                                         graph_;

		//以下暂时不需要
		//节点名称数组
		//std::vector<std::string>                      vertexLabelArray_;
		//边索引加边名称的map
		//std::map<EdgeDesc, std::string>               edgeLabelMap_;

		//边的节点索引对 的set集合
		//std::set<std::pair<std::string, std::string>> edgeSet_;
	};
}

struct Person
{
	string name;
	int age;

	bool operator<(const Person& other) const
	{
		return name < other.name || (name == other.name && age < other.age);
	}

	bool operator==(const Person& other) const
	{
		return name == other.name && age == other.age;
	}
};

struct PersonHash
{
	size_t operator()(const Person& person) const
	{
		size_t name_hash = std::hash<std::string>{}(person.name);
		size_t age_hash = std::hash<int>{}(person.age);
		return name_hash ^ age_hash;
	}
};

template<typename C, typename T, typename V>
vector<T> find_objects(const C& objects, V T::* member, const std::function<bool(const V&)>& condition) 
{
	vector<T> result;
	for (const auto& obj : objects)
	{
		if (condition(obj.*member))
		{
			result.push_back(obj);
		}
	}
	return result;
}

//template<typename VertexIte, typename G,typename T, typename V, typename Predicate>
//bool find_vertex(VertexIte vi, VertexIte vi_end, T& node, V T::* member, Predicate pred)


template<typename VertexIte, typename G, typename T, typename V>
vector<T>  find_vertex(VertexIte vi, VertexIte vi_end, T& node, V T::* member, const std::function<bool(const V&)>& condition)
{
	vector<T> result;
	for (; vi != vi_end; ++vi) 
	{
		if (condition((*vi).*member))
		{
			node = G[*vi];
			result.push_back(node);
		}
	}
	return result;
}