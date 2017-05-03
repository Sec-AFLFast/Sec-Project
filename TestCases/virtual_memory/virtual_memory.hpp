/*
 * vitrual_memory.hpp
 *
 *  Created on: Feb 27, 2015
 *      Author: cammyluffy
 */

#ifndef VITRUAL_MEMORY_HPP_
#define VITRUAL_MEMORY_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include <fstream>
#include <string.h>
#include <queue>
#include <list>
#include <cmath>

struct frame {
	int in_frame[512] = {0};
};

struct LRU_TLB {
	int LRU = 0;
	int sp = 0;
	int f = 0;
};


class VM {

private:
	frame pm[1024];
	int bm[32] = {0};
	int s_p_w[4] = {0};
	LRU_TLB tlb[4];

public:
	VM();

	void set_bit(int k);
	void clear_bit(int k);
	int test_bit(int k);
	int get_free_frame();
	int get_free_pt();

	void read_segment(int s, int f);
	void read_page(int p, int s, int f);

	int read(int va);
	int write(int va);
	int* translate(int va);
	void print_st();
	void print_pt();

	int read_with_TLB(int va, std::ofstream& outfile);
	int write_with_TLB(int va, std::ofstream& outfile);
};

int* VM::translate(int va) {
	int s = va / std::pow(2, 19);
	int sp = va / std::pow(2, 9);
	int w = va - sp * std::pow(2, 9);
	int pw = va - s * std::pow(2, 19);
	int p = pw / std::pow(2, 9);
	s_p_w[0] = s;
	s_p_w[1] = p;
	s_p_w[2] = w;
	s_p_w[3] = sp;
//	std::cout << "va " << va << " : ";
//	std::cout << s_p_w[0] << " " << s_p_w[1] << " " << s_p_w[2] << std::endl;
	return s_p_w;
}

int VM::write_with_TLB(int va, std::ofstream& outfile) {
	translate(va);
	int s = s_p_w[0];
	int p = s_p_w[1];
	int w = s_p_w[2];
	int sp = s_p_w[3];
	int ptn = (pm[0].in_frame[s]) / 512;
	for (int i = 0; i < 4; i++) {
		if (tlb[i].sp == sp) {
			outfile << "h" << " ";
			tlb[i].LRU = 3;
			for (int j = 0; j < 4; j++) {
				if (j != i && tlb[j].LRU > tlb[i].LRU) {
					tlb[j].LRU -= 1;
				}
			}
			outfile << tlb[i].f + w << " ";
			return tlb[i].f + w;
		}
	}
//	std::cout << "m" << " ";
//	outfile << "m" << " ";
	if (pm[0].in_frame[s] == -1 or pm[ptn].in_frame[p] == -1) {
		outfile << "pf" << " ";
		return -1;
	}
	else if (pm[0].in_frame[s] == 0) {
		int pt = get_free_frame();
		set_bit(pt);
		set_bit(pt+1);
		pm[0].in_frame[s] = pt * 512;
		if (pm[ptn].in_frame[p] == 0) {
			int page = get_free_frame();
			set_bit(page);
			pm[ptn].in_frame[p] = page * 512;
		}
		for (int i = 0; i < 4; i++) {
			if (tlb[i].LRU == 0) {
				for (int z = 0; z < 4; z++) {
					if (z != i) {
						tlb[z].LRU -= 1;
					}
				}
				tlb[i].LRU = 3;
				tlb[i].sp = sp;
				tlb[i].f = pm[ptn].in_frame[p];
			}
		}
		outfile << "m " << pm[ptn].in_frame[p] + w << " ";
		return pm[ptn].in_frame[p] + w;
	}
	else {
		for (int i = 0; i < 4; i++) {
			if (tlb[i].LRU == 0) {
				for (int z = 0; z < 4; z++) {
					if (z != i) {
						tlb[z].LRU -= 1;
					}
				}
				tlb[i].LRU = 3;
				tlb[i].sp = sp;
				tlb[i].f = pm[ptn].in_frame[p];
			}
		}
		outfile << "m " << pm[ptn].in_frame[p] + w << " ";
		return pm[ptn].in_frame[p] + w;
	}

}


int VM::write(int va) {
	translate(va);
	int s = s_p_w[0];
	int p = s_p_w[1];
	int w = s_p_w[2];
	int ptn = (pm[0].in_frame[s]) / 512;
	std::cout << std::endl << "write " << va << " : ";
	std::cout << s_p_w[0] << " " << s_p_w[1] << " " << s_p_w[2] << std::endl;

	if (pm[0].in_frame[s] == 0) {
			int pt = get_free_pt();
			set_bit(pt);
			set_bit(pt+1);
			pm[0].in_frame[s] = pt * 512;
			int ptn = (pm[0].in_frame[s]) / 512;
			std::cout << "free frame: " << pt * 512 << std::endl;
			if (pm[ptn].in_frame[p] == 0) {
				int page = get_free_frame();
				set_bit(page);
				std::cout << "free page: " << page << std::endl;
				pm[ptn].in_frame[p] = page * 512;
				return pm[ptn].in_frame[p] + w;
			}
			else {
				return pm[ptn].in_frame[p] + w;
			}
	}
	else if (pm[0].in_frame[s] == -1 or pm[ptn].in_frame[p] == -1) {
		return -1;
	}
	else {
		if (p >= 512) {
			ptn = ptn + 1;
			p = p % 512;
		}
		if (pm[ptn].in_frame[p] == 0) {
			int page = get_free_frame();
			std::cout << "free page: " << page << std::endl;
			set_bit(page);
			pm[ptn].in_frame[p] = page * 512;
		}
		return pm[ptn].in_frame[p] + w;
	}

}

