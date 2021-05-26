//
// Created by andgel on 03/05/2021
//

#include "LCDSerenityLibGui.hpp"
#include "SerenityPlatformWindow.hpp"
#include <LibCore/EventLoop.h>

static bool drawMutex = false;

void lockMutex(bool &mutex) { while (mutex); mutex = true; }
void unlockMutex(bool &mutex) { mutex = false; }

GBEmulator::Graphics::LCDSerenityLibGui::LCDSerenityLibGui(Serenity::Vector2i size, const standard::string &title) :
	_innerWindow(new Serenity::SerenityPlatformWindow(size)),
	_size{160, 144},
	_winSize(size),
	_screen(new Gfx::Color[this->_size.x * this->_size.y]),
	_framebuffer(new Gfx::Color[size.x * size.y]),
	_title(title)
{
	this->_innerWindow->window()->set_double_buffering_enabled(false);
	this->_innerWindow->widget()->set_fill_with_background_color(false);
	this->_innerWindow->window()->set_main_widget(this->_innerWindow->widget());
	this->_innerWindow->window()->on_close_request = [this] {
		this->close();
		return GUI::Window::CloseRequestDecision::Close;
	};
	this->_innerWindow->widget()->m_buffer = Gfx::Bitmap::create(
		Gfx::BitmapFormat::BGRx8888,
		Gfx::IntSize(this->_innerWindow->window()->width(), this->_innerWindow->window()->height())
	);
	this->_innerWindow->window()->show();
	auto& loop = Core::EventLoop::current();
	if (loop.was_exit_requested()) {
		this->close();
		return;
	}
	loop.pump(Core::EventLoop::WaitMode::PollForEvents);
}

GBEmulator::Graphics::LCDSerenityLibGui::~LCDSerenityLibGui()
{
	delete this->_innerWindow;
	delete[] this->_screen;
	delete[] this->_framebuffer;
}

void GBEmulator::Graphics::LCDSerenityLibGui::display()
{
	lockMutex(drawMutex);
	this->_lastFrameTime = this->_emulatorSpeed.getElapsedTime().asSeconds();

	auto buffer = this->_innerWindow->widget()->m_buffer.ptr();

	VERIFY(buffer);
	VERIFY(buffer->scanline(0));
	auto width  = this->_innerWindow->widget()->m_buffer->physical_width();
	auto height = this->_innerWindow->widget()->m_buffer->physical_height();

	for (auto x = 0; x < width; x++)
		for (auto y = 0; y < height; y++) {
			int realX = x * this->_size.x / width;
			int realY = y * this->_size.y / height;

			VERIFY(realX <= this->_size.x);
			VERIFY(realY <= this->_size.y);
			buffer->set_pixel(x, y, this->_screen[realX + realY * this->_size.x]);
		}
	this->_emulatorSpeed.restart();
	unlockMutex(drawMutex);
}

void GBEmulator::Graphics::LCDSerenityLibGui::clear()
{
	for (int i = 0; i < this->_size.x * this->_size.y; i++)
		this->_screen[i] = {
			RGBColor::White.r,
			RGBColor::White.g,
			RGBColor::White.b,
		};
}

void GBEmulator::Graphics::LCDSerenityLibGui::setMaxSize(unsigned int x, unsigned int y)
{
	this->_size.x = x;
	this->_size.y = y;
	delete[] this->_screen;
	this->_screen = new Gfx::Color[this->_size.x * this->_size.y];
}

void GBEmulator::Graphics::LCDSerenityLibGui::setPixel(unsigned int x, unsigned int y, const GBEmulator::Graphics::RGBColor &color)
{
	this->_screen[x + y * this->_size.x] = Gfx::Color{
		color.r,
		color.g,
		color.b,
	};
}

bool GBEmulator::Graphics::LCDSerenityLibGui::isClosed() const
{
	return this->_closed;
}

void GBEmulator::Graphics::LCDSerenityLibGui::close()
{
	this->_closed = true;
	this->_innerWindow->window()->close();
}

void GBEmulator::Graphics::LCDSerenityLibGui::render()
{
	auto& loop = Core::EventLoop::current();
	if (loop.was_exit_requested()) {
		this->close();
		return;
	}
	loop.pump(Core::EventLoop::WaitMode::PollForEvents);

	if (this->_clock.getElapsedTime().asMilliseconds() > 500) {
		this->_innerWindow->window()->set_title((this->_title + " " + standard::to_string(static_cast<int>(100 / this->_lastFrameTime / 60)) + "% (" + standard::to_string(static_cast<int>(this->getFramerate())) + " FPS)").c_str());
		this->_clock.restart();
	}
	lockMutex(drawMutex);
	this->_innerWindow->widget()->update();
	unlockMutex(drawMutex);

	uint64_t t = this->_fpsClock.restart().asMicroSeconds();

	if (t < (1000000 / 60)) {
		uint64_t usecs = (1000000 / 60) - t;
		timespec ti;

		ti.tv_nsec = (usecs % 1000000) * 1000;
		ti.tv_sec = usecs / 1000000;
		while ((nanosleep(&ti, &ti) == -1) && (errno == EINTR));
	}
}

double GBEmulator::Graphics::LCDSerenityLibGui::getFramerate()
{
	return 1 / this->_fpsClock.getElapsedTime().asSeconds();
}
