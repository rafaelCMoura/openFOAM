# include <iostream>

using namespace std;

int main()
{
int np(1.0e6);

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
cout<<"    object      u;"<<endl;
cout<<"}"<<endl;
cout<<"// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //"<<endl;
cout<<endl;
cout<<"dimensions      [0 0 0 0 0 0 0];"<<endl;
cout<<endl;
cout<<"internalField   nonuniform List"<<"<scalar>"<<endl;
cout<<np<<endl;
cout<<"("<<endl;
for(int i(0);i<npx;i++)
{
	for(int j(0);i<npy;i++)
	{
		for(int k(0);i<npz;i++)
		{
			if ((i>20)&&(i<40)&&(j>20)&&(j<40)&&(k>20)&&(k<40))
			cout<<1<<endl;
			else
			cout<<1<<endl;
		}
	}
}
cout<<");"<<endl<<endl;
cout<<"// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //"<<endl;

return 0;
}
