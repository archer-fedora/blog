#include <iostream>


class VirtualBase1
{

};
class VirtualBase2
{
	int var;
};

class VirtualBase3
{
public:
	VirtualBase3(){var =111;};	
public:
	virtual void printVar1(){return ;};
	virtual void printVar2(){return ;};
	virtual void printVar3(){return ;};
	virtual void printVar4(){std::cout<<"VirtualBase3 "<<__FUNCTION__<<std::endl;};
private:
	int var;
};

typedef void (*ptr_fun)(void);

int main()
{
	std::cout<<"VirtualBase1 size is "<<sizeof(VirtualBase1)<<std::endl;
	std::cout<<"VirtualBase2 size is "<<sizeof(VirtualBase2)<<std::endl;
	std::cout<<"VirtualBase3 size is "<<sizeof(VirtualBase3)<<std::endl;
	
	void (VirtualBase3::*pmf)() = &VirtualBase3::printVar4;

	
	//pmf = &(VirtualBase3::printVar4);

	VirtualBase3 b3;
	
	std::cout<<"b3 addr begin is "<<&b3<<std::endl;
	std::cout<<"pmf addr begin is "<<pmf<<std::endl;
	int* p = (int*)&b3;

	std::cout<<"p is "<<p[3]<<std::endl;
	std::cout<<"var is "<<*(p+2)<<std::endl;
	std::cout<<"var is "<<*(p+3)<<std::endl;
	std::cout<<"var is "<<*(p+4)<<std::endl;
	std::cout<<"var is "<<p<<std::endl;
	//(b3.(*pmf-4))();

	
}

