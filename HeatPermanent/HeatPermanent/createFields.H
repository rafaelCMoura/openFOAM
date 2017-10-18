Info<< "Reading field T\n" << endl;

volScalarField T
(
	IOobject
	(
		"T",
		runTime.constant(),
		mesh,
		IOobject::MUST_READ,
		IOobject::AUTO_WRITE
	),
	mesh
);

Info<< "Reading field Q\n" << endl;

volScalarField Q
(
	IOobject
	(
		"Q",
		runTime.constant(),
		mesh,
		IOobject::MUST_READ,
		IOobject::NO_WRITE
	),
	mesh
);
