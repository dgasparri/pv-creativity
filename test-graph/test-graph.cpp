#define _USE_MATH_DEFINES
#include <cmath> 

#include <algorithm>
#include <iostream>
#include <fstream>

#include "../src/config.h"
#include "../src/lib/sun_fp.h"
#include "../src/lib/panel_irradiance.h"


class pvcl_state_class {
public:
	double L;
	double L_rad;
	double lon;
	int day;
	int hour;
	int min;
	int h;
	double h_rad;
	double beta;
	double beta_rad;
	double Z_s;
	double Z_s_rad;
	double area;
	double n_refraction_index;
	double thickness;
	double K;
	double a0 = 0.918093;
	double a1 = 0.086257;
	double a2 = -0.024459;
	double a3 = 0.002816;
	double a4 = -0.000126;

};

void settime(pvcl_state_class &pvstate, int hour, int min) {
	pvstate.hour = hour;
	pvstate.min = min;
    pvstate.h = -720 + pvstate.hour * 60 + pvstate.min;
    pvstate.h_rad = (double) pvstate.h / 720.0 * M_PI;
}

void seth(pvcl_state_class &pvstate, int h) {
	pvstate.h = h;
	pvstate.hour = (pvstate.h + 720) / 60; //decimal part discarded
	pvstate.min = pvstate.h + 720 - pvstate.hour * 60;
    pvstate.h_rad = (double) pvstate.h / 720.0 * M_PI;
}

void _updateh_rad(pvcl_state_class &pvstate) {
    pvstate.h_rad = (double) pvstate.h / 720.0 * M_PI;
}

void setbeta(pvcl_state_class &pvstate, double beta) {
	pvstate.beta = beta;
	pvstate.beta_rad = beta / 180 * M_PI;
}

void setZ_S(pvcl_state_class &pvstate, double Z_S) {
	pvstate.Z_s = Z_S;
	pvstate.Z_s_rad = Z_S /180 * M_PI;

}

void output(std::ofstream sout, pvcl_state_class pvstate, pv_sun::position_in_sky* pos, panel_irradiance::s_debug debug_output) {
    sout << "Printing the current state of the program:" << std::endl;
    sout << "  lat: " << pvstate.L << std::endl;
    sout << "  lat_rad: " << pvstate.L_rad << std::endl;
    sout << "  lon: " << pvstate.lon << std::endl;
    sout << "  day: " << pvstate.day << std::endl;
    sout << "  hour: " << pvstate.hour << std::endl;
    sout << "  min: " << pvstate.min << std::endl;
    sout << "  h: " << pvstate.h << std::endl;
    //sout << "  h_rad: " << pvstate.h_rad << std::endl;
    sout << "  beta: " << pvstate.beta << std::endl;
    sout << "  beta_rad: " << pvstate.beta_rad << std::endl;
    sout << "  Z_s: " << pvstate.Z_s << std::endl;
    sout << "  Z_s_rad: " << pvstate.Z_s_rad << std::endl;
    sout << "  K: " << pvstate.K << std::endl;
    sout << "  Thickness of glass: " << pvstate.thickness << std::endl;
    sout << "  Refraction index: " << pvstate.n_refraction_index << std::endl;
    sout << "  alpha_0: " << pvstate.a0 << std::endl;
    sout << "  alpha_1: " << pvstate.a1 << std::endl;
    sout << "  alpha_2: " << pvstate.a2 << std::endl;
    sout << "  alpha_3: " << pvstate.a3 << std::endl;
    sout << "  alpha_4: " << pvstate.a4 << std::endl;
    sout << "  Area: " << pvstate.area << std::endl;

	sout << "Sun position_in_sky:" << std::endl;
	sout << " alpha_rad : " << pos->alpha_rad << std::endl;  
	sout << " z_rad     : " << pos->z_rad << std::endl; 
    sout << " h_rad     : " << pos->h_rad << std::endl;  
	sout << " h_ss_rad  : " << pos->h_ss_rad << std::endl;  
	sout << " delta_rad : " << pos->delta_rad << std::endl;  
	sout << " cos_Phi   : " << pos->cos_Phi << std::endl;  
	sout << " m         : " << pos->m << std::endl;  
	sout << " valid     : " << pos->valid << std::endl;  

    sout << "compute_S:" << std::endl;
    sout << " G_on      : " << debug_output.G_on << std::endl;  
    sout << " G_oH      : " << debug_output.G_oH << std::endl;
    sout << " H_o_rad   : " << debug_output.H_o_rad << std::endl;
    sout << " H_o       : " << debug_output.H_o << std::endl;
    sout << " r_ground  : " << debug_output.r_ground << std::endl;
    sout << " H         : " << debug_output.H <<  " J/m^2*day (" << (debug_output.H / (24* 60 *60)) << " W/m^2*day)" << std::endl;;
    sout << " r         : " << debug_output.r << std::endl;
    sout << " G         : " << debug_output.G << " J/m^2*h (" << (debug_output.G / 3600) << " W/m^2*h)" << std::endl;
    sout << " G_B       : " << debug_output.G_B << " J/m^2*h (" << (debug_output.G_B / 3600) << " W/m^2*h)" << std::endl;
    sout << " G_D       : " << debug_output.G_D << " J/m^2*hh (" << (debug_output.G_D / 3600) << " W/m^2*h)" << std::endl;
    sout << " cos_theta : " << debug_output.cos_theta << std::endl;
    sout << " R_B       : " << debug_output.R_B << std::endl;
    sout << " M         : " << debug_output.M << std::endl;
    sout << " theta_r   : " << debug_output.theta_r << std::endl;
    sout << " theta_e_D : " << debug_output.theta_e_D << std::endl;
    sout << " taualpha_B: " << debug_output.taualpha_B << std::endl;
    sout << " taualpha_D: " << debug_output.taualpha_D << std::endl;
    sout << " taualpha_n: " << debug_output.taualpha_n << std::endl;
    sout << " K_theta_B : " << debug_output.K_theta_B << std::endl;
    sout << " k_theta_D : " << debug_output.K_theta_D << std::endl;
    sout << " S_B       : " << debug_output.S_B <<  " J/m^2*h (" << (debug_output.S_B / 3600) << " W/m^2*h)" << std::endl;
    sout << " S_D       : " << debug_output.S_D <<  " J/m^2*h (" << (debug_output.S_D / 3600) << " W/m^2*h)" << std::endl;
    sout << " S         : " << debug_output.S <<  " J/m^2*h (" << (debug_output.S / 3600) << " W/m^2*h)" << std::endl;
    sout << "Absorbed irradiance S:" << std::endl;
    sout << " lat  : " << pvstate.L  << std::endl;
    sout << " beta : " << pvstate.beta  << std::endl;
    sout << " Z_S  : " << pvstate.Z_s << std::endl;
    sout << " day  : " << pvstate.day  << std::endl;
    sout << " time : " << pvstate.hour <<":"<<pvstate.min  << std::endl;
    sout << " S    : " << debug_output.S <<  " J/m^2*h (" << (debug_output.S / 3600) << " W/m^2*h)" << std::endl;

}

