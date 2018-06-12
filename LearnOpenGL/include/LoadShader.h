#pragma once

#include <GL/gl3w.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <GL/GL.h>

 typedef struct {
	 GLenum type;
	 const char * filename;
	 GLuint shader;
 } ShaderInfo; 

 GLuint LoadShaders(ShaderInfo *);

#ifdef __cplusplus
};
#endif // __cplusplus
