//
// Created by andgel on 11/10/2020
//

#include <cmath>
#include <sstream>
#include "CompiledCondition.hpp"

namespace GBEmulator::Debugger
{
	const std::map<std::string, std::function<double(const CPU &, double)>> _unFcts{
		{"~", [](const CPU &   , double a){
			return ~static_cast<unsigned>(a);
		}},
		{"-", [](const CPU &   , double a){
			return -a;
		}},
		{"*", [](const CPU &cpu, double a){
			return cpu.read(a);
		}},
		{"!", [](const CPU &   , double a){
			return !a;
		}},
		{":", [](const CPU &   , double a){
			return static_cast<unsigned>(a);
		}}
	};
	const std::map<std::string, std::function<double(double, double)>> _binFcts{
		{"+", [](double a, double b){
			return a + b;
		}},
		{"-", [](double a, double b){
			return a - b;
		}},
		{"**", [](double a, double b){
			return std::pow(a, b);
		}},
		{"/", [](double a, double b){
			return a / b;
		}},
		{"%", [](double a, double b){
			return std::fmod(a, b);
		}},
		{"&&", [](double a, double b){
			return static_cast<unsigned>(a) && static_cast<unsigned>(b);
		}},
		{"||", [](double a, double b){
			return static_cast<unsigned>(a) || static_cast<unsigned>(b);
		}},
		{"<<", [](double a, double b){
			return static_cast<unsigned>(a) << static_cast<unsigned>(b);
		}},
		{">>", [](double a, double b){
			return static_cast<unsigned>(a) >> static_cast<unsigned>(b);
		}},
		{"&", [](double a, double b){
			return static_cast<unsigned>(a) & static_cast<unsigned>(b);
		}},
		{"|", [](double a, double b){
			return static_cast<unsigned>(a) | static_cast<unsigned>(b);
		}},
		{"*", [](double a, double b){
			return a * b;
		}},
		{"<", [](double a, double b){
			return a < b;
		}},
		{">", [](double a, double b){
			return a > b;
		}},
		{"=", [](double a, double b){
			return a == b;
		}},
		{"==", [](double a, double b){
			return a == b;
		}},
		{"<=", [](double a, double b){
			return a <= b;
		}},
		{">=", [](double a, double b){
			return a >= b;
		}}
	};
	const std::vector<std::string> _binOps{
		"&",
		"|",
		"&&",
		"||",
		"<",
		">",
		"=",
		"==",
		"<=",
		">=",
		"<<",
		">>",
		"+",
		"-",
		"*",
		"/",
		"**",
	};

	BinaryOperation::BinaryOperation(
		const std::shared_ptr<Operation> &operand1,
		const std::shared_ptr<Operation> &operand2,
		const std::string &operato
	) :
		_operand1(operand1),
		_operand2(operand2),
		_operator(operato)
	{
	}

	double BinaryOperation::getValue(const CPU &cpu) const
	{
		return _binFcts.at(this->_operator)(this->_operand1->getValue(cpu), this->_operand2->getValue(cpu));
	}

	std::string BinaryOperation::tostring() const
	{
		return "(" + this->_operand1->tostring() + ") " + this->_operator + " (" + this->_operand2->tostring() + ")";
	}

	UnaryOperation::UnaryOperation(
		const std::shared_ptr<Operation> &operand,
		const std::string &operato
	) :
		_operand(operand),
		_operator(operato)
	{
	}

	double UnaryOperation::getValue(const CPU &cpu) const
	{
		return _unFcts.at(this->_operator)(cpu, this->_operand->getValue(cpu));
	}

	std::string UnaryOperation::tostring() const
	{
		return this->_operator + "(" + this->_operand->tostring() + ")";
	}

	Value::Value(double v) :
		_v(v)
	{
	}

	double Value::getValue(const CPU &) const
	{
		return this->_v;
	}

	std::string Value::tostring() const
	{
		std::stringstream s;

		s << this->_v;
		return s.str();
	}

	static void deleteSpaces(std::string &str)
	{
		size_t start = 0;

		while (start < str.size() && std::isspace(str[start]))
			start++;
		str.erase(0, start);
	}

	static std::shared_ptr<Value> getNumber(std::string &str)
	{
		int base = 10;
		size_t index;

		switch (str[0]) {
		case '$':
			base = 16;
			str.erase(0, 1);
			break;
		case '%':
			base = 2;
			str.erase(0, 1);
			break;
		case '&':
			base = 8;
			str.erase(0, 1);
			break;
		default:
			break;
		}

		try {
			auto val = std::stol(str, &index, base);

			str.erase(0, index);
			return std::make_shared<Value>(val);
		} catch (...) {
			throw std::invalid_argument("Invalid number literal");
		}
	}

