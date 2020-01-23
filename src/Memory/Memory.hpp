/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Memory.hpp
*/

#ifndef GBEMULATOR_MEMORY_HPP
#define GBEMULATOR_MEMORY_HPP


#include <vector>

namespace GBEmulator::Memory
{
	class Memory {
	private:
		bool _readOnly;
		unsigned char _currentBank;
		unsigned short _bankSize;
		unsigned char *_bankPtr = nullptr;

	protected:
		size_t _size;
		unsigned char *_memory;

	public:
		Memory() = delete;
		Memory(const Memory &) = delete;
		~Memory();
		Memory &operator=(const Memory &) = delete;
		Memory(unsigned size, unsigned short bankSize, bool readOnly = false);

		void resize(size_t size);
		//! Change la banque utilisé pour l'adressage de la cartouche
		void setBank(unsigned char bank);
		//! Change la taille de banque utilisé
		void setBankSize(size_t size);
		//! Récupère le numéro de la banque en cours d'utilisation
		unsigned char getCurrentBank() const;
		//! Lis la valeur à l'adresse de la mémoire
		unsigned char read(unsigned short address) const;
		//! Lis la valeur à l'adresse de la mémoire en ignorant les banks
		unsigned char rawRead(unsigned short address) const;
		//! renvoie la taille de la mémoire
		size_t getSize() const;
		//! remplace l'intégralité de la mémoire par la donnée envoyé en paramètre
		void setMemory(unsigned char *memory, size_t size);
		//! Écrit la valeur à l'adresse de la mémoire
		void write(unsigned short address,unsigned char value);
		//! Écrit la valeur à l'adresse de la mémoire en ignorant les permissions
		void forceWrite(unsigned short address,unsigned char value);
		//! Écrit dans la sortie standard un debug de la mémoire
		void dump(unsigned short offset = 0) const;
	};
}


#endif //GBEMULATOR_MEMORY_HPP
