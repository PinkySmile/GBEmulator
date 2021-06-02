/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Memory.hpp
*/

#ifndef GBEMULATOR_MEMORY_HPP
#define GBEMULATOR_MEMORY_HPP

#ifndef ARDUINO
#include <vector>
#include <cstddef>
#include <cstdint>
#else
#include <stddef.h>
#include <stdint.h>
#include "../ArduinoStuff/FakeSTL.hpp"
#endif

namespace GBEmulator::Memory
{
	//! @brief Représente un morceau de mémoire.
	class Memory {
	private:
		//! @brief Est-ce en lecture seule ?
		bool _readOnly;
		//! @brief Bank actuelle.
		uint8_t _currentBank;
		//! @brief Taille d'une bank.
		uint16_t _bankSize;
		//! @brief Pointeur vers le début de la bank séléctionnée.
		unsigned char *_bankPtr = nullptr;

	protected:
		//! @brief Taille totale.
		size_t _size;
		//! @brief Mémoire allouée.
		unsigned char *_memory;

	public:
		//! @brief Constructeur de copie.
		Memory(const Memory &) = delete;
		//! @brief Assignement.
		Memory &operator=(const Memory &) = delete;
		//! @brief Destructor
		~Memory();
		//! @brief Constructeur.
		//! @param size Taille totale.
		//! @param bankSize Taille d'une bank.
		//! @param readOnly Lecture seule.
		//! @note La mémoire est initialisée à des valeurs aléatoires (en appellant rand())
		Memory(unsigned size, unsigned short bankSize, bool readOnly = false);

		//! @brief Change la taille de la memoire.
		//! @note Les données présentes sont présevervées si la nouvelle taille est plus grande.
		//! Sinon, les données sont préservées jusqu'à la nouvelle taille.
		//! Les valeurs non initialisées sont aléatoires (en appellant rand())
		void resize(size_t size);
		//! Change la banque utilisé pour l'adressage de la cartouche
		//! @param bank Nouvelle bank.
		void setBank(uint8_t bank);
		//! Change la taille de banque utilisé
		//! @param size Nouvelle taille de bank.
		void setBankSize(size_t size);
		//! Récupère le numéro de la banque en cours d'utilisation
		//! @return La bank actuelle.
		uint8_t getCurrentBank() const;
		//! Lis la valeur à l'adresse de la mémoire
		//! @param address Adresse à lire.
		//! @return La valeur à l'adresse.
		uint8_t read(uint16_t address) const;
		//! Lis la valeur à l'adresse de la mémoire en ignorant les banks
		//! @param address Adresse à lire.
		//! @return La valeur à l'adresse.
		uint8_t rawRead(uint16_t address) const;
		//! Renvoie la taille de la mémoire
		//! @return La taille totale de la mémoire.
		size_t getSize() const;
		//! Supprime la mémoire alloué actuellement pour la remplacer par la mémoire envoyer en paramètre.
		//! @param memory Pointeur sur un tableau de taille size, alloué avec new.
		//! @param size Taille de l'allocation de memory.
		void setMemory(unsigned char *memory, size_t size);
		//! Écrit la valeur à l'adresse de la mémoire
		//! @param address Adresse à laquelle écrire.
		//! @param value Valeur à écrire.
		void write(uint16_t address,uint8_t value);
		//! Écris la valeur à l'adresse de la mémoire en ignorant les banks et les permissions.
		//! @param address Adresse à écrire.
		//! @param value Valeur à écrire.
		//! @return La valeur à l'adresse.
		void rawWrite(uint16_t address,uint8_t value);
		//! Écrit la valeur à l'adresse de la mémoire en ignorant les permissions
		//! @param address Adresse à laquelle écrire.
		//! @param value Valeur à écrire.
		void forceWrite(uint16_t address, uint8_t value);
		unsigned char *getBuffer();
	};
}


#endif //GBEMULATOR_MEMORY_HPP
