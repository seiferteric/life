#include <SDL/SDL.h>
#include <stdint.h>
#define WIDTH 800
#define HEIGHT 800




SDL_Surface* srf = NULL;
uint32_t life[WIDTH][HEIGHT];
void step();
void init();
void set_point(int x, int y, uint32_t color);
uint32_t get_point(int x, int y);
int main() {
  int start = 0;
  SDL_Init(SDL_INIT_VIDEO);
  srf = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);
  init();
  
  
  SDL_Event event;
  while(1) {
    while(SDL_PollEvent(&event)) {  
      switch(event.type) { 
        case SDL_KEYDOWN:
          if(event.key.keysym.sym == SDLK_ESCAPE ) {
            exit(0);
          }
          if(event.key.keysym.sym == SDLK_SPACE ) {
            if(!start)
              start = 1;
            else
              start = 0;
          }
          break;
        default:
          break;
      }
    }
    if(start)
      step();
  }
  SDL_Quit();
  return 0;
}



void init() {

  SDL_FillRect(srf, 0, 0x00000000);
  int x, y;
  for(y=0;y<HEIGHT;y++) {
    for(x=0;x<WIDTH;x++) {
      if((rand() % 10) == 1) 
        set_point(x, y, 0x0000ff00);
    } 
  }
  SDL_UpdateRect(srf, 0, 0, 0, 0);
  
}


uint32_t get_point(int x, int y) {
 
  //return *((unsigned int*)srf->pixels + (WIDTH*y + x));
  return life[y][x];
}

void set_point(int x, int y, uint32_t color) {
  *((uint32_t*)srf->pixels + (WIDTH*y + x)) = color;
}

uint32_t north(int x, int y) {
  if(y > 0)
    return get_point(x, y-1);
  else
    return get_point(x, HEIGHT);
}
uint32_t south(int x, int y) {
  if(y < HEIGHT)
    return get_point(x, y+1);
  else
    return get_point(x, 0);
}
uint32_t east(int x, int y) {
  if(x < WIDTH)
    return get_point(x+1, y);
  else
    return get_point(0, y);
}
uint32_t west(int x, int y) {
  if(x > 0)
    return get_point(x-1, y);
  else
    return get_point(WIDTH, y);
}

uint32_t north_west(int x, int y) {
  int nx, ny;
  if(y > 0)
    ny = y -1;
  else
    ny = HEIGHT;

  if(x > 0)
    nx = x-1;
  else
    nx = WIDTH;
  return get_point(nx, ny); 
}
uint32_t north_east(int x, int y) {
  int nx, ny;
  if(y > 0)
    ny = y -1;
  else
    ny = HEIGHT;

  if(x < WIDTH)
    nx = x+1;
  else
    nx = 0;
  return get_point(nx, ny); 
}
uint32_t south_west(int x, int y) {
  int nx, ny;
  if(y < HEIGHT)
    ny = y + 1;
  else
    ny = 0;

  if(x > 0)
    nx = x-1;
  else
    nx = WIDTH;
  return get_point(nx, ny); 
}
uint32_t south_east(int x, int y) {
  int nx, ny;
  if(y < HEIGHT)
    ny = y + 1;
  else
    ny = 0;

  if(x < WIDTH)
    nx = x+1;
  else
    nx = 0;
  return get_point(nx, ny); 
}
uint32_t living_neighbours(int x, int y) {
  int count = 0;
  if(north_west(x, y))
    count++;
  if(north(x, y))
    count++;
  if(north_east(x, y))
    count++;
  if(west(x, y))
    count++;
  if(east(x, y))
    count++;
  if(south_west(x, y))
    count++;
  if(south(x, y))
    count++;
  if(south_east(x, y))
    count++;    
  return count;
}


void step() {
  memcpy(life, srf->pixels, WIDTH*HEIGHT*4);
  int x, y;
  for(y=0;y<HEIGHT;y++) {
    for(x=0;x<WIDTH;x++) {
      int n = living_neighbours(x, y);
      if(!get_point(x,y) && !(rand() % 10000)) {
        set_point(x, y, 0x0000ff00);
        continue;
      }
      if(n < 2) {
        set_point(x, y, 0x00000000);
        continue;
      }
      if(n > 3) {
        set_point(x, y, 0x00000000);
        continue; 
      }
      if(n == 3) {
        set_point(x, y, 0x0000ff00);
      }
    } 
  }
  SDL_UpdateRect(srf, 0, 0, 0, 0);
}

