#include "p3dt_objloader.h"
#include "p3dt_texture.h"
#include <iostream>
#include <string>

// OPENGL
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#elif _WIN32
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glut32.lib")
#include <glut.h>
#endif

#define PI 3.14159265

using namespace std;

namespace shared {
	// stores window width
	float window_width = 1024.0f;
	// stores window height
	float window_height = 720.0f;
	// tracks the last frame tick time
	int last_tick = 0;
	// stores the time taken to render a single frame
	float delta_time_milliseconds = 0.0f;
	// stores the person mesh (vertices)
	p3dt::trimesh_t person_mesh;
	// stores the perosn texture
	GLuint person_texture;
	// stores the road mesh (vertices)
	p3dt::trimesh_t road_mesh;
	// stores the road texture
	GLuint road_texture;
	// stores the building mesh
	p3dt::trimesh_t building_mesh;
	// stores the building texture
	GLuint building_texture;
	// stores the ruined wall mesh 
	p3dt::trimesh_t ruinedwall_mesh;
	// stores the ruined wall texture
	GLuint ruinedwall_texture;
	// stores the farm house mesh
	p3dt::trimesh_t farmhouse_mesh;
	// stores the farm house texture
	GLuint farmhouse_texture;
	// stores the tall building mesh
	p3dt::trimesh_t tallbuilding_mesh;
	// stores the tall building texture
	GLuint tallbuilding_texture;
	// stores the rocks mesh
	p3dt::trimesh_t rocks_mesh;
	//stores the rocks texture
	GLuint rocks_texture;
	//stores the wall mesh
	p3dt::trimesh_t wall_mesh;
	// stores the wall texture
	GLuint wall_textures;
	//stores the rock mesh
	GLuint rock_textures;
	//stores the rock texture
	p3dt::trimesh_t rock_mesh;
	//stores the drum mesh
	p3dt::trimesh_t drum_mesh;
	//stores the drum mesh
	GLuint drum_textures;
	//stores the chair mesh
	p3dt::trimesh_t chair_mesh;
	//stores the chair texture
	GLuint chair_textures;
	//stores the spider mesh
	p3dt::trimesh_t spider_mesh;
	//stores the spider texture
	GLuint spider_textures;
	// stoes the dog mesh
	p3dt::trimesh_t dog_mesh;
	// stores the dog texture
	GLuint dog_texture;
	// stores the tower mesh
	p3dt::trimesh_t tower_mesh;
	// stores the tower texture
	GLuint tower_texture;
	// stores the tree mesh
	p3dt::trimesh_t tree_mesh;
	// stores the tree texture
	GLuint tree_texture;

	p3dt::trimesh_t crate_mesh;
	GLuint crate_textures;

	p3dt::trimesh_t wood_mesh;
	GLuint wood_textures;

	p3dt::trimesh_t debris_mesh;
	GLuint debris_textures;

	//rotation value
	float rotation = 0.0f;
	//forward direction
	float forward = 0.0f;
	//right direction
	float right = 0.0f;
	//up direction
	float up = 0.0f;
	//mouse x direction
	float mouseX = 0.0;
	//mouse y direction
	float mouseY = 0.0;
	//spider x movment
	float spiderX = 0;
	//spider y movment
	float spiderY = 0;
	//spider z movment
	float spiderZ = 0;
	//jump index
	float jump = 0.0f;
	//scoring
	int score = 0;
	float perpX = 0;
	float perpY = 0;
	float perpZ = 0;
	//perspective
	bool perspective = false;
	//jump action flag
	bool jumpB = false;
	//jump action flag distance
	bool jumpBF = true;
	//scene change boolean
	bool sceneBoolean = true;
	//movemnt forward variable
	bool movmentF = true;
	float lastObs1 = -14;
	float lastObs2 = -1.75;
	float lastObs3 = -5.5;
	float lastObs4 = -8.5;
} // namespace shared

void onResize(int width, int height)
{
	shared::window_width = width;
	shared::window_height = height;
}

