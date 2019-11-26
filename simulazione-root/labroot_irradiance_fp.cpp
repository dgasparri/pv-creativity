#include "../src/lib/irradiance_fp.h"

void cos_theta() {
	const Int_t n = 365;
	Double_t x[n];
	Double_t y[n];
	double h_rad = 0;

	int i;
	double L_rad = 0 * M_PI /180; //Equatore
    double beta_rad = 0 * M_PI /180; 
    double Z_S_rad = 0; 

	for (i=0;i<n;i++) {
        double delta_rad = pv_sun::compute_delta_rad(i+1);
        x[i] = i;
		//y[i] = pv_sun::cos_Phi(i+1,0,L_rad);
        y[i] = compute_cos_theta(
            L_rad, 
            beta_rad, 
            Z_S_rad, 
            delta_rad, 
            0 //double h_rad
            );
	}
	TGraph *gr1 = new TGraph(i,x,y);
	gr1->SetLineColor(2);
	gr1->SetLineWidth(4);
	gr1->SetMarkerColor(4);
	gr1->SetMarkerStyle(21);
	std::string title("Cos-Theta - Beta -30 h 0 Z_s 0");
	gr1->SetTitle(title.c_str());
	gr1->GetXaxis()->SetTitle("Giorno");
	gr1->GetYaxis()->SetTitle("cos(Phi)");
	//gr->GetYaxis()->SetTitle("S [W]");
	gr1->Draw();

    
}