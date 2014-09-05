#include <SDL2/SDL.h>
#include <time.h>

int randomNumber (int min, int max) {
	int result=0,low_num=0,hi_num=0;
	if(min<max) {
		low_num = min;
		hi_num = max+1; // this is done to include max_num in output.
	}
	else { 
		low_num=max+1; // this is done to include max_num in output.
		hi_num=min;
	}
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

	if((BottomA <= TopB && (RightA <= LeftB || LeftA >= RightB)) || (TopA >= BottomB && (RightA <= LeftB || LeftA >= RightB)))
		return 0; 
	else
		return 1;
}

void move(SDL_Rect A, int step) {
	A.x = A.x - step;
}

int main (int argc, char* args[]) {

	//Inicialization

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("AVOID!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	//Setup

	srand(time(NULL));
	int timer1 = 0;
	int timer2 = 0;
	int points = 0;
	int step = 10;
	int n = 1;
	int collision = 1;
	SDL_Rect r = {270, 390, 50, 50};
	SDL_Rect r2 = {590, randomNumber(0, 430), 20, 50};
	SDL_Event event;
	while (1) {
	while (SDL_PollEvent(&event) == 0);
	if (event.type == SDL_QUIT) {
		break;
	}
	else if (event.type == SDL_KEYDOWN) {
	switch (event.key.keysym.sym) { 
		case SDLK_UP:
			r.y +­= 10;
			break;
		case SDLK_DOWN:
			r.y -= 10;
			break;
			}
		}
	timer1 = SDL_GetTicks();
	if(collision != 0) {
		timer2 = SDL_GetTicks();
		if(timer2 >= timer1 + 100)
			move(r2, step);
		collision = CollisionCheck(r, r2);
		if(r2.x == 5) {
			step = -step;
			points++;
			r2.y = randomNumber(0, 430);
		}
		if(r2.x == 640) {
			step = 10;
			points++;
			r2.y = randomNumber(0, 430);
		}
		if(points >= n*10) {
			step = (n+1)*step;
			n++;
		}
	}
	else
		break;

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