#include "./PointVertex.h"

namespace maze
{
	/** {@inheritdoc} */
	PointVertex::PointVertex(coordinates::grid::Point _point) : PointVertex(_point, false) {}

	/** {@inheritdoc} */
	PointVertex::PointVertex(coordinates::grid::Point _point, bool _fixed) : fixed(_fixed), point(_point), Vertex() {}
}