void _initsettings(pvcl_state_class &pvstate) {
    pvstate.day = 180; 
	pvstate.hour = 13;
	pvstate.min = 0;
	pvstate.h = 60;
	pvstate.beta = 30.0;
	pvstate.beta_rad = pvstate.beta / 180 * M_PI;
	pvstate.Z_s = 0;
	pvstate.Z_s_rad = 0;
	pvstate.area = 1.0;
	pvstate.n_refraction_index = n_refraction_index;
	pvstate.K = K; 
	pvstate.thickness = thickness; 
	pvstate.a0 = alpha_0;
	pvstate.a1 = alpha_1;
	pvstate.a2 = alpha_2;
	pvstate.a3 = alpha_3;
	pvstate.a4 = alpha_4;

	pvstate.L = 44.498991;
	pvstate.L_rad = pvstate.L / 180 * M_PI;
	pvstate.lon = 11.353503;

}



int main(int argc, char **argv) {
	pvcl_state_class pvstate;
    _initsettings(pvstate);

    pv_sun::position_in_sky* pos;

    pvstate.day = 211;
    settime(pvstate, 13, 0);
    setZ_S(pvstate, 0);
    pos = pv_sun::sun(
   		pvstate.day,
   		pvstate.h,
  		pvstate.L_rad
	);

    std::ofstream outfile;
    outfile.open("UniBo day 211 Jul 30 hour 13_00 Z_S 0 run beta out b S_B S_D S.csv");
    for(double beta = 0; beta < 91; beta+= 5) {
        setbeta(pvstate, beta);
        panel_irradiance::s_debug debug_output;
        double S = panel_irradiance::compute_S(
            pos,
            pvstate.day,
            pvstate.L_rad,
            pvstate.beta_rad,
            pvstate.Z_s_rad,
            pvstate.n_refraction_index, 
            pvstate.thickness, 
            pvstate.K,
            pvstate.a0,
            pvstate.a1,
            pvstate.a2,
            pvstate.a3,
            pvstate.a4,
            &debug_output
        );
        std::cout<<"beta: " << beta <<" beta_rad: " << pvstate.beta_rad << " S: " << (debug_output.S / 3600) << " W/m^2*h)" << std::endl;
        outfile << beta << "," << (debug_output.S_B / 3600) << "," <<(debug_output.S_D / 3600) << "," << (debug_output.S / 3600) << "\n";

    }
    outfile.close();

    


    
    outfile.open("UniBo day 211 Jul 30 hour 13_00 beta 27 run Z_S out Z_S S_B S_D S.csv");
    setbeta(pvstate, 27);
    for(double Z_S = -90; Z_S < 91; Z_S += 5) {
        setZ_S(pvstate, Z_S);
        panel_irradiance::s_debug debug_output;
        double S = panel_irradiance::compute_S(
            pos,
            pvstate.day,
            pvstate.L_rad,
            pvstate.beta_rad,
            pvstate.Z_s_rad,
            pvstate.n_refraction_index, 
            pvstate.thickness, 
            pvstate.K,
            pvstate.a0,
            pvstate.a1,
            pvstate.a2,
            pvstate.a3,
            pvstate.a4,
            &debug_output
        );
        std::cout<<"Z_S: " << Z_S <<" ZS_rad: " << pvstate.Z_s_rad << " S: " << (debug_output.S / 3600) << " W/m^2*h)" << std::endl;
        outfile << Z_S << "," << (debug_output.S_B / 3600) << "," <<(debug_output.S_D / 3600) << "," << (debug_output.S / 3600) << "\n";

    }
    outfile.close();

			

}

