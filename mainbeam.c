#include "shear.h"
#include "moment.h"
#include <cmath>
#include <iostream>
using namespace std;

float cdeflection (float P, float l2, float L, float I, float E)
{
       float d;
       
       d = ((P*l2*pow(pow(L,2)-pow(l2,2),3/2))/(9*sqrt(3)*E*I));
       
       return d;
       
       }
       
float udl (float W, float L, float I, float E)
{
       float u;
           
       u = ((5*W*pow(L,4))/(384*E*I));
       
       return u;
           
}

float tal (float W, float L, float E, float I)
{
      float v;
      
      v = (0.00652*(W*pow(L,4))/E*I);
      }

void menu1(float length, float b, float h, float e, float inertia)
{
	cout << "Specified parameters are as follows:" << endl << endl;
             
            cout << "Span of beam = " << length << " meters" << endl; 
            cout << "Modulus of Elasticity = " << e << endl;
            cout << "Cross sectional base = " << b << " meters" << endl;
            cout << "Cross-sectional height = " << h << " meters" << endl;
            cout << "Moment of Inertia = " << inertia << " meters^4" << endl << endl;
}

int menu2(int &z)
{
	cout << "The possible actions for the program are as follows:" << endl;
	cout << "(1) Solve for Reactions" << endl;
    cout << "(2) Show tabulated Shear values" << endl;
    cout << "(3) Show Maximum Moment Value" << endl;
    cout << "(4) Calculate the deflection of the beam" << endl;
    
    cout << "Your chosen category: ";
    cin >> z;
    return z;
}

