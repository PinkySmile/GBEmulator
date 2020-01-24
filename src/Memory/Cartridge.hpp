/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Cartridge.hpp
*/

#ifndef GBEMULATOR_CARTRIDGE_HPP
#define GBEMULATOR_CARTRIDGE_HPP


#include <map>
#include "ROM.hpp"

//! La taille d'une bank de ROM
#define ROM_BANK_SIZE 0x4000

//! La taille d'une bank de RAM
#define RAM_BANKING_SIZE 0x2000

namespace GBEmulator::Memory
{
	//! Répresente une cartouche de GameBoy.
	class Cartridge {
	private:
		//! @brief La ROM donnée est invalide.
		class InvalidRomException : public std::exception {
		private:
			std::string _msg;

		public:
			InvalidRomException(const std::string &msg) : _msg(msg) {};
			const char *what() const noexcept override { return this->_msg.c_str(); };
		};

		//! @brief La taille de la rom renseigné n'est pas valide.
		class InvalidRomSizeException : public InvalidRomException {
		public:
			InvalidRomSizeException(const std::string &msg) : InvalidRomException(msg) {};
		};

		//! @brief La taille de la ram renseigné n'est pas valide.
		class InvalidRomRamSizeException : public InvalidRomException {
		public:
			InvalidRomRamSizeException(const std::string &msg) : InvalidRomException(msg) {};
		};

		//! @brief La sauvegarde a échoué.
		class SavingFailedException : public InvalidRomException {
		public:
			SavingFailedException(const std::string &msg) : InvalidRomException(msg) {};
		};

		//! @brief Types de cartouches.
		enum CartridgeType {
			ROM_ONLY                = 0x00,
			MBC1                    = 0x01,
			MBC1_RAM                = 0x02,
			MBC1_RAM_BATTERY        = 0x03,
			MBC2                    = 0x05,
			MBC2_BATTERY            = 0x06,
			ROM_RAM                 = 0x08,
			ROM_RAM_BATTERY         = 0x09,
			MMM01                   = 0x0B,
			MMM01_RAM               = 0x0C,
			MMM01_RAM_BATTERY       = 0x0D,
			MBC3_TIMER_BATTERY      = 0x0F,
			MBC3_TIMER_RAM_BATTERY  = 0x10,
			MBC3                    = 0x11,
			MBC3_RAM                = 0x12,
			MBC3_RAM_BATTERY        = 0x13,
			MBC5                    = 0x19,
			MBC5_RAM                = 0x1A,
			MBC5_RAM_BATTERY        = 0x1B,
			MBC5_RUMBLE             = 0x1C,
			MBC5_RUMBLE_RAM         = 0x1D,
			MBC5_RUMBLE_RAM_BATTERY = 0x1E,
			POCKET_CAMERA           = 0xFC,
			BANDAI_TAMA5            = 0xFD,
			HuC3                    = 0xFE,
			HuC1_RAM_BATTERY        = 0xFF,
		};

		//! @brief Taille de ROM.
		enum ROMSize
		{
			SIZE_32KByte  = 0x00,
			SIZE_64KByte  = 0x01,
			SIZE_128KByte = 0x02,
			SIZE_256KByte = 0x03,
			SIZE_512KByte = 0x04,
			SIZE_1MByte   = 0x05,
			SIZE_2MByte   = 0x06,
			SIZE_4MByte   = 0x07,
			SIZE_1_1MByte = 0x52,
			SIZE_1_2MByte = 0x53,
			SIZE_1_5MByte = 0x54,
		};

		//! @brief Lie une taille de fichier à son byte de taille en ROM.
		//! http://problemkaputt.de/pandocs.htm#thecartridgeheader
		static const std::map<size_t, ROMSize> _sizeBytes;

		//! @brief Le fichier de ROM chargé.
		ROM _rom;
		//! @brief La mémoire RAM de la cartouche.
		unsigned char *_ramMem = nullptr;
		//! @brief Le chemin de sauvegarde.
		std::string _savePath;
		//! @brief Est-ce que la RAM de la cartouche est activée.
		bool _ramEnabled = false;
		//! @brief Est-ce que la RAM est en mode étendue.
		bool _ramExtended = false;
		//! @brief La bank de ROM séléctionnée.
		unsigned short _romBank = 1;
		//! @brief La RAM de la cartouche.
		Memory _ram{0, RAM_BANKING_SIZE};
		//! @brief La type actuel de la cartouche.
		CartridgeType _type = ROM_ONLY;

		//! @brief Vérifie si la ROM est valide.
		//! @throw InvalidRomException
		void _checkROM();
		//! @brief Trouve la taille valide d'une cartouche de GameBoy la
		//! plus proche et plus grande de la taille du fichier.
		//! @param path Le chemin d'accès au fichier.
		//! @return La taille trouvée.
		static size_t _getBestSizeForFile(const std::string &path);

		//! @brief Appelée pour écrire si la cartouche est de type HuC.
		//! @param address Adresse d'écriture.
		//! @param value Valeur écrite.
		void _handleHuCWrite(unsigned short address, unsigned char value);
		//! @brief Appelée pour écrire si la cartouche est de type MBC1.
		//! @param address Adresse d'écriture.
		//! @param value Valeur écrite.
		void _handleMBC1Write(unsigned short address, unsigned char value);
		//! @brief Appelée pour écrire si la cartouche est de type MBC2.
		//! @param address Adresse d'écriture.
		//! @param value Valeur écrite.
		void _handleMBC2Write(unsigned short address, unsigned char value);
		//! @brief Appelée pour écrire si la cartouche est de type MBC3.
		//! @param address Adresse d'écriture.
		//! @param value Valeur écrite.
		void _handleMBC3Write(unsigned short address, unsigned char value);
		//! @brief Appelée pour écrire si la cartouche est de type MBC5.
		//! @param address Adresse d'écriture.
		//! @param value Valeur écrite.
		void _handleMBC5Write(unsigned short address, unsigned char value);
		//! @brief Appelée pour écrire si la cartouche est de type rumble.
		//! @param address Adresse d'écriture.
		//! @param value Valeur écrite.
		void _handleRumbleWrite(unsigned short address, unsigned char value);

	public:
		//! @brief Réinitialise la ROM présente.
		void resetROM();
		//! @brief Charge une ROM.
		//! @param rom Chemin d'accès vers le fichier de ROM.
		void loadROM(const std::string &rom);
		//! @brief Sauvegarde la RAM dans un fichier.
		void saveRAM();
		//! Écrit la valeur à l'adresse donnée dand la cartouche
		//! @param address Adresse à laquelle écrire.
		//! @param value La valeur à écrire.
		void write(unsigned short address, unsigned char value);
		//! Lis la valeur à l'adresse donnée dand la cartouche
		//! @param address Adresse à lire.
		//! @return Valeur lue.
		unsigned char read(unsigned short address) const;
		//! Récupère le numéro de la Banque de ROM en cours d'utilisation
		//! @return Le numéro de la Banque de ROM en cours d'utilisation.
		unsigned char getRomBank() const;
		//! Récupère le numéro de la Banque de RAM en cours d'utilisation
		//! @return Le numéro de la Banque de RAM en cours d'utilisation.
		unsigned char getRamBank() const;
	};
}


#endif //GBEMULATOR_CARTRIDGE_HPP
