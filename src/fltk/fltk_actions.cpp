#include "fltk_actions.h"


void fltk_actions::assign_file(Fl_File_Chooser* w, void* userdata)
{
    auto filename = w->value();
    std::cout << "FILE: " << filename <<std::endl;
	
	//std::vector<geometry::vertex *> *v = new std::vector<geometry::vertex *>;
	fltk_window->panel->clear_vertices();
	std::vector<geometry::vertex *> *v = fltk_window->panel->get_vertices_ptr();
	if(!panel_io::load_vertices(filename, v)) {
		return;
	}
	
	
	std::cout << "Ci sono " << v->size() << " vertici "<<std::endl;
	// std::cout << "In fltk ci sono " << fltk_window->panel->get_vertices(v).size() << " vertici "<<std::endl;

	// fltk_window->panel->set_vertices(v);
	std::cout << "In panel ci sono " << fltk_window->panel->get_vertices().size() << " vertici "<<std::endl;



	fltk_window->panel->clear_triangles();
	// std::vector<geometry::triangle *> *triangles = new std::vector<geometry::triangle *>;
	std::vector<geometry::triangle *> *triangles = fltk_window->panel->get_triangles_ptr();

	//std::vector<geometry::triangle *> *triangles = fltk_window->panel->get_triangles();
	//triangles.clear();

	triangles->reserve(v->size() / 3 + 1);
	std::ofstream fout;
	fout.open(global::workdir_path("panel-geometry.csv"));

	fout << "#tr\tv1,v2,v3,direction\tplane\tbeta(rad)\tZ_S(rad)\tArea(m^2)"<<std::endl;
	int num_triangles = 0;
	for (int i = 0; i + 2 < (int) v->size(); i += 3) {
		geometry::triangle *t = new geometry::triangle(*(*v)[i], *(*v)[i + 1], *(*v)[i + 2]);

		if (t->mbeta_rad < 0 ) {
			std::cout << "Triangle # " << num_triangles << " with negative beta (" << t->mbeta_rad << "). Recovering." << std::endl;
			
			geometry::vertex *v_old, *v1_old, *v2_old;
			v_old = (*v)[i];
			v1_old = (*v)[i + 1];
			v2_old = (*v)[i + 2];
			(*v)[i] = new geometry::vertex((*v)[i]->x, (*v)[i]->y, (*v)[i]->z, -(*v)[i]->direction);
			(*v)[i + 1] = new geometry::vertex((*v)[i + 1]->x, (*v)[i + 1]->y, (*v)[i + 1]->z, -(*v)[i + 1]->direction);
			(*v)[i + 2] = new geometry::vertex((*v)[i + 2]->x, (*v)[i + 2]->y, (*v)[i + 2]->z, -(*v)[i + 2]->direction);
			delete(v_old);
			delete(v1_old);
			delete(v2_old);
			delete(t);
			t = new geometry::triangle(*(*v)[i], *(*v)[i + 1], *(*v)[i + 2]);
			if (t->mbeta_rad < 0 ) {
				
				std::cout << "   Unsuccessful." << std::endl;
				delete(t);
				continue;

			}
		}

		triangles->emplace_back(t);

		fout 
			<< num_triangles << "\t"
			<< *(*v)[i]  << ","
			<< *(*v)[i+1] << ","
			<< *(*v)[i+2] << ","
			<< (*(*v)[i]).direction << "\t"
			<< triangles->back()->mplane_normal << "\t"
			<< triangles->back()->mbeta_rad << "\t"
			<< triangles->back()->mZ_S_rad << "\t"
			<< triangles->back()->marea << std::endl;
			
		num_triangles ++;
	}

	fout.close();
	// fltk_window->panel->set_triangles(triangles);

	// init(vertices); 
	fltk_3dpanel_opengl::draw(v);
}

void fltk_actions::open_input_file()
{
	Fl_File_Chooser *fc = new Fl_File_Chooser(".", NULL, 0, "Panel Geometry");
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

	

	std::string nf = "";

	std::ofstream daily;
	std::ofstream yearly;

	yearly.open(global::workdir_path("simulation-data-yearly.txt"));


	std::vector<geometry::vertex *> vertices = fltk_window->panel->get_vertices();
	std::vector<geometry::triangle *> triangles = fltk_window->panel->get_triangles();
	std::cout <<"Ci sono " << triangles.size() << "triangoli " << std::endl;

	char day_str_buf[10];

	//giorno
	for (int day = 1; day <= 365; day++)
	{
		std::string daily_name = "simulation-data-day-";
		snprintf(day_str_buf, 10, "%03d", day);
		daily_name += day_str_buf;
		daily_name += ".txt";

		daily.open(global::workdir_path(daily_name));

		//ora
		for (int hour = 8; hour < 18; hour++)
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
			const int ntr = triangles.size();
			for (int j=0; j <ntr; j++) {
				geometry::triangle *t = triangles[j];

				S_temp = panel_irradiance::compute_S(
					pos,
					day,
					L_rad,
					t->mbeta_rad,
					t->mZ_S_rad,
					n_refraction_index,
					thickness,
					K,
					global::alpha_0,
					global::alpha_1,
					global::alpha_2,
					global::alpha_3,
					global::alpha_4

				);
				S += t->marea * S_temp / 3600.0;
				
				
				/* daily << "triangolo n: "<< j << " beta_rad " <<  t.mbeta_rad << " Z_S: " << t.mZ_S_rad << " Area: " << t.marea << std::endl
						<< "  v1: " << (*vertices[j*3]) << std::endl
						<< "  v2: " << (*vertices[j*3 + 1]) << std::endl
						<< "  v3: " << (*vertices[j*3 + 2]) << std::endl;
				*/

				//if (S_temp/3600.0 > 1000.0) {
					daily <<"#: " << j << " h: " << h << " beta: " << t->mbeta_rad << " Z_S: " << t->mZ_S_rad << " Area: " << t->marea << " S_temp: " << S_temp/3600 <<std::endl;
					daily 
		            << "             pos: L_rad: " << L_rad
					<< "pos: alpha_rad: " << pos->alpha_rad
		            << " z_rad(z_rad): " << pos->z_rad
        		    << " h_rad(h_rad): " << pos->h_rad
            		<< " h_ss_rad: " << pos->h_ss_rad
            		<< " delta_rad: " << pos->delta_rad
            		<< " cos_Phi: " << pos->cos_Phi
            		<< " m: " << pos->m
            		<< " valid: " << pos->valid
					<< std::endl;

				//}

				//daily << j << " " << hour << " " << S_temp << " beeta " << t->mbeta_rad << " z_S " << t->mZ_S_rad <<  "\n";
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
			free(chr);

			yearly << day << " " << hour << " " << S << "\n";
			
		}
		//stampa riga vuota per cambio giorno
		daily.close();
		yearly << "\n";
	}

	yearly.close();

}

void fltk_actions::plot_yearly()
{

	std::string plot_line = "set terminal wxt size 800,800 \n";
			plot_line += "set title 'Solar Absorption' \n";
			plot_line += "set xlabel 'Day of year' \n";
			plot_line += "set ylabel 'Hour' \n";
			plot_line += "set xrange[1:365] \n";
			plot_line += "set yrange[9:18] \n";
			plot_line += "set palette\n ";
			plot_line += "set pm3d at s \n";
			plot_line += "splot '"; plot_line += global::workdir_path("simulation-data-yearly.txt").string(); plot_line += "' with lines \n";
			
	GnuplotPipe gp;	
	gp.sendLine(plot_line);

}
