#include<cstdio>
#include<functional>
using namespace std;

int main(){
	function<double(double,double)> f = [](double x,double y){return 9.0*x*x + 2.0*y*y;};
	printf("%.5f\n",f(2.0,3.0));
	return 0;
}
