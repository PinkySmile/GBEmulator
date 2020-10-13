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
	extern const std::map<std::string, std::function<double(const CPU &, double)>> _unFcts;
	extern const std::map<std::string, std::function<double(double, double)>> _binFcts;
	extern const std::vector<std::string> _binOps;

	class Operation {
	public:
		virtual double getValue(const CPU &) const = 0;
		virtual std::string tostring() const = 0;
	};

	class UnaryOperation : public Operation {
	private:
		std::shared_ptr<Operation> _operand;
		std::string _operator;

	public:
		UnaryOperation(const std::shared_ptr<Operation> &operand, const std::string &operato);
		double getValue(const CPU &) const override;
		std::string tostring() const override;
	};

	class BinaryOperation : public Operation {
	private:
		std::shared_ptr<Operation> _operand1;
		std::shared_ptr<Operation> _operand2;
		std::string _operator;

	public:
		BinaryOperation(const std::shared_ptr<Operation> &operand1, const std::shared_ptr<Operation> &operand2, const std::string &operato);
		double getValue(const CPU &) const override;
		std::string tostring() const override;
	};

	class Value : public Operation {
	private:
		double _v;

	public:
		Value(double v);
		double getValue(const CPU &) const override;

		std::string tostring() const override;
	};

	template<typename T>
	class ValueRegister : public Operation {
	private:
		const T &_v;
		std::string _name;

	public:
		ValueRegister(const T &reg, const std::string &name) : _v(reg), _name(name) {};
		double getValue(const CPU &) const override
		{
			return this->_v;
		}

		std::string tostring() const override
		{
			return this->_name;
		}
	};

	std::shared_ptr<Operation> compileCondition(const CPU::Registers &regs, const CPU &cpu, const std::string &line);
}


#endif //GBEMULATOR_COMPILEDCONDITION_HPP
