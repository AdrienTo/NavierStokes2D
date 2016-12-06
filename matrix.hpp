class matrix {

public:

	matrix(int i, int j); // default constructor, row m * column n
	matrix(const matrix& mat); // copy constructor
	virtual ~matrix(); // destructor

	matrix& operator=(const matrix& mat); // assignment operator overload
	matrix operator+(const matrix& mat);
	matrix operator*(double x);
	friend matrix operator*(double x, const matrix& mat);
	matrix operator*(const matrix& mat);
	double operator[](int i) const; // access operator overload
	double& operator[](int i); // access operator for assignment overload
	double operator()(int i, int j) const; // function call operator overload
	double& operator()(int i, int j); // function call operator operator overload
	friend std::ostream& operator<<(std::ostream& out, const matrix& mat);

	void initialise(double* p); // p represents elements of matrice
	int getNumRow() const;
	int getNumColumn() const;

private:

	int nr; // number of row
	int nc; // number of column

	double* m;
	// elements of matrice, size m * n
	// [(1, 1), (1, 2), ... , (n, n - 1), (n, n)]

	bool init;
	// if elements has been initialised with values, true
	// otherwise false, default value is of course false

};
