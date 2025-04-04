#include <cstdio>
#include <future>

#include "Gui/MainWindow.hpp"
#include "Gui/CameraSettingsWidget.hpp"
#include "Gui/StreamCameraView.hpp"
#include "Gui/FixedCameraView.hpp"
#include "Gui/CameraCornerTableView.hpp"
#include "Video/VideoStream.hpp"
#include "Video/CornerFinder.hpp"

#include "Wor/Wrappers/Singleton.hpp"

#include <opencv2/opencv.hpp>

#include <SDL3/SDL.h>

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_internal.h>

using namespace Wor::CCC;
using namespace std::chrono_literals;

namespace {
	/**
	 * @brief
	 *
	 * @param	input
	 *
	 * @param	output
	 *
	 * @return
	 *
	 * @author	WorHyako
	 */
	[[maybe_unused]]
	auto convert = [](const cv::Mat& input, SDL_Texture* output)-> SDL_Texture* {
		const Uint8* pixel_data{input.data};

		std::uint32_t pitch{static_cast<std::uint32_t>(input.step1())};
		void* gray_pixels;
		int gray_pitch;
		SDL_LockTexture(output, nullptr, &gray_pixels, &gray_pitch);
		Uint8* gray_pixel_data{static_cast<Uint8*>(gray_pixels)};

		for (std::size_t y = 0; y < input.rows; ++y) {
			for (std::size_t x = 0; x < input.cols; ++x) {
				Uint8 pixel{pixel_data[y * pitch + x]};

				const std::size_t dest_index{y * gray_pitch + x * 3};
				gray_pixel_data[dest_index] = pixel;
				gray_pixel_data[dest_index + 1] = pixel;
				gray_pixel_data[dest_index + 2] = pixel;
			}
		}
		SDL_UnlockTexture(output);
		return output;
	};
}

int main() {
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_CAMERA)) {
		std::printf("Error: SDL_Init(): %s\n", SDL_GetError());
		return -1;
	}

	auto main_window{Gui::MainWindow::create()};
	if (main_window == nullptr) {
		return -1;
	}

	const auto window{main_window->window_handle()};
	main_window->show();

	std::vector<SDL_Texture*> corner_sdl_textures;

	const auto renderer{main_window->renderer_handle()};

	Gui::CameraSettingsWidget camera_settings_window;
	Gui::StreamCameraView stream_camera_view(renderer);
	Gui::CameraCornerTableView corner_table_view(renderer);
	Gui::FixedCameraView fixed_camera_view(renderer);

	auto& video_stream = Wor::Wrappers::Singleton<Video::VideoStream>::get();

	bool done{false};
	while (!done) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			ImGui_ImplSDL3_ProcessEvent(&event);
			if (event.type == SDL_EVENT_QUIT) {
				done = true;
			}
			if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(window)) {
				done = true;
			}
		}

		if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) {
			SDL_Delay(10);
			continue;
		}

		main_window->new_frame();

		const cv::Mat stream_cv_texture{video_stream.frame()};

		auto find_corners_task{
					std::async(std::launch::async,
							   Video::CornerFinder::find,
							   stream_cv_texture)
				};

		const auto main_window_size{main_window->size()};

		ImVec2 camera_window_size{main_window_size.x * 0.5f, main_window_size.y * 0.5f};

		/**
		 * Stream camera view
		 */
		ImGui::SetNextWindowPos({0.0f, 0.0f});
		ImGui::SetNextWindowSize(camera_window_size);
		stream_camera_view.draw(stream_cv_texture);

		/**
		 * Camera settings view
		 */
		ImGui::SetNextWindowPos({0.0f, main_window_size.y * 0.5f});
		ImGui::SetNextWindowSize(camera_window_size);
		camera_settings_window.draw();

		/**
		 * Corner table view
		 */
		ImGui::SetNextWindowPos({main_window_size.x * 0.5f, main_window_size.y * 0.5f});
		ImGui::SetNextWindowSize(camera_window_size);
		corner_table_view.draw();

		/**
		 * Fixed camera view
		 */
		// ImGui::SetNextWindowPos({main_window_size.x * 0.5f, 0.0f});
		// ImGui::SetNextWindowSize(camera_window_size);
		// fixed_camera_view.draw();

		main_window->render();

		std::vector corners{find_corners_task.get()};
		if (corners.empty() == false) {
			cv::Mat corner_cv_texture{stream_cv_texture.clone()};

			for (const auto& corner : corners) {
				cv::circle(corner_cv_texture,
						   corner,
						   5,
						   cv::Scalar(0, (255 - 5 * std::size(corners)) * 2, 255),
						   cv::FILLED);
			}

			corner_table_view.push_texture(corner_cv_texture);
		}
	}
	SDL_Quit();
	return 0;
}
