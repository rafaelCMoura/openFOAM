fileName KrFile(runTime.path()/runTime.constant()/"splineData"/"Kr.dat");
fileName PcFile(runTime.path()/runTime.constant()/"splineData"/"Pc.dat");

IFstream dataKr(KrFile), dataPc(PcFile);

// Reading relative permeability file:
int npKr;
dataKr >> npKr;

double *swVec  = new double [npKr];
double *kroVec = new double [npKr];
double *krwVec = new double [npKr];

for(int i(0);i<npKr;i++)
dataKr >> swVec[i];
for(int i(0);i<npKr;i++)
dataKr >> kroVec[i];
for(int i(0);i<npKr;i++)
dataKr >> krwVec[i];


// Reading capilar pressure file:
int npPc;
dataPc >> npPc;

double *swPcVec  = new double [npPc];
double *PcVec    = new double [npPc];

for(int i(0);i<npPc;i++)
dataPc >> swPcVec[i];
for(int i(0);i<npPc;i++)
dataPc >> PcVec[i];

// Creating spline second derivative aproximation:
double xbcbeg(0), fbcbeg(0), xbcend(0), fbcend(0), *d2krw, * d2kro, *d2Pc;

d2kro = spline_cubic_set ( npKr, swVec, kroVec, xbcbeg, fbcbeg, xbcend, fbcend );
d2krw = spline_cubic_set ( npKr, swVec, krwVec, xbcbeg, fbcbeg, xbcend, fbcend );
d2Pc  = spline_cubic_set ( npPc, swPcVec, PcVec, xbcbeg, fbcbeg, xbcend, fbcend );

// Creating variables to store outputs from spline_cubic_val:
double krw_pval, krw_ppval, kro_pval, kro_ppval, Pc_pval, Pc_ppval;

forAll(sw,cellI)
{
  kr_o[cellI] = spline_cubic_val ( npKr, swVec, sw[cellI], kroVec, d2kro, &kro_pval, &kro_ppval );
  kr_w[cellI] = spline_cubic_val ( npKr, swVec, sw[cellI], krwVec, d2krw, &krw_pval, &krw_ppval );
  pc[cellI] = spline_cubic_val ( npPc, swPcVec, sw[cellI], PcVec, d2Pc, &Pc_pval, &Pc_ppval );
}

scalarField swVecData(npKr);
scalarField swPcVecData(npPc);

scalarField kroVecData(swVecData.size());
scalarField krwVecData(swVecData.size());
scalarField PcVecData(swPcVecData.size());

for(int i(0);i<npKr;i++)
{
  swVecData[i] = swVec[i];
  kroVecData[i] = kroVec[i];
  krwVecData[i] = krwVec[i];
}

for(int i(0);i<npPc;i++)
{
  swPcVecData[i] = swPcVec[i];
  PcVecData[i] = PcVec[i];
}

graph krGraph ("Curvas de Permeabilidade Relativa", "Sw", "kro", swVecData,  kroVecData);
krGraph.insert("krw", new curve("krw", curve::curveStyle::CONTINUOUS, krwVecData) );
krGraph.write ("kr", "xmgr");

graph("Pressao Capilar", "Sw", "Pc", swPcVecData,  PcVecData).write("Pc", "xmgr");
