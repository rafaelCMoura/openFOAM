Info<< "Reading field p\n" << endl;

volScalarField p
(
	IOobject
	(
		"p",
		runTime.timeName(),
		mesh,
		IOobject::MUST_READ,
		IOobject::AUTO_WRITE
	),
	mesh
);

Info<< "Reading field q\n" << endl;

volScalarField q
(
	IOobject
	(
		"q",
		runTime.constant(),
		mesh,
		IOobject::MUST_READ,
		IOobject::NO_WRITE
	),
	mesh
);

Info<< "Reading field K\n" << endl;

volTensorField K
(
	IOobject
	(
		"K",
		runTime.constant(),
		mesh,
		IOobject::MUST_READ,
		IOobject::NO_WRITE
	),
	mesh
);

Info<< "Reading field phi_ref\n" << endl;

volScalarField phi_ref
(
	IOobject
	(
		"phi_ref",
		runTime.constant(),
		mesh,
		IOobject::MUST_READ,
		IOobject::NO_WRITE
	),
	mesh
);

Info<< "Reading transportProperties\n" << endl;

IOdictionary transportProperties
(
	IOobject
	(
		"transportProperties",
		runTime.constant(),
		mesh,
		IOobject::MUST_READ,
		IOobject::NO_WRITE
	)
);

Info<< "Reading Well Perforations\n" << endl;

IOdictionary wellPerforations
(
	IOobject
	(
		"wellPerforations",
		runTime.constant(),
		mesh,
		IOobject::MUST_READ,
		IOobject::NO_WRITE
	)
);

Info<< "Reading field Z\n" << endl;

volScalarField Z = max(mesh.C().component(2)) - mesh.C().component(2);

dimensionedScalar ALPHA_C (transportProperties.lookup("ALPHA_C"));
dimensionedScalar BETA_C  (transportProperties.lookup("BETA_C"));
dimensionedScalar GAMA_C  (transportProperties.lookup("GAMA_C"));
dimensionedScalar c_r     (transportProperties.lookup("c_r"));
dimensionedScalar c_f     (transportProperties.lookup("c_f"));
dimensionedScalar B_ref   (transportProperties.lookup("B_ref"));
dimensionedScalar mu_ref  (transportProperties.lookup("mu_ref"));
dimensionedScalar G       (transportProperties.lookup("G"));
dimensionedScalar Pref    (transportProperties.lookup("Pref"));
dimensionedScalar rho_sc  (transportProperties.lookup("rho_sc"));
dimensionedScalar rho_ref (transportProperties.lookup("rho_ref"));
dimensionedScalar q_in    (transportProperties.lookup("q_in"));
dimensionedScalar P_out   (transportProperties.lookup("P_out"));

// unit change factors:
dimensionedScalar p_unit ("p_unit", p.dimensions(), 1.0);
dimensionedScalar tol = 1.0e-4;
dimensionedScalar r = 2*tol;
// ------------------------------- Setting flow fields ------------------------------ //
p = Pref + rho_ref*G*Z;
volScalarField p_old = p;

volScalarField phi = phi_ref*(1 + c_f*(p-Pref));
volScalarField rho = rho_ref*(1 + c_f*(p-Pref));

// Equilibrio de pressões/deformações rocha sistema
while(r>tol)
{
	p = Pref + rho*G*Z;
	rho = rho_ref*(1 + c_f*(p-Pref));
	r = max(mag(p-p_old))/p_unit;
	p_old = p;
}
// Calculo da porosidade com as pressões de equilíbrio :)
phi = phi_ref*(1 + c_r*(p-Pref));

volScalarField B = (B_ref*rho_ref)/rho;
volTensorField lambda = BETA_C*K/(mu_ref*B);
volTensorField lgama = lambda*GAMA_C*rho*G;
volScalarField C1 = (phi*c_f/B_ref + phi_ref*c_r/B)/ALPHA_C;


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

surfaceTensorField lambdaf = fvc::interpolate(lambda);
surfaceTensorField lgamaf = fvc::interpolate(lgama);

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

// ------------------------------------------------------------------------------------- //
