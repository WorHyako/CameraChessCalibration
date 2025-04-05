#include "Gui/CameraSettingsWidget.hpp"

#include <imgui.h>

#include "Video/VideoStream.hpp"

#include <Wor/Wrappers/Singleton.hpp>

using namespace Wor::CCC::Gui;

CameraSettingsWidget::CameraSettingsWidget()
	: camera_enabled_{false},
	  show_chessboard_pattern_{false},
	  chessboard_position_{Video::ChessboardPattern::Alias::Center},
	  camera_index_{0},
	  corner_num_{8, 6} {
}

auto CameraSettingsWidget::draw() -> void {
	ImGui::Begin("Settings");

	ImGui::BeginTable("Settings", 2);
	ImGui::TableNextRow();
	ImGui::TableSetColumnIndex(0);

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

	auto& capture_handle{video_stream.capture_handle()};

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

	ImGui::TableSetColumnIndex(1);

	ImGui::Checkbox("Show chessboard pattern", &show_chessboard_pattern_);
	ImGui::BeginDisabled((show_chessboard_pattern_ && camera_enabled_) == false);
	ImGui::InputInt2("Corners num", corner_num_.data());

	static int state{0};
	if (ImGui::BeginTable("Chessboard position alias table", 3)) {
		for (int i{0}; i < 9; i++) {
			ImGui::TableNextColumn();
			ImGui::PushID(i);
			if (ImGui::RadioButton("", &state, i)) {
				chessboard_position_ = static_cast<Video::ChessboardPattern::Alias>(i);
			}
			ImGui::PopID();
		}
		ImGui::EndTable();
	}
	ImGui::EndTable();
	ImGui::EndDisabled();

	ImGui::End();
}

#pragma region Accessors/Mutators

auto CameraSettingsWidget::init(Video::CameraSettings camera_settings) -> void {
	// camera_settings_ = std::move(camera_settings);
}

auto CameraSettingsWidget::corner_num() const noexcept -> cv::Size {
	return {corner_num_.at(0), corner_num_.at(1)};
}

auto CameraSettingsWidget::chessboard_position() const noexcept -> Video::ChessboardPattern::Alias {
	return chessboard_position_;
}

auto CameraSettingsWidget::is_show_chessboard_pattern() const noexcept -> bool {
	return show_chessboard_pattern_;
}

#pragma endregion Accessors/Mutators
