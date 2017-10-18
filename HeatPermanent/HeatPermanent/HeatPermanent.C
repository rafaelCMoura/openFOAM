# include "fvCFD.H"


int main(int argc, char *argv[])
{

# include "setRootCase.H"
# include "createTime.H"
# include "createMesh.H"
# include "createFields.H"

Info<< "\nStarting time loop\n" << endl;
Info << "Time = " << runTime.value() << endl;

solve(fvm::laplacian(T) == Q);	// Solving the Heat problem

runTime.write();
Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
    << "  ClockTime = " << runTime.elapsedClockTime() << " s"
    << nl << endl;

T.write();			// Writing the field values

    
return 0;
}
