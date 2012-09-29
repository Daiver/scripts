#include <stdio.h>
#include <fstream>
#include <sstream>

using namespace std;
int main(int argc, char** argv)
{
	if (argc < 3)
	{
		printf("use with 3 or many params");
		return 0;
	}
	
	char *outname = argv[1];
	printf("writting into file %s...\n", outname);
	ofstream fs(outname, std::ios::out | std::ios::binary);
	for (int i = 2; i < argc; i++)
	{
		istringstream ss(argv[i]);
		float res;// = atof(argv[i]);
		ss >> res;
		printf("writing %f\n", res);
		fs.write((const char*) &res, sizeof(res));
	}
	fs.close();
	printf("Trying reading from %s...\n", outname);
	ifstream rfs(outname, std::ios::out | std::ios::binary);
	for (int i = 2; i < argc; i++)
	{
		float res;
		rfs.read( (char*) &res, sizeof(res) );
		printf("%i is %f\n", i - 1, res);
	}
	rfs.close();
	return 0;	
}
