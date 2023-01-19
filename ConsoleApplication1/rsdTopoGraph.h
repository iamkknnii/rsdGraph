#pragma once
//=======================================================================
// Copyright 2022
// Authors: Maoning
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#include <boost/graph/directed_graph.hpp> // A subclass to provide reasonable arguments to adjacency_list for a typical directed graph
#include <boost//graph/graph_traits.hpp>
#include <vector>
#include <string.h>
using namespace boost;
using namespace std;

//网络层次枚举
enum zcNetWorkLevel
{
	Macro = 0,    //宏观层次
	Meso = 1,     //中观层次
 	Micro = 2,    //微观层次
	Nano=3,       //细节

};

//节点示例
class vertexPropSample
{
public:
	//好像必须写缺省构造函数
	vertexPropSample()
	{
		m_uID = "UUID";
		m_index = 0;
		m_name = "sample";
		m_type = 0;
	}

	vertexPropSample(int myIndex)
	{
		m_uID = "UUID";
		m_index = myIndex;
		m_name = "sampleVertex";
		m_type = 0;
	}
	vertexPropSample(int myIndex,string name)
	{
		m_uID = "UUID";
		m_index = myIndex;
		m_name = name;
		m_type = 0;
	}
	void setName(string name)
	{
		m_name = name;
	}
	string m_uID;
	int    m_index;
	string m_name;
	int    m_type;
};

//边示例
class edgePropSample
{
public:
	//好像必须写缺省构造函数
	edgePropSample()
	{
		m_uID = "UUID";
		m_index = 0;
		m_name = "sampleEdge";
		m_type = 0;
	}

	edgePropSample(int myIndex)
	{
		m_uID = "UUID";
		m_index = myIndex;
		m_name = "sample";
		m_type = 0;
	}
	edgePropSample(int myIndex, string name)
	{
		m_uID = "UUID";
		m_index = myIndex;
		m_name = name;
		m_type = 0;
	}
	void setName(string name)
	{
		m_name = name;
	}
	string m_uID;
	int    m_index;
	string m_name;
	int    m_type;
};


//namespace rsdTopo
//{
//	// 站场拓扑图基类模板
//	template < class OutEdgeListS = vecS,
//		class VertexListS = vecS,
//		class DirectedS = directedS, class VertexProperty = no_property,
//		class EdgeProperty = no_property, class GraphProperty = no_property,
//		class EdgeListS = listS >
//		class rsdTopoGraph : public adjacency_list< OutEdgeListS, VertexListS, DirectedS, VertexProperty, EdgeProperty, GraphProperty, EdgeListS>
//	{
//
//	public:
//		
//	public:
//		//typedef graph_traits<rsdTopoGraph>::vertices_size_type vertices_size_type;
//		rsdTopoGraph(int level= zcNetWorkLevel::Micro)
//		{
//			networkLevel = level;
//		}
//
//			template < class EdgeIterator >
//			rsdTopoGraph(EdgeIterator first, EdgeIterator last, int n, const GraphProperty& p = GraphProperty())
//				: adjacency_list( first, last,n)
//			{
//
//			}
//
//
//		int networkLevel;
//	};
//
//}

//重定义的示例
/*
typedef rsdTopo::rsdTopoGraph<
	boost::listS, boost::vecS, boost::bidirectionalS,
	no_property, no_property, no_property , boost::listS>	zcGudaoTopo;   //股道用双向图

typedef rsdTopo::rsdTopoGraph<
	boost::listS, boost::vecS, boost::directedS,
	no_property, no_property, no_property, boost::listS>	zcDrainTopo;     //排水单向图

typedef rsdTopo::rsdTopoGraph<
	boost::listS, boost::vecS, boost::undirectedS,
	no_property, no_property, no_property, boost::listS>	zcEqTopo;       //设备用无向图
*/

