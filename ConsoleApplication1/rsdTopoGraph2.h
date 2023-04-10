
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
	BOTH = 0,        //˫����
	SINGLE = 1,     //������
	NONE = 99,   //��������ͨ

};


//�ڵ�ʾ��
class netElement
{
public:
	//�������дȱʡ���캯��

	string m_ID;
	int    m_index;
	string m_name;
	int    m_type;

	//����ó�Ա��ʼ����
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

//�߹�ϵʾ��
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
	//�������дȱʡ���캯��

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
			netElement, netRelation >;
		/*std::shared_ptr<netElement>, std::shared_ptr<netRelation> >;*/

	//�ڵ㼰��������
		using VertexDesc = Graph::vertex_descriptor;
		using EdgeDesc = Graph::edge_descriptor;

		//�ڵ������
		using VertexIte = boost::graph_traits<Graph>::vertex_iterator;
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

		bool delNode(netElement& node)
		{
			VertexIte vi, vi_end;
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



		//��ӡ������Ժ���

		void print(std::ostream& out)
		{

			print_graph(graph_, get(&netElement::m_name, graph_), out << "---�ڽӱ���\n");
			print_edges(graph_, get(&netElement::m_name, graph_), out << "---�߼���\n");
			print_vertices(graph_, get(&netElement::m_name, graph_), out << "---�㼯��\n");

			//�������
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
		}

		int networkLevel;  //����ͼ�ĵȼ�

	
		//���½ڵ������(ID���ܱ�)
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
		//���±ߵ�����(ID���ܱ�)
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


		//�ڲ�ʹ�ú��� ��Ҫ�ǰ����ڵ�ͱߵĲ�ѯ ���������ж��Ƿ����
		
		bool  hasVertex(netElement& node, VertexDesc& nodeDescriper)
		{

			VertexIte vi, vi_end;
			for (tie(vi, vi_end) = vertices(graph_); vi != vi_end; ++vi)
			{
				auto descriptor = *vi;
				netElement curNode = graph_[descriptor];
				//�˴���Ϊ����==�������
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
				//�˴���Ϊ����==�������
				if (curEdge == edge)
				{
					edgeDescriper = descriptor;
					return true;
				}
			}
			return false;
		}


		protected:
			//�ڲ�����ʹ��
			//�ж�vertex desc�Ƿ��Ѿ�����
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

			//�ж�edge desc�Ƿ��Ѿ�����
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