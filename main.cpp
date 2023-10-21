#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include <ft2build.h>

void moveBall();

int main(int argc, char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Surface* text;
    TTF_Font* font;
    SDL_Texture* text_texture;
    char score1[] = "0";
    char score2[] = "0";


    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_CreateWindowAndRenderer(1080, 720, 0, &window, &renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_Rect paddle2;
    paddle2.w = 25;
    paddle2.h = 150;
    paddle2.y = 360-75;
    paddle2.x = 1080-10-paddle2.w;
    SDL_RenderDrawRect(renderer, &paddle2);
    SDL_Rect paddle;
    paddle.w = 25;
    paddle.h = 150;
    paddle.y = 360-75;
    paddle.x = 10;
    SDL_RenderDrawRect(renderer, &paddle);

    SDL_Rect rect;
    rect.w = 25;
    rect.h = 25;
    rect.y = 240;
    rect.x = 320;
    SDL_RenderDrawRect(renderer, &rect);

    font = TTF_OpenFont("Arial Unicode.ttf", 25);
    if ( !font ) {printf("Failed to load font: ");}
    SDL_Color color = { 255, 255, 255 };
    text = TTF_RenderText_Solid(font, "Hello", color);

    text_texture = SDL_CreateTextureFromSurface( renderer, text );
    SDL_Rect dest = { 0, 0, text->w, text->h };
    SDL_RenderCopy(renderer, text_texture, NULL, &dest);

    //Speed up integer
    float speedUp = 1.1;
    



    SDL_RenderPresent(renderer);

    if (window == NULL) {
    // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    float xdirection = 3.0;
    float ydirection = 3.0;


    bool is_running = true;
    SDL_Event event;
    while (is_running) {
        //Wall collision detection
        if (rect.y <= 0)
            ydirection = ydirection * -1;
        if (rect.y >= 720-25)
            ydirection = ydirection * -1;
        if (rect.x <= 0)
            xdirection = xdirection * -1;
        if (rect.x >= 1080-25)
            xdirection = xdirection * -1;

        //Paddle collision detection
        if (rect.x <= paddle.x + paddle.w  && rect.y >= paddle.y && rect.y < paddle.y + paddle.h)
            xdirection = xdirection * -1 * speedUp;
        if (rect.x >= paddle2.x - paddle2.w  && rect.y >= paddle2.y && rect.y < paddle2.y + paddle.h)
            xdirection = xdirection * -1 * speedUp;

        //Score detection
        if (rect.x <= 0 or rect.x >= 1080-rect.w) {
            rect.x = 320;
            rect.y = 240;
            xdirection = 3.0;
            ydirection = 3.0;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 255,255,255,255);
            SDL_RenderDrawRect(renderer, &rect);
            SDL_RenderDrawRect(renderer, &paddle);
            SDL_RenderDrawRect(renderer, &paddle2);
            SDL_RenderFillRect(renderer, &rect);
            SDL_RenderFillRect(renderer, &paddle);
            SDL_RenderFillRect(renderer, &paddle2);
            SDL_RenderPresent(renderer);
            SDL_Delay(1000);
            
        }

        rect.y += ydirection;
        rect.x += xdirection;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderDrawRect(renderer, &paddle);
        SDL_RenderDrawRect(renderer, &paddle2);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &paddle);
        SDL_RenderFillRect(renderer, &paddle2);
        //SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&event)) {
            switch( event.type ){
        case SDL_KEYDOWN:
        /* Check the SDLKey values and move change the coords */
                switch( event.key.keysym.sym ){
                    case SDLK_UP:
                        paddle2.y = paddle2.y - 30;
                        break;
                    case SDLK_DOWN:
                        paddle2.y = paddle2.y + 30;
                        break;
                    case SDLK_w:
                        paddle.y = paddle.y - 30;
                        break;
                    case SDLK_s:
                        paddle.y = paddle.y + 30;
                        break;
                    default:
                        break;
                }

            break;

        default:
            break;
    }

            if (event.type == SDL_QUIT) {
                is_running = false;
            }
        }

    }

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    //SDL_DestroyTexture(texture);
    SDL_FreeSurface(text);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}