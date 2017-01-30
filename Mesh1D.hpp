#include <string>
#include <map>

class Mesh1D {

public:

	Mesh1D(int nm); // nm = number of mesh (= ne in 1D)
	Mesh1D(std::string str);
	virtual ~Mesh1D();
	double operator[](int i);

	void writeMeshFile(std::string str);
	int getNumVertex() const;
	int getNumEdge() const;
	std::pair<int, int> getVertexIndexPair(int ei);
	double getVertexCoordinate(int vi);
	double getEdgeLength(int ei);


private:

	int nv; // number of vertex
	int ne; // number of edge, normally ne = nv - 1 in 1D
	std::map<int, double> vi2vc; // vertex index -> vertex coordinate
	std::map<int, std::pair<int, int> > ei2vip; // edge index -> vertex index pair
	std::map<int, int> vi2bi; // vertex index -> boundary indicator: 1 = boundary, 0 = not
	int* bv; // boundary vertex list

};
