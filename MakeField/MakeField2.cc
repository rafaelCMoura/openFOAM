# include <iostream>

using namespace std;

int main()
{
int npx(20), npy(60), npz(20);

cout<<"/*--------------------------------*- C++ -*----------------------------------*\\"<<endl;
cout<<"| ========                 |                                                 |"<<endl;
cout<<"| \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |"<<endl;
cout<<"|  \\    /   O peration     | Version:  1.6                                   |"<<endl;
cout<<"|   \\  /    A nd           | Web:      http://www.OpenFOAM.org               |"<<endl;
cout<<"|    \\/     M anipulation  |                                                 |"<<endl;
cout<<"\\*---------------------------------------------------------------------------*/"<<endl;
cout<<endl;
cout<<"FoamFile"<<endl;
cout<<"{"<<endl;
cout<<"    version     2.0;"<<endl;
cout<<"    format      ascii;"<<endl;
cout<<"    class       volScalarField;"<<endl;
cout<<"    object      f;"<<endl;
cout<<"}"<<endl;
cout<<"// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //"<<endl;
cout<<endl;
cout<<"dimensions      [0 0 0 0 0 0 0];"<<endl;
cout<<endl;
cout<<"internalField   nonuniform List<scalar>"<<endl;
cout<<npx*npy*npz<<endl;
cout<<"("<<endl;
for(int i(0);i<npx;i++)
{
	for(int j(0);j<npy;j++)
	{
		for(int k(0);k<npz;k++)
		{
			if ((i>5)&&(i<15)&&(j>5)&&(j<15)&&(k>5)&&(k<15)){
			cout<<1<<endl;
			}
			else
			{
			cout<<0<<endl;
			}
		}
	}
}
cout<<");"<<endl<<endl;
cout<<"// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //"<<endl;

return 0;
}
