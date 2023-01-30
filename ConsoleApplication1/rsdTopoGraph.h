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

//节点是否自闭合
template <typename Graph>
bool is_selfloop(typename graph_traits<Graph>::edge_descriptor e, const Graph& g)
{
	typename graph_traits<Graph>::vertex_descriptor u, v;
	u = source(e, g);
	v = target(e, g);
	return u == v;

}



int dow(int m, int d, int  y)
{
	y -= m < 3; return(y + y / 4 - y / 100 + y / 400 + "-bed=pen+mad."[m] + d) % 7;
}

//将文件vcopy到指定目录
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