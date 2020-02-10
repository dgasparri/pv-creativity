#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>

struct vertex {
    double x;
    double y;
    double z;
    //vertex(double x, double y, double z);
    
    friend std::ostream& operator<<(std::ostream& os, const vertex& v)    
    {
        os << v.x << " " << v.y << " " << v.z;
        return os;
    }

};


//ondulato
//Omega = angular frequency
//A = Amplitude (height in y)
//phi 
void sinu(std::string filename , double A, double omega, double phi, double x0, double x1, double y0, double y1, double z_offset, double delta_x )
{ 
     
    std::ofstream fout;
    fout.open(filename);

    std::string filename_original = filename + ".original.csv" ;
    std::ofstream fout_original;
    fout_original.open(filename_original);


    double r_x;
    double direction;
    vertex vlf, vlb, vrf, vrb; //vertex_left_front, vertex_left_back, vertex_right_front, vertex_right_back
    for(double l_x = x0; l_x <= x1; l_x += delta_x)
    {
        double z1 = A * std::sin(omega * l_x + phi) + z_offset;
        r_x = l_x + delta_x;
        double z2 = A * std::sin(omega * r_x + phi) + z_offset;

        vlf.x = l_x; vlf.y = y0; vlf.z = z1;
        vlb.x = l_x; vlb.y = y1; vlb.z = z1;
        vrf.x = r_x; vrf.y = y0; vrf.z = z2;
        vrb.x = r_x; vrb.y = y1; vrb.z = z2;
        
        direction = (z1 < z2) ? -1.0 : 1.0;

        std::cout << "x_l: " << l_x << " x_r: " << r_x << " y0 " << y0 << " y1: " << y1 << " z1 " << z1 << " z2: " << z2 <<std::endl;


        fout << vlf << "," << vlb << "," << vrf << ", " << direction << std::endl;
        fout << vlb << "," << vrf << "," << vrb << ", " << direction << std::endl;

        fout_original << vlf << "," << vlb << "," << vrf << std::endl;
        fout_original << vlb << "," << vrf << "," << vrb << std::endl;


    }

    fout.close();
    fout_original.close();

}





//ondulato
//Omega = angular frequency
//A = Amplitude (height in y)
//phi 
void circ(std::string filename , double x0, double y0, double r, double omega_start, double omega_end, double y1, double y2, double delta_omega )
{ 
     
    std::ofstream fout;
    fout.open(filename);

    std::string filename_original = filename + ".original.csv" ;
    std::ofstream fout_original;
    fout_original.open(filename_original);



    double direction;
    vertex vlf, vlb, vrf, vrb; //vertex_left_front, vertex_left_back, vertex_right_front, vertex_right_back
    for(double o1 = omega_start; o1 <= omega_end; o1 += delta_omega)
    {
        double x1 = r * std::cos(o1);
        double z1 = r * std::sin(o1);
        double o2 = o1 + delta_omega;
        double x2 = r * std::cos(o2);
        double z2 = r * std::sin(o2);

        vlf.x = x2; vlf.y = y1; vlf.z = z2;
        vlb.x = x2; vlb.y = y2; vlb.z = z2;
        vrf.x = x1; vrf.y = y1; vrf.z = z1;
        vrb.x = x1; vrb.y = y2; vrb.z = z1;
        
        direction = (z2 > z1) ? 1.0 : -1.0;

        std::cout << "o1: " << 01 << " o2: " << o2 << " x1 " << x1 << " z1: " << z1 << " x2 " << x2 << " z2: " << z2 <<std::endl;


        fout << vlf << "," << vlb << "," << vrf << ", " << direction << std::endl;
        fout << vlb << "," << vrf << "," << vrb << ", " << direction << std::endl;

        fout_original << vlf << "," << vlb << "," << vrf << std::endl;
        fout_original << vlb << "," << vrf << "," << vrb << std::endl;


    }

    fout.close();
    fout_original.close();

}




//ondulato
//Omega = angular frequency
//A = Amplitude (height in y)
//phi 
void cono(std::string filename , double x0, double y0, double r, double h, double delta_omega )
{ 
     
    std::ofstream fout;
    fout.open(filename);

    std::string filename_original = filename + ".original.csv" ;
    std::ofstream fout_original;
    fout_original.open(filename_original);



    double direction;
    vertex vt, vb1, vb2; //vertex_top, vertex_left_back, ertex_right_back
    vt.x = x0; vt.y = y0; vt.z = h;
    for(double omega = 0; omega <= (2* M_PI); omega += delta_omega)
    {
        double x1 = x0 + r * std::cos(omega);
        double y1 = y0 + r * std::sin(omega);
        double o2 = omega + delta_omega;
        double x2 = x0 + r * std::cos(o2);
        double y2 = y0 + r * std::sin(o2);

        vb1.x = x1; vb1.y = y1; vb1.z = 0;
        vb2.x = x2; vb2.y = y2; vb2.z = 0;
        


        //direction = ( (omega > (M_PI / 2)) && (omega < (M_PI * 3 / 4)) ) ? -1.0 : 1.0;
        direction = ( (x1 - x0) < 0 ) ? -1.0 : 1.0;

        //std::cout << "o1: " << 01 << " o2: " << o2 << " x1 " << x1 << " z1: " << z1 << " x2 " << x2 << " z2: " << z2 <<std::endl;


        fout << vt << "," << vb1 << "," << vb2 << ", " << direction << std::endl;
        
        fout_original << vt << "," << vb1 << "," << vb2 << std::endl;


    }

    fout.close();
    fout_original.close();

}












int main() {
    std::string filename = "corrugated.csv";
    sinu(
        filename,
        2,  //A
        3.4147,  //omega
        0,  //phi
        -0.90,  //x0
        4.6, //x1
        0,   //y0
        4,   //y1
        0,   //z_offset
        0.05 //delta_x
        );
    
    filename = "tettoia.csv";
    //Circ(4, 0, 5, 179,0,0);
    //void circ(std::string filename , double x0, double y0, double r, double omega_start, double omega_end, double y0, double y1, double delta_omega )
    circ(
        filename,
        0,  //x0
        0,  //y0
        4,  //r
        0, //omega_start
        M_PI,   //omega_end
        0,   //y0
        5,   //y1
        0.01 //delta_omega
        );

    filename = "cono.csv";
    cono(
        filename, 
        1.5, // double x0, 
        0, //double y0, 
        3, //double r, 
        4, //double h, 
        0.1 //double delta_omega 
        );

}