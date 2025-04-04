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
	class FixedCameraView final
			: private CameraViewBase {
	public:
		/**
		 * @brief	Ctor.
		 */
		explicit FixedCameraView(SDL_Renderer* renderer) noexcept;

		/**
		 * @brief	Dtor.
		 */
		~FixedCameraView() noexcept override = default;

		/**
		 * @brief
		 *
		 * @param	cv_texture
		 */
		auto draw(cv::Mat cv_texture) noexcept -> void override;
	};
}
