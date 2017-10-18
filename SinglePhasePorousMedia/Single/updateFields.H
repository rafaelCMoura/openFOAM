// Updating fields:
rho = rho_ref*(1 + c_f*(p-Pref));
phi = phi_ref*(1 + c_r*(p-Pref));
B = (B_ref*rho_ref)/rho;

// Recalculating coeffs:
lambda = BETA_C*K/(mu_ref*B);
lgama = lambda*GAMA_C*rho*G;
C1 = (phi*c_f/B_ref + phi_ref*c_r/B)/ALPHA_C;

