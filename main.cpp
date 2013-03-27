#include"BigInt.h"
#include<ctime>
int main() {
    /* test cases */

    /*
    * case 1: addition a>b and b>a and a=b 
    */
    BigInt a1("99");
    BigInt b1("9131");
    std::cout<<"\na = "<<a1.toString();
    std::cout<<"\nb = "<<b1.toString();
    std::cout<<"\nsum = "<<(a1+b1).toString();
    std::cout<<"\na-b = "<<(a1-b1).toString();

    BigInt a2("99");
    BigInt b2("91");
    std::cout<<"\na = "<<a2.toString();
    std::cout<<"\nb = "<<b2.toString();
    std::cout<<"\nsum = "<<(a2+b2).toString();
    std::cout<<"\nproduct = "<<(a2*b2).toString();
    std::cout<<"\na-b = "<<(a2-b2).toString();

    /*
    * case 2: a=b and one is negative
    */
    BigInt a3("-99");
    BigInt b3("91");
    std::cout<<"\na = "<<a3.toString();
    std::cout<<"\nb = "<<b3.toString();
    std::cout<<"\nsum = "<<(a3+b3).toString();
    std::cout<<"\nsum = "<<(b3+a3).toString();
    std::cout<<"\nproduct = "<<(b3*a3).toString();
    std::cout<<"\na-b = "<<(a3-b3).toString();

    /*
    * case 2: abs(a)>abs(b) and a is negative
    */
    BigInt a4("-999");
    BigInt b4("91");
    std::cout<<"\na = "<<a4.toString();
    std::cout<<"\nb = "<<b4.toString();
    std::cout<<"\nsum = "<<(a4+b4).toString();
    std::cout<<"\nsum = "<<(b4+a4).toString();
    std::cout<<"\nproduct = "<<(b4*a4).toString();
    std::cout<<"\na-b = "<<(a4-b4).toString();

    /*
    * case 3: abs(b)>abs(a) and b is negative
    */
    BigInt a5("99");
    BigInt b5("-991");
    std::cout<<"\na = "<<a5.toString();
    std::cout<<"\nb = "<<b5.toString();
    std::cout<<"\nsum = "<<(a5+b5).toString();
    std::cout<<"\nsum = "<<(b5+a5).toString();
    std::cout<<"\nproduct = "<<(b5*a5).toString();
    std::cout<<"\na-b = "<<(a5-b5).toString();

    /*
    * case 4: abs(b)>abs(a) and a,b is negative
    */
    BigInt a6("-99");
    BigInt b6("-991");
    std::cout<<"\na = "<<a6.toString();
    std::cout<<"\nb = "<<b6.toString();
    std::cout<<"\nsum = "<<(a6+b6).toString();
    std::cout<<"\nsum = "<<(b6+a6).toString();
    std::cout<<"\na-b = "<<(a6-b6).toString();

    /*
    * case 4: abs(b)=abs(a) and a,b is negative
    */
    BigInt a7("-999");
    BigInt b7("-991");
    std::cout<<"\na = "<<a7.toString();
    std::cout<<"\nb = "<<b7.toString();
    std::cout<<"\nsum = "<<(a7+b7).toString();
    std::cout<<"\nsum = "<<(b7+a7).toString();
    std::cout<<"\nproduct = "<<(b7*a7).toString();
    std::cout<<"\na-b = "<<(a7-b7).toString();

    /*
    * case 5: a-b
    */
    BigInt a8("-999");
    BigInt b8("-991");
    std::cout<<"\na = "<<a8.toString();
    std::cout<<"\nb = "<<b8.toString();
    std::cout<<"\na-b = "<<(a8-b8).toString();
    std::cout<<"\na-b = "<<(a8-b8).toString();



    BigInt fact("1");
    clock_t time = clock();
    fact = fact.factorial(10000);
    time = clock() - time;
    std::cout<<"\n\n10000 Factorial:\n"<<fact.toString()<<std::endl;
    std::cout<<"\n\ntime taken to find 10000! = "<<time/CLOCKS_PER_SEC<<" seconds";

    return 0;
}
