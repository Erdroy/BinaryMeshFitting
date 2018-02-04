#pragma once

#include <gl/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include "FPSCamera.hpp"
#include "Chunk.hpp"
#include "GLChunk.hpp"
#include "WorldOctree.hpp"
#include "BinaryChunk.hpp"

#include <thread>
#include <mutex>

class DebugScene
{
	int last_space : 1;
	bool outline_visible;
	int fillmode;
	bool cull;
	bool quads;
	bool smooth_shading;
	bool flat_quads;
	bool gui_visible;
	bool auto_update;
	float line_width;
	float line_color[4];
	float fill_color[4];
	float clear_color[4];
	float specular_power;
	GLuint points_vbo;
	GLuint colors_vbo;
	GLuint vao;
	GLuint ibo;

	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint shader_program;

	GLuint outline_vs;
	GLuint outline_fs;
	GLuint outline_sp;

	GLint shader_projection;
	GLint shader_view;
	GLint shader_mul_clr;
	GLint shader_eye_pos;
	GLint shader_smooth_shading;
	GLint shader_specular_power;

	GLint outline_shader_projection;
	GLint outline_shader_view;
	GLint outline_shader_mul_clr;

	class FPSCamera camera;
	Chunk* dual_chunk;
	GLChunk gl_chunk;
	WorldOctree world;

	BinaryChunk* binary_chunk;

	std::thread update_thread;
	std::mutex gl_mutex;
	clock_t last_extraction;
	bool update_required;
	std::mutex update_mutex;

public:
	DebugScene(struct RenderInput* input);
	~DebugScene();

	void init_single_chunk();
	void init_binary_chunk();
	void init_world();
	int update(struct RenderInput* input);
	int render(struct RenderInput* input);

	void render_single_chunk();
	void render_binary_chunk();
	void render_world();

	void key_callback(int key, int scancode, int action, int mods);
	void render_gui();

	void watch_world_updates();
};