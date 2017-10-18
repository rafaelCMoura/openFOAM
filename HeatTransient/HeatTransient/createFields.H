Info<< "Reading field T\n" << endl;

volScalarField T
(
	IOobject
	(
		"T",
		runTime.timeName(),
		mesh,
		IOobject::MUST_READ,
		IOobject::AUTO_WRITE
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

Info<< "Reading field alpha\n" << endl;

volScalarField alpha
(
	IOobject
	(
		"alpha",
		runTime.constant(),
		mesh,
		IOobject::MUST_READ,
		IOobject::NO_WRITE
	),
	mesh
);