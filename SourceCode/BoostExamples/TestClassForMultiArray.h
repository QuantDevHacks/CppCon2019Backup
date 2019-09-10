#ifndef TEST_CLASS_H
#define TEST_CLASS_H

class TestClassForMultiArray
{
public:
	void calc(double x, double y)
	{
		result_ = x * y;
	}

	double operator()() const
	{
		return result_;
	}

private:
	double result_;
};


#endif // !TEST_CLASS_H

