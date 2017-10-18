forAll(lambda,cellI)
{
	for(int i(0);i<6;i++)
	{
		if(lambda[cellI][i]==0)
		{ 
			lambda[cellI][i] = 0; 
		}
		else
		{ 
			lambda[cellI][i] = 1/lambda[cellI][i]; 
		}
		
		if(lgama[cellI][i]==0)
		{ 
			lgama[cellI][i] = 0; 
		}
		else
		{ 
			lgama[cellI][i] = 1/lgama[cellI][i]; 
		}
	}
}

lambdaf = fvc::interpolate(lambda);
lgamaf = fvc::interpolate(lgama);


forAll(lambdaf,faceI)
{
	for(int i(0);i<6;i++)
	{
		if(lambdaf[faceI][i]==0)
		{ 
			lambdaf[faceI][i] = 0; 
		}
		else
		{ 
			lambdaf[faceI][i] = 1/lambdaf[faceI][i]; 
		}
		
		if(lgamaf[faceI][i]==0)
		{ 
			lgamaf[faceI][i] = 0; 
		}
		else
		{ 
			lgamaf[faceI][i] = 1/lgamaf[faceI][i]; 
		}
	}
}
