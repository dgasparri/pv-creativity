#include "../src/lib/sun_fp.h"


double deg_to_rad(double deg) {
    return deg/180 * 3.14;
}


void delta_rad() {
	const Int_t n = 365;
	Double_t x[n];
	Double_t y[n];
	

	int i;
	for (i=0;i<n;i++) {
        x[i] = i;
		//y[i] = pv_sun::cos_Phi(i+1,0,L_rad);
        y[i] = pv_sun::compute_delta_rad(i+1);
	}
	TGraph *gr1 = new TGraph(i,x,y);
	gr1->SetLineColor(2);
	gr1->SetLineWidth(4);
	gr1->SetMarkerColor(4);
	gr1->SetMarkerStyle(21);
	std::string title("Delta-rad");
	gr1->SetTitle(title.c_str());
	gr1->GetXaxis()->SetTitle("Giorno");
	gr1->GetYaxis()->SetTitle("delta(rad)");
	//gr->GetYaxis()->SetTitle("S [W]");
	gr1->Draw();

}

void cos_Phi( ) {
	const Int_t n = 365;
	Double_t x[n];
	Double_t y[n];
	double h_rad = 0;

	int i;
	double L_rad = 0 * M_PI /180; //Equatore
	for (i=0;i<n;i++) {
        double delta_rad = pv_sun::compute_delta_rad(i+1);
        x[i] = i;
		//y[i] = pv_sun::cos_Phi(i+1,0,L_rad);
        y[i] = pv_sun::compute_cos_Phi(L_rad, delta_rad, h_rad);
	}
	TGraph *gr1 = new TGraph(i,x,y);
	gr1->SetLineColor(2);
	gr1->SetLineWidth(4);
	gr1->SetMarkerColor(4);
	gr1->SetMarkerStyle(21);
	std::string title("Cos-Phi - Ore 12 - L45(black) L22(red) L35(blue)");
	gr1->SetTitle(title.c_str());
	gr1->GetXaxis()->SetTitle("Giorno");
	gr1->GetYaxis()->SetTitle("cos(Phi)");
	//gr->GetYaxis()->SetTitle("S [W]");
	gr1->Draw();




	/*
	L_rad = 35 * M_PI /180;
	for (i=0;i<n;i++) {
        double delta_rad = pv_sun::compute_delta_rad(i+1);
        x[i] = i;
		//y[i] = pv_sun::cos_Phi(i+1,0,L_rad);
        y[i] = pv_sun::compute_cos_Phi(L_rad, delta_rad, h_rad);
	}
	TGraph *gr2 = new TGraph(i,x,y);
	gr2->SetLineColor(3);
	gr2->SetLineWidth(4);
	gr2->SetMarkerColor(3);
	gr2->SetMarkerStyle(21);
	//gr->GetYaxis()->SetTitle("S [W]");
	gr2->Draw();


	L_rad = 22 * M_PI /180;
	for (i=0;i<n;i++) {
        double delta_rad = pv_sun::compute_delta_rad(i+1);
        x[i] = i;
		//y[i] = pv_sun::cos_Phi(i+1,0,L_rad);
        y[i] = pv_sun::compute_cos_Phi(L_rad, delta_rad, h_rad);
	}
	TGraph *gr3 = new TGraph(i,x,y);
	gr3->SetLineColor(6);
	gr3->SetLineWidth(4);
	gr3->SetMarkerColor(6);
	gr3->SetMarkerStyle(21);
	//gr->GetYaxis()->SetTitle("S [W]");
	gr3->Draw();
*/
}



