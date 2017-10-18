double *d3_np_fs ( int n, double a[], double b[] );
double *spline_cubic_set ( int n, double t[], double y[], int ibcbeg, double ybcbeg, 
  int ibcend, double ybcend );
double spline_cubic_val ( int n, double t[], double tval, double y[], double ypp[],
  double *ypval, double *yppval );