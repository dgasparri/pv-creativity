#define _USE_MATH_DEFINES
#include <algorithm>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>

#include "../config.h"
// #include "../lib/panel_io.h"
#include "../lib/sun_fp.h"
// #include "../lib/sun_panel_fp.h"
// #include "../lib/geometry_fp.h"
#include "../lib/panel_irradiance.h"


namespace po = boost::program_options;


class pvcl_state_class {
public:
	double L;
	double L_rad;
	double lon;
	int day;
	int hour;
	int min;
	int h;
	// double h_rad;
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



int main(int argc, char **argv) {
	pvcl_state_class pvstate;

	po::options_description desc("allowed options");
	desc.add_options()
		("help", "produce the help message")
		("status", "print the currently set parameters")
		("sun", "print the sun parameters")
		("quit", "exit the program")
		("default", "set the parameters to default")
		("lat", po::value<double>(), "set the latitude of the installation")
		("lon", po::value<double>(), "set the longitude of the installation")
		("UniBo", "set the location to 44.498991 lat, 11.353503 lon (University of Bologna 44°29'56.4\"N 11°21'12.6\"E)")
		("day", po::value<int>(), "set the day of the year from 1 to 365")
		("hour", po::value<int>(), "set the hour of the day from 0 to 23")
		("min", po::value<int>(), "set the minutes from 0 to 59")
		("h", po::value<int>(), "set the number of minutes from midday, negatives are morning time")
		// ("h_rad", po::value<double>(), "set the number of minutes from midday in radians")
		("beta", po::value<double>(), "set the beta of the panel")
		("beta_rad", po::value<double>(), "set the beta of the panel in radians")
		("Z_s", po::value<double>(), "set the Z_s of the panel")
		("Z_s_rad", po::value<double>(), "set the Z_s of the panel in radians")
		("area", po::value<double>(), "set the area of the panel in square meters")
		("S", "return the irradiance S in W/m^2")
		("verbose", "return the irradiance S in W/m^2 - verbose mode")
		;


	std::cout << "Type a command ( --help for help, --quit to quit )" << std::endl;

	bool update_h_rad = false;
    while (std::cin) {
		std::cout << ">";
		std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> parsedInput;
        boost::split(parsedInput, input, boost::is_any_of(" "), boost::token_compress_on);

        std::vector<char const*> args { "command" };
        for (auto& arg : parsedInput)
            args.push_back(arg.c_str());

        po::variables_map vm;
		try {
			po::store(po::parse_command_line(args.size(), args.data(), desc), vm);
		} catch (...) {
			std::cout<<"Unknown or malformed command"<<std::endl;
		}
		
		po::notify(vm);
       

        if (vm.count("help")) {
            std::cout << desc << std::endl;
			std::cout << "Example:" << std::endl;
			std::cout << "    >--beta 12.24" << std::endl;
			std::cout << "    >--beta_rad 0.18" << std::endl;
			std::cout << "    >--quit" << std::endl;
		}

		if (vm.count("quit")) {
			std::cout << "Quitting program" << std::endl;
			return 0;
		}

		if (vm.count("status") || vm.count("verbose")) {
			std::cout << "Printing the current state of the program:" << std::endl;
			std::cout << "  lat: " << pvstate.L << std::endl;
			std::cout << "  lat_rad: " << pvstate.L_rad << std::endl;
			std::cout << "  lon: " << pvstate.lon << std::endl;
			std::cout << "  day: " << pvstate.day << std::endl;
			std::cout << "  hour: " << pvstate.hour << std::endl;
			std::cout << "  min: " << pvstate.min << std::endl;
			std::cout << "  h: " << pvstate.h << std::endl;
			// std::cout << "  h_rad: " << pvstate.h_rad << std::endl;
			std::cout << "  beta: " << pvstate.beta << std::endl;
			std::cout << "  beta_rad: " << pvstate.beta_rad << std::endl;
			std::cout << "  Z_s: " << pvstate.Z_s << std::endl;
			std::cout << "  Z_s_rad: " << pvstate.Z_s_rad << std::endl;
			std::cout << "  K: " << pvstate.K << std::endl;
			std::cout << "  Thickness of glass: " << pvstate.thickness << std::endl;
			std::cout << "  Refraction index: " << pvstate.n_refraction_index << std::endl;
			std::cout << "  alpha_0: " << pvstate.a0 << std::endl;
			std::cout << "  alpha_1: " << pvstate.a1 << std::endl;
			std::cout << "  alpha_2: " << pvstate.a2 << std::endl;
			std::cout << "  alpha_3: " << pvstate.a3 << std::endl;
			std::cout << "  alpha_4: " << pvstate.a4 << std::endl;
			std::cout << "  Area: " << pvstate.area << std::endl;
		}

		if (vm.count("sun") || vm.count("verbose")) { 
		    const pv_sun::position_in_sky* pos = pv_sun::sun(
        		pvstate.day,
        		pvstate.h,
        		pvstate.L_rad
    		);

			std::cout << "Sun position_in_sky:" << std::endl;
			std::cout << " alpha_rad : " << pos->alpha_rad << std::endl;  
			std::cout << " z_rad     : " << pos->z_rad << std::endl; 
			std::cout << " h_rad     : " << pos->h_rad << std::endl;  
			std::cout << " h_ss_rad  : " << pos->h_ss_rad << std::endl;  
			std::cout << " delta_rad : " << pos->delta_rad << std::endl;  
			std::cout << " cos_Phi   : " << pos->cos_Phi << std::endl;  
			std::cout << " m         : " << pos->m << std::endl;  
			std::cout << " valid     : " << pos->valid << std::endl;  
		}

		if (vm.count("default")) {
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

			update_h_rad = true;
		}

		if (vm.count("default") || vm.count("UniBo") ) {
			pvstate.L = 44.498991;
			pvstate.L_rad = pvstate.L / 180 * M_PI;
			pvstate.lon = 11.353503;
		}

		if (vm.count("day")) {
			std::cout << "set the day to " << vm["day"].as<int>() << std::endl;	
			pvstate.day = vm["day"].as<int>();
		}

		if (vm.count("hour")) {
			std::cout << "set the hour to " << vm["hour"].as<int>() << std::endl;	
			pvstate.hour = vm["hour"].as<int>();
			pvstate.h = -720 + pvstate.hour * 60 + pvstate.min;
			update_h_rad = true;
		}

		if (vm.count("min")) {
			std::cout << "set the min to " << vm["min"].as<int>() << std::endl;	
			pvstate.min = vm["min"].as<int>();
			pvstate.h = -720 + pvstate.hour * 60 + pvstate.min;
			update_h_rad = true;
		}

		if (vm.count("h")) {
			std::cout << "set h to " << vm["h"].as<int>() << std::endl;	
			pvstate.h = vm["h"].as<int>();
			pvstate.hour = (pvstate.h + 720) / 60; //decimal part discarded
			pvstate.min = pvstate.h + 720 - pvstate.hour * 60;
			update_h_rad = true;
		}

		// if (update_h_rad) {
		// 	pvstate.h_rad = (double) pvstate.h / 720.0 * M_PI;
		// 	update_h_rad = false;
		// }


		if (vm.count("beta")) {
			std::cout << "set the beta to " << vm["beta"].as<double>() << std::endl;
			pvstate.beta = vm["beta"].as<double>();
			pvstate.beta_rad = vm["beta"].as<double>() /180 * M_PI;
		}

		if (vm.count("Z_s")) {
			std::cout << "set the Z_s to " << vm["Z_s"].as<double>() << std::endl;
			pvstate.Z_s = vm["Z_s"].as<double>();
			pvstate.Z_s_rad = vm["Z_s"].as<double>() /180 * M_PI;
		}

		if (vm.count("Z_s_rad")) {
			std::cout << "set the Z_s to " << vm["Z_s_rad"].as<double>() << std::endl;
			pvstate.Z_s = vm["Z_s_rad"].as<double>()  * 180 / M_PI;
			pvstate.Z_s_rad = vm["Z_s_rad"].as<double>();
		}


		if (vm.count("beta_rad")) {
			std::cout << "set the beta_rad to " << vm["beta_rad"].as<double>() << std::endl;
			pvstate.beta = vm["beta_rad"].as<double>() / M_PI * 180;
			pvstate.beta_rad = vm["beta_rad"].as<double>();
		}

		if(vm.count("lat")) {
			std::cout << "set the latitude to " << vm["lat"].as<double>() << std::endl;
			pvstate.L = vm["lat"].as<double>();
			pvstate.L_rad = pvstate.L / 180 * M_PI;
		}

		if(vm.count("lon")) {
			std::cout << "set the longitude " << vm["lon"].as<double>() << std::endl;
			pvstate.lon = vm["lon"].as<double>();
		}

		if(vm.count("S") || vm.count("verbose")) {
		    const pv_sun::position_in_sky* pos = pv_sun::sun(
        		pvstate.day,
        		pvstate.h,
        		pvstate.L_rad
    		);

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

			if(vm.count("verbose")) {


				std::cout << "compute_S:" << std::endl;
				std::cout << " G_on      : " << debug_output.G_on << std::endl;  
				std::cout << " G_oH      : " << debug_output.G_oH << std::endl;
				std::cout << " H_o_rad   : " << debug_output.H_o_rad << std::endl;
				std::cout << " H_o       : " << debug_output.H_o << std::endl;
				std::cout << " r_ground  : " << debug_output.r_ground << std::endl;
				std::cout << " H         : " << debug_output.H <<  " J/m^2*day (" << (debug_output.H / (24* 60 *60)) << " W/m^2*day)" << std::endl;;
				std::cout << " r         : " << debug_output.r << std::endl;
				std::cout << " G         : " << debug_output.G << " J/m^2*h (" << (debug_output.G / 3600) << " W/m^2*h)" << std::endl;
				std::cout << " G_B       : " << debug_output.G_B << " J/m^2*h (" << (debug_output.G_B / 3600) << " W/m^2*h)" << std::endl;
				std::cout << " G_D       : " << debug_output.G_D << " J/m^2*hh (" << (debug_output.G_D / 3600) << " W/m^2*h)" << std::endl;
				std::cout << " cos_theta : " << debug_output.cos_theta << std::endl;
				std::cout << " R_B       : " << debug_output.R_B << std::endl;
				std::cout << " M         : " << debug_output.M << std::endl;
				std::cout << " theta_r   : " << debug_output.theta_r << std::endl;
				std::cout << " theta_e_D : " << debug_output.theta_e_D << std::endl;
				std::cout << " taualpha_B: " << debug_output.taualpha_B << std::endl;
				std::cout << " taualpha_D: " << debug_output.taualpha_D << std::endl;
				std::cout << " taualpha_n: " << debug_output.taualpha_n << std::endl;
				std::cout << " K_theta_B : " << debug_output.K_theta_B << std::endl;
				std::cout << " k_theta_D : " << debug_output.K_theta_D << std::endl;
				std::cout << " S_B       : " << debug_output.S_B <<  " J/m^2*h (" << (debug_output.S_B / 3600) << " W/m^2*h)" << std::endl;
				std::cout << " S_D       : " << debug_output.S_D <<  " J/m^2*h (" << (debug_output.S_D / 3600) << " W/m^2*h)" << std::endl;
				std::cout << " S         : " << debug_output.S <<  " J/m^2*h (" << (debug_output.S / 3600) << " W/m^2*h)" << std::endl;

			}

			std::cout << "Absorbed irradiance S:" << std::endl;
			std::cout << " lat  : " << pvstate.L  << std::endl;
			std::cout << " beta : " << pvstate.beta  << std::endl;
			std::cout << " Z_S  : " << pvstate.Z_s << std::endl;
			std::cout << " day  : " << pvstate.day  << std::endl;
			std::cout << " time : " << pvstate.hour <<":"<<pvstate.min  << std::endl;
			std::cout << " S    : " << debug_output.S <<  " J/m^2*h (" << (debug_output.S / 3600) << " W/m^2*h)" << std::endl;
			
			delete pos;


		}


    }
}

