
#include <vector>

class dsu{

public:

	void init(int n);

	int find(int x);

	void unir(int x, int y);


private:

	vector<int> padre;
	vector<int> altura;

};
