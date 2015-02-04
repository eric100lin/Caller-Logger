#ifndef _CALLER_VARIABLE_
#define _CALLER_VARIABLE_

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

template<class T>
class CalleeVariable {
private:
	T variable;

	char *binaryName;

	std::vector< std::string > calleesInfo;

	void logCalleeInfo(void *p) {
		char cmd[128];

		snprintf(cmd, sizeof(cmd), "addr2line -e %s -f %p", binaryName, p);
		FILE * fp = popen(cmd, "r");
		if (!fp)
			return;

		char buf[128];
		std::string addr2lineInfo;
		while (fgets(buf, sizeof(buf), fp)) {
			addr2lineInfo.append(buf);
		}
		calleesInfo.push_back(addr2lineInfo);
	}

public:
	CalleeVariable(char *binaryName, T initValue) {
		this->variable = initValue;
		this->binaryName = binaryName;
	}

	T operator+(const T& addend) {
		logCalleeInfo(__builtin_return_address(0));
		return variable + addend;
	}

	T operator-(const T& subtrahend) {
		logCalleeInfo(__builtin_return_address(0));
		return variable - subtrahend;
	}

	T operator*(const T& multiplier) {
		logCalleeInfo(__builtin_return_address(0));
		return variable * multiplier;
	}

	T operator/(const T& divisor) {
		logCalleeInfo(__builtin_return_address(0));
		return variable / divisor;
	}

	T operator+=(const T& addend) {
		logCalleeInfo(__builtin_return_address(0));
		variable += addend;
		return variable;
	}

	T operator-=(const T& subtrahend) {
		logCalleeInfo(__builtin_return_address(0));
		variable -= subtrahend;
		return variable;
	}

	T operator*=(const T& multiplier) {
		logCalleeInfo(__builtin_return_address(0));
		variable *= multiplier;
		return variable;
	}

	T operator/=(const T& divisor) {
		logCalleeInfo(__builtin_return_address(0));
		variable /= divisor;
		return variable;
	}

	T operator=(const T& value) {
		logCalleeInfo(__builtin_return_address(0));
		this->variable = value;
		return value;
	}

	void printCalleeInfo() {
		if(calleesInfo.size()==0)
			std::cout << "calleesInfo is empty." << std::endl;
		for(unsigned i=0, size=calleesInfo.size(); i<size; i++)
			std::cout << "[" << i << "]" << calleesInfo[i] << std::endl;
	}
};

#endif
