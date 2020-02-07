#include "fltk_actions.h"


namespace patch
{
	template < typename T > std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
}


void fltk_actions::assign_file(Fl_File_Chooser* w, void* userdata)
{
    auto filename = w->value();
    std::cout << "FILE: " << filename <<std::endl;
	
    std::vector<geometry::vertex *> v = panel_io::load_vertices(filename);
	fltk_window->panel->set_vertices(v); 

	// init(vertices); 
	panel_opengl::draw(v);
}

void fltk_actions::open_input_file()
{
	Fl_File_Chooser *fc = new Fl_File_Chooser(".", NULL, 0, "Input File");
	fc->callback(fltk_actions::assign_file);
	fc->show();
}


void fltk_actions::calcola(
    double l_L_deg,
	double K, 
	double n_refraction_index, 
	double thickness, 
    Fl_Text_Buffer* buff) {


    double L_rad = l_L_deg * M_PI / 180;
	
    //std::cout << " SIZE VERTEXS DENTRO A CALCOLIAMUS: " << vertices.size();
	//definisco il file di testo  
	ofstream myfile;
	nf = "";
	myfile.open("buffer-data.txt");


	std::vector<geometry::triangle> triangles;
	triangles.reserve(vertices.size() / 3 + 1);
	//Checks for 3 available vertices
	for (int i = 0; i + 2 < vertices.size(); i += 3) {
		triangles.emplace_back(geometry::triangle(*vertices[i], *vertices[i + 1], *vertices[i + 2]));
		geometry::plane pl = geometry::fplane(*vertices[i], *vertices[i + 1], *vertices[i + 2]);
	}
	
	//giorno
	for (int i = 1; i <= 365; i++)
	{
		//ora
		for (int j = 0; j < 24; j++)
		{
			//definisco posizione sole

			L_rad = L->value();

			int h = 720 - j * 60;
			const pv_sun::position_in_sky* pos = pv_sun::sun(
				i,
				h,
				L_rad
			);

			//risultato S
			double S = 0;
			//triangolo
			for (geometry::triangle t : triangles) {

				double S_temp = panel_irradiance::compute_S(
					pos,
					i,
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
				S += (S_temp / 3600);
			}
			//stampa informazioni
			nf += std::string("GIORNO:") + patch::to_string(i)  + std::string(" ORA: ") + patch::to_string(j)  + std::string(" Rendimento: ")  + patch::to_string(S) + "\n";
			
			char* chr = strdup(nf.c_str());
			buff->text(chr);
			myfile << i << " " << j << " " << S << "\n";
			free(chr);
		}
		//stampa riga vuota
		myfile << "\n";
	}

	myfile.close();
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
			"splot 'C:\\Users\\andre\\source\\repos\\pv-creativity\\pv-creativity\\outputS.txt' with lines \n"
			);

}
