#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

const GLchar *vertexSource=	
	"attribute vec3 position;"
	"void main(){"
	"	gl_Position=vec4(position,1.0);"
	"}";
const GLchar *fragmentSource=
	"void main(){"
	"	gl_FragColor=vec4(1.0,0.8,0.0,1.0);"
	"}";

int main(int argc, char *argv[]){
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	
	SDL_Window *window = SDL_CreateWindow("OpenGL",100,100,800,600,SDL_WINDOW_OPENGL);
	if(window==NULL){
		printf("Couldn't create window %s\n",SDL_GetError());
	}
	
	SDL_GLContext context=SDL_GL_CreateContext(window);
	
	glewExperimental=GL_TRUE;
	glewInit();
	
	printf("\nGL Version: %s\n",glGetString(GL_VERSION));
	fflush(0);
	//start code for triangle
	float vertices[]={
		0.0f, 0.5f,1.0f,
		0.5f, -0.5f,1.0f,
		-0.5f, -0.5f,.0f
	};
	printf("Size of vertex: %ld, vertices: %ld\n",sizeof(float),sizeof(vertices));
	printf("Hi! Beginning the program.....\n");
	GLuint vbo;
	glGenBuffers(1, &vbo);
	printf("%u\n",vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//compile shaders
	GLuint vertexShader=glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertexSource,NULL);
	glCompileShader(vertexShader);
	
	GLint status;
	glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&status);
	
	char buffer[512];
	glGetShaderInfoLog(vertexShader,512,NULL,buffer);
	printf("vertex shader says: %s\n",buffer);
	
	GLuint fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1,&fragmentSource,NULL);
	glCompileShader(fragmentShader);
	
	glGetShaderInfoLog(fragmentShader,512,NULL,buffer);
	printf("fragment shader says: %s\n",buffer);
	
	GLuint shaderProgram=glCreateProgram();
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram,fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	
	GLint posAttrib=glGetAttribLocation(shaderProgram,"position");
	glVertexAttribPointer(posAttrib,3,GL_FLOAT,GL_FALSE,0,0);
	glEnableVertexAttribArray(posAttrib);
	
	SDL_Event windowEvent;
	while(true){
		if(SDL_PollEvent(&windowEvent)){
			if(windowEvent.type==SDL_QUIT) break;
			if(windowEvent.type==SDL_KEYUP && windowEvent.key.keysym.sym==SDLK_ESCAPE) break;
		}
		if(glGetError()!=GL_NO_ERROR) printf("There's some sort of error: %d.\n",glGetError());
		glClearColor(0.0f,0.0f,0.8f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES,0,3);

		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext(context);
	
	SDL_Quit();
	return 0;
}
