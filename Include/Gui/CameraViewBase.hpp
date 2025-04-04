#pragma once

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
	class CameraViewBase {
	public:
		/**
		 * @brief	Ctor.
		 *
		 * @param	renderer
		 */
		explicit CameraViewBase(SDL_Renderer* renderer) noexcept;

		/**
		 * @brief	Dtor.
		 */
		virtual ~CameraViewBase() = default;

		/**
		 * @brief
		 *
		 * @param	cv_texture
		 */
		virtual auto draw(cv::Mat cv_texture) noexcept -> void = 0;

	protected:
		/**
		 * @brief
		 *
		 * @param	cv_texture
		 */
		auto cv_to_sdl(cv::Mat&& cv_texture) noexcept -> void;

	protected:
		/**
		 * @brief
		 */
		SDL_Renderer* renderer_;

		/**
		 * @brief
		 */
		SDL_Texture* sdl_texture_;
	};
}
