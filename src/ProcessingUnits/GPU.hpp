/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Gpu.hpp
*/

#ifndef GBEMULATOR_GPU_HPP
#define GBEMULATOR_GPU_HPP

#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include "../Memory/Memory.hpp"
#include "../LCD/ILCD.hpp"

#define TILE_DATA_SIZE 0x1800
#define NB_TILES TILE_DATA_SIZE * 4
#define BG_MAP_SIZE 0x800
#define OAM_SIZE 0xA0
#define GPU_FULL_CYCLE_DURATION 69905
#define VBLANK_CYCLE_PT 66093
#define HBLANK_CYLCE_PT

namespace GBEmulator
{
	namespace Debugger {
		class Debugger;
	}

	/*!@class GPU
	 * @brief Classe représentant le GPU.
	 * Cette classe gère l'écriture/lecture de la VRAM et de l'OAM.
	 */
	class GPU {
	private:
		bool _triggeredStatInterrupt = false;
		bool _triggeredVBlankInterrupt = false;
		Memory::Memory _oam;
		Graphics::ILCD &_screen;

		//! Palettes default value
		std::vector<Graphics::RGBColor> _bgPalette{
			Graphics::RGBColor::White,
			Graphics::RGBColor::LGray,
			Graphics::RGBColor::DGray,
			Graphics::RGBColor::Black
		};
		std::vector<Graphics::RGBColor> _objectPalette0{
			Graphics::RGBColor::White,
			Graphics::RGBColor::LGray,
			Graphics::RGBColor::DGray,
			Graphics::RGBColor::Black
		};
		std::vector<Graphics::RGBColor> _objectPalette1{
			Graphics::RGBColor::White,
			Graphics::RGBColor::LGray,
			Graphics::RGBColor::DGray,
			Graphics::RGBColor::Black
		};

		//! I/O ports
		unsigned char _stat = 0;
		unsigned char _lyc = 0;
		unsigned char _control = 0;
		unsigned char _scrollX = 0;
		unsigned char _scrollY = 0;
		signed short _windowX = 0;
		unsigned char _windowY = 0;
		unsigned char _bgPaletteValue = 0b00011011;
		unsigned char _objectPalette0Value = 0b00011011;
		unsigned char _objectPalette1Value = 0b00011011;

		unsigned char *_tiles = nullptr;
		unsigned char *_spritesMap = nullptr;
		unsigned char *_backgroundMap = nullptr;

		unsigned _cycles = 0;
		std::vector<unsigned> _tilesToUpdate;

		/*! @struct Sprite
		 *  @brief struct représentant un sprite dans l'OAM.
		 */
		struct Sprite {
			unsigned char x;
			unsigned char y;
			unsigned char texture_id;
			union {
				struct {
					unsigned char cgb_palette_number:3;
					bool tile_bank:1;
					bool palette_number:1;
					bool x_flip:1;
					bool y_flip:1;
					bool priority:1;
				};
				unsigned char flags;
			};
		};

		/*!
		 * @brief Dessine un pixel à la position x, y
		 * @param x: position du pixel sur l'axe des abscisses.
		 * @param y: position du pixel sur l'axe des ordonnées.
		 */
		void _drawPixel(unsigned x, unsigned y);
		/*!
		 * @brief Obtient le pixel à une position x, y d'un sprite.
		 * @param sprite: sprite dont on veut obtenir le pixel.
		 * @param x: position du pixel sur l'axe des abscisses.
		 * @param y: position du pixel sur l'axe des ordonnées.
		 * @return le pixel
		 */
		unsigned char _getSpritePixel(const Sprite &sprite, unsigned int x, unsigned int y);
		/*!
		 * @brief Obtient le pixel à la position x, y d'une tile map.
		 * @param tile: la tile map
		 * @param x: position du pixel sur l'axe des abscisses.
		 * @param y: position du pixel sur l'axe des ordonnées.
		 * @return le pixel
		 */
		unsigned char _getPixelAt(const unsigned char *tile, unsigned int x, unsigned int y);
		/*!
		 * @brief Obtient le pixel à la position x, y d'une tile map.
		 * @param tile: la tile map
		 * @param x: position du pixel sur l'axe des abscisses.
		 * @param y: position du pixel sur l'axe des ordonnées.
		 * @param signedMode: mode signé
		 * @return le pixel
		 */
		unsigned char _getPixelAt(const unsigned char *tiles, unsigned int x, unsigned int y, bool signedMode);

	public:
		/*!
		 * @param brief Constructeur
		 * @param screen: technologie d'affichage.
		 */
		GPU(Graphics::ILCD &screen);
		/*!
		 * @brief Destructeur
		 */
		~GPU();
		GPU() = delete;
		GPU(const GPU &) = delete;
		GPU &operator=(const GPU &) = delete;

		static const std::vector<Graphics::RGBColor> defaultColors;

