double deg_to_rad(double deg) {
    return deg/180 * 3.14;
}
double compute_cos_Phi(double L_rad, double delta_rad, double h) {
	return (sin(L_rad) * sin(delta_rad)) + (cos(L_rad) * cos(delta_rad) * cos(h));
}

void cos_p(TCanvas *c1, double L_rad) {
	const Int_t n = 365;
	Double_t x[n];
	Double_t y[n];
	double h_rad = pv_sun::compute_h_rad(0);

	int i;
	for (i=0;i<n;i++) {
        double delta_rad = pv_sun::compute_delta_rad(i+1);
        x[i] = i;
		//y[i] = pv_sun::cos_Phi(i+1,0,L_rad);
        y[i] = compute_cos_Phi(L_rad, delta_rad, h_rad);
	}
	TGraph *gr1 = new TGraph(i,x,y);
	gr1->SetLineColor(2);
	gr1->SetLineWidth(4);
	gr1->SetMarkerColor(4);
	gr1->SetMarkerStyle(21);
	std::string title("Cos-Phi calcolato");
	gr1->SetTitle(title.c_str());
	gr1->GetXaxis()->SetTitle("Giorno");
	gr1->GetYaxis()->SetTitle("cos(Phi)");
	//gr->GetYaxis()->SetTitle("S [W]");
	gr1->Draw();
}



