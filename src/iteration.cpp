#include "iteration.h"



/*
pv_sun::position_in_sky
* cos_Phi (Zenith)
* alpha_rad (Altitude)
* h_rad (not yet)
* delta_rad
* cos_Phi
* m
* valid

*/
pv_sun::position_in_sky* iteration::sun_position_matrix(double L_rad, int day_start, int day_end, int minutes_start, int minutes_in_step, int n_steps)
{
    int day, int min;
    //Da implementare il for
    pv_sun::position_in_sky *pos = pv_sun::sun(day, min, L_rad);
}

/*
struct triangle {
        const beta_rad mbeta_rad;
        const Z_S_rad mZ_S_rad;
        const m_squared marea;
        const plane_normal_vector mplane_normal;
*/
geometry::triangle* iteration::panel_triangle_array()
{
    //Non usiamo i vettori!! A meno che non capiamo come cavolo si passano
    std::vector<geometry::triangle> triangles;
	triangles.reserve(vertices.size() / 3 + 1);
	//Checks for 3 available vertices
	for (int i = 0; i+2 < vertices.size(); i+=3) {
		triangles.emplace_back(geometry::triangle(*vertices[i], *vertices[i + 1], *vertices[i + 2]));
		geometry::plane pl = geometry::fplane(*vertices[i], *vertices[i + 1], *vertices[i + 2]);
		std::cout<<"Piano: "<<pl<<std::endl;
	}
	for (geometry::triangle t : triangles) {
		std::cout << "Triangolo beta: " << t.mbeta_rad << " Z_S: " << t.mZ_S_rad << " area: " << t.marea << std::endl;
	}

}



double iteration::S_thread()
{

	//Ci manca della roba!!!
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

	return S;

}
