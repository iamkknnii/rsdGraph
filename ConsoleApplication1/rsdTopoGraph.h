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

//������ö��
enum zcNetWorkLevel
{
	Macro = 0,    //��۲��
	Meso = 1,     //�й۲��
 	Micro = 2,    //΢�۲��
	Nano=3,       //ϸ��

};

//�ڵ�ʾ��
class vertexPropSample
{
public:
	//�������дȱʡ���캯��
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

//��ʾ��
class edgePropSample
{
public:
	//�������дȱʡ���캯��
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
//	// վ������ͼ����ģ��
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

//�ض����ʾ��
/*
typedef rsdTopo::rsdTopoGraph<
	boost::listS, boost::vecS, boost::bidirectionalS,
	no_property, no_property, no_property , boost::listS>	zcGudaoTopo;   //�ɵ���˫��ͼ

typedef rsdTopo::rsdTopoGraph<
	boost::listS, boost::vecS, boost::directedS,
	no_property, no_property, no_property, boost::listS>	zcDrainTopo;     //��ˮ����ͼ

typedef rsdTopo::rsdTopoGraph<
	boost::listS, boost::vecS, boost::undirectedS,
	no_property, no_property, no_property, boost::listS>	zcEqTopo;       //�豸������ͼ
*/

