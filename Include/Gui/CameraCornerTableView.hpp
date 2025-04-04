#pragma once

#include <vector>

namespace cv {
	class Mat;
}

class SDL_Renderer;
class SDL_Texture;

namespace Wor::CCC::Gui {
	/**
	 * @brief
	 *
	 * @usage
	 *
	 * @author	WorHyako
	 */
	class CameraCornerTableView final {
	public:
		/**
		 * @brief	Ctor.
		 *
		 * @param	renderer
		 */
		explicit CameraCornerTableView(SDL_Renderer* renderer) noexcept;

		/**
		 * @brief
		 */
		auto draw() noexcept -> void;

		/**
		 * @brief
		 *
		 * @param	cv_texture
		 */
		auto push_texture(const cv::Mat& cv_texture) noexcept -> void;

	private:
		/**
		 * @brief
		 */
		std::vector<SDL_Texture*> sdl_textures_;

		/**
		 * @brief
		 */
		SDL_Renderer* renderer_;
	};
}
