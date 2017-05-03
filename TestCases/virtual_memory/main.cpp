/*
 * main.cpp

 *
 *  Created on: Feb 3, 2015
 *      Author: cammyluffy
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include "virtual_memory.hpp"
#include <list>

int main() {

	std::string line, line2;

	//std::string defaultpath = "/Volumes/NO NAME/";
	std::string path = "";
	//path = defaultpath;
	std::ifstream infile1(path + "input1.txt");
	if (!infile1.is_open()) {
		std::cout << "wrong file" << std::endl;
	}

	std::ifstream infile2(path + "input2.txt");
	if (!infile2.is_open()) {
		std::cout << "wrong file" << std::endl;
	}
	std::ofstream outfile1;
	std::ofstream outfile2;
	outfile1.open(path + "91132408.txt", std::ios::out);
	outfile2.open(path + "91132408_2.txt", std::ios::out);


	VM vmp;
	std::getline(infile1, line);
	std::istringstream linestream(line);
	while (!linestream.eof()) {
		int s = - 99;
		int f = -99;
		linestream >> s >> f;
		if (s != -99 and f != -99) {
			std::cout << s << " " << f << std::endl;
			vmp.read_segment(s, f);
		}
	}
	std::getline(infile1, line);
	std::istringstream linestream2(line);
	while (!linestream2.eof()) {
		int p = -99;
		int s = -99;
		int f2 = -99;
		linestream2 >> p >> s >> f2;
		if (p != -99 and s != - 99 and f2 != -99) {
			std::cout << p << " " << s << " " << f2 << std::endl;
			vmp.read_page(p, s, f2);
		}
	}
	std::cout << std::endl;
//	vmp.print_st();
//	std::cout << std::endl;
//	vmp.print_pt();
	std::getline(infile2, line2);
	std::istringstream stream(line2);
	while (!stream.eof()) {
		int o = -99;
		int va = -99;
		stream >> o >> va;
		if (o != -99 and va != -99) {
//			std::cout << o << " " << va << " ";
			if (o == 0) {
				int n = vmp.read(va);
	//			int n_tlb = vmp.read_with_TLB(va, outfile2);
				if (n == -1) {
					std::cout << "pf" << " ";
					outfile1 << "pf" << " ";
				}
				else if (n == 0) {
					std::cout << "err" << " ";
					outfile1 << "err" << " ";
				}
				else {
					std::cout << n << " ";
					outfile1 << n << " ";
				}
			}
			else if (o == 1) {
				int n2 = vmp.write(va);
	//			int n2_tlb = vmp.write_with_TLB(va, outfile2);
				if (n2 == -1) {
					std::cout << "pf" << " ";
					outfile1 << "pf" << " ";
				}
				else if (n2 == 0) {
					std::cout << "0? error" << " ";
					outfile1 << "0? error" << " ";
				}
				else {
					std::cout << n2 << " ";
					outfile1 << n2 << " ";
				}
			}
			else {
				std::cout << "err" << " ";
				outfile1 << "err" << " ";
				outfile2 << "err" << " ";
			}
//			std::cout << std::endl;
		}
	}





	std::cout << "\nend" << std::endl;

	infile1.close();
	infile2.close();
	outfile1.close();
	outfile2.close();

	return 0;
}
