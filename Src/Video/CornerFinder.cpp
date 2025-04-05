#include "Video/CornerFinder.hpp"

#include <opencv2/opencv.hpp>

using namespace Wor::CCC::Video;

namespace {
	/**
	 * @brief
	 */
	constexpr float correspond_delta{0.01f};
}

ChessboardPattern::ChessboardPattern(cv::Size area_size) noexcept
	: area_size_{area_size} {
}

auto ChessboardPattern::corresponds_to(const cv::Rect& rect, Alias alias) noexcept -> bool {
	const auto chessboard{get_chessboard_rect(alias)};
	const auto tl_res{
				std::abs<float>(rect.tl().x - chessboard.tl().x) < area_size_.x * correspond_delta
				&& std::abs<float>(rect.tl().y - chessboard.tl().y) < area_size_.y * correspond_delta
			};
	const auto br_res{
				std::abs<float>(rect.br().x - chessboard.br().x) < area_size_.x * correspond_delta
				&& std::abs<float>(rect.br().y - chessboard.br().y) < area_size_.y * correspond_delta
			};
	return tl_res && br_res;
}

auto ChessboardPattern::get_chessboard_rect(Alias alias) noexcept -> cv::Rect2i {
	cv::Rect2i chessboard;
	chessboard.width = area_size_.x / 2;
	chessboard.height = area_size_.y / 2;

	switch (alias) {
		case Alias::TopLeft:
		case Alias::TopCenter:
		case Alias::TopRight:
			chessboard.y = 0;
			break;
		case Alias::Left:
		case Alias::Center:
		case Alias::Right:
			chessboard.y = area_size_.y / 4;
			break;
		case Alias::BottomLeft:
		case Alias::BottomCenter:
		case Alias::BottomRight:
			chessboard.y = area_size_.y / 2;
			break;
		default:
			chessboard.y = area_size_.y;
			break;
	}
	switch (alias) {
		case Alias::TopLeft:
		case Alias::Left:
		case Alias::BottomLeft:
			chessboard.x = 0;
			break;
		case Alias::TopCenter:
		case Alias::Center:
		case Alias::BottomCenter:
			chessboard.x = area_size_.x / 4;
			break;
		case Alias::TopRight:
		case Alias::Right:
		case Alias::BottomRight:
			chessboard.x = area_size_.x / 2;
			break;
		default:
			chessboard.x = area_size_.x;
			break;
	}
	return chessboard;
}

auto CornerFinder::find(const cv::Mat& cv_texture, cv::Size corner_num) noexcept -> std::vector<cv::Point2f> {
	if (cv_texture.empty()) {
		return {};
	}

	std::vector<cv::Point2f> corners;
	cv::Mat gray_cv_texture{};
	cv::cvtColor(cv_texture, gray_cv_texture, cv::COLOR_BGR2GRAY);
	bool chessboard_result{cv::findChessboardCorners(gray_cv_texture, corner_num, corners, cv::CALIB_CB_FAST_CHECK)};

	return chessboard_result
			   ? corners
			   : std::vector<cv::Point2f>();
}
