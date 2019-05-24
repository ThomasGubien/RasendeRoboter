#include "IAController.h"
#include "RasendeRoboterController.h"
#include "StartWindow.h"
#include <QtWidgets/QApplication>
#include <qmessagebox.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// On crée une instance de RasendeRoboter
	RasendeRoboterController w;
	StartWindow startWindow;
	startWindow.setRasen(&w);
	//startWindow.setIAControler(&iaController);
	startWindow.show();
	// On affiche l'instance du RasenderRoboter
	//w.show();

	// =========================A SUPPR==================================
	/*IAController ia(&w);
	int coord[2] = {6, 1};
	std::vector<Move> sol = ia.getSolution(coord, 4);
	std::string s = "Goal : ";
	s.append(std::to_string(coord[0]));
	s.append("-");
	s.append(std::to_string(coord[1]));
	s.append("\n");
	s.append("nbStarts : ");
	s.append(std::to_string(sol.size()));
	s.append("\n");
	for (int i = 0; i < sol.size(); i++) {
		s.append(std::to_string(sol.at(i).getGoal().at(0)));
		s.append("-");
		s.append(std::to_string(sol.at(i).getGoal().at(1)));
		s.append("\n");
	}

	QMessageBox msg;
	msg.setText(s.c_str());
	msg.show();*/
	// ==================================================================

	return a.exec();
}

