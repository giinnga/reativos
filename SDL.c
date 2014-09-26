#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>

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

	if((BottomA <= TopB || TopA >= BottomB || RightA <= LeftB || LeftA >= RightB))
		return 0; 
	else
		return 1;
}

int main (int argc, char* args[]) {

	//Inicialization

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("AVOID!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	//Setup

	srand(time(NULL));
	int y1 = randomNumber(0,430), y2 = randomNumber(0,430);
	int timer_points = 0;
	int timer1 = SDL_GetTicks();
	int timer2 = 0;
	int points = 0;
	int step = 3;
	int n = 1;
	int x = 1;
	int collision = 0;
	SDL_Rect r = {290, 390, 50, 50};
	SDL_Rect r2 = {590, randomNumber(0, 430), 20, 60};
	SDL_Rect r3 = {-20, randomNumber(0, 430), 20, 60};
	SDL_Event e;
	if(y1 <= y2 - 70 && y1 >= y2 + 70) {
		y1 = randomNumber(0,430);
	}
	while (1) {
		if(SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT) {
				break;
			}
			else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) { 
					case SDLK_UP:
						r.y -= 15;
						break;
					case SDLK_DOWN:
						r.y += 15;
						break;
				}
			}
		}
		if(collision == 0) {
			timer2 = SDL_GetTicks();
			timer_points = SDL_GetTicks();
			if (timer2 >= timer1 + 10) {
				r2.x -= step;
				r3.x += step;
				collision = CollisionCheck(r, r2);
				collision = CollisionCheck(r, r3);
				timer1 = timer2;
			}
			if (r2.x <= -20 && r3.x >= 650) {
				r2.y = randomNumber (0, 430);
				r3.y = randomNumber (0, 430);
				if(r2.y <= r3.y - 70 && r2.y >= r3.y + 70)
					r3.y = randomNumber (0,430);
				step = -randomNumber(3,4);
			}
			else if (r2.x >= 650 && r3.x <= -20) {
				r2.y = randomNumber (0, 430);
				r3.y = randomNumber (0, 430);
				if(r2.y <= r3.y - 70 && r2.y >= r3.y + 70)
					r3.y = randomNumber (0,430);
				step = randomNumber(3,4);
			}
		}
		else
			break;

		SDL_SetRenderDrawColor(renderer, 0x00,0x00,0x00,0x00);
		SDL_RenderFillRect(renderer, NULL);
		SDL_SetRenderDrawColor(renderer, 0x00,0xFF,0x00,0x00);
		SDL_RenderFillRect(renderer, &r);
		SDL_SetRenderDrawColor(renderer, 0xFF,0x00,0x00,0x00);
		SDL_RenderFillRect(renderer, &r2);
		SDL_SetRenderDrawColor(renderer, 0x00,0x00,0xFF,0x00);
		SDL_RenderFillRect(renderer, &r3);
		SDL_RenderPresent(renderer);
	}

//Finalization

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}