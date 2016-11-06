#include "./PointVertex.h"

namespace maze
{
	/** {@inheritdoc} */
	PointVertex::PointVertex(coordinates::grid::Point _p) : PointVertex(_p, VertexType::DEFAULT) {}

	/** {@inheritdoc} */
	PointVertex::PointVertex(coordinates::grid::Point _p, VertexType _t) : type(_t), point(_p), Vertex() {}
}