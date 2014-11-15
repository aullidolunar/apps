#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <iomanip>
#include <iterator>
#include <libintl.h>
#include <locale.h>

void show_vector (const std::vector<int>& l) {
	std::copy(l.begin(), l.end(), std::ostream_iterator<int>(std::cout, " "));
}

int main() {
	int index = 0; // item counter
	int value = 0; // inputed value
	std::vector<int> f; // container of frecuencies
	double m2 = 0.0; // median
	
	// begin input
	while (1) {
		std::cout << "frecuency [" << index+1 << "]: "; std::cin >> value;
		if (value > -1) {
			index++;
			f.push_back (value);
		} else {
			break;
		}
	}
	
	// sort first
	sort (f.begin(), f.end());
	
	double tmp = std::accumulate (f.begin(), f.end(), 0);
	double m1 = tmp / f.size();
	int m3 = *std::max_element (f.begin(), f.end());
	
	// total items
	int items = f.size();
		
	// median
	int div = items / 2;
	int mod = items % 2;
	if (mod == 0) {
		// here means is pair
		int min = div-1;
		int max = min+1;
		int val1 = f.at(min);
		int val2 = f.at(max);
		m2 = (val1 + val2)/2;
	} else {
		m2 = f.at(div);
	}
	
	// show results
	std::cout << "=== " << "frecuencies inputed (sorted)" << " ===" << std::endl;
	show_vector (f);
	std::cout << "\n=== " << "results" << " ===" << std::endl
		 << "N: " << items << std::endl
		 << "Media: " << std::setprecision(2) << std::showpoint << m1 << std::endl
		 << "Median: " << std::setprecision(2) << std::showpoint << m2 << std::endl
		 << "Mode: " << m3 << std::endl
		 << " === " << "done" << " ===" << std::endl;
	return 0;
}
