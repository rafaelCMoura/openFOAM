#include "fvCFD.H"
#include "IFstream.H"
#include "OFstream.H"
#include "spline.H"
#include "graph.H"

int main(int argc, char *argv[])
{  
#   include "setRootCase.H"
#   include "createTime.H"
#   include "createMesh.H"
#   include "createFields.H"

Info<< "\nStarting time loop\n" << endl;
for (runTime++; !runTime.end(); runTime++)
{
  Info<< "Time = " << runTime.timeName() << nl << endl;

  # include "storeFields.H"
  // --------------------------------------------------- BEGIN IMPES STEP //
  // Implicit pressure step --------------------------------------------- //
  Info << "Solving Pressure Equation" << endl;
  fvScalarMatrix poEqn
  (
    fvm::laplacian(Tpof,po)
    ==
    fvc::laplacian(Tpcf,pc)
    + fvc::laplacian(Tpzf,Z)
    - Q
  );
  poEqn.setReference(refCell1, PrefP.value(),1); //
  //poEqn.setReference(refCell2, PrefI.value(),1);
  poEqn.solve();
  // Explicit saturation step ------------------------------------------- //  
  Info << "Solving Saturation Equation" << endl;
  fvScalarMatrix swEqn
  (
    ac*fvm::ddt(sw) == 
    fvc::laplacian(Tpcf,po)
    - fvc::laplacian(Tpcf,pc)
    - fvc::laplacian(Tszf,Z)
    + Qw
  );
  swEqn.solve();
  // ------------------------------------------------------ END IMPES STEP //
  
  // Updating all field values 
  # include "updateFields.H"
  // Material balance check 
  Imb = sum((Vb*phi/ALPHA_C)*(sw-sw.prevIter()))/(runTime.deltaT()*sum(qw));
  Info << nl << "Imb = " << Imb.value() << nl << endl;
  Cmb = sum((Vb*phi/ALPHA_C)*(sw-sw_ini))/(runTime.time()*sum(qw));
  Info << nl << "Cmb = " << Cmb.value() << nl << endl;
  ImbData << Imb.value() << endl;
  CmbData << Cmb.value() << endl;
  // Automatic Timestep Selection:
  # include "updateDt.H"

  runTime.write();
  Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
  << "  ClockTime = " << runTime.elapsedClockTime() << " s"
  << nl << endl;
}
#   include "deleteTables.H"
Info<< "End\n" << endl;

return 0;
}
