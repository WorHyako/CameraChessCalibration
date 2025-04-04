#include "Gui/FixedCameraView.hpp"

#include <imgui.h>

#include <opencv2/core/mat.hpp>

using namespace Wor::CCC::Gui;

FixedCameraView::FixedCameraView(SDL_Renderer* renderer) noexcept
	: CameraViewBase(renderer) {
}

auto FixedCameraView::draw(cv::Mat cv_texture) noexcept -> void {
	ImGui::Begin("FixedCameraView");

	cv_to_sdl(std::move(cv_texture));
	if (sdl_texture_) {
		ImGui::Image(reinterpret_cast<ImU64>(sdl_texture_), ImGui::GetWindowSize());
	}
	ImGui::End();
}
