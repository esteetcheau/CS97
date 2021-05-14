#include <stdbool.h>
//#include <stdio.h>

enum Input {RDRAND, MRAND48_R, SLASH_F};
enum Output {STDIO, N};

struct opts
{
	bool valid;
	enum Input input;
	enum Output output;
	char* r_src;
	int block;
	long long nbytes;
};
  

void optionProcess(int argc, char **argv, struct opts* opts);
