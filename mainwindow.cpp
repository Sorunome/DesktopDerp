#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMovie>
#include <QLabel>
#include <QSize>
#include <QString>
#include <QTimer>
#include <QList>
#include <QTextStream>
#include <QMenu>

class derp {
public:
	int posx;
	int posy;
	derp() {
		posx=500;
		posy=500;
		action="stand";
		position="right";
		movex=0;
		movey=0;
		oldmovex=0;
		oldmovey=0;
		height=100;
		width=100;
		speed=1;
		possibleMultiMoveActions.append("fly");
		possibleMultiMoveActions.append("fly");
		possibleMultiMoveActions.append("flyupsidedown");
		possibleMoveActions.append("fly");
		possibleMoveActions.append("fly");
		possibleMoveActions.append("flyupsidedown");
		possibleMoveActions.append("walking");
		possibleMoveActions.append("walking");
		possibleMoveActions.append("walking_wing");
		possibleMoveActions.append("walking_wing");
		possibleStandActions.append("hover");
		possibleStandActions.append("hover");
		possibleStandActions.append("hoverupsidedown");
		possibleStandActions.append("sleep");
		possibleStandActions.append("stand");
		possibleStandActions.append("stand");
		possibleStandActions.append("stand_wing");
		possibleStandActions.append("stand_wing");
	}
	bool changeGif() {
		
		if (oldmovex!=movex||oldmovey!=movey) {
			if (movex!=0||movey!=0) {
				if (movey!=0)
					action=possibleMultiMoveActions[qrand()%possibleMultiMoveActions.size()];
				else
					action=possibleMoveActions[qrand()%possibleMoveActions.size()];
				if (movex==1) 
					position="right";
				if (movex==-1)
					position="left";
			} else
				action=possibleStandActions[qrand()%possibleStandActions.size()];
			
			return true;
		}
		return false;
	}
	void doChangeGif() {
		oldmovex = movex;
		oldmovey = movey;
	}
	QString getFileName() {
		QTextStream out(stdout);
		out << "derpy_"+action+"_"+position+".gif";
		
		return "derpy_"+action+"_"+position+".gif";
	}
	void move() {
		if (qrand()%300==0) {
			if (movex!=0)
				movex=0;
			else {
				if (qrand()%2)
					movex=1;
				else
					movex=-1;
			}
		}
		if (qrand()%300==0) {
			if (movey!=0)
				movey=0;
			else {
				if (qrand()%2)
					movey=1;
				else
					movey=-1;
			}
		}
		posx+=movex*speed;
		posy+=movey*speed;
		if (posx<0) {
			posx=0;
			movex=0;
		}
		if (posy<0) {
			posy=0;
			movey=0;
		}
		
	}

private:
	QString action;
	QString position;
	int movex;
	int movey;
	int oldmovex;
	int oldmovey;
	int height;
	int width;
	int speed;
	QStringList possibleMultiMoveActions;
	QStringList possibleMoveActions;
	QStringList possibleStandActions;
};
derp derpy;
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool),
	ui(new Ui::MainWindow) {
	setAttribute(Qt::WA_TranslucentBackground);
	setStyleSheet("background:transparent;");
	ui->setupUi(this);
	
	QMovie *movie = new QMovie("derpy_stand_right.gif");
	ui->ponyLabel->setMovie(movie);
	
	resizeWindow();
	movie->start();
	QTimer *loopHandler = new QTimer(this);
	loopHandler->start(1000/60);
	QObject::connect(loopHandler, SIGNAL(timeout()), this, SLOT(loop()));
}

void MainWindow::resizeWindow() {
	int height = ui->ponyLabel->movie()->scaledSize().height();
	int width = ui->ponyLabel->movie()->scaledSize().width();
	ui->centralWidget->setMinimumSize(100,100);
	ui->centralWidget->setMaximumSize(100,100);
	ui->ponyLabel->setMinimumSize(100,100);
	ui->ponyLabel->setMaximumSize(100,100);
}
void MainWindow::loop() {
	derpy.move();
	if (derpy.changeGif()) {
		derpy.doChangeGif();
		ui->ponyLabel->movie()->stop();
		QMovie *movie = new QMovie(derpy.getFileName());
		ui->ponyLabel->setMovie(movie);
		movie->start();
	}
	move(QPoint(derpy.posx,derpy.posy));
}

MainWindow::~MainWindow() {
	delete ui;
}

