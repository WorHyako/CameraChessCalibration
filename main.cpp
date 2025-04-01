#include <cstdio>

#include "Gui/MainWindow.hpp"

#include <opencv2/opencv.hpp>

#include <SDL3/SDL.h>

#include <imgui.h>
#include <imgui_impl_sdl3.h>

using namespace Wor;

int main() {
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_CAMERA)) {
		std::printf("Error: SDL_Init(): %s\n", SDL_GetError());
		return -1;
	}

	auto main_window{CCC::Gui::MainWindow::create()};
	if (main_window == nullptr) {
		return -1;
	}

	auto window{main_window->window_handle()};
	auto renderer{main_window->renderer_handle()};

	main_window->show();

	auto io{ImGui::GetIO()};

	cv::VideoCapture cam;
	cam.open(0, cv::CAP_ANY);

	bool done{false};
	while (!done && cam.isOpened()) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			ImGui_ImplSDL3_ProcessEvent(&event);
			if (event.type == SDL_EVENT_QUIT)
				done = true;
			if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(window))
				done = true;
		}

		if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) {
			SDL_Delay(10);
			continue;
		}

		main_window->new_frame();

		cv::Mat pic;
		cam >> pic;
		ImGui::Begin("Camera view");

		SDL_Texture* tex{
					SDL_CreateTexture(renderer,
									  SDL_PIXELFORMAT_BGR24,
									  SDL_TEXTUREACCESS_STREAMING,
									  pic.cols,
									  pic.rows)
				};
		SDL_UpdateTexture(tex, nullptr, pic.data, static_cast<int>(pic.step1()));

		ImGui::Image(reinterpret_cast<ImU64>(tex), {static_cast<float>(tex->w), static_cast<float>(tex->h)});

		ImGui::End();

		main_window->render();
	}
	SDL_Quit();
	return 0;
}
