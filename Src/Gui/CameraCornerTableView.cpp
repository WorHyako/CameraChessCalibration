#include "Gui/CameraCornerTableView.hpp"

#include <opencv2/core/mat.hpp>

#include <SDL3/SDL_render.h>

#include <imgui.h>

using namespace Wor::CCC::Gui;

CameraCornerTableView::CameraCornerTableView(SDL_Renderer* renderer) noexcept
	: renderer_{renderer} {
}

auto CameraCornerTableView::draw() noexcept -> void {
	ImGui::Begin("Corners");

	const auto table_length{static_cast<std::uint8_t>(std::sqrt(std::size(sdl_textures_)))};
	if (table_length > 0) {
		if (ImGui::BeginTable("Corner screenshots", table_length)) {
			for (std::uint8_t row{0}; row < table_length; row++) {
				ImGui::TableNextRow();
				for (std::uint8_t column{0}; column < table_length; column++) {
					const std::int32_t index{row * column + column};
					if (index >= std::size(sdl_textures_)) {
						break;
					}

					ImGui::TableSetColumnIndex(column);
					if (ImGui::ImageButton("",
										   reinterpret_cast<ImU64>(sdl_textures_.at(index)),
										   {
											   ImGui::GetWindowSize().x / table_length,
											   ImGui::GetWindowSize().y / table_length
										   })) {
					}
				}
			}
			ImGui::EndTable();
		}
	}
	ImGui::End();
}

auto CameraCornerTableView::push_texture(const cv::Mat& cv_texture) noexcept -> void {
	SDL_Texture* sdl_texture{
				SDL_CreateTexture(renderer_,
								  SDL_PIXELFORMAT_BGR24,
								  SDL_TEXTUREACCESS_STATIC,
								  cv_texture.cols,
								  cv_texture.rows)
			};

	SDL_UpdateTexture(sdl_texture, nullptr, cv_texture.data, cv_texture.step1());

	sdl_textures_.emplace_back(sdl_texture);
}
