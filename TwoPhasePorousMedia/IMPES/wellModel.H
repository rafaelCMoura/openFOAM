/*// Using Peacema's model to get wellBlock reference pressure:
dimensionedScalar kRadial_xx ("kRadial_xx", dimLength*dimLength, sqrt(K[refCell].yy()*K[refCell].zz()) ); //kRadial_xx
dimensionedScalar kRadial_yy ("kRadial_yy", dimLength*dimLength, sqrt(K[refCell].xx()*K[refCell].zz()) ); //kRadial_yy
dimensionedScalar kRadial_zz ("kRadial_zz", dimLength*dimLength, sqrt(K[refCell].xx()*K[refCell].yy()) ); //kRadial_zz

dimensionedScalar kRadial ("kradial", dimLength*dimLength, 1.0 ); // Any value, only for initalization
kRadial = (sin(teta_yz)+sin(teta_xz))*kRadial_zz + cos(teta_yz)*kRadial_yy + cos(teta_xz)*kRadial_xx
//scalar re = ;
// -------------------- input this on updatefields
scalar s = 0; // define in params file
scalar rw = 1;// define in params file
scaler h = dz ? or h? espessure of reservoir? from profiles?
//scalar IPw = BETA_C*kr_w[refCell]*kRadial*h/(mu_w*(ln(re/rw) + s)); //Confirm this equation!
//scalar IPo = BETA_C*kr_o[refCell]*kRadial*h/(mu_o*(ln(re/rw) + s));
scalar IP = IPw + IPo;

scalar refCellValue = pwf - Q[refCell]/IP;//Q é constante! IP(Sw)  varia!

*/
