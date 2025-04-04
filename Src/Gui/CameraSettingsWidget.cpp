#include "Gui/CameraSettingsWidget.hpp"

#include <imgui.h>

#include "Video/VideoStream.hpp"

#include <Wor/Wrappers/Singleton.hpp>

using namespace Wor::CCC::Gui;

CameraSettingsWidget::CameraSettingsWidget()
	: camera_enabled_{false},
	  camera_index_{0} {
}

auto CameraSettingsWidget::draw() -> void {
	ImGui::Begin("Camera Settings");

	auto& video_stream{Wrappers::Singleton<Video::VideoStream>::get()};

	ImGui::InputInt("Camera Index", &camera_index_);
	if (ImGui::Checkbox("Enable", &camera_enabled_)) {
		if (camera_enabled_) {
			if (video_stream.open(camera_index_) == false) {
				video_stream.close();
				camera_enabled_ = false;
			}
		} else {
			video_stream.close();
		}
	}

	ImGui::BeginDisabled(camera_enabled_ == false);

	auto& capture_handle = video_stream.capture_handle();

	static std::int32_t fps{0};
	static std::int32_t frame_width{0};
	static std::int32_t frame_height{0};
	static std::int32_t focus{0};
	static bool autofocus{false};

	if (ImGui::Button("Refresh")) {
		fps = static_cast<std::int32_t>(capture_handle.get(cv::CAP_PROP_FPS));
		frame_width = static_cast<std::int32_t>(capture_handle.get(cv::CAP_PROP_FRAME_WIDTH));
		frame_height = static_cast<std::int32_t>(capture_handle.get(cv::CAP_PROP_FRAME_HEIGHT));
		autofocus = static_cast<bool>(capture_handle.get(cv::CAP_PROP_AUTOFOCUS));
		focus = static_cast<std::int32_t>(capture_handle.get(cv::CAP_PROP_FRAME_HEIGHT));
	}

	if (ImGui::InputInt("FPS", &fps)) {
		capture_handle.set(cv::CAP_PROP_FPS, fps);
	}

	if (ImGui::InputInt("Frame width", &frame_width)) {
		capture_handle.set(cv::CAP_PROP_FRAME_WIDTH, frame_width);
	}

	if (ImGui::InputInt("Frame height", &frame_height)) {
		capture_handle.set(cv::CAP_PROP_FRAME_HEIGHT, frame_height);
	}

	if (ImGui::Checkbox("Autofocus", &autofocus)) {
		capture_handle.set(cv::CAP_PROP_AUTOFOCUS, autofocus);
	}

	if (ImGui::InputInt("Focus", &focus)) {
		capture_handle.set(cv::CAP_PROP_FOCUS, autofocus);
	}

	ImGui::EndDisabled();
	ImGui::End();
}

#pragma region Accessors/Mutators

auto CameraSettingsWidget::init(Video::CameraSettings camera_settings) -> void {
	// camera_settings_ = std::move(camera_settings);
}

#pragma endregion Accessors/Mutators
