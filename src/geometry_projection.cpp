#include "geometry_vector.h"

[[cpp11::register]]
geometry_vector_base_p geometry_project_to_line(geometry_vector_base_p geometries, geometry_vector_base_p lines) {
  return geometries->project_to_line(*lines);
}

[[cpp11::register]]
geometry_vector_base_p geometry_project_to_plane(geometry_vector_base_p geometries, geometry_vector_base_p planes) {
  return geometries->project_to_plane(*planes);
}

[[cpp11::register]]
geometry_vector_base_p geometry_map_to_plane(geometry_vector_base_p geometries, geometry_vector_base_p planes) {
  return geometries->map_to_plane(*planes);
}
