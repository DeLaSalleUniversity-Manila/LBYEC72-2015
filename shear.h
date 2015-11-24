#ifndef shear
#include <iostream>
using namespace std;


float Ushear1(float reaction1);
float Ushear2(float reaction1, float length, float dist, float load);
float Ushear3(float reaction1, float reaction2, float load, float span);

float Tshear1(float reaction1);
float Tshear2(float reaction1, float length, float dist, float load);
float Tshear3(float reaction1, float reaction2, float load, float span);

// CL
float Cshear1(float reaction1)
{
          float shear1;
          shear1 = reaction1;
          return shear1;            
}

float Cshear2(float reaction1, float load)
{
          float shear2;
          shear2 = reaction1 - load;
          return shear2;
}

float Cshear3(float reaction1, float reaction2, float load)
{
    float shear3, x;
    shear3 = reaction1 + reaction2 - load;
    return shear3;
}



// UDL
float Ushear1(float reaction1)
{
	return reaction1;
}

float Ushear2(float reaction1, float length, float dist, float load)
{
	return (reaction1 - (load*(length-dist)));
}



float Ushear3(float reaction1, float reaction2, float load, float span)
{
	return (reaction1 + reaction2 - (load*span));
}



// TAL
float Tshear1(float reaction1)
{
	return reaction1;
}

float Tshear2(float reaction1, float length, float dist, float load)
{
	return (reaction1 - (load*(length-dist)/2));
}


float Tshear3(float reaction1, float reaction2, float load, float span)
{
	return (reaction1 + reaction2 - (load * span/2));
}

#endif     
    

