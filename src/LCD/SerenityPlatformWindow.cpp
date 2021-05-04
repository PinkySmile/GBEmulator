//
// Created by Gegel85 on 04/05/2021
//

#include <LibGUI/Painter.h>
#include <LibGUI/Application.h>
#include "SerenityPlatformWindow.hpp"

namespace GBEmulator::Serenity
{
	static RefPtr<GUI::Application> g_app;

	void initSerenityApp()
	{
		VERIFY(!g_app);
		g_app = GUI::Application::construct(0, nullptr);
	}

	SerenitySDLWidget::SerenitySDLWidget()
	{
		update();
	}

	void SerenitySDLWidget::paint_event(GUI::PaintEvent& event)
	{
		VERIFY(size() == m_buffer->size());
		if (size() != m_buffer->size()) {
			return; // can't paint this
		}
		GUI::Painter painter(*this);
		painter.add_clip_rect(event.rect());
		painter.blit(event.rect().location(), *m_buffer, event.rect());
	}
	void SerenitySDLWidget::resize_event(GUI::ResizeEvent&)
	{
		//TODO: Set viewport in here
		//SDL_SendWindowEvent(m_sdl_window, SDL_WINDOWEVENT_RESIZED, width(), height());
	}

	void SerenitySDLWidget::show_event(GUI::ShowEvent&)
	{
		//SDL_SendWindowEvent(m_sdl_window, SDL_WINDOWEVENT_SHOWN, 0, 0);
	}
	void SerenitySDLWidget::hide_event(GUI::HideEvent&)
	{
		//SDL_SendWindowEvent(m_sdl_window, SDL_WINDOWEVENT_HIDDEN, 0, 0);
	}

	static int map_button(GUI::MouseButton button)
	{
		//switch (button) {
		//	case GUI::MouseButton::None:
		//			VERIFY(false);
		//		break;
		//	case GUI::MouseButton::Left:
		//		return SDL_BUTTON_LEFT;
		//	case GUI::MouseButton::Middle:
		//		return SDL_BUTTON_MIDDLE;
		//	case GUI::MouseButton::Right:
		//		return SDL_BUTTON_RIGHT;
		//}

		//VERIFY_NOT_REACHED();
		return 0;
	}

	void SerenitySDLWidget::mousedown_event(GUI::MouseEvent& event)
	{
		//SDL_SendMouseMotion(m_sdl_window, 0, 0, event.x(), event.y());
		//SDL_SendMouseButton(m_sdl_window, 0, SDL_PRESSED, map_button(event.button()));
	}

	void SerenitySDLWidget::mousemove_event(GUI::MouseEvent& event)
	{
		//SDL_SendMouseMotion(m_sdl_window, 0, 0, event.x(), event.y());
	}

	void SerenitySDLWidget::mouseup_event(GUI::MouseEvent& event)
	{
		//SDL_SendMouseMotion(m_sdl_window, 0, 0, event.x(), event.y());
		//SDL_SendMouseButton(m_sdl_window, 0, SDL_RELEASED, map_button(event.button()));
	}

	void SerenitySDLWidget::keydown_event(GUI::KeyEvent& event)
	{
		//TODO: Feed this event to the JoypadEmulator
		//SDL_SendKeyboardKey(SDL_PRESSED, scancode_map[event.key()]);
		//auto text = event.text();
		//if (!text.is_empty())
		//	SDL_SendKeyboardText(text.characters());
	}

	void SerenitySDLWidget::keyup_event(GUI::KeyEvent& event)
	{
		//TODO: Feed this event to the JoypadEmulator
		//SDL_SendKeyboardKey(SDL_RELEASED, scancode_map[event.key()]);
	}

	void SerenitySDLWidget::enter_event(Core::Event&)
	{
		//SDL_SetMouseFocus(m_sdl_window);
	}

	void SerenitySDLWidget::leave_event(Core::Event&)
	{
		//SDL_SetMouseFocus(nullptr);
	}

}