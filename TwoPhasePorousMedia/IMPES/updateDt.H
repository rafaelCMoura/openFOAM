DtData << runTime.deltaT().value() << endl;
MaxDS = max(mag(sw-sw.prevIter()));   // maximun absolute value
Dt = (DSmax/MaxDS)*runTime.deltaT().value();
//dt = 2*(Norm/(Norm+Ds)*dt), if dt>Norm dt=Norm/2?
//Dt = ( Dt.value() > 1.25*runTime.deltaT().value() ) ? 0.75*runTime.deltaT().value() : Dt;
//Dt = ( Dt.value() < 0.75*runTime.deltaT().value() ) ? 1.25*runTime.deltaT().value() : Dt;
runTime.setDeltaT(runTime.deltaT().value() + DtOpt.value()*Dt);
Info<<nl<<"NewDeltaT = "<<runTime.deltaT().value()<<nl<<endl;
