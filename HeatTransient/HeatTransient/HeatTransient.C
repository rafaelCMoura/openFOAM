#include "fvCFD.H"

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
	T.storePrevIter();
	{
		solve(fvm::laplacian(T) == (1/alpha)*fvm::ddt(T));
	}
	runTime.write();
	Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
	<< "  ClockTime = " << runTime.elapsedClockTime() << " s"
	<< nl << endl;
}

Info<< "End\n" << endl;

return 0;
}
