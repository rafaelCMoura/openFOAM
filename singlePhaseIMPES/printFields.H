Info<<"-------------------- Fields --------------------"<< endl << endl
    <<"Field p:"<<endl<<p<<endl
    <<"Field K:"<<endl<<K<<endl
    <<"Field rho:"<<endl<<rho<<endl
    <<"Field Z:"<<endl<<Z<<endl
    <<"Field phi:"<<endl<<phi<<endl
    <<"------------------ Equation Coeffs -------------"<< endl << endl
    <<"Field lambda:"<<endl<<lambda<<endl
    <<"Field lgama:"<<endl<<lgama<<endl
    <<"Field lambdaf:"<<endl<<lambdaf<<endl
    <<"Field lgamaf:"<<endl<<lgamaf<<endl
    <<"Field C1:"<<endl<<C1<<endl
    <<"Field q:"<<endl<<q<<endl
    <<"------------------- fvMatrix -------------------"<< endl << endl
//Info<<endl<<pEqn<<endl; // See .../src/finiteVolume/fvMatrices/fvMatrix/fvMatrix.C at EOF
    <<"pEqn:"<< endl
    << static_cast<const lduMatrix&>(pEqn) << nl // See ../src/OpenFOAM/matrices/lduMatrix/lduMatrix/lduMatrix.C at EOF
    <<"Dimensions:"<< endl
    << pEqn.dimensions_ << nl
    <<"Souce font terms:"<< endl
    << pEqn.source_ << nl
    <<"Internal Coeffs:"<< endl
    << pEqn.internalCoeffs_ << nl
    <<"Boundary Coeffs:"<< endl
    << pEqn.boundaryCoeffs_ << endl;