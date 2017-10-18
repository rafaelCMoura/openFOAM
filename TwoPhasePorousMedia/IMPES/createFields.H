// Reading problem fields ------------------------------------------------------------------------------------------------- //
Info<< "Reading fields                     ";
volScalarField po    (IOobject ("po",   runTime.timeName(), mesh, IOobject::MUST_READ, IOobject::AUTO_WRITE), mesh);
volScalarField pw    (IOobject ("pw",   runTime.timeName(), mesh, IOobject::MUST_READ, IOobject::AUTO_WRITE), mesh);
volScalarField pc    (IOobject ("pc",   runTime.timeName(), mesh, IOobject::MUST_READ, IOobject::AUTO_WRITE), mesh);
volScalarField so    (IOobject ("so",   runTime.timeName(), mesh, IOobject::MUST_READ, IOobject::AUTO_WRITE), mesh);
volScalarField sw    (IOobject ("sw",   runTime.timeName(), mesh, IOobject::MUST_READ, IOobject::AUTO_WRITE), mesh);
volScalarField kr_w  (IOobject ("kr_w", runTime.timeName(), mesh, IOobject::MUST_READ, IOobject::AUTO_WRITE), mesh);
volScalarField kr_o  (IOobject ("kr_o", runTime.timeName(), mesh, IOobject::MUST_READ, IOobject::AUTO_WRITE), mesh);
surfaceScalarField phi_w (IOobject ("phi_w",runTime.timeName(), mesh, IOobject::MUST_READ, IOobject::AUTO_WRITE), mesh);
surfaceScalarField phi_o (IOobject ("phi_o",runTime.timeName(), mesh, IOobject::MUST_READ, IOobject::AUTO_WRITE), mesh);
volScalarField Vb    (IOobject ("Vb",   runTime.constant(), mesh, IOobject::MUST_READ, IOobject::AUTO_WRITE), mesh);
volTensorField K     (IOobject ("K",    runTime.constant(), mesh, IOobject::MUST_READ, IOobject::NO_WRITE), mesh);
volScalarField qo    (IOobject ("qo",   runTime.constant(), mesh, IOobject::MUST_READ, IOobject::NO_WRITE), mesh);
volScalarField qw    (IOobject ("qw",   runTime.constant(), mesh, IOobject::MUST_READ, IOobject::NO_WRITE), mesh);
volScalarField phi   (IOobject ("phi",  runTime.constant(), mesh, IOobject::MUST_READ, IOobject::NO_WRITE), mesh);
Info << "[  OK  ]" <<endl;
// Reading problem parameters --------------------------------------------------------------------------------------------- //
Info<< "Reading problem parameters         ";
IOdictionary params(IOobject("params",runTime.constant(),mesh,IOobject::MUST_READ,IOobject::NO_WRITE));
dimensionedScalar ALPHA_C       (params.lookup("ALPHA_C"));
dimensionedScalar BETA_C        (params.lookup("BETA_C"));
dimensionedScalar GAMA_C        (params.lookup("GAMA_C"));
dimensionedScalar mu_o          (params.lookup("mu_o"));
dimensionedScalar mu_w          (params.lookup("mu_w"));
dimensionedScalar rho_osc       (params.lookup("rho_osc"));
dimensionedScalar rho_wsc       (params.lookup("rho_wsc"));
dimensionedScalar G             (params.lookup("G"));
dimensionedScalar DtOpt         (params.lookup("DtOpt"));
dimensionedScalar DSmax         (params.lookup("DSmax"));
dimensionedScalar PrefW         (params.lookup("PrefW"));
dimensionedScalar PrefI       (params.lookup("PrefI"));
dimensionedScalar PrefP       (params.lookup("PrefP"));
//dimensionedVector refCellPoint  (params.lookup("refCellPoint"));
dimensionedScalar dz            (params.lookup("dz"));
Info << "[  OK  ]" <<endl;
// Creating splines ------------------------------------------------------------------------------------------------------ //
Info << "Creating tables                    ";
# include "createTables.H"
Info << "[  OK  ]" <<endl;
// Problem fields initialization ---------------------------------------------------------------------------------------- //
Info << "Initializating problem fields      ";
volScalarField fw = (kr_w/mu_w)/(kr_o/mu_o + kr_w/mu_w); 

dimensionedScalar Zmax ("Zmax", dimLength, 1.0 );
Zmax = max(mesh.C().component(2));
volScalarField Z = Zmax - mesh.C().component(2); //profundidadess

dimensionedScalar gama_o = GAMA_C*rho_osc*G;
dimensionedScalar gama_w = GAMA_C*rho_wsc*G;

pw = PrefW + gama_w*Z;
po = pw + pc;

