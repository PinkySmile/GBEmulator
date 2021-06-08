//
// Created by andgel on 08/06/2021
//

#ifndef GBEMULATOR_SDLSOUNDPLAYER_HPP
#define GBEMULATOR_SDLSOUNDPLAYER_HPP


#include <cstddef>
#include "ISound.hpp"

namespace GBEmulator
{
	class SDLSoundPlayer : public ISound {
	public:
		SDLSoundPlayer();
		void setVolume(float volume) override;
		void pushSamples(int16_t *samples, size_t sampleCount) override;

		std::vector<int16_t> _buffer;
		volatile bool _mutex = false;

	private:
		float _masterVolume;
	};
}


#endif //GBEMULATOR_SDLSOUNDPLAYER_HPP
