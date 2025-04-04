#include "Video/CameraSettings.hpp"

#include "Wor/Wrappers/Singleton.hpp"

#include "Video/VideoStream.hpp"

using namespace Wor::CCC::Video;
using namespace std::string_view_literals;

using CvProp = cv::VideoCaptureProperties;

namespace {
	/**
	 * @brief
	 *
	 * @author WorHyako
	 */
	constexpr std::array infos{
				PropertyInfo(CvProp::CAP_PROP_FPS, "Fps", PropertyInfo::Type::Writable, 0.0f, 240.0f),
				PropertyInfo(CvProp::CAP_PROP_BITRATE, "Bitrate", PropertyInfo::Type::ReadOnly),
				PropertyInfo(CvProp::CAP_PROP_FRAME_WIDTH, "Frame width", PropertyInfo::Type::Writable, 0, 4.0e+3),
				PropertyInfo(CvProp::CAP_PROP_FRAME_HEIGHT, "Frame height", PropertyInfo::Type::Writable, 0, 4.0e+3),
				PropertyInfo(CvProp::CAP_PROP_BRIGHTNESS, "Brightness"),
				PropertyInfo(CvProp::CAP_PROP_CONTRAST, "Contrast"),
				PropertyInfo(CvProp::CAP_PROP_SATURATION, "Saturation"),
				PropertyInfo(CvProp::CAP_PROP_HUE, "Hue"),
				PropertyInfo(CvProp::CAP_PROP_GAIN, "Gain"),
				PropertyInfo(CvProp::CAP_PROP_EXPOSURE, "Exposure"),
				PropertyInfo(CvProp::CAP_PROP_ZOOM, "Zoom"),
			};
}

PropertyValue::PropertyValue() noexcept
	: current{0.0f},
	  basic{0.0f} {
}

Property::Property(PropertyInfo info) noexcept
	: info{std::move(info)} {
}

CameraSettings::CameraSettings() noexcept {
}

auto CameraSettings::refresh() noexcept -> void {
	properties.clear();
	auto& capture{Wrappers::Singleton<VideoStream>::get().capture_handle()};
	if (capture.isOpened() == false) {
		return;
	}
	properties.reserve(std::size(infos));
	std::ranges::for_each(infos,
						  [properties{&properties}, &capture](const auto& info) {
							  Property prop{info};
							  auto cv_prop{static_cast<float>(capture.get(info.cv_prop))};
							  prop.value.basic = cv_prop;
							  prop.value.current = cv_prop;
							  properties->emplace_back(std::move(prop));
						  });
}

auto CameraSettings::accept(cv::VideoCaptureProperties cv_prop) -> void {
	auto& capture{Wrappers::Singleton<VideoStream>::get().capture_handle()};
	auto res{capture.set(cv_prop, get(cv_prop).value.current)};
	std::printf("Changing result - %s\n", res ? "true" : "false");
}

#pragma region Accessors/Mutators

auto CameraSettings::get(std::uint16_t index) -> Property& {
	return properties.at(index);
}

auto CameraSettings::get(cv::VideoCaptureProperties cv_prop) -> Property& {
	const auto result{
				std::ranges::find_if(properties,
									 [cv_prop](const Property& prop) {
										 return prop.info.cv_prop == cv_prop;
									 })
			};
	return get(std::distance(std::begin(properties), result));
}

#pragma endregion Accessors/Mutators