//phi_w = fvc::grad(pw) - gama_w*fvc::grad(Z);
/*
forAll(K,cellI) // Geometrical dependent coeffs: harmonic interpolation
{
		K[cellI].xx()  = (K[cellI].xx() < 1.0e-4) ? 0 : 1/K[cellI].xx();
		K[cellI].yy()  = (K[cellI].yy() < 1.0e-4) ? 0 : 1/K[cellI].yy();
		K[cellI].zz()  = (K[cellI].zz() < 1.0e-4) ? 0 : 1/K[cellI].zz();
		Vb[cellI] = mesh.V()[cellI];    // Use it or mesh.cellVolumes()
}
// Warning: K will keep modified, if you want use K again make inverse process.
surfaceTensorField Kf = fvc::interpolate(K,"linear");
// Calculating reciprocal values of aritimetic average (the result is the harmonic average):
forAll(Kf,faceI)
{
		Kf[faceI].xx()  = (Kf[faceI].xx() < 1.0e-4) ? 0 : 1/Kf[faceI].xx();
		Kf[faceI].yy()  = (Kf[faceI].yy() < 1.0e-4) ? 0 : 1/Kf[faceI].yy();
		Kf[faceI].zz()  = (Kf[faceI].zz() < 1.0e-4) ? 0 : 1/Kf[faceI].zz();
}
*/
// Saturation dependent coeffs: upstream interpolation
surfaceScalarField kr_of = fvc::interpolate(kr_o); //only for initialization
surfaceScalarField kr_wf = fvc::interpolate(kr_w); //only for initialization
surfaceTensorField Kf = fvc::interpolate(K);
//scalar DPHI_w = 1;
//scalar DPHI_o = 1;

const unallocLabelList& own = mesh.owner();
const unallocLabelList& nei = mesh.neighbour();

forAll(kr_wf,faceI)
{
  //DPHI_w = (pw[own[faceI]]-pw[nei[faceI]]) - gama_w.value()*(Z[own[faceI]]-Z[nei[faceI]]);
  //DPHI_o = (po[own[faceI]]-po[nei[faceI]]) - gama_o.value()*(Z[own[faceI]]-Z[nei[faceI]]);

  //kr_of[faceI] = (DPHI_o > 0) ? kr_o[own[faceI]] : kr_o[nei[faceI]];
  //kr_wf[faceI] = (DPHI_w > 0) ? kr_w[own[faceI]] : kr_w[nei[faceI]];
  phi_w[faceI] = (pw[own[faceI]]-pw[nei[faceI]]) + gama_w.value()*(Z[own[faceI]]-Z[nei[faceI]]);
  phi_o[faceI] = (po[own[faceI]]-po[nei[faceI]]) + gama_o.value()*(Z[own[faceI]]-Z[nei[faceI]]);
  // Valido apenas para o campo K diagonal:
  if(K[own[faceI]].xx()*K[nei[faceI]].xx()==0){
    Kf[faceI].xx() = 0;
  }else{
    Kf[faceI].xx() = 2*K[own[faceI]].xx()*K[nei[faceI]].xx()/(K[own[faceI]].xx()+K[nei[faceI]].xx());
  }
  if(K[own[faceI]].yy()*K[nei[faceI]].yy()==0){
    Kf[faceI].yy() = 0;
  }else{
    Kf[faceI].yy() = 2*K[own[faceI]].yy()*K[nei[faceI]].yy()/(K[own[faceI]].yy()+K[nei[faceI]].yy());
  }
  if(K[own[faceI]].zz()*K[nei[faceI]].zz()==0){
    Kf[faceI].zz() = 0;
  }else{
    Kf[faceI].zz() = 2*K[own[faceI]].zz()*K[nei[faceI]].zz()/(K[own[faceI]].zz()+K[nei[faceI]].zz());
  }
}
Info << "[  OK  ]" <<endl;
// Internal boudary conditions ---------------------------------------------------------------------------------------------------- //
Info << "Setting sources                    ";
# include "sourceTerms.H"
//dimensionedScalar Pref ("Pref", po.dimensions(), po[refCell1] );
Info << "[  OK  ]" <<endl;
// Equations coefficients --------------------------------------------------------------------------------------------------------- //
Info << "Calculationg equation coefficients ";
volScalarField Q  = (qo + qw)/(BETA_C*Vb);
volScalarField Qw = qw/(BETA_C*Vb);
volScalarField ac = phi/(ALPHA_C*BETA_C);

surfaceTensorField Tpof  = Kf*(kr_of/mu_o + kr_wf/mu_w);
surfaceTensorField Tpcf  = Kf*(kr_wf/mu_w);
surfaceTensorField Tpzf  = Kf*((kr_of/mu_o)*gama_o + (kr_wf/mu_w)*gama_w);
surfaceTensorField Tszf  = Kf*(kr_wf/mu_w)*gama_w;
Info << "[  OK  ]" <<endl;
// Creating OFstream Files ---------------------------------------------------------------------------------------------------------------- //
fileName DtFile(runTime.path()/"Dt.dat");
OFstream DtData(DtFile);
fileName ImbFile(runTime.path()/"Imb.dat");
OFstream ImbData(ImbFile);
fileName CmbFile(runTime.path()/"Cmb.dat");
OFstream CmbData(CmbFile);

dimensionedScalar MaxDS = 1; // Any value, unused at the first time step
dimensionedScalar Dt = 1;    // Any value, unused at the first time step
// Material Balance Check ---------------------------------------------------------------------------------------------------------- //
dimensionedScalar Imb ("Imb", phi.dimensions(), 1.0 ); // Incremental material-balance
dimensionedScalar Cmb ("Cmb", phi.dimensions(), 1.0 ); // Cumulative material-balance
volScalarField sw_ini = sw;
// --------------------------------------------------------------------------------------------------------------------------------- //
