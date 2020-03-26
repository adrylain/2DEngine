#include <iostream>
#include <vector>
#include <math.h>

#include <fstream>
#include <strstream>
#include <algorithm>

#include <SDL2/SDL.h>

#include "SDLInter.h"

using namespace std;



struct vector3D {
    
    float x,y,z;
    
};


struct triangle {
    
    vector3D p[3];
    
    wchar_t sym;
	short col;
    
};

struct mesh {
    
    vector<triangle> tris;
    
};

struct matrix44 {
    
    float m[4][4] = { 0 };
    
};





void MultiplyMatrixVector(vector3D &i, vector3D &o, matrix44 &m)
{
	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	
	float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

	if (w != 0.0f)
	{
		o.x /= w;
		o.y /= w;
		o.z /= w;
	}
}





int main(){


        SDLInter SDLObject;

        SDLObject.init();


	    //Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;




		float screenWidth = (float)SDLObject.SCREEN_WIDTH;
		float screenHeight = (float)SDLObject.SCREEN_HEIGHT;

		matrix44 projMatrix;
    
    	mesh meshCube;
    
    
    	//set cube values
    
		meshCube.tris = {


		{ 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },


		{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },


		{ 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },


		{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },


		{ 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },


		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },

		};


		//set projection matrix values

		float fNear = 0.1f;
		float fFar = 1000.0f;
		float fFov = 90.0f;
		float fAspectRatio = ((float)screenHeight / (float)screenWidth);
		float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

		projMatrix.m[0][0] = fAspectRatio * fFovRad;
		projMatrix.m[1][1] = fFovRad;
		projMatrix.m[2][2] = fFar / (fFar - fNear);
		projMatrix.m[3][2] = (-fFar * fNear) / (fFar - fNear);
		projMatrix.m[2][3] = 1.0f;
		projMatrix.m[3][3] = 0.0f;



 		for (float i = 0.0f; i < 180.0f; i = i + 0.05f) {
		
		SDL_Delay(25);
 		SDL_SetRenderDrawColor(SDLObject.gameRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderClear( SDLObject.gameRenderer );


		// Set up rotation matrices
		matrix44 matRotZ, matRotX;
		float fTheta = (float)i;

		// Rotation Z
		matRotZ.m[0][0] = cosf(fTheta);
		matRotZ.m[0][1] = sinf(fTheta);
		matRotZ.m[1][0] = -sinf(fTheta);
		matRotZ.m[1][1] = cosf(fTheta);
		matRotZ.m[2][2] = 1;
		matRotZ.m[3][3] = 1;

		// Rotation X
		matRotX.m[0][0] = 1;
		matRotX.m[1][1] = cosf(fTheta * 0.5f);
		matRotX.m[1][2] = sinf(fTheta * 0.5f);
		matRotX.m[2][1] = -sinf(fTheta * 0.5f);
		matRotX.m[2][2] = cosf(fTheta * 0.5f);
		matRotX.m[3][3] = 1;


		// Draw Triangles
		for (auto tri : meshCube.tris)
		{
			triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;

			// Rotate in Z-Axis
			MultiplyMatrixVector(tri.p[0], triRotatedZ.p[0], matRotZ);
			MultiplyMatrixVector(tri.p[1], triRotatedZ.p[1], matRotZ);
			MultiplyMatrixVector(tri.p[2], triRotatedZ.p[2], matRotZ);

			// Rotate in X-Axis
			MultiplyMatrixVector(triRotatedZ.p[0], triRotatedZX.p[0], matRotX);
			MultiplyMatrixVector(triRotatedZ.p[1], triRotatedZX.p[1], matRotX);
			MultiplyMatrixVector(triRotatedZ.p[2], triRotatedZX.p[2], matRotX);

			// Offset into the screen
			triTranslated = triRotatedZX;
			triTranslated.p[0].z = triRotatedZX.p[0].z + 3.0f;
			triTranslated.p[1].z = triRotatedZX.p[1].z + 3.0f;
			triTranslated.p[2].z = triRotatedZX.p[2].z + 3.0f;

			// Project triangles from 3D --> 2D
			MultiplyMatrixVector(triTranslated.p[0], triProjected.p[0], projMatrix);
			MultiplyMatrixVector(triTranslated.p[1], triProjected.p[1], projMatrix);
			MultiplyMatrixVector(triTranslated.p[2], triProjected.p[2], projMatrix);

			// Scale into view
			triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
			triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
			triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;
			triProjected.p[0].x *= 0.5f * screenWidth;
			triProjected.p[0].y *= 0.5f * screenHeight;
			triProjected.p[1].x *= 0.5f * screenWidth;
			triProjected.p[1].y *= 0.5f * screenHeight;
			triProjected.p[2].x *= 0.5f * screenWidth;
			triProjected.p[2].y *= 0.5f * screenHeight;

			// Rasterize triangle
			//DrawTriangle(triProjected.p[0].x, triProjected.p[0].y,
			//	triProjected.p[1].x, triProjected.p[1].y,
			//	triProjected.p[2].x, triProjected.p[2].y,
			//	PIXEL_SOLID, FG_WHITE);



                SDL_SetRenderDrawColor(SDLObject.gameRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

				SDL_RenderDrawLine(SDLObject.gameRenderer, triProjected.p[0].x, triProjected.p[0].y, triProjected.p[1].x, triProjected.p[1].y);

				SDL_RenderDrawLine(SDLObject.gameRenderer, triProjected.p[0].x, triProjected.p[0].y, triProjected.p[2].x, triProjected.p[2].y);

				SDL_RenderDrawLine(SDLObject.gameRenderer, triProjected.p[1].x, triProjected.p[1].y, triProjected.p[2].x, triProjected.p[2].y);




				//Update screen
				SDL_RenderPresent( SDLObject.gameRenderer );


		}



		}



		while( !quit ){
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}

				//Clear screen
				//SDL_RenderClear( SDLObject.gameRenderer );

				//Update screen
				//SDL_RenderPresent( SDLObject.gameRenderer );
		}


SDLObject.close();

return 0;

}














