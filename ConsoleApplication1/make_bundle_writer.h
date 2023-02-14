#pragma once

#include <ostream>
#include <sstream>
#include <string>
#include <algorithm>

#include <boost/algorithm/string/replace.hpp>
#include <stdexcept>

enum class copy_file_mode { allow_overwrite, prevent_overwrite };


std::string graphviz_encode(std::string s) noexcept
{
    boost::algorithm::replace_all(s, ",", "$$$COMMA$$$");
    boost::algorithm::replace_all(s, " ", "$$$SPACE$$$");
    boost::algorithm::replace_all(s, "\"", "$$$QUOTE$$$");
    return s;
}

bool is_graphviz_friendly(const std::string& s) noexcept
{
    return graphviz_encode(s) == s;
}



template < typename graph>
class bundled_vertices_writer {
public:
    bundled_vertices_writer( graph g ) : m_g{ g }
    {

    }
    template <class vertex_descriptor>
    void operator()( std::ostream& out,  const vertex_descriptor& vd  ) const noexcept 
    {
        out
            << "[label=\""
            << graphviz_encode(
                m_g[vd].m_name
            )
            << "\",comment=\""
            << graphviz_encode(
                m_g[vd].m_ID
            )
            << "\",width="
            << m_g[vd].m_index
            << ",height="
            << m_g[vd].m_type
            << "]"
            ;
    }
private:
    graph m_g;
};

template <typename graph>
inline bundled_vertices_writer<graph>
make_bundled_vertices_writer(const graph& g)
{
    return bundled_vertices_writer<graph>(g);
}


template <typename graph>
class bundled_edges_writer {
public:
    bundled_edges_writer(  graph g ) : m_g{ g }
    {

    }
    template <class edge_descriptor>
    void operator()(      std::ostream& out,      const edge_descriptor& ed   ) const noexcept 
    {
        out << "[edgeName=\""
            << graphviz_encode(
                m_g[ed].m_name
            )
            << "\",edgeComment=\""
            << graphviz_encode(
                m_g[ed].m_ID
            )
            << "\",edgeIndex="
            << m_g[ed].m_index
            << ",edgeType="
            << m_g[ed].m_type
            << "]"
            ;
    }
private:
    graph m_g;
};




template <typename graph>
inline bundled_edges_writer<graph>
make_bundled_edges_writer(  const graph& g)
{
    return bundled_edges_writer< graph >(g);
}




bool has_dot() noexcept
{
    std::stringstream cmd;
    //cmd << "type dot > /dev/null";   //linux 命令行 
    cmd << "dot -?";   //windows命令行 
    const auto error = std::system(cmd.str().c_str());
    const bool has_dot{ error == 0 };
    if (!has_dot) {
        std::cout << "Tip: 请先安装 graphviz" << std::endl;
    }
    return has_dot;
}

bool is_regular_file(const std::string& filename) noexcept
{
    std::fstream f;
    f.open(filename.c_str(), std::ios::in);
    return f.is_open();
}



std::vector<std::string> file_to_vector(const std::string& filename)

{
    if (!is_regular_file(filename))
    {
        std::stringstream msg;
        msg << __func__ << ": file '"
            << filename << "' not found"
            ;
        throw std::invalid_argument(msg.str());
    }
    std::vector<std::string> v;
    std::ifstream in{ filename.c_str() };
    assert(in.is_open());
    for (int i = 0; !in.eof(); ++i)
    {
        std::string s;
        std::getline(in, s);
        v.emplace_back(s); //Might throw std::bad_alloc
    }

    //Remove empty line at back of vector
    if (!v.empty() && v.back().empty()) v.pop_back();
    assert(!v.back().empty());
    return v;
}


bool is_valid_dot_file(const std::string& dot_filename)
{
    if (!is_regular_file(dot_filename)) { return false; }
    const auto v = file_to_vector(dot_filename);
    if (v.size() <= 1) return false;
    //Remove trailing newlines
    assert(!v.back().empty());
    return v.back()[0] == '}';
}



//输出svg文件函数
void outsvg(const std::string& dot_filename, const std::string& svg_filename)
{
    if (!has_dot())
    {
        std::stringstream msg;
        msg << __func__ << ": 'dot' 未发现. "
            << "请先安装 graphviz"
            ;
        throw std::runtime_error(msg.str());
    }
    if (!is_valid_dot_file(dot_filename))
    {
        std::stringstream msg;
        msg << __func__ << ": file '" << dot_filename
            << "' 不是标准的DOT格式文件"
            ;
        throw std::invalid_argument(msg.str());
    }
    std::stringstream cmd;
    cmd << "dot -Tsvg " << dot_filename << " -o " << svg_filename;
    const int error{
      std::system(cmd.str().c_str())
    };
    if (error)
    {
        std::cerr << __func__ << ": warning: command "
            << cmd.str() << "' resulting in error "
            << error;
    }
    if (!is_regular_file(svg_filename))
    {
        std::stringstream msg;
        msg << __func__ << ": 创建 SVG  file 失败 "
            << svg_filename << "'"
            ;
        throw std::runtime_error(msg.str());
    }
}


void copy_file(
    const std::string& filename_from,
    const std::string& filename_to,
    const copy_file_mode copy_mode
)
{
    if (!is_regular_file(filename_from))
    {
        std::stringstream msg;
        msg << __func__ << ": "
            << "cannot copy a non-existing file, "
            << "filename supplied was '"
            << filename_from
            << "'"
            ;
        throw std::invalid_argument(msg.str());
    }
    if (copy_mode == copy_file_mode::prevent_overwrite && is_regular_file(filename_to))
    {
        std::stringstream msg;
        msg << __func__ << ": "
            << "Copying to existing file '"
            << filename_to << "'is not allowed, "
            << "use copy_file_mode::allow_overwrite if you really want to"
            ;
        throw std::invalid_argument(msg.str());
    }
    if (is_regular_file(filename_to))
    {
        std::remove(filename_to.c_str());
        assert(!is_regular_file(filename_to));
    }
    std::ifstream in{ filename_from.c_str() };
    std::ofstream out{ filename_to.c_str() };
    out << in.rdbuf();
    out.close();
    in.close();
}
