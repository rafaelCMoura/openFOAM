#include "fvCFD.H"

int main(int argc, char *argv[])
{

#   include "setRootCase.H"
#   include "createTime.H"
#   include "createMesh.H"
#   include "createFields.H"


Info<<"Runnig Aplication on: "<<runTime.path()/"constant"<<endl;
int count;
Info<< "\nStarting time loop\n" << endl;

for (runTime++; !runTime.end(); runTime++)
{
	Info<< "Time = " << runTime.timeName() << nl << endl;
	p.storePrevIter();

	tol = 1.0e-4;
	r = 2*tol;
	count = 1;
	while(r>tol)
	{
		Info<< endl << "Solving pressure equation at step "<< count << endl;
		fvScalarMatrix pEqn
		(
			fvm::laplacian(lambdaf,p) 
			- fvc::laplacian(lgamaf,Z) 
			== 
			C1*fvm::ddt(p) 
			- q
		);
		//#include "printFields.H"
		pEqn.solve();
        
		#include "updateFields.H"
		#include "harmonicInterp.H"
		
        r = max(mag(p-p_old))/p_unit;
		p_old = p;
		count += 1;
	}

	runTime.write();
	Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
	<< "  ClockTime = " << runTime.elapsedClockTime() << " s"
	<< nl << endl;
}

Info<< "End\n" << endl;

return 0;
}
