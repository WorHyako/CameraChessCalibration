#pragma once

#include "Video/CameraSettings.hpp"

namespace Wor::CCC::Gui {
	/**
	 * @brief
	 *
	 * @usage
	 *
	 * @author	WorHyako
	 */
	class CameraSettingsWidget final {
	public:
		/**
		 * @brief	Ctor.
		 */
		CameraSettingsWidget();

		/**
		 * @brief
		 */
		auto draw() -> void;

	private:
		bool camera_enabled_;

		std::int32_t camera_index_;

		// Video::CameraSettings camera_settings_;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief
		 *
		 * @param	camera_settings
		 */
		auto init(Video::CameraSettings camera_settings) -> void;

#pragma endregion Accessors/Mutators
	};
}
