#include "Video/CornerFinder.hpp"

using namespace Wor::CCC::Video;

auto CornerFinder::find(const cv::Mat& cv_texture) noexcept -> std::vector<cv::Point2f> {
	if (cv_texture.empty()) {
		return {};
	}

	std::vector<cv::Point2f> corners;
	cv::Mat gray_cv_texture{};
	cv::cvtColor(cv_texture, gray_cv_texture, cv::COLOR_BGR2GRAY);
	bool chessboard_result{cv::findChessboardCorners(gray_cv_texture, cv::Size(8, 6), corners)};

	return chessboard_result
			   ? corners
			   : std::vector<cv::Point2f>();
}
