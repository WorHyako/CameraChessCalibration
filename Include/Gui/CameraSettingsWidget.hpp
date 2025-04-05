#pragma once

#include "Video/CornerFinder.hpp"
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

		bool show_chessboard_pattern_;

		Video::ChessboardPattern::Alias chessboard_position_;

		std::int32_t camera_index_;

		std::array<int, 2> corner_num_;

		// Video::CameraSettings camera_settings_;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief
		 *
		 * @param	camera_settings
		 */
		auto init(Video::CameraSettings camera_settings) -> void;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		auto corner_num() const noexcept -> cv::Size;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		auto chessboard_position() const noexcept -> Video::ChessboardPattern::Alias;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		auto is_show_chessboard_pattern() const noexcept -> bool;

#pragma endregion Accessors/Mutators
	};
}