	static std::shared_ptr<Operation> getRegister(const CPU::Registers &regs, std::string &str)
	{
		std::string name;

		while (std::isalpha(str[0])) {
			name += str[0];
			str.erase(0, 1);
		}
		if (name == "a")
			return std::make_shared<ValueRegister<unsigned char>>(regs.a, name);
		else if (name == "b")
			return std::make_shared<ValueRegister<unsigned char>>(regs.b, name);
		else if (name == "c")
			return std::make_shared<ValueRegister<unsigned char>>(regs.c, name);
		else if (name == "d")
			return std::make_shared<ValueRegister<unsigned char>>(regs.d, name);
		else if (name == "e")
			return std::make_shared<ValueRegister<unsigned char>>(regs.e, name);
		else if (name == "h")
			return std::make_shared<ValueRegister<unsigned char>>(regs.h, name);
		else if (name == "l")
			return std::make_shared<ValueRegister<unsigned char>>(regs.l, name);
		else if (name == "zf")
			return std::make_shared<ValueRegister<bool>>(regs.fz, name);
		else if (name == "cf")
			return std::make_shared<ValueRegister<bool>>(regs.fc, name);
		else if (name == "nf")
			return std::make_shared<ValueRegister<bool>>(regs.fn, name);
		else if (name == "hcf")
			return std::make_shared<ValueRegister<bool>>(regs.fh, name);
		else if (name == "f")
			return std::make_shared<ValueRegister<unsigned char>>(regs.f, name);
		else if (name == "af")
			return std::make_shared<ValueRegister<unsigned short>>(regs.af, name);
		else if (name == "bc")
			return std::make_shared<ValueRegister<unsigned short>>(regs.bc, name);
		else if (name == "de")
			return std::make_shared<ValueRegister<unsigned short>>(regs.de, name);
		else if (name == "hl")
			return std::make_shared<ValueRegister<unsigned short>>(regs.hl, name);
		else if (name == "pc")
			return std::make_shared<ValueRegister<unsigned short>>(regs.pc, name);
		else if (name == "sp")
			return std::make_shared<ValueRegister<unsigned short>>(regs.sp, name);
		throw std::invalid_argument(name + " is not a valid register name");
	}

	static std::shared_ptr<Operation> getVal(const CPU::Registers &regs, std::string &str)
	{
		deleteSpaces(str);
		if (std::isalpha(str[0]))
			return getRegister(regs, str);
		return getNumber(str);
	}

	static std::string getOperator(std::string &str, unsigned operatorPriority)
	{
		std::string check = _binOps[operatorPriority];

		if (str.substr(0, check.size()) == check) {
			str.erase(0, check.size());
			return check;
		}
		if (str[0] == '%' && operatorPriority == 13) {
			str.erase(0, 1);
			return "%";
		}
		return "";
	}

	static std::shared_ptr<Operation> getValue(const CPU::Registers &regs, const CPU &cpu, std::string &str);
	static std::shared_ptr<Operation> compileCondition(const CPU::Registers &regs, const CPU &cpu, std::string &str, unsigned operatorPriority)
	{
		deleteSpaces(str);
		if (operatorPriority >= _binOps.size())
			return getValue(regs, cpu, str);

		std::shared_ptr<Operation> op1;

		op1 = compileCondition(regs, cpu, str, operatorPriority + 1);
		deleteSpaces(str);
		if (str[0] == ')') {
			str.erase(0, 1);
			return op1;
		}

		std::string op = getOperator(str, operatorPriority);

		if (operatorPriority == 14) {

			if (op.empty())
				return op1;
			return std::make_shared<BinaryOperation>(op1, compileCondition(regs, cpu, str, operatorPriority), op);
		}

		while (!op.empty()) {
			std::shared_ptr<Operation> op2 = compileCondition(regs, cpu, str, operatorPriority + 1);

			op1 = std::make_shared<BinaryOperation>(op1, op2, op);
			op = getOperator(str, operatorPriority);
		}
		return op1;
	}

	static std::shared_ptr<Operation> getValue(const CPU::Registers &regs, const CPU &cpu, std::string &str)
	{
		try {
			_unFcts.at(str.substr(0, 1));
		} catch (std::out_of_range &) {
			if (str[0] == '(') {
				str.erase(0, 1);
				return compileCondition(regs, cpu, str, 0);
			}
			return getVal(regs, str);
		}

		char op = str[0];

		str.erase(0, 1);
		deleteSpaces(str);
		return std::make_shared<UnaryOperation>(getValue(regs, cpu, str), std::string(&op, &op + 1));
	}

	std::shared_ptr<Operation> compileCondition(const CPU::Registers &regs, const CPU &cpu, const std::string &line)
	{
		std::string str = line;
		try {
			auto val = compileCondition(regs, cpu, str, 0);

			if (!str.empty())
				throw std::invalid_argument("Unexpected character found");
			return val;
		} catch (std::exception &e) {
			throw std::invalid_argument(e.what() + std::string(" near character ") + std::to_string(line.size() - str.size()) + " \"" + str + "\"");
		}
	}
}