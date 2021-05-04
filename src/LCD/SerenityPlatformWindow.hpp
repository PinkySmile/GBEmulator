//
// Created by Gegel85 on 04/05/2021
//

#ifndef GBEMULATOR_SERENITYPLATFORMWINDOW_HPP
#define GBEMULATOR_SERENITYPLATFORMWINDOW_HPP


#include <LibGUI/Widget.h>
#include <LibGUI/Window.h>

namespace GBEmulator::Serenity
{
	struct Vector2i {
		int x;
		int y;
	};

	void initSerenityApp();

	//Gotten from the Serenity SDL port
	class SerenitySDLWidget final : public GUI::Widget {
		C_OBJECT(SerenitySDLWidget)
	public:
		explicit SerenitySDLWidget();
		RefPtr<Gfx::Bitmap> m_buffer;

	protected:
		void paint_event(GUI::PaintEvent&) override;
		void resize_event(GUI::ResizeEvent&) override;
		void show_event(GUI::ShowEvent&) override;
		void hide_event(GUI::HideEvent&) override;

		void mousedown_event(GUI::MouseEvent&) override;
		void mousemove_event(GUI::MouseEvent&) override;
		void mouseup_event(GUI::MouseEvent&) override;

		void keydown_event(GUI::KeyEvent& event) override;
		void keyup_event(GUI::KeyEvent& event) override;

		void enter_event(Core::Event&) override;
		void leave_event(Core::Event&) override;
	};

	class SerenityPlatformWindow {
	public:
		SerenityPlatformWindow(Vector2i size) :
			m_window(GUI::Window::construct()),
			m_widget(SerenitySDLWidget::construct())
		{
			m_window->resize(size.x, size.y);
			m_window->set_resizable(false);
		}

		NonnullRefPtr<GUI::Window> window() { return m_window; }
		NonnullRefPtr<SerenitySDLWidget> widget() { return m_widget; }

	private:
		NonnullRefPtr<GUI::Window> m_window;
		NonnullRefPtr<SerenitySDLWidget> m_widget;
	};
}

#endif //GBEMULATOR_SERENITYPLATFORMWINDOW_HPP
