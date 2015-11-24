#ifndef moment
#include <iostream>
using namespace std;

float moment1(float dist, float load);
float moment2(float dist, float span, float load);
float moment3(float dist, float span, float load);

float maxmoment1(float dist, float load);
float maxmoment2(float dist, float span, float load);
float maxmoment3(float dist, float span, float load);


float moment1(float dist, float load)
{
	
	return (load*dist);
}

float moment2(float dist, float span, float load)
{
	
	return load*span*((span/2)+dist);
}

float moment3(float dist, float span, float load)
{
	
	return (load*span/2)*((2*span/3)+dist);

}

float maxmoment1(float dist, float load)
{
	return (load*dist)/2;
}

float maxmoment2(float dist, float span, float load)
{
	return (load*span/2)*((span+dist)/2)/2;
}


#endif

