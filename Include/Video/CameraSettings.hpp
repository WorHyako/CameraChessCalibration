#pragma once

#include <opencv2/videoio.hpp>

namespace Wor::CCC::Video {
	/**
	 * @brief
	 *
	 * @author	WorHyako
	 */
	class [[deprecated]] PropertyInfo {
	public:
		/**
		 * @brief
		 *
		 * @author	WorHyako
		 */
		enum class Type
				: std::uint8_t {
			ReadOnly,
			Writable
		};

		/**
		 * @brief	Ctor.
		 *
		 * @param	cv_prop
		 *
		 * @param 	name
		 *
		 * @param 	type
		 *
		 * @param	limits
		 */
		constexpr PropertyInfo(cv::VideoCaptureProperties cv_prop,
							   const std::string_view& name,
							   Type type = Type::ReadOnly,
							   float min = -10'000.f,
							   float max = 10'000.f)
			: cv_prop{cv_prop},
			  type{type},
			  name{name},
			  min{min},
			  max{max} {
		}

		/**
		 * @brief
		 */
		cv::VideoCaptureProperties cv_prop;

		/**
		 * @brief
		 */
		Type type;

		/**
		 * @brief
		 */
		std::string_view name;

		/**
		 * @brief
		 */
		float min;

		float max;
	};

	/**
	 * @brief
	 *
	 * @usage
	 *
	 * @author	WorHyako
	 */
	struct [[deprecated]] PropertyValue {
		/**
		 * @brief	Ctor.
		 */
		PropertyValue() noexcept;

		float current;

		float basic;
	};

	/**
	 * @brief
	 *
	 * @usage
	 *
	 * @author	WorHyako
	 */
	struct [[deprecated]] Property {
		/**
		 * @brief	Ctor.
		 */
		explicit Property(PropertyInfo info) noexcept;

		PropertyInfo info;

		PropertyValue value;
	};

	/**
	 * @brief
	 *
	 * @author	WorHyako
	 */
	class [[deprecated]] CameraSettings final {
	public:
		/**
		 * @brief	Ctor.
		 */
		CameraSettings() noexcept;

		/**
		 * @brief
		 */
		auto refresh() noexcept -> void;

	private:
		std::vector<Property> properties;

	public:
#pragma region Accessors/Mutators

		[[nodiscard]]
		auto begin() noexcept -> decltype(properties.begin()) {
			return properties.begin();
		}

		[[nodiscard]]
		auto cbegin() const noexcept -> decltype(properties.cbegin()) {
			return properties.cbegin();
		}

		[[nodiscard]]
		auto end() noexcept -> decltype(properties.end()) {
			return properties.end();
		}

		[[nodiscard]]
		auto cend() const noexcept -> decltype(properties.cend()) {
			return properties.cend();
		}

		/**
		 * @brief
		 *
		 * @param index
		 *
		 * @return
		 */
		[[nodiscard]]
		auto get(std::uint16_t index) -> Property&;

		/**
		 * @brief
		 *
		 * @param cv_prop
		 *
		 * @return
		 */
		[[nodiscard]]
		auto get(cv::VideoCaptureProperties cv_prop) -> Property&;

		auto accept(cv::VideoCaptureProperties cv_prop) -> void;

#pragma endregion Accessors/Mutators
	};
}
