#include "Renderer.h"

Renderer::Renderer() {
	m_window = nullptr;
	m_renderer = nullptr;
	m_destRect = {};
}

Renderer::~Renderer() {
	Shutdown();
}

void Renderer::Inititlaize(int _xResolution, int _yResolution) {
	M_ASSERT((SDL_Init(SDL_INIT_EVERYTHING) >= 0), "");
	m_window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _xResolution, _yResolution, SDL_WINDOW_SHOWN);

	M_ASSERT(m_window != nullptr, "Failed to initialize SDL window");
	m_renderer = SDL_CreateRenderer(Renderer::Instance().GetWindow(), -1, 0);
	M_ASSERT(m_renderer != nullptr, "Failed to initialize SDL renderer.");
}

void Renderer::Shutdown() {
	if (m_renderer != nullptr) {
		SDL_DestroyRenderer(m_renderer);
	}

	if (m_window != nullptr) {
		SDL_DestroyWindow(m_window);
	}
	SDL_Quit();
}

void Renderer::SetDrawColor(Color _color) {
	SDL_SetRenderDrawColor(m_renderer, _color.R, _color.G, _color.B, _color.A);
}

void Renderer::ClearScreen() {
	SDL_RenderClear(m_renderer);
}

void Renderer::RenderPoint(Point _point) {
	SDL_RenderDrawPoint(m_renderer, _point.X, _point.Y);
}

void Renderer::RenderLine(Rect _point) {
	SDL_RenderDrawLine(m_renderer, _point.X1, _point.Y1, _point.X2, _point.Y2);
}

void Renderer::RenderRectangle(Rect _point) {
	m_destRect.x = _point.X1;
	m_destRect.y = _point.Y1;
	m_destRect.w = _point.X2 - _point.X1;
	m_destRect.h = _point.Y2 - _point.Y1;
	SDL_RenderDrawRect(m_renderer, &m_destRect);
}

void Renderer::RenderFillRectangle(Rect _point) {
	m_destRect.x = _point.X1;
	m_destRect.y = _point.Y1;
	m_destRect.w = _point.X2 - _point.X1;
	m_destRect.h = _point.Y2 - _point.Y1;
	SDL_RenderFillRect(m_renderer, &m_destRect);
}