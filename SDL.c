#include <SDL2/SDL.h>
#include <time.h>

int random (int min, int max) {
	int result=0,low_num=0,hi_num=0;
	if(min_num<max_num) {
	low_num = min_num;
	hi_num = max_num+1; // this is done to include max_num in output.
	}
	else { 
	low_num=max_num+1; // this is done to include max_num in output.
	hi_num=min_num;
	}
	srand(time(NULL));
	result = (rand()%(hi_num-low_num))+low_num;
	return result;
}

int CollisionCheck(SDL_Rect A, SDL_Rect B) {

    //The sides of the rectangles
	unsigned int LeftA, LeftB;
	unsigned int RightA, RightB;
	unsigned int TopA, TopB;
	unsigned int BottomA, BottomB;
     
    //Get the sizes from the SDL_Rect structs - Rect A
	LeftA = A.x;
	RightA = A.x + A.w;
	TopA = A.y;
	BottomA = A.y + A.h;
     
    //Get the sizes from the SDL_Rect structs - Rect B
	LeftB = B.x;
	RightB = B.x + B.w;
	TopB = B.y;
	BottomB = B.y + B.h;

	if( (BottomA <= TopB) || (TopA >= BottomB) || (RightA <= LeftB) || (LeftA >= RightB) )
		return 0; 
	else
		return 1;
}

int main (int argc, char* args[]) {

//Inicialization

SDL_Init(SDL_INIT_EVERYTHING);
SDL_Window* window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

//Setup

int collision = 1;
SDL_Rect r = {200, 200, 50, 50};
SDL_Event event;
while (1) {
while (SDL_PollEvent(&event) == 0);
if (event.type == SDL_QUIT) {
	break;
}
else if (event.type == SDL_KEYDOWN) {
switch (event.key.keysym.sym) { 
	case SDLK_UP:
		r.y ­= 10;
	case SDLK_DOWN:
		r.y += 10;
		}
	}
while(collision != 0) {
	SDL_Rect r2 = {590, random(0, 430), 50, 50};
	collision = CollisionCheck(r, r2);
	
}
SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0xFF,0x00);
SDL_RenderFillRect(renderer, NULL);
SDL_SetRenderDrawColor(renderer, 0x00,0xFF,0x00,0x00);
SDL_RenderFillRect(renderer, &r);
SDL_SetRenderDrawColor(renderer, 0xFF,0x00,0x00,0x00);
SDL_RenderFillRect(renderer, &r2);
SDL_RenderPresent(renderer);
	}

//Finalization

SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();
}