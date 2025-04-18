#include "Gui/StreamCameraView.hpp"

#include <imgui.h>

#include <opencv2/core/mat.hpp>

using namespace Wor::CCC::Gui;

StreamCameraView::StreamCameraView(SDL_Renderer* renderer) noexcept
	: CameraViewBase(renderer) {
}

auto StreamCameraView::draw(cv::Mat cv_texture) noexcept -> void {
	ImGui::Begin("Stream Camera View");

	CameraViewBase::cv_to_sdl(std::move(cv_texture));
	if (sdl_texture_) {
		ImGui::Image(reinterpret_cast<ImU64>(sdl_texture_), ImGui::GetWindowSize());
	}
	ImGui::End();
}
