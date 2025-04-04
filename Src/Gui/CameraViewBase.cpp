#include "Gui/CameraViewBase.hpp"

#include <opencv2/core/mat.hpp>

#include <SDL3/SDL_render.h>

using namespace Wor::CCC::Gui;

CameraViewBase::CameraViewBase(SDL_Renderer* renderer) noexcept
	: renderer_{renderer},
	  sdl_texture_{nullptr} {
}

auto CameraViewBase::cv_to_sdl(cv::Mat&& cv_texture) noexcept -> void {
	if (cv_texture.empty()) {
		return;
	}
	if (sdl_texture_ == nullptr) {
		sdl_texture_ = SDL_CreateTexture(renderer_,
										 SDL_PIXELFORMAT_BGR24,
										 SDL_TEXTUREACCESS_STATIC,
										 cv_texture.cols,
										 cv_texture.rows);
	}

	SDL_UpdateTexture(sdl_texture_, nullptr, cv_texture.data, cv_texture.step1());
}
