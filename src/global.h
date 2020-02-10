#pragma once

#ifndef pure
#define pure
#endif

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#ifndef EQUAL_COORDINATES_EPSILON
#define EQUAL_COORDINATES_EPSILON 0.00001
#endif

#ifndef G_SC_CONSTANT
#define G_SC_CONSTANT 1366.1  //W/m^2 
#endif


#ifndef DATA_PIPE_DIRECTORY
#define DATA_PIPE_DIRECTORY "./.data-pipe"
#endif

#include <string>
#include <filesystem>


namespace global {
    const double K = 4; // m^-1
    const double thickness_L = 0.002; 
    const double n_refraction_index = 1.526;
    const double alpha_0 = 0.935823;
    const double alpha_1 = 0.054289;
    const double alpha_2 = -0.008677;
    const double alpha_3 = 0.000527;
    const double alpha_4 = -0.000011;

    const double UniBo_Lat_deg = 44.498991;


    pure std::filesystem::path workdir_path(std::string filename);
}