void onStart()
{
	// enable opengl features
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	// load assets
	{
		std::vector<p3dt::trimesh_t> obj_file;

		// load person mesh and texture
		p3dt::objloader::load_from_file("models/human/person.obj", obj_file);
		{
			shared::person_mesh = obj_file[0];
			p3dt::texture::buffer_t person_texture_buffer = {};
			if (p3dt::texture::load("models/human/49ff07b7-63b7-4002-bc2e-044c90f3ff33.jpg", &person_texture_buffer)) {
				shared::person_texture = p3dt::texture::create_opengl_texture(&person_texture_buffer);
				p3dt::texture::unload(&person_texture_buffer);
			}
		}

		//load road mesh and texture
		p3dt::objloader::load_from_file("models/road/road.obj", obj_file);
		{
			shared::road_mesh = obj_file[1];
			p3dt::texture::buffer_t road_texture_buffer = {};
			if (p3dt::texture::load("models/road/road.png", &road_texture_buffer)) {
				shared::road_texture = p3dt::texture::create_opengl_texture(&road_texture_buffer);
				p3dt::texture::unload(&road_texture_buffer);
			}
		}

		// load ruined wall mesh and texture
		p3dt::objloader::load_from_file("models/buildings/ruinedwall.obj", obj_file);
		{
			shared::ruinedwall_mesh = obj_file[10];
			p3dt::texture::buffer_t ruinedwall_texture_buffer = {};
			if (p3dt::texture::load("models/buildings/ruinedwall.jpg", &ruinedwall_texture_buffer)) {
				shared::ruinedwall_texture = p3dt::texture::create_opengl_texture(&ruinedwall_texture_buffer);
				p3dt::texture::unload(&ruinedwall_texture_buffer);
			}
		}

		//load building mesh and texture
		p3dt::objloader::load_from_file("models/buildings/building.obj", obj_file);
		{
			shared::building_mesh = obj_file[11];
			p3dt::texture::buffer_t building_texture_buffer = {};
			if (p3dt::texture::load("models/buildings/bricks.jpg", &building_texture_buffer)) {
				shared::building_texture = p3dt::texture::create_opengl_texture(&building_texture_buffer);
				p3dt::texture::unload(&building_texture_buffer);
			}
		}

		// load farmhouse mesh and texture
		p3dt::objloader::load_from_file("models/buildings/farmhouse.obj", obj_file);
		{
			shared::farmhouse_mesh = obj_file[12];
			p3dt::texture::buffer_t farmhouse_texture_buffer = {};
			if (p3dt::texture::load("models/buildings/Farmhouse.jpg", &farmhouse_texture_buffer)) {
				shared::farmhouse_texture = p3dt::texture::create_opengl_texture(&farmhouse_texture_buffer);
				p3dt::texture::unload(&farmhouse_texture_buffer);
			}
		}

		// load tall building mesh and texture
		p3dt::objloader::load_from_file("models/buildings/tallbuilding.obj", obj_file);
		{
			shared::tallbuilding_mesh = obj_file[13];
			p3dt::texture::buffer_t tallbuilding_texture_buffer = {};
			if (p3dt::texture::load("models/buildings/tallbuilding.jpg", &tallbuilding_texture_buffer)) {
				shared::tallbuilding_texture = p3dt::texture::create_opengl_texture(&tallbuilding_texture_buffer);
				p3dt::texture::unload(&tallbuilding_texture_buffer);
			}
		}

		//load rocks mesh and texture
		p3dt::objloader::load_from_file("models/buildings/derbis1.obj", obj_file);
		{
			shared::rocks_mesh = obj_file[14];
			p3dt::texture::buffer_t rocks_texture_buffer = {};
			if (p3dt::texture::load("models/buildings/ruinedbricks.jpg", &rocks_texture_buffer)) {
				shared::rocks_texture = p3dt::texture::create_opengl_texture(&rocks_texture_buffer);
				p3dt::texture::unload(&rocks_texture_buffer);
			}
		}

		//load fence mesh and textures
		p3dt::objloader::load_from_file("models/wall/wall.obj", obj_file);
		{
			shared::wall_mesh = obj_file[15];
			p3dt::texture::buffer_t fence_texture_buffer = {};
			if (p3dt::texture::load("models/wall/wall.jpg", &fence_texture_buffer)) {
				shared::wall_textures = p3dt::texture::create_opengl_texture(&fence_texture_buffer);
				p3dt::texture::unload(&fence_texture_buffer);
			}
		}

		//load rock mesh and textures
		p3dt::objloader::load_from_file("models/rock/rock.obj", obj_file);
		{
			shared::rock_mesh = obj_file[16];
			p3dt::texture::buffer_t rock_texture_buffer = {};
			if (p3dt::texture::load("models/rock/rock.jpg", &rock_texture_buffer)) {
				shared::rock_textures = p3dt::texture::create_opengl_texture(&rock_texture_buffer);
				p3dt::texture::unload(&rock_texture_buffer);
			}
		}

		//load drum mesh and textures
		p3dt::objloader::load_from_file("models/drum/drum.obj", obj_file);
		{
			shared::drum_mesh = obj_file[17];
			p3dt::texture::buffer_t drum_texture_buffer = {};
			if (p3dt::texture::load("models/drum/drum.jpg", &drum_texture_buffer)) {
				shared::drum_textures = p3dt::texture::create_opengl_texture(&drum_texture_buffer);
				p3dt::texture::unload(&drum_texture_buffer);
			}
		}

		//load chair mesh and textures
		p3dt::objloader::load_from_file("models/chair/chair.obj", obj_file);
		{
			shared::chair_mesh = obj_file[18];
			p3dt::texture::buffer_t fence_mesh_buffer = {};
			if (p3dt::texture::load("models/chair/chair.png", &fence_mesh_buffer)) {
				shared::chair_textures = p3dt::texture::create_opengl_texture(&fence_mesh_buffer);
				p3dt::texture::unload(&fence_mesh_buffer);
			}
		}

		//load spider mesh and texture
		p3dt::objloader::load_from_file("models/spider/spider.obj", obj_file);
		{
			shared::spider_mesh = obj_file[19];
			p3dt::texture::buffer_t spider_mesh_buffer = {};
			if (p3dt::texture::load("models/spider/spider.png", &spider_mesh_buffer)) {
				shared::spider_textures = p3dt::texture::create_opengl_texture(&spider_mesh_buffer);
				p3dt::texture::unload(&spider_mesh_buffer);
			}
		}

		//load tree mesh and texture
		p3dt::objloader::load_from_file("models/tree/tree.obj", obj_file);
		{
			shared::tree_mesh = obj_file[20];
			p3dt::texture::buffer_t tree_texture_buffer = {};
			if (p3dt::texture::load("models/tree/tree.jpeg", &tree_texture_buffer)) {
				shared::tree_texture = p3dt::texture::create_opengl_texture(&tree_texture_buffer);
				p3dt::texture::unload(&tree_texture_buffer);
			}
		}

		//load tower mesh and texture
		p3dt::objloader::load_from_file("models/tower/tower.obj", obj_file);
		{
			shared::tower_mesh = obj_file[21];
			p3dt::texture::buffer_t tower_texture_buffer = {};
			if (p3dt::texture::load("models/tower/tower.jpeg", &tower_texture_buffer)) {
				shared::tower_texture = p3dt::texture::create_opengl_texture(&tower_texture_buffer);
				p3dt::texture::unload(&tower_texture_buffer);
			}
		}

		//load dog mesh and texture
		p3dt::objloader::load_from_file("models/dog/dog.obj", obj_file);
		{
			shared::dog_mesh = obj_file[22];
			p3dt::texture::buffer_t dog_texture_buffer = {};
			if (p3dt::texture::load("models/dog/dog.jpeg", &dog_texture_buffer)) {
				shared::dog_texture = p3dt::texture::create_opengl_texture(&dog_texture_buffer);
				p3dt::texture::unload(&dog_texture_buffer);
			}
		}

		std::vector<p3dt::trimesh_t> obj_file5;
		p3dt::objloader::load_from_file("models/crate/crate.obj", obj_file5);

		{
			shared::crate_mesh = obj_file5[0];
			p3dt::texture::buffer_t crate_mesh_buffer = {};
			if (p3dt::texture::load("models/crate/crate.png", &crate_mesh_buffer)) {
				shared::crate_textures = p3dt::texture::create_opengl_texture(&crate_mesh_buffer);
				p3dt::texture::unload(&crate_mesh_buffer);
			}
		}

		std::vector<p3dt::trimesh_t> obj_file6;
		p3dt::objloader::load_from_file("models/wood/wood.obj", obj_file6);

		{
			shared::wood_mesh = obj_file6[0];
			p3dt::texture::buffer_t wood_mesh_buffer = {};
			if (p3dt::texture::load("models/wood/wood.png", &wood_mesh_buffer)) {
				shared::wood_textures = p3dt::texture::create_opengl_texture(&wood_mesh_buffer);
				p3dt::texture::unload(&wood_mesh_buffer);
			}
		}

		std::vector<p3dt::trimesh_t> obj_file7;
		p3dt::objloader::load_from_file("models/pile/pile.obj", obj_file7);

		{
			shared::debris_mesh = obj_file7[0];
			p3dt::texture::buffer_t debris_mesh_buffer = {};
			if (p3dt::texture::load("models/pile/pile.jpg", &debris_mesh_buffer)) {
				shared::debris_textures = p3dt::texture::create_opengl_texture(&debris_mesh_buffer);
				p3dt::texture::unload(&debris_mesh_buffer);
			}
		}

		assert(shared::person_texture != 0 && "Person texture wasn't loaded properly!");
		assert(shared::road_texture != 0 && "road texture wasn't loaded properly!");
		assert(shared::ruinedwall_texture != 0 && "ruinedwall texture wasn't loaded properly!");
		assert(shared::building_texture != 0 && "building texture wasn't loaded properly!");
		assert(shared::farmhouse_texture != 0 && "farmhouse texture wasn't loaded properly!");
		assert(shared::tallbuilding_texture != 0 && "tallbuilding texture wasn't loaded properly!");
		assert(shared::rocks_texture != 0 && "rocks texture wasn't loaded properly!");
		assert(shared::wall_textures != 0 && "wall texture wasn't loaded properly!");
		assert(shared::rock_textures != 0 && "rock texture wasn't loaded properly!");
		assert(shared::drum_textures != 0 && "drum texture wasn't loaded properly!");
		assert(shared::chair_textures != 0 && "chair texture wasn't loaded properly!");
		assert(shared::spider_textures != 0 && "spider texture wasn't loaded properly!");
		assert(shared::tree_texture != 0 && "tree texture wasn't loaded properly!");
		assert(shared::tower_texture != 0 && "tower texture wasn't loaded properly!");
		assert(shared::dog_texture != 0 && "dog texture wasn't loaded properly!");

	}
}

