#pragma once

#include <vector>

#include <opencv2/opencv.hpp>

namespace Wor::CCC::Video {
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
		static auto find(const cv::Mat& cv_texture) noexcept -> std::vector<cv::Point2f>;
	};
}
