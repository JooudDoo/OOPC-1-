class BigBin {

public:
	BigBin(BigInt&);
	~BigBin() = default;

private:
	void insert(const BigInt&);

	std::string value;
};