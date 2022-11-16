#pragma once
#include "Texture.h"
#include <vector>
#include "Core/Logger.h" 
#include <SDL.h> 
#include <SDL_image.h> 
#include <cstdarg> 

namespace neu
{
	class CubeMapTexture : public Texture
	{
	public:
		bool Create(std::string filename, ...) override;
		bool Load(const std::vector<std::string>& filename);
		std::vector<std::string> GenerateCubeMapNames(const std::string& basename, const std::string& extension);
		static GLenum GetInternalFormat(GLuint format);

	private:

	};
}