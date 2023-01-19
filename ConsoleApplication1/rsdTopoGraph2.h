
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

//������ö��
enum zcNetWorkLevel
{
	Macro = 0,    //��۲��
	Meso = 1,     //�й۲��
	Micro = 2,    //΢�۲��
	Nano = 3,       //ϸ��

};

//�ɵ���ϵ��ͨ����ö��
enum zcNetNavigablity
{
	BOTH =0,        //˫����
	SINGLE = 1,     //������
	NONE = 99,   //��������ͨ

};


//�ڵ�ʾ��
class netElement
{
public:
	//�������дȱʡ���캯��

	string m_uID;
	int    m_index;
	string m_name;
	int    m_type;

	//����ó�Ա��ʼ����
	 netElement(
		const std::string& name = "",
		const std::string& uID = "",
		const int type = 0.0,
		const int index = 0.0
	    ): m_name(name),m_uID(uID),m_type(type),m_index(index)
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
		if (m_name == vertex.m_name)
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

//�߹�ϵʾ��
class netRelation
{
public:
	netRelation(
		const std::string& name = "",
		const std::string& uID = "",
		const int type = 0.0,
		const int index = 0.0
	) : m_name(name), m_uID(uID), m_type(type), m_index(index)
	{
	}
	//�������дȱʡ���캯��
	
	void setName(string name)
	{
		m_name = name;
		
	}

	void setIndex(int myIndex)
	{
		m_index = myIndex;
		
	}
	
	string m_uID;
	int    m_index;
	string m_name;
	int    m_type;

	bool operator ==(const netRelation& edge)
	{
		if (m_name == edge.m_name)
		{
			return true;
		}

		return false;
	}
};

namespace rsdTopo
{
	// վ������ͼ����ģ��
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
			netElement,netRelation >;
			/*std::shared_ptr<netElement>, std::shared_ptr<netRelation> >;*/

		//�ڵ㼰��������
		using VertexDesc = Graph::vertex_descriptor;
		using EdgeDesc = Graph::edge_descriptor;

		//�ڵ������
		using VertexIte= boost::graph_traits<Graph>::vertex_iterator;
		//�߱�����
		using EdgeIte = boost::graph_traits<Graph>::edge_iterator;

		


		/*using VertexDesc = boost::graph_traits<Graph>::vertex_descriptor;
		using EdgeDesc = boost::graph_traits<Graph>::edge_descriptor;*/

		//��ͼ�����ӽڵ㣨��ȫ�б�֤��
		
		VertexDesc ensureNode(netElement& node)
		{
			if (auto it = vertexMap_.find(node.m_name); it != vertexMap_.end())
				return it->second;

			auto descriptor = add_vertex(node, graph_);
			vertexMap_[node.m_name] = descriptor;
			vertexMap_.emplace(node.m_name, descriptor);
			return descriptor;
		}
		// ��ͼ�����ӱߣ���ȫ�б�֤��
		EdgeDesc ensureEdge(netElement& src, netElement& dst, netRelation edge)
		{
			auto [descriptor, isnew] =
				add_edge(ensureNode(src), ensureNode(dst), std::move(edge), graph_);
			return descriptor; // 
		}
		//�Խڵ�����Ϊƥ��ɾ���ڵ㣨����map��
		
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

		//�Խڵ��������Ϊƥ�� ɾ���ڵ㣨����graph��

		bool delNode(netElement&  node)
		{
			VertexIte vi ,vi_end;
			for (tie(vi, vi_end) = vertices(graph_); vi != vi_end; ++vi)
			{
				auto descriptor = *vi;
				netElement curNode = graph_[descriptor];
				//�˴���Ϊ����==�������
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
				//�˴���Ϊ����==�������
				if (curEdge == edge)
				{
					remove_edge(descriptor, graph_);
					return true;
				}
			}

			return false;
		}

		//ɾ�������ڵ�֮��ı� ����һ��Ϊһ����
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

			/*auto neighbors = adjacent_vertices(descriptor, graph_);

			for (auto nit = neighbors.first; nit != neighbors.second; ++nit)
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
		
	

		//��ӡ������Ժ���

		void print(std::ostream& out)  
		{

			print_graph(graph_, get(&netElement::m_name, graph_), out << "---�ڽӱ�����\n");
			print_edges(graph_, get(&netElement::m_name, graph_), out << "---�߼���\n");
			print_vertices(graph_, get(&netElement::m_name, graph_), out << "---�㼯��\n");

		/*	write_graphviz(out, graph_,
				make_label_writer(get(&netElement::m_name, graph_)),
				make_label_writer(get(&netRelation::m_name, graph_)));*/
		}

	
		//���dot�ļ�����
		void dotOut(const std::string& filename)
		{
			std::ofstream f(filename);
			//�ڽӱ������vecs ��listS�ᱨ�� 
			boost::write_graphviz(f, graph_, make_bundled_vertices_writer(graph_), make_bundled_edges_writer(graph_));
		}
		//���svg�ļ����� ͬʱ���dot�ļ�
		void svgOut(const std::string& dot_filename, const std::string& svg_filename)
		{
			dotOut(dot_filename);
			outsvg(dot_filename, svg_filename);

			//���ļ�vcopy��ָ��Ŀ¼
		/*	copy_file(
				dot_filename,
				"../BoostGraphTutorial/" + dot_filename,
				copy_file_mode::allow_overwrite
			);
			copy_file(
				svg_filename,
				"../BoostGraphTutorial/" + svg_filename,
				copy_file_mode::allow_overwrite
			);
			std::remove(dot_filename.c_str());
			std::remove(svg_filename.c_str());*/
		}


		int networkLevel;  //����ͼ�ĵȼ�
	private:

		//�ڵ����Ƽӽڵ�������map
		std::map<std::string, VertexDesc>             vertexMap_;
		Graph                                         graph_;

		//������ʱ����Ҫ
		//�ڵ���������
		//std::vector<std::string>                      vertexLabelArray_;
		//�������ӱ����Ƶ�map
		//std::map<EdgeDesc, std::string>               edgeLabelMap_;
		
		//�ߵĽڵ������� ��set����
		//std::set<std::pair<std::string, std::string>> edgeSet_;
		
	};
}