int VM::read_with_TLB(int va, std::ofstream& outfile) {
	translate(va);
	int s = s_p_w[0];
	int p = s_p_w[1];
	int w = s_p_w[2];
	int sp = s_p_w[3];
	int ptn = (pm[0].in_frame[s]) / 512;
	for (int i = 0; i < 4; i++) {
		if (tlb[i].sp == sp) {
			outfile << "h" << " ";
			tlb[i].LRU = 3;
			for (int j = 0; j < 4; j++) {
				if (j != i && tlb[j].LRU > tlb[i].LRU) {
					tlb[j].LRU -= 1;
				}
			}
			outfile << tlb[i].f + w << " ";
			return tlb[i].f + w;
		}
	}
//	std::cout << "m" << " ";
//	outfile << "m" << " ";
	if (pm[0].in_frame[s] == -1 or pm[ptn].in_frame[p] == -1) {
		outfile << "pf" << " ";
		return -1;
	}
	else if (pm[0].in_frame[s] == 0 or pm[ptn].in_frame[p] == 0) {
		outfile << "err" << " ";
		return 0;
	}
	else {
		for (int i = 0; i < 4; i++) {
			if (tlb[i].LRU == 0) {
				for (int z = 0; z < 4; z++) {
					if (z != i) {
						tlb[z].LRU -= 1;
					}
				}
				tlb[i].LRU = 3;
				tlb[i].sp = sp;
				tlb[i].f = pm[ptn].in_frame[p];
			}
		}
		outfile << "m " << pm[ptn].in_frame[p] + w << " ";
		return pm[ptn].in_frame[p] + w;
	}
}


int VM::read(int va) {
	translate(va);
	int s = s_p_w[0];
	int p = s_p_w[1];
	int w = s_p_w[2];
	int ptn = (pm[0].in_frame[s]) / 512;
	std::cout << std::endl << "read " << va << " : ";
	std::cout << s_p_w[0] << " " << s_p_w[1] << " " << s_p_w[2] << std::endl;

	if (p >= 512) {
		ptn += 1;
		p = p % 512;
	}

	if (pm[0].in_frame[s] == 0 or pm[ptn].in_frame[p] == 0) {
			return 0;
		}
	else if (pm[0].in_frame[s] == -1 or pm[ptn].in_frame[p] == -1) {
		return -1;
	}
	else {
		if (p >= 512) {
			ptn = ptn + 1;
		}
		return pm[ptn].in_frame[p] + w;
	}
}

void VM::print_pt() {
	for (int i = 1; i < 512; i++) {
		if (test_bit(i) != 0) {
			std::cout << i << std::endl;
			for (int j = 0; j < 512; j++) {
				if (pm[i].in_frame[j] != 0) {
					std::cout << "page table index: " << j + i * 512 << ": " << pm[i].in_frame[j] << std::endl;
				}
			}
		}
	}
	std::cout << std::endl;
}

void VM::read_page(int p, int s, int f) {
	int ptf = (pm[0].in_frame[s]) / 512;
	pm[ptf].in_frame[p] = f;
	int page_frame = f / 512;
	set_bit(page_frame);
	if (test_bit(ptf) == 0) {
		set_bit(ptf);
		set_bit(ptf+1);
	}
}
void VM::print_st() {
	for (int i = 0; i < 10; i++) {
		std::cout << pm[0].in_frame[i] << " ";
	}
	std::cout << std::endl;
}
void VM::read_segment(int s, int f) {
	pm[0].in_frame[s] = f;
}

VM::VM() {
	set_bit(0);
	for (int i = 0; i < 4; i++) {
		tlb[i].LRU = i;
		tlb[i].sp = -1;
		tlb[i].f = 0;
	}

}

int VM::get_free_pt() {
	for (int i = 0; i < 1023; i++) {
		if (test_bit(i) == 0 and test_bit(i+1) == 0) {
			return i;
		}
	}
	return -1;
}

int VM::get_free_frame() {
	for (int i = 0; i < 1024; i++) {
		if (test_bit(i) == 0) {
			return i;
		}
	}
	return -1;
}


void VM::set_bit(int k) {
	int i = k / 32;
	int pos = k % 32;
	unsigned int flag = 1;   // flag = 0000.....00001
	flag = flag << pos;      // flag = 0000...010...000   (shifted k positions)
	bm[i] = bm[i] | flag;      // Set the bit at the k-th position in BM[i]
}

void VM::clear_bit(int k) {
	int i = k / 32;
	int pos = k % 32;
	unsigned int flag = 1;  // flag = 0000.....00001
	flag = flag << pos;     // flag = 0000...010...000   (shifted k positions)
	flag = ~flag;           // flag = 1111...101..111
	bm[i] = bm[i] & flag;     // RESET the bit at the k-th position in BM[i]
}

int VM::test_bit(int k) {
	int i = k / 32;
	int pos = k % 32;
	unsigned int flag = 1;  // flag = 0000.....00001
	flag = flag << pos;     // flag = 0000...010...000   (shifted k positions)
	if (bm[i] & flag)      // Test the bit at the k-th position in A[i]
		return 1;
	else
		return 0;
}


#endif /* VITRUAL_MEMORY_HPP_ */
