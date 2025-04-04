#include "Video/VideoStream.hpp"

#include <thread>

using namespace Wor::CCC::Video;

VideoStream::VideoStream() noexcept {
}

auto VideoStream::open(int camera_index) noexcept -> bool {
	capture_.open(camera_index, cv::CAP_ANY);
	std::this_thread::sleep_for(std::chrono::milliseconds(5));
	return capture_.isOpened();
}

auto VideoStream::open(const std::string_view& file_name) noexcept -> bool {
	capture_.open(std::string(file_name));
	return capture_.isOpened();
}

auto VideoStream::close() noexcept -> void {
	if (is_opened() == false) {
		return;
	}
	capture_.release();
}

#pragma region Accessors/Mutators

auto VideoStream::is_opened() const noexcept -> bool {
	return capture_.isOpened();
}

auto VideoStream::frame() noexcept -> cv::Mat {
	cv::Mat frame;
	if (is_opened() && capture_.grab()) {
		capture_ >> frame;
	}
	return frame;
}

auto VideoStream::capture_handle() noexcept -> cv::VideoCapture& {
	return capture_;
}

#pragma endregion Accessors/Mutators