		/*!
		 * @brief Obtient le mode actuel
		 * le mode peut être H-Blank, V-Blank, Searching OAM-RAM ou Transfering Data to LCD Driver.
		 * @return 0 pendant H-Blank, 1 pendant V-Blank, 2 pendant Searching OAM-RAM ou 3 pendant Transfering Data to LCD Driver.
		 */
		unsigned char getMode() const;
		/*!
		 * @brief Obtient la ligne d'écriture de pixel sur le LCD.
		 * @return le numero de la ligne (0-153)
		 */
		unsigned char getCurrentLine() const;
		/*!
		 * @brief Lit la VRAM
		 * @param address: position du byte lu.
		 * @return la valeur du byte lu.
		 */
		unsigned char readVRAM(unsigned short address) const;
		/*!
		 * @brief Lit l'OAM
		 * @param address: position du byte lu.
		 * @return la valeur du byte lu.
		 */
		unsigned char readOAM(unsigned short address) const;
		/*!
		 * @brief Obtient le LCD Control Register (FF40)
		 * @return la valeur byte
		 */
		unsigned char getControlByte() const;
		/*!
		 * @brief Obtient la LCD Monochrome Palettes (FF47)
		 * @return la valeur byte
		 */
		unsigned char getBGPalette() const;
		/*!
		 * @brief Obtient le Scroll X (FF43)
		 * @return la valeur byte
		 */
		unsigned char getXScroll() const;
		/*!
		 * @brief Obtient le Scroll Y (FF42)
		 * @return la valeur byte
		 */
		unsigned char getYScroll() const;
		/*!
		 * @brief Obtient le STAT - LCD Status (FF41)
		 * @return la valeur du byte
		 */
		unsigned char getStatByte() const;
		/*!
		 * @brief Obtient LYC - LY Compare (FF45)
		 * @return la valeur du byte
		 */
		unsigned char getLycByte() const;
		/*!
		 * @brief Obtient Window X Position (FF4B)
		 * @return la valeur du byte moins 7
		 */
		unsigned char getWindowX() const;
		/*!
		 * @brief Obtient Window Y Position (FF4A)
		 * @return la valeur du byte
		 */
		unsigned char getWindowY() const;
		/*!
		 * @brief Obtient Object Palette 0 Data (FF48)
		 * @return la valeur du byte
		 */
		unsigned char getObjectPalette0() const;
		/*!
		 * @brief Obtient Object Palette 1 Data (FF49)
		 * @return la valeur du byte
		 */
		unsigned char getObjectPalette1() const;

		/*!
		 * @brief Met à jour l'OAM.
		 */
		void updateOAM();
		/*!
		 * @brief Ecrit sur la VRAM
		 * @param address: position du byte à écrire.
		 * @param value: valeur à écrire.
		 */
		void writeVRAM(unsigned short address, unsigned char value);
		/*!
		 * @brief Ecrit sur l'OAM
		 * @param address: position du byte à écrire?
		 * @param value: valeur à écrire.
		 */
		void writeOAM(unsigned short address, unsigned char value);
		/*!
		 * @brief Ecrit le byte LCD Monochrome Palettes (FF47)
		 * @param value: la valeur à écrire.
		 */
		void setControlByte(unsigned char value);
		/*!
		 * @brief Ecrit le byte LCD Status (FF41)
		 * @param value: la valeur à écrire.
		 */
		void setStatByte(unsigned char value);
		/*!
		 * @brief Ecrit le byte  BG Palette Data (FF47)
		 * @param value: la valeur à écrire.
		 */
		void setBGPalette(unsigned char value);
		/*!
		 * @brief Ecrit le byte Scroll X (FF43)
		 * @param value: la valeur à écrire.
		 */
		void setXScroll(unsigned char value);
		/*!
		 * @brief Ecrit le byte Scroll Y (FF42)
		 * @param value: la valeur à écrire.
		 */
		void setYScroll(unsigned char value);
		/*!
		 * @brief Ecrit le byte LY Compare (FF45)
		 * @param value: la valeur à écrire.
		 */
		void setLycByte(unsigned char value);
		/*!
		 * @brief Ecrit le byte Window X Position (FF4B)
		 * @param value: la valeur à écrire.
		 */
		void setWindowX(unsigned char value);
		/*!
		 * @brief Ecrit le byte Window Y Position (FF4A)
		 * @param value: la valeur à écrire.
		 */
		void setWindowY(unsigned char value);
		/*!
		 * @brief Ecrit le byte Object Palette 0 Data (FF48)
		 * @param value: la valeur à écrire.
		 */
		void setObjectPalette0(unsigned char value);
		/*!
		 * @brief Ecrit le byte Object Palette 1 Data (FF49)
		 * @param value: la valeur à écrire.
		 */
		void setObjectPalette1(unsigned char value);

		/*!
		 * @brief Met à jour le GPU
		 * Met à jour le GPU 'cycle' nombre de fois.
		 * @param cycle: cycle GPU à un instant T.
		 * @return 0 ou un interrupt.
		 */
		unsigned char update(int cycle);
		/*!
		 * @brief Met à jour le GPU
		 */
		void update();

	private:
		friend Debugger::Debugger;
		/*!
		 * @brief Obtient une tile par son id
		 * @param id: nombre identifiant la tile.
		 * @return la tile
		 */
		unsigned char *_getTile(std::size_t id);
		/*!
		 * Obtient une tile map
		 * @param alt: mode signé
		 * @return la tile map
		 */
		unsigned char *_getTileMap(bool alt);

		//Interrupts
		/*!
		 * @brief Si VBLANK interrupt
		 * @return true si interrupt.
		 */
		bool _isVBlankInterrupt();
		/*!
		 * @brief Si Stat interrupt
		 * @return true si interrupt.
		 */
		bool _isStatInterrupt();
	};
}


#endif //GBEMULATOR_GPU_HPP
