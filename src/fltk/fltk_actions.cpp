#include "fltk_actions.h"


void assign_file(Fl_File_Chooser* w, void* userdata)
{
    std::cout << "FILE: " << w->value();
	nomeFile = w->value();
	//nf = w->value();
	vertices = panel_io::load_vertices(nomeFile);
	std::cout << " SIZE VERTEXSSS: " << vertices.size();
	init(vertices);
	panel_opengl::draw(vertices);
}

void open_input_file()
{
	Fl_File_Chooser *fc = new Fl_File_Chooser(".", NULL, 0, "Input File");
	fc->callback(assignFile);
	fc->show();
}


void calcola(double n_refraction_index, double thickness, double K, Fl_Text_Buffer* buff, Fl_Value_Input* L_T, Fl_Value_Input* K_, Fl_Value_Input* n, Fl_Value_Input* L) {

	//std::cout << " SIZE VERTEXS DENTRO A CALCOLIAMUS: " << vertices.size();
	//definisco il file di testo  
	ofstream myfile;
	nf = "";
	myfile.open("outputS.txt");

	//valori polycristalline
	double a0 = 0.918093;
	double a1 = 0.086257;
	double a2 = -0.024459;
	double a3 = 0.002816;
	double a4 = -0.000126;
	


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

				thickness_holder  = L_T->value();
				K_holder          = K_->value();
				refraction_holder = n->value();

				double S_temp = panel_irradiance::compute_S(

					pos,

					i,

					L_rad,

					t.mbeta_rad,

					t.mZ_S_rad,

					refraction_holder,

					thickness_holder,

					K_holder,

					alpha_0,

					alpha_1,

					alpha_2,

					alpha_3,

					alpha_4

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

void PlotIT()
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
