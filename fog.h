#include <iostream>
using namespace std;

class fog {
	public:
		fog();
		fog(unsigned int src_w, unsigned int src_h);
		fog(const fog& src);
		~fog();
		bool** get_arr();
		void clear(unsigned int src_w, unsigned int src_h);
		void clear_rad(unsigned int src_w, unsigned int src_h, unsigned int radius);
	private:
		unsigned int width, height;
		bool** arr;
};
