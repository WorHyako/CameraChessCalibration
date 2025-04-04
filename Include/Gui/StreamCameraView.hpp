#pragma once

#include "Gui/CameraViewBase.hpp"

namespace Wor::CCC::Gui {
	/**
	 * @brief
	 *
	 * @usage
	 *
	 * @author	WorHyako
	 */
	class StreamCameraView final
			: private CameraViewBase {
	public:
		/**
		 * @brief	Ctor.
		 *
		 * @param	renderer
		 */
		explicit StreamCameraView(SDL_Renderer* renderer) noexcept;

		/**
		 * @brief	Dtor.
		 */
		~StreamCameraView() noexcept override = default;

		/**
		 * @brief
		 *
		 * @param	cv_texture
		 */
		auto draw(cv::Mat cv_texture) noexcept -> void override;
	};
}
