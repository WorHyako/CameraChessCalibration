#include "Gui/MainWindow.hpp"

#include <string_view>

#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

using namespace Wor::CCC::Gui;

namespace {
	/**
	 * @brief	Main window title.
	 */
	constexpr std::string_view window_title{"CameraChessCalibration"};

	/**
	 * @brief	Main window SDL flags.
	 */
	constexpr std::uint32_t window_flags{SDL_WINDOW_RESIZABLE};

	/**
	 * @brief	Main window background color.
	 */
	constexpr ImVec4 background_color{ImVec4(0.45f, 0.55f, 0.60f, 1.00f)};

	/**
	 * @brief	Main window size.
	 */
	constexpr SDL_Point window_size{1200, 800};
}

auto MainWindow::create() noexcept -> Ptr {
	auto main_window{std::make_unique<MainWindow>()};
	SDL_Window* sdl_window{SDL_CreateWindow(window_title.data(), window_size.x, window_size.y, window_flags)};

	if (sdl_window == nullptr) {
		SDL_Log("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
		return nullptr;
	}
	main_window->window_ = SDLWindowPtr(sdl_window,
										[](SDL_Window* window) {
											if (window == nullptr) {
												return;
											}
											SDL_DestroyWindow(window);
										});

	SDL_Renderer* renderer{SDL_CreateRenderer(sdl_window, nullptr)};
	if (renderer == nullptr) {
		SDL_Log("Error: SDL_CreateRenderer(): %s\n", SDL_GetError());
		return nullptr;
	}
	main_window->renderer_ = SDLRendererPtr(renderer,
											[](SDL_Renderer* renderer) {
												if (renderer == nullptr) {
													return;
												}
												SDL_DestroyRenderer(renderer);
											});
	SDL_SetRenderVSync(renderer, 1);
	SDL_SetWindowPosition(sdl_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	ImGui_ImplSDL3_InitForSDLRenderer(main_window->window_.get(), renderer);
	ImGui_ImplSDLRenderer3_Init(renderer);

	SDL_ShowWindow(sdl_window);
	return main_window;
}

auto MainWindow::show() noexcept -> void {
	if (window_handle() == nullptr) {
		return;
	}
	SDL_ShowWindow(window_.get());
}

auto MainWindow::destroy() noexcept -> void {
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();

	renderer_.reset();
	window_.reset();
}

MainWindow::~MainWindow() noexcept {
	destroy();
}

auto MainWindow::new_frame() const noexcept -> void {
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();
}

auto MainWindow::render() const noexcept -> void {
	auto renderer{renderer_.get()};

	ImGui::Render();
	SDL_SetRenderDrawColorFloat(renderer,
								background_color.x,
								background_color.y,
								background_color.z,
								background_color.w);
	SDL_RenderClear(renderer);
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
	SDL_RenderPresent(renderer);
}

#pragma region Accessors/Mutators

auto MainWindow::window_handle() const noexcept -> SDL_Window* {
	return window_.get();
}

auto MainWindow::renderer_handle() const noexcept -> SDL_Renderer* {
	return renderer_.get();
}

#pragma endregion Accessors/Mutators
