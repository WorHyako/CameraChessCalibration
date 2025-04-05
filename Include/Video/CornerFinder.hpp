#pragma once

#include <vector>

#include <opencv2/core/mat.hpp>

namespace Wor::CCC::Video {
	/**
	 * @brief
	 *
	 * @author	WorHyako
	 */
	class ChessboardPattern final {
	public:
		/**
		 * @brief
		 *
		 * @author	WorHyako
		 */
		enum class Alias
				: std::uint8_t {
			TopLeft = 0,
			TopCenter,
			TopRight,
			Left,
			Center,
			Right,
			BottomLeft,
			BottomCenter,
			BottomRight
		};

		/**
		 * @brief	Ctor.
		 *
		 * @param	area_size
		 */
		explicit ChessboardPattern(cv::Size area_size) noexcept;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		auto corresponds_to(const cv::Rect2i& rect, Alias alias) noexcept -> bool;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		auto corresponds_to(cv::Rect2i texture_rect, cv::Point2i point, Alias alias) noexcept -> bool;

	private:
		cv::Point2i area_size_;

#pragma region Accessors/Mutators

	public:
		/**
		 * @brief
		 *
		 * @param alias
		 *
		 * @return
		 */
		[[nodiscard]]
		auto get_chessboard_rect(Alias alias) noexcept -> cv::Rect2i;

#pragma endregion Accessors/Mutators
	};

	/**
	 * @brief
	 *
	 * @usage
	 *
	 * @author	WorHyako
	 */
	class CornerFinder {
	public:
		/**
		 * @brief
		 *
		 * @param	cv_texture
		 *
		 * @return
		 */
		[[nodiscard]]
		static auto find(const cv::Mat& cv_texture, cv::Size) noexcept -> std::vector<cv::Point2f>;
	};
}
