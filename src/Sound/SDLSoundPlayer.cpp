//
// Created by andgel on 08/06/2021
//

#include <cassert>
#include <string>
#include <SDL2/SDL.h>
#include "SDLSoundPlayer.hpp"

#ifndef __cpp_exceptions
#define throw abort(), (void)
#endif

#if MONO_SOUND
#define NB_CHANNEL 1
#else
#define NB_CHANNEL 2
#endif

namespace GBEmulator
{
	class Exception : public standard::exception {
	private:
		standard::string _msg;

	public:
		Exception(const standard::string &msg) : _msg(msg) {};
		const char *what() const noexcept override { return this->_msg.c_str(); };
	};

	void SDL_AudioCallback(void *userdata, Uint8 *stream, int len)
	{
		auto object = reinterpret_cast<SDLSoundPlayer *>(userdata);

		while (object->_mutex);
		object->_mutex = true;
		assert(len == object->_buffer.size() * sizeof(*object->_buffer.data()));
		memcpy(stream, object->_buffer.data(), len);
		object->_mutex = false;
	}

	SDLSoundPlayer::SDLSoundPlayer()
	{
		if (SDL_Init(SDL_INIT_AUDIO) == -1)
			throw Exception(standard::string("Can't init SDL audio: ") + SDL_GetError());
		SDL_AudioSpec spec;

		memset(&spec, 0, sizeof(spec));
		spec.freq = SAMPLE_RATE;
		spec.format = AUDIO_S16SYS;
		spec.channels = NB_CHANNEL;
		spec.samples = SAMPLE_BUFFER_SIZE;
		spec.callback = SDL_AudioCallback;
		spec.userdata = this;
		this->_buffer.resize(SAMPLE_BUFFER_SIZE);

		SDL_AudioDeviceID dev = SDL_OpenAudioDevice(nullptr, 0, &spec, &spec, 0);

		assert(spec.freq == SAMPLE_RATE);
		assert(spec.format == AUDIO_S16SYS);
		assert(spec.channels == NB_CHANNEL);
		assert(spec.samples == SAMPLE_BUFFER_SIZE);
		SDL_PauseAudioDevice(dev, SDL_FALSE);
	}

	void SDLSoundPlayer::setVolume(float volume)
	{
		this->_masterVolume = volume;
	}

	void SDLSoundPlayer::pushSamples(int16_t *samples, size_t sampleCount)
	{
		while (this->_mutex);
		this->_mutex = true;
		this->_buffer = std::vector<int16_t>{samples, samples + sampleCount};
		this->_mutex = false;
	}
}