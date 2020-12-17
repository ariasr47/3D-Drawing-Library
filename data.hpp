//
//  data.hpp
//  drawinglib
//
//  Created by Rodrigo on 3/28/20.
//

#ifndef DATA_HPP
#define DATA_HPP

#include <memory>
#include <unordered_map>

namespace Geometry {
	class Vertex;
	class Edge;
	class Polygon;
	class Polyhedron;
}

using object_t = std::shared_ptr<class Object>;
using vertex_t = std::shared_ptr<Geometry::Vertex>;
using edge_t = std::shared_ptr<Geometry::Edge>;
using polygon_t = std::shared_ptr<Geometry::Polygon>;
using polyhedron_t = std::shared_ptr<Geometry::Polyhedron>;

struct pair_hash
{
	std::size_t operator () (std::pair<int, int> const& pair) const
	{
		auto h1 = std::hash<int>()(pair.first);
		auto h2 = std::hash<int>()(pair.second);

		return h1 + h2;
	}
};

class DataInterface {};

template<typename T, typename U = void, typename X = void>
class Data : public DataInterface {};

template<>
class Data <vertex_t> : public DataInterface {
public:
	std::vector<vertex_t> vertex_list;
};

template<>
class Data <vertex_t, edge_t> : public DataInterface {
public:
	std::vector<vertex_t> vertex_list;
	std::unordered_map<std::pair<int, edge_t>, size_t, pair_hash> edge_table;
};

template<>
class Data <vertex_t, edge_t, polygon_t> : public DataInterface {
public:
	std::vector<vertex_t> vertex_list;
	std::unordered_map<std::pair<int, int>, edge_t, pair_hash> edge_table;
	std::vector<polygon_t> polygon_list;
};

using data_t = std::unique_ptr<DataInterface>;

using edge_data = Data<vertex_t>;
using polygon_data = Data<vertex_t, edge_t>;
using polyhedron_data = Data<vertex_t, edge_t, polygon_t>;

class DataBase
{
public:
	std::unordered_map<int, object_t> object_table = std::unordered_map<int, object_t>();
	std::unordered_map<int, data_t> object_data = std::unordered_map<int, data_t>();
};



#endif /* DATA_HPP */