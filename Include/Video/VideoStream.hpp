#pragma once

#include <opencv2/videoio.hpp>

namespace Wor::CCC::Video {
	/**
	 * @brief
	 *
	 * @usage
	 *
	 * @author	WorHyako
	 */
	class VideoStream {
	public:
		/**
		 * @brief	Ctor.
		 */
		VideoStream() noexcept;

		/**
		 * @brief	Copy ctor.
		 */
		VideoStream(const VideoStream&) = delete;

		/**
		 * @brief	Move ctor.
		 */
		VideoStream(VideoStream&&) = delete;

		/**
		 * @brief	Dtor.
		 */
		virtual ~VideoStream() noexcept = default;

		/**
		 * @brief
		 */
		[[nodiscard]]
		auto open(int camera_index) noexcept -> bool;

		/**
		 * @brief
		 */
		[[nodiscard]]
		auto open(const std::string_view& file_name) noexcept -> bool;

		/**
		 * @brief
		 */
		auto close() noexcept -> void;

	private:
		/**
		 * @brief
		 */
		cv::VideoCapture capture_;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		auto is_opened() const noexcept -> bool;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		auto frame() noexcept -> cv::Mat;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		auto capture_handle() noexcept -> cv::VideoCapture&;

#pragma endregion Accessors/Mutators
	};
}
