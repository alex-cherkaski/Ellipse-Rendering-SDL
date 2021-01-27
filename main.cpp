#include <SDL.h>
#include <iostream>
#include <string>

struct Ellipse { int x, y, a, b; };

SDL_Window* g_window;
SDL_Renderer* g_renderer;

bool InitializeWindow(int windowWidth, int windowHeight);
void RenderEllipse(const Ellipse& circle);
void Destroy();

int main(int argc, char* argv[])
{
	if (InitializeWindow(800, 600))
	{
		Ellipse ellipse = { 400, 300, 200, 100 };
		RenderEllipse(ellipse);
		SDL_Delay(2000);
	}

	Destroy();

	return 0;
}

bool InitializeWindow(int windowWidth, int windowHeight)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << std::string("Could not initialize SDL. SDL Error: ") + SDL_GetError() << "\n";
		return false;
	}

	g_window = SDL_CreateWindow("Efficient Circle Rendering", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	if (g_window == nullptr)
	{
		std::cout << std::string("Could not create SDL window. SDL Error: ") + SDL_GetError() << "\n";
		return false;
	}

	g_renderer = SDL_CreateRenderer(g_window, -1, 0);
	if (g_renderer == nullptr)
	{
		std::cout << std::string("Could not get create SDL Renderer. SDL Error: ") + SDL_GetError() << "\n";
		return false;
	}

	return true;
}

void RenderEllipse(const Ellipse& ellipse)
{
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);

    float p = static_cast<float>(ellipse.b * ellipse.b - ellipse.a * ellipse.a * ellipse.b + ellipse.a * ellipse.a / 4.0F);
    float x = 0;
    float y = static_cast<float>(ellipse.b);

    while (2.0F * ellipse.b * ellipse.b * x <= 2.0F * ellipse.a * ellipse.a * y)
    {
        if (p < 0)
        {
            x++;
            p = p + 2 * ellipse.b * ellipse.b * x + ellipse.b * ellipse.b;
        }

        else
        {
            x++;
            y--;
            p = p + 2 * ellipse.b * ellipse.b * x - 2 * ellipse.a * ellipse.a * y - ellipse.b * ellipse.b;
        }
        
        SDL_RenderDrawPoint(g_renderer, static_cast<int>(ellipse.x + x), static_cast<int>(ellipse.y + y));
        SDL_RenderDrawPoint(g_renderer, static_cast<int>(ellipse.x + x), static_cast<int>(ellipse.y - y));
        SDL_RenderDrawPoint(g_renderer, static_cast<int>(ellipse.x - x), static_cast<int>(ellipse.y + y));
        SDL_RenderDrawPoint(g_renderer, static_cast<int>(ellipse.x - x), static_cast<int>(ellipse.y - y));
    }


    p = ellipse.b * ellipse.b * (x + 0.5F) * (x + 0.5F) + ellipse.a * ellipse.a * (y - 1) * (y - 1) - ellipse.a * ellipse.a * ellipse.b * ellipse.b;

    while (y > 0)
    {
        if (p <= 0)
        {
            x++;
            y--;
            p = p + 2 * ellipse.b * ellipse.b * x - 2 * ellipse.a * ellipse.a * y + ellipse.a * ellipse.a;
        }

        else
        {
            y--;
            p = p - 2 * ellipse.a * ellipse.a * y + ellipse.a * ellipse.a;
        }

        SDL_RenderDrawPoint(g_renderer, static_cast<int>(ellipse.x + x), static_cast<int>(ellipse.y + y));
        SDL_RenderDrawPoint(g_renderer, static_cast<int>(ellipse.x + x), static_cast<int>(ellipse.y - y));
        SDL_RenderDrawPoint(g_renderer, static_cast<int>(ellipse.x - x), static_cast<int>(ellipse.y + y));
        SDL_RenderDrawPoint(g_renderer, static_cast<int>(ellipse.x - x), static_cast<int>(ellipse.y - y));
    }

	SDL_RenderPresent(g_renderer);
}

void Destroy()
{
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	SDL_Quit();
}