main()
{
	float length, b, h, e , inertia;
	float d, f, s, l, k, m;
	float moment, r2, r1, d2, shear1, shear2, shear3;
	int w,x,y,z;
	bool next = false;
	
	cout << "Parameters to be defined are as follows"<<endl<<endl;
	cout << "1 - Span of beam" << endl;
	cout << "2 - Moment of Inertia" << endl;
	cout << "3 - Modulus of Elasticity" << endl;
	cout << "4 - Loads and its corresponding types" << endl << endl;
	
	cout << "1. Specify span of the beam (meters): ";
	cin >> length;
	
	cout << "2a. Input the cross-sectional base of the beam (meters): ";
    cin >> b;
    
    cout << "2b. Input the cross-sectional height of the beam (meters): ";
    cin >> h;
    
	cout << "3. Input Modulus of Elasticity of the beam: ";
	cin >> e;
	
	inertia = (b*pow(h,3))/12;
	
	system("CLS");
	
	cout << "4. Common Types of Loading" << endl << endl;
	cout << "Loading Type (1)  - Concentrated Load" << endl;
	cout << "Loading Type (2)  - Uniformly Distributed Load (UDL)" << endl;
	cout << "Loading Type (3)  - Triangular Ascending Load (TAL)" << endl;
	
	cout << "Please choose preferred Load Type(Integer): ";
	cin >> y;
	
	system("CLS");
	
	switch(y)
	{
		case 1:
			menu1(length,b,h,e,inertia);
			cout << "Please input the distance of the Concentrated Load from point A (meters): ";
			cin >> d;
			cout << "Please input the load intensity (kN): ";
			cin >> f;
			
			//start of reactions
			
			moment = moment1(d, f);
			r2 = moment/length;
			r1 = f - r2;
			break;
			
		case 2:
			menu1(length,b,h,e,inertia);
			cout  << "Please input the distance of the UDL from point A (meters): ";
			cin   >> d;
			cout  << "Please input the span of the UDL (meters): ";
			cin   >> s;
			cout  << "Please input the UDL intensity (kN/m): ";
			cin   >> f;
			
			//start of reactions
			moment = moment2(d, s, f);
			r2 = moment/length;
			r1 = (f*s) - r2;
			//end of reactions
			d2 = length-d-s; 
			break;
			
		case 3:
			menu1(length,b,h,e,inertia);
			cout << "Please input the distance of the TAL from point A (meters): ";
			cin >> d;
			cout << "Please input the span of the TAL (meters): ";
			cin >> s;
			cout << "Please input the TAL intensity (kN/m): ";
			cin >> f;
			
			//start of reactions
			moment = moment3(d, s, f);
			r2 = moment/length;
			r1 = (f*s/2) - r2;
			//end of reactions
			break;		
	}
	
	system("CLS");
	while(!next)
	{
	menu2(z);
	switch(z)
	{
		case 1:		//start of case 1
            cout << "The reaction for point A is: " << r1 << " kN." << endl;
			cout << "The reaction for point B is: " << r2 << " kN." << endl;
            break;
        			//end of case 1
		case 2:		//start of case 2
			switch(y)
			{
				case 1: //concentrated load shear
					for(x=0;x<=length;x++)
                  	{
                        if(x<d)
                        {
                            shear1 = Cshear1(r1);
                            cout<<"at dist. "<<x<<"\t"<<shear1<<endl;
                        }
                        else if(x>=d && x!=length)
                        {
                            shear2 = Cshear2(r1,f);
                            cout<<"at dist. "<<x<<"\t"<<shear2<<endl;
                        }
                        else if(x==length)
                        {
                            shear3 = Cshear3(r1,r2,f);
                            cout<<"at dist. "<<x<<"\t"<<shear3<<endl;
                        }
                    }
                    break;
                    
                case 2: //UDL shear
                	for(x=0;x<=length;x++)
                    	{
                    		if(x<d)
                    		{
                    			shear1 = Ushear1(r1);
                    			cout << "At Distance " << x << "m" << '\t' << shear1 << endl; 
							}
							else if(x>=d && x!=length)
							{
								if(x<=s+d)
								{
								shear2 = Ushear2(r1,x,d,f);
								cout << "At Distance " << x << "m" << '\t' << shear2 << endl;
								}
								else if(x>s+d)
								{
								//shear2 = shear2;
								cout << "At Distance " << x << "m" << '\t' << shear2 << endl;
								}
							}
							else if(x==length)
							{
								shear3 = Ushear3(r1,r2,f,s);
								cout << "At Distance " << x << "m" << '\t' << shear3 << endl;
							}
						}
                	break;
                	
                case 3: // TAL shear
                	for(x=0;x<=length;x++)
                    	{
                    		if(x<d)
                    		{
                    			shear1 = Tshear1(r1);
                    			cout << "At Distance " << x << "m" << '\t' << shear1 << endl; 
							}
							else if(x>=d && x!=length)
							{
								if(x<=s+d)
								{
									shear2 = Tshear2(r1,x,d,f);
									cout << "At Distance " << x << "m" << '\t' << shear2 << endl;
								}
								else if(x>s+d)
								{
									cout << "At Distance " << x << "m" << '\t' << shear2 << endl;
								}
							}
							else if(x==length)
							{
								shear3 = Tshear3(r1,r2,f,s);
								cout << "At Distance " << x << "m" << '\t' << shear3 << endl;
							}
						}	
                	break;
			}
			break;
					//end of case 2
		case 3:		//start of case 3
			switch(y)
			{
				case 1:
					moment = moment1(d,f);
                    cout << "The maximum moment for the specified Concentrated Load is = " << moment << " kN-m" << endl;
                    break;
                    
                case 2:
                	moment = moment2(d,s,f);
                    cout << "The maximum moment for the specified UDL is = " << moment << " kN-m" << endl;
                    break;
                    
                case 3:
                	moment = moment3(d,s,f);
                    cout << "The maximum moment for the specified TAL is = " << moment << " kN-m" << endl;
                    break;
			}
			break;
					//end of case 3
					
		case 4: 	//start of case 4
			switch(y)
			{
				case 1:
					inertia = (b*pow(h,3))/12;
                    l = cdeflection(f, d2, length, inertia, e);
                    cout << "The maximum deflection for the specified Concentrated Load is = " << l << " meters" << endl;
                    break;
                    
                case 2:
                	inertia = (b*pow(h,3))/12;
					k = udl(f, s, inertia, e);
                    cout << "The maximum deflection for the specified UDL is = " << k << " meters" << endl;
                    break;
                    
                case 3:
                	m = tal(f, s, e, inertia);
                    cout << "The maximum deflection for the specified TAL is = " << m << " meters" << endl;
                    break;
			}
			break;	//end of case 4 
	}
	
	cout<<"Would you like to go back?"<<endl;
	cout<<"(1)Back \t(2)End"<<endl;
	cin>>w;
	switch(w)
	{
		case 1:
			system("CLS");
			break;
		case 2:
			next = true;
			break;
	}
	}
	
}
