#define _USE_MATH_DEFINES
#include <windows.h>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Buffer.H>


// #include "form.h"

// #include "frame.h"
#include "PanelView.h"
#include "PVCreativityUI.h"

#include <cmath>
#include "irradiance_fp.h"
#include "panel_geometry_fp.h"
#include "panel_pv_fp.h"
#include "sun_fp.h"




double compute_absorbed_radiation_S(
	int N, // giorno dell'anno
	int minutes, //minuti
	double L=35, // = 35, //Latitute degrees
	double beta = 30, // = 30, //tilt/slope paneldegrees
	double Z_S = 0, // inclinazione pannello tra est/ovest
	double n_refraction_index = 1.526, // n_refraction_index = 1.526;
	double L_T = 0.002, // Spessore pannello in m 0.002
	double K=4, //Coefficiente di estinzione del sistema fotovoltaico (di solito = 4), 
	double G_B=715, // = 715 // W/m^2
	int printToBuffer = 0
);



PanelView   *scene;
Fl_Text_Buffer* resultsBuffer;

//-------------------------------------------------------------------------------------------------
void idle_cb(void*)
{
  scene->redraw();    
}
//-------------------------------------------------------------------------------------------------
int main(int argc, char **argv) {
	// compute_absorbed_radiation_S();
	

	PVCreativityUI* w = new PVCreativityUI();
	scene = w->panel;
	
	resultsBuffer = new Fl_Text_Buffer();
	w->results->buffer(resultsBuffer);

	w->show(argc, argv);

	/*
	resultsBuffer->text("line 0\nline 1\nline 2\n"
		"line 3\nline 4\nline 5\n"
		"line 6\nline 7\nline 8\n"
		"line 9\nline 10\nline 11\n"
		"line 12\nline 13\nline 14\n"
		"line 15\nline 16\nline 17\n"
		"line 18\nline 19\nline 20\n"
		"line 21\nline 22\nline 23\n");
		*/
	Fl::add_idle(idle_cb, 0);
	Fl::run();
	return 0;
}
//-------------------------------------------------------------------------------------------------


#include <FL/Fl_Text_Buffer.H>
extern Fl_Text_Buffer* resultsBuffer;


double compute_absorbed_radiation_S(
	int N, // giorno dell'anno
	int minutes, //minuti
	double L, // = 35, //Latitute degrees
	double beta, // = 30, //tilt/slope paneldegrees
	double Z_S, // inclinazione pannello tra est/ovest
	double n_refraction_index, // n_refraction_index = 1.526;
	double L_T, // Spessore pannello in m 0.002
	double K, //Coefficiente di estinzione del sistema fotovoltaico (di solito = 4), 
	// double delta, // = 23.09, //Degrees sole
	double G_B, // = 715 // W/m^2
	int printToBuffer
) {
	/*
	double L = 35; //Latitute degrees
	double beta = 30; //tilt/slope paneldegrees
	double delta = 23.09; //Degrees sole
	double G_B = 715; // W/m^2
	* /


	//double K = 4; // m^-1
	//double thickness = 0.002; // m la chiama L

	//double delta_rad = delta * M_PI / 180;
	*/

	//Monocristallino Tabella pg. 514
	double alpha_0 = 0.935823;
	double alpha_1 = 0.054289;
	double alpha_2 = -0.008677;
	double alpha_3 = 0.000527;
	double alpha_4 = -0.000011;


	double delta = compute_delta(N); //Eq. 1n
	double h = compute_h(minutes); //Eq. 2n

	double L_rad = L * M_PI / 180;
	double cos_Phi = compute_cos_Phi(L_rad, delta, h); //Eq. 3n

	double beta_rad = beta * M_PI / 180;
	double Z_S_rad = Z_S * M_PI / 180;

	double cos_theta = compute_cos_theta(L_rad, beta_rad, 
		Z_S_rad, delta, h); //Eq. 4
	double theta = acos(cos_theta);

	double R_B = compute_R_B(cos_theta, cos_Phi); //Eq. 5n
	double m = compute_m(cos_Phi); //Eq. 6n

	double M = compute_M(m, alpha_0, alpha_1, 
		alpha_2, alpha_3, alpha_4); //Eq. 7n

	double theta_r = compute_theta_r(theta, n_refraction_index); //Eq. 8n

	double taualpha_B = compute_taualpha_B(K, L_T, 
		theta_r, theta); //Eq. 9n

	double taualpha_n = compute_taualpha_n(K, L_T, 
		n_refraction_index); //Eq. 10n

	double K_theta_B = compute_K_theta_B(taualpha_B, taualpha_n); //Eq. 11n

	double S = compute_S(taualpha_n, M, G_B, R_B, K_theta_B); //Eq. 12n

	std::cout << "TauAlpha_n: " << taualpha_n << std::endl
		<< "M: " << M << std::endl
		<< "G_B: " << G_B << std::endl
		<< "R_B: " << R_B << std::endl
		<< "K_theta_B: " << K_theta_B << std::endl
		<< "S: " << S << std::endl;

	char strbuffer[500];
	sprintf_s(strbuffer, 500, "Buffer: TauAlpha_n: %f\nM: %f\nG_B: %f\nR_B: %f\nK_theta_B: %f\nS: %f  [W/m^2]\n", taualpha_n, M, G_B, R_B, K_theta_B, S);
	if (printToBuffer) {
		resultsBuffer->text(strbuffer);
	}

	return S;

}