void onExit()
{
	// destroy opengl textures
	p3dt::texture::destroy_opengl_texture(shared::person_texture);
	p3dt::texture::destroy_opengl_texture(shared::road_texture);
	p3dt::texture::destroy_opengl_texture(shared::ruinedwall_texture);
	p3dt::texture::destroy_opengl_texture(shared::building_texture);
	p3dt::texture::destroy_opengl_texture(shared::farmhouse_texture);
	p3dt::texture::destroy_opengl_texture(shared::tallbuilding_texture);
	p3dt::texture::destroy_opengl_texture(shared::rocks_texture);
	p3dt::texture::destroy_opengl_texture(shared::wall_textures);
	p3dt::texture::destroy_opengl_texture(shared::rock_textures);
	p3dt::texture::destroy_opengl_texture(shared::drum_textures);
	p3dt::texture::destroy_opengl_texture(shared::chair_textures);
	p3dt::texture::destroy_opengl_texture(shared::spider_textures);
	p3dt::texture::destroy_opengl_texture(shared::tree_texture);
	p3dt::texture::destroy_opengl_texture(shared::tower_texture);
	p3dt::texture::destroy_opengl_texture(shared::dog_texture);
}

//void setup_lights()
//{
//	// Light
//	glEnable(GL_LIGHT0);
//	GLfloat light0_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
//	GLfloat light0_diffuse[] = { 5.0f, 5.0f, 5.0f, 1.0f };
//	GLfloat light0_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
//	GLfloat light0_position[] = { 0.0f, 250.0f, 200.0f, 0.0f };
//	GLfloat light0_constant_attenuation = 0.0f;
//	GLfloat light0_linear_attenuation = 0.0f;
//	GLfloat light0_quadratic_attenuation = 0.1f;
//	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
//	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
//	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
//	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, light0_constant_attenuation);
//	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, light0_linear_attenuation);
//	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, light0_quadratic_attenuation);
//}

