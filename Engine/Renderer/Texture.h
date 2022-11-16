#pragma once 
#include "Math/Vector2.h" 
#include "Resource/Resource.h" 
#include "Renderer.h" 
#include <string> 

// !! forward declaration for SDL pointers (SDL likes to use structs instead 
struct SDL_Texture;
struct SDL_Surface;

namespace neu
{
	// !! forward declaration for Renderer 
	class Renderer;

	class Texture : public Resource
	{
	public:
		Texture() = default;
		~Texture();

		bool Create(std::string filename, ...) override;

		bool CreateFromSurface(SDL_Surface* surface, Renderer& renderer);

		bool Load(const std::string& filename);

		void setActive(GLuint unit) { glActiveTexture(unit); }

		void Bind() { glBindTexture(m_target, m_texture); }

		Vector2 GetSize() const;

		friend class Renderer;

	protected:
		void FlipSurface(SDL_Surface* surface);

	protected:
		GLuint m_texture = 0;
		GLenum m_target = GL_TEXTURE_2D;
	};
}