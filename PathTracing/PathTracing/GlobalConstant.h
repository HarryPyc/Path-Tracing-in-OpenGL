#pragma once
#include <string>

const int WINDOW_WIDTH = 1280, WINDOW_HEIGHT = 720;
const std::string quad_vertex_shader = "shader/quad.vert", quad_fragment_shader = "shader/quad.frag";
const std::string quad_compute_shader = "shader/path_tracing.comp";
const std::string vertex_process_shader = "shader/vertex_process.comp";