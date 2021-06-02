//
// Created by andgel on 11/10/2020
//

#include <cmath>
#include <sstream>
#include "CompiledCondition.hpp"

namespace GBEmulator::Debugger
{
	const standard::map<standard::string, standard::function<double(const CPU &, double)>> _unFcts{
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
			return a == 0;
		}},
		{":", [](const CPU &   , double a){
			return static_cast<unsigned>(a);
		}}
	};
	const standard::map<standard::string, standard::function<double(double, double)>> _binFcts{
		{"+", [](double a, double b){
			return a + b;
		}},
		{"-", [](double a, double b){
			return a - b;
		}},
		{"**", [](double a, double b){
			return standard::pow(a, b);
		}},
		{"/", [](double a, double b){
			return a / b;
		}},
		{"%", [](double a, double b){
			return standard::fmod(a, b);
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
	const standard::vector<standard::string> _binOps{
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
		const standard::shared_ptr<Operation> &operand1,
		const standard::shared_ptr<Operation> &operand2,
		const standard::string &operato
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

	standard::string BinaryOperation::tostring() const
	{
		return "(" + this->_operand1->tostring() + ") " + this->_operator + " (" + this->_operand2->tostring() + ")";
	}

	UnaryOperation::UnaryOperation(
		const standard::shared_ptr<Operation> &operand,
		const standard::string &operato
	) :
		_operand(operand),
		_operator(operato)
	{
	}

	double UnaryOperation::getValue(const CPU &cpu) const
	{
		return _unFcts.at(this->_operator)(cpu, this->_operand->getValue(cpu));
	}

	standard::string UnaryOperation::tostring() const
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

	standard::string Value::tostring() const
	{
		standard::stringstream s;

		s << this->_v;
		return s.str();
	}

	static void deleteSpaces(standard::string &str)
	{
		size_t start = 0;

		while (start < str.size() && standard::isspace(str[start]))
			start++;
		str.erase(0, start);
	}

	static standard::shared_ptr<Value> getNumber(standard::string &str)
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
			auto val = standard::stol(str, &index, base);

			str.erase(0, index);
			return standard::make_shared<Value>(val);
		} catch (...) {
			throw standard::invalid_argument("Invalid number literal");
		}
	}

	static standard::shared_ptr<Operation> getRegister(const CPU::Registers &regs, standard::string &str)
	{
		standard::string name;

		while (standard::isalpha(str[0])) {
			name += str[0];
			str.erase(0, 1);
		}
		if (name == "a")
			return standard::make_shared<ValueRegister<uint8_t>>(regs.a, name);
		else if (name == "b")
			return standard::make_shared<ValueRegister<uint8_t>>(regs.b, name);
		else if (name == "c")
			return standard::make_shared<ValueRegister<uint8_t>>(regs.c, name);
		else if (name == "d")
			return standard::make_shared<ValueRegister<uint8_t>>(regs.d, name);
		else if (name == "e")
			return standard::make_shared<ValueRegister<uint8_t>>(regs.e, name);
		else if (name == "h")
			return standard::make_shared<ValueRegister<uint8_t>>(regs.h, name);
		else if (name == "l")
			return standard::make_shared<ValueRegister<uint8_t>>(regs.l, name);
		else if (name == "zf")
			return standard::make_shared<ValueRegister<bool>>(regs, name);
		else if (name == "cf")
			return standard::make_shared<ValueRegister<bool>>(regs, name);
		else if (name == "nf")
			return standard::make_shared<ValueRegister<bool>>(regs, name);
		else if (name == "hcf" || name == "hf")
			return standard::make_shared<ValueRegister<bool>>(regs, "hf");
		else if (name == "f")
			return standard::make_shared<ValueRegister<uint8_t>>(regs.f, name);
		else if (name == "af")
			return standard::make_shared<ValueRegister<unsigned short>>(regs.af, name);
		else if (name == "bc")
			return standard::make_shared<ValueRegister<unsigned short>>(regs.bc, name);
		else if (name == "de")
			return standard::make_shared<ValueRegister<unsigned short>>(regs.de, name);
		else if (name == "hl")
			return standard::make_shared<ValueRegister<unsigned short>>(regs.hl, name);
		else if (name == "pc")
			return standard::make_shared<ValueRegister<unsigned short>>(regs.pc, name);
		else if (name == "sp")
			return standard::make_shared<ValueRegister<unsigned short>>(regs.sp, name);
		throw standard::invalid_argument(name + " is not a valid register name");
	}

	static standard::shared_ptr<Operation> getVal(const CPU::Registers &regs, standard::string &str)
	{
		deleteSpaces(str);
		if (standard::isalpha(str[0]))
			return getRegister(regs, str);
		return getNumber(str);
	}

	static standard::string getOperator(standard::string &str, unsigned operatorPriority)
	{
		standard::string check = _binOps[operatorPriority];

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

	static standard::shared_ptr<Operation> getValue(const CPU::Registers &regs, const CPU &cpu, standard::string &str);
	static standard::shared_ptr<Operation> compileCondition(const CPU::Registers &regs, const CPU &cpu, standard::string &str, unsigned operatorPriority)
	{
		deleteSpaces(str);
		if (operatorPriority >= _binOps.size())
			return getValue(regs, cpu, str);

		standard::shared_ptr<Operation> op1;

		op1 = compileCondition(regs, cpu, str, operatorPriority + 1);
		deleteSpaces(str);
		if (str[0] == ')') {
			str.erase(0, 1);
			return op1;
		}

		standard::string op = getOperator(str, operatorPriority);

		if (operatorPriority == 14) {

			if (op.empty())
				return op1;
			return standard::make_shared<BinaryOperation>(op1, compileCondition(regs, cpu, str, operatorPriority), op);
		}

		while (!op.empty()) {
			standard::shared_ptr<Operation> op2 = compileCondition(regs, cpu, str, operatorPriority + 1);

			op1 = standard::make_shared<BinaryOperation>(op1, op2, op);
			op = getOperator(str, operatorPriority);
		}
		return op1;
	}

	static standard::shared_ptr<Operation> getValue(const CPU::Registers &regs, const CPU &cpu, standard::string &str)
	{
		try {
			_unFcts.at(str.substr(0, 1));
		} catch (standard::out_of_range &) {
			if (str[0] == '(') {
				str.erase(0, 1);
				return compileCondition(regs, cpu, str, 0);
			}
			return getVal(regs, str);
		}

		char op = str[0];

		str.erase(0, 1);
		deleteSpaces(str);
		return standard::make_shared<UnaryOperation>(getValue(regs, cpu, str), standard::string(&op, &op + 1));
	}

	standard::shared_ptr<Operation> compileCondition(const CPU::Registers &regs, const CPU &cpu, const standard::string &line)
	{
		standard::string str = line;
		try {
			auto val = compileCondition(regs, cpu, str, 0);

			if (!str.empty())
				throw standard::invalid_argument("Unexpected character found");
			return val;
		} catch (standard::exception &e) {
			throw standard::invalid_argument(e.what() + standard::string(" near character ") + standard::to_string(line.size() - str.size()) + " \"" + str + "\"");
		}
	}
}