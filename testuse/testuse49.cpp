///testuse49
#include<iostream>

#define Da     do                          \
{                           \
std::cout<<"win"<<std::endl;               \
std::cout<<"win again"<<std::endl;	\
}while (0)

#include<dos.h>



void main() {

	Da;

	
}
///end