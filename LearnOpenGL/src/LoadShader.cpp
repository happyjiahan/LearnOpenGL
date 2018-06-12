#include "LoadShader.h"
#include <cstdlib>
#include <cstdio>
#include <GL/gl3w.h>
#include <iostream>


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	static
	GLchar const *
	ReadShader(char const * filename)
	{
		FILE* inFile = fopen(filename, "rb");
		if (!inFile)
		{
			std::cerr << "can not open shader file: " << filename << std::endl;
			return NULL;
		}

		int ok = fseek(inFile, 0, SEEK_END);
		if (ok != 0)
		{
			std::cerr << "can not open shader file: " << filename << std::endl;
			return NULL;
		}

		long len = ftell(inFile);
		fseek(inFile, 0, SEEK_SET);
		GLchar * source = new GLchar[len + 1];
		size_t readSize = fread(source, 1, len, inFile);
		if (readSize != len)
		{
			std::cerr << "read file error: readSize=" << readSize << " len=" << len << std::endl;
			fclose(inFile);
			return NULL;
		}
		fclose(inFile);

		source[len] = 0;

		return const_cast<GLchar const *>(source);
	}


	GLuint 
	LoadShaders(ShaderInfo * infos)
	{
		if (NULL == infos) { return 0; }

		GLuint program = glCreateProgram();
		if (0 == program) 
		{
			std::cerr << "glCreateProgram error." << std::endl;
			return 0; 
		}

		ShaderInfo * entry = infos;
		while (entry->type != GL_NONE)
		{
			GLuint shader = glCreateShader(entry->type);
			entry->shader = shader;

			GLchar const * source = ReadShader(entry->filename);
			if (NULL == source)
			{
				std::cerr << "shader error : " << shader << std::endl;
				glDeleteShader(shader);

				// todo, delete shaders
			}

			glShaderSource(shader, 1, &source, NULL);
			delete[] source;

			glCompileShader(shader);

			GLint compiled;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
			if (GL_FALSE == compiled)
			{
#if _DEBUG
				GLsizei len;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

				GLchar * log = new GLchar[len + 1];
				glGetShaderInfoLog(shader, len, &len, log);
				std::cerr << "compile shader error : " << log << std::endl;
				delete[] log;

#endif // _DEBUG
				return 0;
			}

			glAttachShader(program, shader);
			
			++entry;
		}

		glLinkProgram(program);

		GLint linked;
		glGetProgramiv(program, GL_LINK_STATUS, &linked);
		if (!linked) {
#ifdef _DEBUG
			GLsizei len;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetProgramInfoLog(program, len, &len, log);
			std::cerr << "Shader linking failed: " << log << std::endl;
			delete[] log;
#endif /* DEBUG */

			for (entry = infos; entry->type != GL_NONE; ++entry) {
				glDeleteShader(entry->shader);
				entry->shader = 0;
			}

			return 0;
		}

		return program;
	}

#ifdef __cplusplus
};
#endif // __cplusplus