Info<< "Reading field f\n" << endl;

volScalarField f
(
	IOobject
	(
		"f",
		runTime.timeName(),
		mesh,
		IOobject::MUST_READ,
		IOobject::AUTO_WRITE
	),
	mesh
);

Info<< "Reading field U\n" << endl;

volVectorField U
(
	IOobject
	(
		"U",
		runTime.constant(),
		mesh,
		IOobject::MUST_READ,
		IOobject::NO_WRITE
	),
	mesh
);


