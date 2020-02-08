#include "fltk_actions.h"


void fltk_actions::assign_file(Fl_File_Chooser* w, void* userdata)
{
    auto filename = w->value();
    std::cout << "FILE: " << filename <<std::endl;
	
    std::vector<geometry::vertex *> v = panel_io::load_vertices(filename);
	fltk_window->panel->set_vertices(v); 

	// init(vertices); 
	fltk_3dpanel_opengl::draw(v);
}

void fltk_actions::open_input_file()
{
	Fl_File_Chooser *fc = new Fl_File_Chooser(".", NULL, 0, "Input File");
	fc->callback(fltk_actions::assign_file);
	fc->show();
}


void fltk_actions::run_simulation(
    double l_L_deg,
	double K, 
	double n_refraction_index, 
	double thickness, 
    Fl_Text_Buffer* buff) {


    double L_rad = l_L_deg * M_PI / 180;

	
    //std::cout << " SIZE VERTEXS DENTRO A CALCOLIAMUS: " << vertices.size();
	//definisco il file di testo  
	std::ofstream myfile;
	std::string nf = "";
	myfile.open("buffer-data.txt");
	std::ofstream tempfile;
	tempfile.open("debug-data.txt");

	std::vector<geometry::vertex *> vertices = fltk_window->panel->get_vertices();
	std::vector<geometry::triangle> triangles;
	triangles.reserve(vertices.size() / 3 + 1);
	//Checks for 3 available vertices
	for (int i = 0; i + 2 < (int) vertices.size(); i += 3) {
		triangles.emplace_back(geometry::triangle(*vertices[i], *vertices[i + 1], *vertices[i + 2]));
		// geometry::plane pl = geometry::fplane(*vertices[i], *vertices[i + 1], *vertices[i + 2]);
	}
	
	//giorno
	for (int day = 1; day <= 365; day++)
	{
		//ora
		for (int hour = 9; hour < 18; hour++)
		{
			//definisco posizione sole

			int h = 720 - hour * 60;
			const pv_sun::position_in_sky* pos = pv_sun::sun(
				day,
				h,
				L_rad
			);

			//risultato S
			double S = 0;
			double S_temp;
			//triangolo
			for (geometry::triangle t : triangles) {

				S_temp = panel_irradiance::compute_S(
					pos,
					day,
					L_rad,
					t.mbeta_rad,
					t.mZ_S_rad,
					n_refraction_index,
					thickness,
					K,
					global::alpha_0,
					global::alpha_1,
					global::alpha_2,
					global::alpha_3,
					global::alpha_4

				);
				S += t.marea * S_temp / 3600.0;
				tempfile <<"d: " << day << " h: " << h << " beta: " << t.mbeta_rad << " Z_S: " << t.mZ_S_rad << " Area: " << t.marea << " S_temp: " << S_temp/3600 <<std::endl;
				if (S_temp/3600.0 > 1000.0) {
					tempfile 
		            << "pos: L_rad: " << L_rad
					<< "pos: alpha_rad: " << pos->alpha_rad
		            << " z_rad(z_rad): " << pos->z_rad
        		    << " h_rad(h_rad): " << pos->h_rad
            		<< " h_ss_rad: " << pos->h_ss_rad
            		<< " delta_rad: " << pos->delta_rad
            		<< " cos_Phi: " << pos->cos_Phi
            		<< " m: " << pos->m
            		<< " valid: " << pos->valid
					<< std::endl;

				}
			}
			//stampa informazioni
			
			nf += "GIORNO: ";
			nf += std::to_string(day);
			nf += " ORA: ";
			nf += std::to_string(hour);  
			nf += " Rendimento: " ;
			nf += std::to_string(S);
			nf += "\n";
			
			char* chr = strdup(nf.c_str());
			buff->text(chr);
			myfile << day << " " << hour << " " << S << "\n";
			free(chr);
		}
		//stampa riga vuota per cambio giorno
		myfile << "\n";
	}

	myfile.close();
	tempfile.close();
	std::cout << " FILE CREATO NELLA CARTELLA DEL PROGETTO: " << "";

}

void fltk_actions::PlotIT()
{

	/*
	
		"set xlabel 'Day of year' "
			"set ylabel 'Hour' "
			"set xrange[1:36] "
			"set yrange[9:18] "
			"set palette "
			"set pm3d at s "
			"splot 'C:\\Users\\andre\\source\\repos\\pv-creativity\\pv-creativity\\outputS.txt' with lines "
	
	*/
		GnuplotPipe gp;	
		gp.sendLine("set terminal wxt size 800,800 \n"
			"set title 'Solar Absorption' \n"
			"set xlabel 'Day of year' \n"
			"set ylabel 'Hour' \n"
			"set xrange[1:36] \n"
			"set yrange[9:18] \n"
			"set palette\n "
			"set pm3d at s \n"
			"splot 'buffer-data.txt' with lines \n"
			);

}