//all models Render Methods
void wall() {
	glPushMatrix();
	{
		glScalef(0.4, 0.5, 0.7);
		glTranslatef(-1.5, 3, -2.5);
		glRotatef(-40, 1, 0, 0);
		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, shared::wall_textures);
			glBegin(GL_TRIANGLES);
			{
				for (size_t i = 0; i < shared::wall_mesh.triangles.size(); ++i)
				{
					const p3dt::triangle_t& t = shared::wall_mesh.triangles[i];
					const p3dt::vertex_t& a = t.a;
					const p3dt::vertex_t& b = t.b;
					const p3dt::vertex_t& c = t.c;
					// a
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(a.texcoord.x, a.texcoord.y);
					glNormal3f(a.normal.x, a.normal.y, a.normal.z);
					glVertex3f(a.position.x, a.position.y, a.position.z);
					// b
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(b.texcoord.x, b.texcoord.y);
					glNormal3f(b.normal.x, b.normal.y, b.normal.z);
					glVertex3f(b.position.x, b.position.y, b.position.z);
					// c
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(c.texcoord.x, c.texcoord.y);
					glNormal3f(c.normal.x, c.normal.y, c.normal.z);
					glVertex3f(c.position.x, c.position.y, c.position.z);
				}
			}
			glEnd();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void rock() {
	glPushMatrix();
	{
		glPushMatrix();
		{
			glScaled(1.0, 0.5, 0.5);
			glTranslatef(-1.0, 1.0, 15);
			glBindTexture(GL_TEXTURE_2D, shared::rock_textures);
			glBegin(GL_TRIANGLES);
			{
				for (size_t i = 0; i < shared::rock_mesh.triangles.size(); ++i)
				{
					const p3dt::triangle_t& t = shared::rock_mesh.triangles[i];
					const p3dt::vertex_t& a = t.a;
					const p3dt::vertex_t& b = t.b;
					const p3dt::vertex_t& c = t.c;
					// a
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(a.texcoord.x, a.texcoord.y);
					glNormal3f(a.normal.x, a.normal.y, a.normal.z);
					glVertex3f(a.position.x, a.position.y, a.position.z);
					// b
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(b.texcoord.x, b.texcoord.y);
					glNormal3f(b.normal.x, b.normal.y, b.normal.z);
					glVertex3f(b.position.x, b.position.y, b.position.z);
					// c
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(c.texcoord.x, c.texcoord.y);
					glNormal3f(c.normal.x, c.normal.y, c.normal.z);
					glVertex3f(c.position.x, c.position.y, c.position.z);
				}
			}
			glEnd();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drum() {
	glPushMatrix();
	{
		glScalef(0.32, 0.32, 0.32);
	//	glTranslatef(-1, -0.4, -9);
		glTranslatef(-1, -0.4, 9.75);
		glBindTexture(GL_TEXTURE_2D, shared::drum_textures);
		glBegin(GL_TRIANGLES);
		{
			for (size_t i = 0; i < shared::drum_mesh.triangles.size(); ++i)
			{
				const p3dt::triangle_t& t = shared::drum_mesh.triangles[i];
				const p3dt::vertex_t& a = t.a;
				const p3dt::vertex_t& b = t.b;
				const p3dt::vertex_t& c = t.c;
				// a
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glTexCoord2f(a.texcoord.x, a.texcoord.y);
				glNormal3f(a.normal.x, a.normal.y, a.normal.z);
				glVertex3f(a.position.x, a.position.y, a.position.z);
				// b
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glTexCoord2f(b.texcoord.x, b.texcoord.y);
				glNormal3f(b.normal.x, b.normal.y, b.normal.z);
				glVertex3f(b.position.x, b.position.y, b.position.z);
				// c
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glTexCoord2f(c.texcoord.x, c.texcoord.y);
				glNormal3f(c.normal.x, c.normal.y, c.normal.z);
				glVertex3f(c.position.x, c.position.y, c.position.z);
			}
		}
		glEnd();
	}
	glPopMatrix();
}

void chair() {
	glPushMatrix();
	{

		glPushMatrix();
		{
			glScalef(0.01, 0.01, 0.01);
			glBindTexture(GL_TEXTURE_2D, shared::chair_textures);
			glBegin(GL_TRIANGLES);
			{
				for (size_t i = 0; i < shared::chair_mesh.triangles.size(); ++i)
				{
					const p3dt::triangle_t& t = shared::chair_mesh.triangles[i];
					const p3dt::vertex_t& a = t.a;
					const p3dt::vertex_t& b = t.b;
					const p3dt::vertex_t& c = t.c;
					// a
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(a.texcoord.x, a.texcoord.y);
					glNormal3f(a.normal.x, a.normal.y, a.normal.z);
					glVertex3f(a.position.x, a.position.y, a.position.z);
					// b
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(b.texcoord.x, b.texcoord.y);
					glNormal3f(b.normal.x, b.normal.y, b.normal.z);
					glVertex3f(b.position.x, b.position.y, b.position.z);
					// c
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(c.texcoord.x, c.texcoord.y);
					glNormal3f(c.normal.x, c.normal.y, c.normal.z);
					glVertex3f(c.position.x, c.position.y, c.position.z);
				}
			}
			glEnd();
		}
		glPopMatrix();
	}
	glPopMatrix();

}

void person() {
	glPushMatrix();
	{
		glScalef(0.005, 0.005, 0.005);

		glTranslatef(shared::right * 200, 0, shared::forward * 200 - 200);
		glRotatef(shared::rotation + 90, 0.0f, 1.0f, 0.0f);
		glTranslatef(-shared::right * 200, 0, -shared::forward * 200 + 200);

		glTranslatef(shared::right * 200, shared::jump * 50 - 23 + shared::up * 50, shared::forward * 200 - 200);
		glBindTexture(GL_TEXTURE_2D, shared::person_texture);
		glBegin(GL_TRIANGLES);
		{
			for (size_t i = 0; i < shared::person_mesh.triangles.size(); ++i)
			{
				const p3dt::triangle_t& t = shared::person_mesh.triangles[i];
				const p3dt::vertex_t& a = t.a;
				const p3dt::vertex_t& b = t.b;
				const p3dt::vertex_t& c = t.c;
				// a
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glTexCoord2f(a.texcoord.x, a.texcoord.y);
				glNormal3f(a.normal.x, a.normal.y, a.normal.z);
				glVertex3f(a.position.x, a.position.y, a.position.z);
				// b
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glTexCoord2f(b.texcoord.x, b.texcoord.y);
				glNormal3f(b.normal.x, b.normal.y, b.normal.z);
				glVertex3f(b.position.x, b.position.y, b.position.z);
				// c
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glTexCoord2f(c.texcoord.x, c.texcoord.y);
				glNormal3f(c.normal.x, c.normal.y, c.normal.z);
				glVertex3f(c.position.x, c.position.y, c.position.z);
			}
		}
		glEnd();
	}
	glPopMatrix();
}

void road() {
	glPushMatrix();
	{
		glScalef(1, 1, 1);
		glBindTexture(GL_TEXTURE_2D, shared::road_texture);
		glBegin(GL_TRIANGLES);
		{
			for (size_t i = 0; i < shared::road_mesh.triangles.size(); ++i)
			{
				const p3dt::triangle_t& t = shared::road_mesh.triangles[i];
				const p3dt::vertex_t& a = t.a;
				const p3dt::vertex_t& b = t.b;
				const p3dt::vertex_t& c = t.c;
				// a
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glTexCoord2f(a.texcoord.x, a.texcoord.y);
				glNormal3f(a.normal.x, a.normal.y, a.normal.z);
				glVertex3f(a.position.x, a.position.y, a.position.z);
				// b
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glTexCoord2f(b.texcoord.x, b.texcoord.y);
				glNormal3f(b.normal.x, b.normal.y, b.normal.z);
				glVertex3f(b.position.x, b.position.y, b.position.z);
				// c
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glTexCoord2f(c.texcoord.x, c.texcoord.y);
				glNormal3f(c.normal.x, c.normal.y, c.normal.z);
				glVertex3f(c.position.x, c.position.y, c.position.z);
			}
		}
		glEnd();
	}
	glPopMatrix();
}

void ruinedWall() {
	glPushMatrix();
	{
		glScaled(0.1, 0.1, 0.1);
		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, shared::ruinedwall_texture);
			glBegin(GL_TRIANGLES);
			{
				for (size_t i = 0; i < shared::ruinedwall_mesh.triangles.size(); ++i)
				{
					const p3dt::triangle_t& t = shared::ruinedwall_mesh.triangles[i];
					const p3dt::vertex_t& a = t.a;
					const p3dt::vertex_t& b = t.b;
					const p3dt::vertex_t& c = t.c;
					// a
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(a.texcoord.x, a.texcoord.y);
					glNormal3f(a.normal.x, a.normal.y, a.normal.z);
					glVertex3f(a.position.x, a.position.y, a.position.z);
					// b
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(b.texcoord.x, b.texcoord.y);
					glNormal3f(b.normal.x, b.normal.y, b.normal.z);
					glVertex3f(b.position.x, b.position.y, b.position.z);
					// c
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(c.texcoord.x, c.texcoord.y);
					glNormal3f(c.normal.x, c.normal.y, c.normal.z);
					glVertex3f(c.position.x, c.position.y, c.position.z);
				}
			}
			glEnd();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void building() {
	glPushMatrix(); {
		glScaled(0.1, 0.1, 0.1);
		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, shared::building_texture);
			glBegin(GL_TRIANGLES);
			{
				for (size_t i = 0; i < shared::building_mesh.triangles.size(); ++i)
				{
					const p3dt::triangle_t& t = shared::building_mesh.triangles[i];
					const p3dt::vertex_t& a = t.a;
					const p3dt::vertex_t& b = t.b;
					const p3dt::vertex_t& c = t.c;
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(a.texcoord.x, a.texcoord.y);
					glNormal3f(a.normal.x, a.normal.y, a.normal.z);
					glVertex3f(a.position.x, a.position.y, a.position.z);
					// b
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(b.texcoord.x, b.texcoord.y);
					glNormal3f(b.normal.x, b.normal.y, b.normal.z);
					glVertex3f(b.position.x, b.position.y, b.position.z);
					// c
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(c.texcoord.x, c.texcoord.y);
					glNormal3f(c.normal.x, c.normal.y, c.normal.z);
					glVertex3f(c.position.x, c.position.y, c.position.z);
				}
			}
			glEnd();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void farmHouse() {
	glPushMatrix(); {
		glRotatef(-90, 0.0f, 1.0f, 0.0f);
		glScaled(0.02, 0.02, 0.02);
		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, shared::farmhouse_texture);
			glBegin(GL_TRIANGLES);
			{
				for (size_t i = 0; i < shared::farmhouse_mesh.triangles.size(); ++i)
				{
					const p3dt::triangle_t& t = shared::farmhouse_mesh.triangles[i];
					const p3dt::vertex_t& a = t.a;
					const p3dt::vertex_t& b = t.b;
					const p3dt::vertex_t& c = t.c;
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(a.texcoord.x, a.texcoord.y);
					glNormal3f(a.normal.x, a.normal.y, a.normal.z);
					glVertex3f(a.position.x, a.position.y, a.position.z);
					// b
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(b.texcoord.x, b.texcoord.y);
					glNormal3f(b.normal.x, b.normal.y, b.normal.z);
					glVertex3f(b.position.x, b.position.y, b.position.z);
					// c
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(c.texcoord.x, c.texcoord.y);
					glNormal3f(c.normal.x, c.normal.y, c.normal.z);
					glVertex3f(c.position.x, c.position.y, c.position.z);
				}
			}
			glEnd();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void tallBuilding() {
	glPushMatrix(); {
		glScaled(0.15, 0.15, 0.15);
		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, shared::tallbuilding_texture);
			glBegin(GL_TRIANGLES);
			{
				for (size_t i = 0; i < shared::tallbuilding_mesh.triangles.size(); ++i)
				{
					const p3dt::triangle_t& t = shared::tallbuilding_mesh.triangles[i];
					const p3dt::vertex_t& a = t.a;
					const p3dt::vertex_t& b = t.b;
					const p3dt::vertex_t& c = t.c;
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(a.texcoord.x, a.texcoord.y);
					glNormal3f(a.normal.x, a.normal.y, a.normal.z);
					glVertex3f(a.position.x, a.position.y, a.position.z);
					// b
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(b.texcoord.x, b.texcoord.y);
					glNormal3f(b.normal.x, b.normal.y, b.normal.z);
					glVertex3f(b.position.x, b.position.y, b.position.z);
					// c
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(c.texcoord.x, c.texcoord.y);
					glNormal3f(c.normal.x, c.normal.y, c.normal.z);
					glVertex3f(c.position.x, c.position.y, c.position.z);
				}
			}
			glEnd();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void rocks() {
	glPushMatrix(); {
		glRotatef(shared::rotation, 0.0f, 1.0f, 0.0f);
		glScaled(0.001, 0.001, 0.001);
		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, shared::rocks_texture);
			glBegin(GL_TRIANGLES);
			{
				for (size_t i = 0; i < shared::rocks_mesh.triangles.size(); ++i)
				{
					const p3dt::triangle_t& t = shared::rocks_mesh.triangles[i];
					const p3dt::vertex_t& a = t.a;
					const p3dt::vertex_t& b = t.b;
					const p3dt::vertex_t& c = t.c;
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(a.texcoord.x, a.texcoord.y);
					glNormal3f(a.normal.x, a.normal.y, a.normal.z);
					glVertex3f(a.position.x, a.position.y, a.position.z);
					// b
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(b.texcoord.x, b.texcoord.y);
					glNormal3f(b.normal.x, b.normal.y, b.normal.z);
					glVertex3f(b.position.x, b.position.y, b.position.z);
					// c
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(c.texcoord.x, c.texcoord.y);
					glNormal3f(c.normal.x, c.normal.y, c.normal.z);
					glVertex3f(c.position.x, c.position.y, c.position.z);
				}
			}
			glEnd();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void dog() {
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, shared::dog_texture);
		glBegin(GL_TRIANGLES);
		{
			for (size_t i = 0; i < shared::dog_mesh.triangles.size(); ++i)
			{
				// by the way
				// here is use const p3dt::triangle_t& for performance reasons
				// this will not copy t, it will only const reference it
				// so we don't lose performance and keep the code readable
				// for more go for related c++ questions on stackoverflow
				const p3dt::triangle_t& t = shared::dog_mesh.triangles[i];
				const p3dt::vertex_t& a = t.a;
				const p3dt::vertex_t& b = t.b;
				const p3dt::vertex_t& c = t.c;
				// ==---------------==
				//          A
				//          *
				//    
				//        *   *
				//       B     C
				// ==---------------==
				// a
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glTexCoord2f(a.texcoord.x, a.texcoord.y);
				glNormal3f(a.normal.x, a.normal.y, a.normal.z);
				glVertex3f(a.position.x, a.position.y, a.position.z);
				// b
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glTexCoord2f(b.texcoord.x, b.texcoord.y);
				glNormal3f(b.normal.x, b.normal.y, b.normal.z);
				glVertex3f(b.position.x, b.position.y, b.position.z);
				// c
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glTexCoord2f(c.texcoord.x, c.texcoord.y);
				glNormal3f(c.normal.x, c.normal.y, c.normal.z);
				glVertex3f(c.position.x, c.position.y, c.position.z);
			}
		}
		glEnd();
	}
	glPopMatrix();
}

void tree() {
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, shared::tree_texture);
		glBegin(GL_TRIANGLES);
		{
			for (size_t i = 0; i < shared::tree_mesh.triangles.size(); ++i)
			{
				// by the way
				// here is use const p3dt::triangle_t& for performance reasons
				// this will not copy t, it will only const reference it
				// so we don't lose performance and keep the code readable
				// for more go for related c++ questions on stackoverflow
				const p3dt::triangle_t& t = shared::tree_mesh.triangles[i];
				const p3dt::vertex_t& a = t.a;
				const p3dt::vertex_t& b = t.b;
				const p3dt::vertex_t& c = t.c;
				// ==---------------==
				//          A
				//          *
				//    
				//        *   *
				//       B     C
				// ==---------------==
				// a
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glTexCoord2f(a.texcoord.x, a.texcoord.y);
				glNormal3f(a.normal.x, a.normal.y, a.normal.z);
				glVertex3f(a.position.x, a.position.y, a.position.z);
				// b
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glTexCoord2f(b.texcoord.x, b.texcoord.y);
				glNormal3f(b.normal.x, b.normal.y, b.normal.z);
				glVertex3f(b.position.x, b.position.y, b.position.z);
				// c
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glTexCoord2f(c.texcoord.x, c.texcoord.y);
				glNormal3f(c.normal.x, c.normal.y, c.normal.z);
				glVertex3f(c.position.x, c.position.y, c.position.z);
			}
		}
		glEnd();
	}
	glPopMatrix();
}

void tower() {
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, shared::tower_texture);
		glBegin(GL_TRIANGLES);
		{
			for (size_t i = 0; i < shared::tower_mesh.triangles.size(); ++i)
			{
				// by the way
				// here is use const p3dt::triangle_t& for performance reasons
				// this will not copy t, it will only const reference it
				// so we don't lose performance and keep the code readable
				// for more go for related c++ questions on stackoverflow
				const p3dt::triangle_t& t = shared::tower_mesh.triangles[i];
				const p3dt::vertex_t& a = t.a;
				const p3dt::vertex_t& b = t.b;
				const p3dt::vertex_t& c = t.c;
				// ==---------------==
				//          A
				//          *
				//    
				//        *   *
				//       B     C
				// ==---------------==
				// a
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glTexCoord2f(a.texcoord.x, a.texcoord.y);
				glNormal3f(a.normal.x, a.normal.y, a.normal.z);
				glVertex3f(a.position.x, a.position.y, a.position.z);
				// b
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glTexCoord2f(b.texcoord.x, b.texcoord.y);
				glNormal3f(b.normal.x, b.normal.y, b.normal.z);
				glVertex3f(b.position.x, b.position.y, b.position.z);
				// c
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glTexCoord2f(c.texcoord.x, c.texcoord.y);
				glNormal3f(c.normal.x, c.normal.y, c.normal.z);
				glVertex3f(c.position.x, c.position.y, c.position.z);
			}
		}
		glEnd();
	}
	glPopMatrix();
}

void crate() {
	glPushMatrix();
	{
		glPushMatrix();
		{
			glRotatef(-30, 1, 0, 0);
			glScaled(0.25, 0.25, 0.25);
			glTranslatef(-4, 14, -25);
			glBindTexture(GL_TEXTURE_2D, shared::crate_textures);
			glBegin(GL_TRIANGLES);
			{
				for (size_t i = 0; i < shared::crate_mesh.triangles.size(); ++i)
				{
					// by the way
					// here is use const p3dt::triangle_t& for performance reasons
					// this will not copy t, it will only const reference it
					// so we don't lose performance and keep the code readable
					// for more go for related c++ questions on stackoverflow
					const p3dt::triangle_t& t = shared::crate_mesh.triangles[i];
					const p3dt::vertex_t& a = t.a;
					const p3dt::vertex_t& b = t.b;
					const p3dt::vertex_t& c = t.c;
					// ==---------------==
					//          A
					//          *
					//
					//        *   *
					//       B     C
					// ==---------------==
					// a
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(a.texcoord.x, a.texcoord.y);
					glNormal3f(a.normal.x, a.normal.y, a.normal.z);
					glVertex3f(a.position.x, a.position.y, a.position.z);
					// b
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(b.texcoord.x, b.texcoord.y);
					glNormal3f(b.normal.x, b.normal.y, b.normal.z);
					glVertex3f(b.position.x, b.position.y, b.position.z);
					// c
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(c.texcoord.x, c.texcoord.y);
					glNormal3f(c.normal.x, c.normal.y, c.normal.z);
					glVertex3f(c.position.x, c.position.y, c.position.z);
				}
			}
			glEnd();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void wood() {
	glPushMatrix();
	{
		glPushMatrix();
		{
			//glTranslated(6, 2.2, -15);
			glScalef(1.5, 1, 1);
			glRotatef(-50, 1, 0, 0);
			glRotatef(60, 0, 1, 0);
			glBindTexture(GL_TEXTURE_2D, shared::wood_textures);
			glBegin(GL_TRIANGLES);
			{
				for (size_t i = 0; i < shared::wood_mesh.triangles.size(); ++i)
				{
					const p3dt::triangle_t& t = shared::wood_mesh.triangles[i];
					const p3dt::vertex_t& a = t.a;
					const p3dt::vertex_t& b = t.b;
					const p3dt::vertex_t& c = t.c;
					// a
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(a.texcoord.x, a.texcoord.y);
					glNormal3f(a.normal.x, a.normal.y, a.normal.z);
					glVertex3f(a.position.x, a.position.y, a.position.z);
					// b
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(b.texcoord.x, b.texcoord.y);
					glNormal3f(b.normal.x, b.normal.y, b.normal.z);
					glVertex3f(b.position.x, b.position.y, b.position.z);
					// c
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(c.texcoord.x, c.texcoord.y);
					glNormal3f(c.normal.x, c.normal.y, c.normal.z);
					glVertex3f(c.position.x, c.position.y, c.position.z);
				}
			}
			glEnd();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawWall(double thickness) {
	glPushMatrix();
	glTranslated(0.5, 0.5 * thickness, 0.5);
	glScaled(1.0, thickness, 1.0);
	glutSolidCube(1);
	glPopMatrix();
}

void spider() {
	glPushMatrix();
	{
		glScalef(3, 3, 3);
		glTranslatef(0, 0, -3.5);
		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, shared::spider_textures);
			glBegin(GL_TRIANGLES);
			{
				for (size_t i = 0; i < shared::spider_mesh.triangles.size(); ++i)
				{
					// by the way
					// here is use const p3dt::triangle_t& for performance reasons
					// this will not copy t, it will only const reference it
					// so we don't lose performance and keep the code readable
					// for more go for related c++ questions on stackoverflow
					const p3dt::triangle_t& t = shared::spider_mesh.triangles[i];
					const p3dt::vertex_t& a = t.a;
					const p3dt::vertex_t& b = t.b;
					const p3dt::vertex_t& c = t.c;
					// ==---------------==
					//          A
					//          *
					//
					//        *   *
					//       B     C
					// ==---------------==
					// a
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(a.texcoord.x, a.texcoord.y);
					glNormal3f(a.normal.x, a.normal.y, a.normal.z);
					glVertex3f(a.position.x, a.position.y, a.position.z);
					// b
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(b.texcoord.x, b.texcoord.y);
					glNormal3f(b.normal.x, b.normal.y, b.normal.z);
					glVertex3f(b.position.x, b.position.y, b.position.z);
					// c
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glTexCoord2f(c.texcoord.x, c.texcoord.y);
					glNormal3f(c.normal.x, c.normal.y, c.normal.z);
					glVertex3f(c.position.x, c.position.y, c.position.z);
				}
			}
			glEnd();
		}
		glPopMatrix();
	}
	glPopMatrix();

}

void resetGame() {
	shared::forward = 0;
	shared::spiderZ = 0;
	shared::score = 0;
}

void buildScene() {


	//glPushMatrix();
	//{
	//	glTranslatef(4.5, -1, 10);
	//	glScaled(1.5,1.5,1.5);
	//	dog();

	//}
	//glPopMatrix();

	glPushMatrix();
	{
		glTranslated(5, -1, 15);
		glScaled(2, 2, 2);
		dog();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslated(5, -1, 20);
		glScaled(2, 2, 2);
		dog();
	}
	glPopMatrix();

	//building
	glPushMatrix();
	{
		glTranslatef(-1, 0, 10);
		glScaled(10, 10, 10);
		building();
	}
	glPopMatrix();

	//tower
	glPushMatrix();
	{
		glTranslatef(7.5, -2, 16);
		tower();
	}
	glPopMatrix();



}

void scoringBoard() {
	shared::score = shared::forward / 10;
}

void moveSpider() {
	shared::spiderZ += 0.2;
}

void collisionDetection() {
	int x1 = (shared::forward - shared::lastObs1);
	int x2 = (shared::forward - shared::lastObs2);
	int x3 = (shared::forward - shared::lastObs3);
	int x4 = (shared::forward - shared::lastObs4);
	std::cout << shared::right << std::endl;
	if (!shared::sceneBoolean) {
		if (((x1 % 18 == 0) || (x2 % 18 == 0)) && (shared::jump < 0.75 && shared::right > 1 && shared::right -1)) {
			shared::movmentF = false;
			if ((x1 % 18 == 0)) {
				shared::lastObs1 = shared::forward;
			}
			if ((x2 % 18 == 0)) {
				shared::lastObs2 = shared::forward;
			}
			std::cout << "IN MONEBTKNGK";
		}
		else {
			shared::movmentF = true;
		}
		if (shared::forward < (shared::spiderZ - 9.5)) {
			std::cout << "You lost kjhfksdhkgsdkfhgksdjhgkhsdkfjhgkds:( \n";
			//resetGame();
		}
	}
	else {
		if (((x3 % 18 == 0) || (x4 % 18 == 0)) && (shared::jump < 0.75 && shared::right > 1 && shared::right - 1)) {
			shared::movmentF = false;
			if ((x3 % 18 == 0)) {
				shared::lastObs3 = shared::forward;
			}
			if ((x4 % 18 == 0)) {
				shared::lastObs4 = shared::forward;
			}
			std::cout << "IN MONEBTKNGK";
		}
		else {
			shared::movmentF = true;
		}
		if (shared::forward < (shared::spiderZ - 9.5)) {
			std::cout << "You lost kjhfksdhkgsdkfhgksdjhgkhsdkfjhgkds:( \n";
			//resetGame();
		}

	}
	
}

void setupLights() {
	GLfloat light0_ambient[] = { 0.45,0.44,0.37, 1.0f };
	GLfloat light0_diffuse[] = { 5.0f, 5.0f, 5.0f, 1.0f };
	GLfloat light0_position[] = { 1.0f, 6.5f, 0.0f + shared::forward, 1.0f };
}

void print(float x, float y, float z, char* str) {
	int len, i;

	glRasterPos3f(x, y, z);
	len = (int)strlen(str);
	for (i = 0; i < len; i++) {
		glColor3f(1, 1, 1);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	
	}
}

//Model Render Method
void render_models()
{
	// we have to enable texturing, we use textures here
	glEnable(GL_TEXTURE_2D);

	// STYLE
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Models

	//character
	person();

	//road
	for (int i = 0; i < 14; i++) {
		glPushMatrix();
		{
			glTranslatef(0, -0.45, -1.6 + (8.7 * i));
			road();
		}
		glPopMatrix();
		glPushMatrix();
		{
			//glTranslatef(0, 0, -1.6 + (8.7 * i));
			if (!shared::sceneBoolean) {
				glTranslatef(0, 0, (9 * i));
				if (i % 2 == 0) {
					for (int j = 0; j < 15; j++) {
						glPushMatrix();
						glTranslatef(j * 0.25 - 1.4, 0, 0);
						drum();
						glPopMatrix();
					}
				}
				else {
					rock();
				}
			}
			else {
				//glTranslatef(0, 0, -5.6 + (8.7 * i));
				glTranslatef(0, 0, (9 * i));
				if (i % 2 == 0) {
					for (int j = 0; j < 6; j++) {
						glPushMatrix();
						glTranslatef(j * 0.65 - 0.8, 0, -3);
						//glTranslatef(j * 0.75 - 1.4, 0, 0);
						glScaled(0.4, 0.25, 0.4);
						crate();
						glPopMatrix();
					}
				}
				else {
					glPushMatrix();
					glScaled(1, 0.6, 1);
					wood();
					glPopMatrix();
				}
			}
		}
		glPopMatrix();
	}

	//Environment 1
	if (!shared::sceneBoolean) {
		glPushMatrix(); 
		{
			//glScalef(4.5, 4.5, 4.5);
			for (int i = shared :: forward / 3; i < shared::forward / 2 + 5; i++) {
				glPushMatrix();
				glTranslatef(-1.5 + 0.5, 0, -1.6 + (2.45 * i));
				building();
				glPopMatrix();

				glPushMatrix();
				glTranslatef(-1.6 + 0.5, -0.12, -1.18 + (2.45 * i));
				farmHouse();
				glPopMatrix();

				glPushMatrix();
				glTranslatef(-1.5 + 0.5, 0, -0.25 + (2.45 * i));
				ruinedWall();
				glPopMatrix();

				glPushMatrix();
				glTranslatef(-1.8 + 0.5, -0.12, 0.45 + (2.45 * i));
				tallBuilding();
				glPopMatrix();

				glPushMatrix();
				glRotatef(180, 0, 1, 0);
				glTranslatef(-1.55 + 0.5, 0, 1.5 - (2.45 * i));
				building();
				glPopMatrix();

				glPushMatrix();
				glRotatef(180, 0, 1, 0);
				glTranslatef(-1.65 + 0.5, -0.12, 1.08 - (2.45 * i));
				farmHouse();
				glPopMatrix();

				glPushMatrix();
				glRotatef(180, 0, 1, 0);
				glTranslatef(-1.55 + 0.5, 0, 0.15 - (2.45 * i));
				ruinedWall();
				glPopMatrix();

				glPushMatrix();
				glRotatef(180, 0, 1, 0);
				glTranslatef(-1.85 + 0.5, -0.12, -0.55 - (2.45 * i));
				tallBuilding();
				glPopMatrix();
			}
		}
		glPopMatrix();
	}

	//Environment 2
	else {
		for (int i = 0; i < 6; i++) {
			glPushMatrix();
			{
				glTranslatef(-3, 1, i * 20);
				buildScene();
			}
			glPopMatrix();

			glPushMatrix();
			{
				glTranslatef(3, 1, i * 20);
				glRotatef(180, 0, 1, 0);
				buildScene();
			}
			glPopMatrix();
		}

	}

	//Spider
	glPushMatrix();
	glTranslatef(shared::spiderX, shared::spiderY, shared::spiderZ);
	spider();
	glPopMatrix();
}

void fall() {
	shared::up -= 0.3;
}

void checkLevels() {
	if (shared::forward >= 50 ) {
		if (shared::up > -5) {
			fall();
		}
		else {
			shared::forward = 0;
			shared::up = 0;
			shared::spiderZ = 0;
			shared::sceneBoolean = !shared::sceneBoolean;
		}
	}
}

void render_front_view()
{
	// set the viewport to left side of the screen
	// this means we will only draw in that region of the screen
	//glViewport(0, 0, shared::window_width * 2.0f / 3.0f, shared::window_height);

	// move the camera to the front
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0 + shared::right, 0.5 + shared::up * 0.5 + shared::perpY, -2.25 + shared::forward + shared::perpZ, 0.0 + shared::right, 0.5 + shared::jump / 3 + shared::perpY, 0.0 + shared::forward + shared::perpZ, 0.0, 1.0, 0.0);

	// render the models
	render_models();
}

void jumpMotion() {
	if (shared::jumpB) {
		if (shared::jumpBF && shared::jump <= 2) {
			shared::jump += 0.15f;
		}
		else {
			shared::jumpBF = false;
		}
		if (!shared::jumpBF && shared::jump >= 0) {
			shared::jump -= 0.25f;
		}
		else {
			if (!shared::jumpBF) {
				shared::jumpB = false;
				shared::jumpBF = true;
			}
		}
	}
}

void displayScore() {
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(1, 1, 1);
	char* c;

	glColor3f(1, 1, 1);
	char mystring1[20];
	sprintf(mystring1, "The color is: %d", shared::score);

	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(1, 1, 1);
	glRasterPos3f(0, 1, 2);

	for (c = mystring1; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);

	}
	glPopAttrib();
}

void mousePosiion(int x, int y)
{
	double param, result;
	param = -((720 / 2 - y) / (1025 / 2 - x + 0.0000001));

	if (x >= 1025 / 2 && y <= 720 / 2) {
		result = atan(param) * 180 / PI;
	}
	if (x <= 1025 / 2 && y <= 720 / 2) {
		result = 180 + atan(param) * 180 / PI;
	}
	if (x <= 1025 / 2 && y >= 720 / 2) {
		result = 180 + atan(param) * 180 / PI;
	}
	if (x >= 1025 / 2 && y >= 720 / 2) {
		result = 360 + atan(param) * 180 / PI;
	}
	shared::rotation = result;
	printf("param: %f, x: %d, y: %d, angle: %f\n", param, x, y, result);
}

void keyBoardFunction(unsigned char key, int x, int y) {
	switch (key) {
	case 'a': shared::right > 1.45 ? NULL : shared::right += 0.5; break;
	case 'd': shared::right < -1.45 ? NULL : shared::right -= 0.5; break;
	case 'w': shared::movmentF ? shared::forward += 0.25 : printf("canot move forward"); break;
	case 's': shared::forward < -1 ? NULL : shared::forward -= 0.25; break;
	case 32: shared::jumpB = true; break;
	case 'c': shared::perspective = !shared::perspective; break;
	default:
		break;
	}
}

void changePerspective() {
	if (shared::perspective) {
		shared::perpX = 0;
		shared::perpY = 0;
		shared::perpZ = 0;
	}
	else {
		shared::perpY = -0.15;
		shared::perpZ = 1.3;
	}
}

void onUpdate() {
	// set the delta time
	const int time_since_start = glutGet(GLUT_ELAPSED_TIME);
	shared::delta_time_milliseconds = float(time_since_start - shared::last_tick);
	shared::last_tick = time_since_start;

	// clear buffers
	glViewport(0, 0, shared::window_width, shared::window_height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// setup lights
	setupLights();

	// set the projection matrix
	//
	// NOTE:
	// ------
	// We here don't need to set the projection matrix multiple times
	// like we will do with the view matrix (gluLookAt) .....
	// The lens is the same, we only move the camera to different locations
	// so the projection matrix doesn't change when we move the camera.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)shared::window_width / (float)shared::window_height, 0.01, 1000.0);

	// rotate the models on y-axis
	// 
	// NOTE:
	// -----
	// Here I multiply by the delta time to keep the rotation speed
	// the same on different hardware ... 
	// So this way the animation speed will be the same even on slower
	// or faster devices

	// render front camera view
	glPushMatrix();
	glScalef(3, 3, 3);
	glTranslatef(0, 3, 0);
	displayScore();
	glPopMatrix();
	render_front_view();
	jumpMotion();
	moveSpider();
	collisionDetection();
	checkLevels();
	changePerspective();
	scoringBoard();
	char* m[20];
	sprintf((char*) m, "{%d}", shared::score);
	glPushMatrix();
	glColor3f(1, 1, 1);
	print(1, 1, shared::forward,(char*) m);
	glPopMatrix();
	//render_side_view();

	// render top_view
	//render_top_view();

	// wait till frame is fully rendered
	glFlush();
}

void onAnimate()
{
	// call onUpdate to redraw
	glutPostRedisplay();
}

void main(int argc, char** argr) {
	// initialize glut
	glutInit(&argc, argr);

	// create glut window with the exact dimensions
	glutInitWindowSize(shared::window_width, shared::window_height);

	// create glut window centered in screen
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - shared::window_width) / 2.0, (glutGet(GLUT_SCREEN_HEIGHT) - shared::window_height) / 2.0);

	// create glut window with that title
	glutCreateWindow("Project3D Template");

	// update window callback function
	glutDisplayFunc(onUpdate);

	// animation callback function
	glutIdleFunc(onAnimate);

	// window resize callback function
	glutReshapeFunc(onResize);

	//keyboard person control
	glutKeyboardFunc(keyBoardFunction);

	//mouse position function
	glutPassiveMotionFunc(mousePosiion);

	// let glut request single buffer, rgb(24bits) per pixel, need depth buffer
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	// initialize and load assets
	onStart();

	// start main rendering loop
	glutMainLoop();

	// cleanup assets' allocated buffers
	onExit();
}