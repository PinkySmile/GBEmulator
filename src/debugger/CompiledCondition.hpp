//
// Created by andgel on 11/10/2020
//

#ifndef GBEMULATOR_COMPILEDCONDITION_HPP
#define GBEMULATOR_COMPILEDCONDITION_HPP


#include <string>
#include <memory>
#include <map>
#include <functional>
#include "../ProcessingUnits/CPU.hpp"

namespace GBEmulator::Debugger
{
	extern const standard::map<standard::string, standard::function<double(const CPU &, double)>> _unFcts;
	extern const standard::map<standard::string, standard::function<double(double, double)>> _binFcts;
	extern const standard::vector<standard::string> _binOps;

	class Operation {
	public:
		virtual double getValue(const CPU &) const = 0;
		virtual standard::string tostring() const = 0;
	};

	class UnaryOperation : public Operation {
	private:
		standard::shared_ptr<Operation> _operand;
		standard::string _operator;

	public:
		UnaryOperation(const standard::shared_ptr<Operation> &operand, const standard::string &operato);
		double getValue(const CPU &) const override;
		standard::string tostring() const override;
	};

	class BinaryOperation : public Operation {
	private:
		standard::shared_ptr<Operation> _operand1;
		standard::shared_ptr<Operation> _operand2;
		standard::string _operator;

	public:
		BinaryOperation(const standard::shared_ptr<Operation> &operand1, const standard::shared_ptr<Operation> &operand2, const standard::string &operato);
		double getValue(const CPU &) const override;
		standard::string tostring() const override;
	};

	class Value : public Operation {
	private:
		double _v;

	public:
		Value(double v);
		double getValue(const CPU &) const override;

		standard::string tostring() const override;
	};

	template<typename T>
	class ValueRegister : public Operation {
	private:
		const CPU::Registers *registers;
		const T *_v;
		standard::string _name;

	public:
		ValueRegister(const CPU::Registers &regs, const standard::string &name) : registers(&regs), _v(nullptr), _name(name) {};
		ValueRegister(const T &reg, const standard::string &name) : registers(nullptr), _v(&reg), _name(name) {};
		double getValue(const CPU &) const override
		{
			if (this->_v)
				return *this->_v;
			if (this->_name == "zf")
				return this->registers->fz;
			if (this->_name == "cf")
				return this->registers->fc;
			if (this->_name == "nf")
				return this->registers->fn;
			return this->registers->fh;
		}

		standard::string tostring() const override
		{
			return this->_name;
		}
	};

	standard::shared_ptr<Operation> compileCondition(const CPU::Registers &regs, const CPU &cpu, const standard::string &line);
}


#endif //GBEMULATOR_COMPILEDCONDITION_HPP
