#pragma once

#include <memory>
#include <functional>

#include "imgui.h"

class SDL_Window;
class SDL_Renderer;

namespace Wor::CCC::Gui {
	/**
	 * @brief
	 *
	 * @usage
	 *
	 * @author	WorHyako
	 */
	class MainWindow final {
	public:
		/**
		 * @brief
		 */
		using SDLWindowPtr = std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>>;

		/**
		 * @brief
		 */
		using SDLRendererPtr = std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>>;

		/**
		 * @brief
		 */
		using Ptr = std::unique_ptr<MainWindow>;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		static auto create() noexcept -> Ptr;

		/**
		 * @brief
		 */
		auto destroy() noexcept -> void;

		/**
		 * @brief
		 */
		auto show() noexcept -> void;

		/**
		 * @brief	Ctor.
		 */
		MainWindow() noexcept = default;

		/**
		 * @brief	Dtor.
		 */
		~MainWindow() noexcept;

		/**
		 * @brief
		 */
		auto new_frame() const noexcept -> void;

		/**
		 * @brief
		 */
		auto render() const noexcept -> void;

	private:
		/**
		 * @brief
		 */
		SDLWindowPtr window_;

		/**
		 * @brief
		 */
		SDLRendererPtr renderer_;

	public:
#pragma region Accessors/Mutators

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		auto window_handle() const noexcept -> SDL_Window*;

		/**
		 * @brief
		 *
		 * @return
		 */
		[[nodiscard]]
		auto renderer_handle() const noexcept -> SDL_Renderer*;

		[[nodiscard]]
		auto size() const noexcept -> ImVec2;

#pragma endregion Accessors/Mutators
	};
}
