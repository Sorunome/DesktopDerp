#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMovie>
#include <QLabel>
#include <QSize>
#include <QString>
#include <QTimer>
#include <QList>
#include <QTextStream>
#include <QImage>
#include <QDesktopWidget>

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
		possibleMultiMoveActions << "fly" << "fly" << "flyupsidedown";
		possibleMoveActions << "fly" << "fly" << "flyupsidedown" << "walking" << "walking" << "walking_wing" << "walking_wing";
		possibleStandActions << "hover" << "hover" << "hoverupsidedown" << "sleep" << "stand" << "stand" << "stand_wing" << "stand_wing";
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
		QString file = QCoreApplication::applicationDirPath() + "/derpy_" + action + "_" + position + ".gif";
		out << file << "\n";
		return file;
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
		
		QDesktopWidget *desk = new QDesktopWidget;
		if (desk->width()-width<posx) {
			posx = desk->width()-width;
			movex=0;
		}
		if (desk->height()-height<posy) {
			posy = desk->height()-height;
			movey=0;
		}
		delete desk;
		
	}
	void setDimentions(int newWidth,int newHeight) {
		width = newWidth;
		height = newHeight;
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
	QImage *img = new QImage(derpy.getFileName());
	
	ui->centralWidget->setMinimumSize(img->width(),img->height());
	ui->centralWidget->setMaximumSize(img->width(),img->height());
	ui->ponyLabel->setMinimumSize(img->width(),img->height());
	ui->ponyLabel->setMaximumSize(img->width(),img->height());
	derpy.setDimentions(img->width(),img->height());
}
void MainWindow::loop() {
	derpy.move();
	if (derpy.changeGif()) {
		derpy.doChangeGif();
		//ui->ponyLabel->movie()->stop();
		
		//QMovie *movie = new QMovie(derpy.getFileName());
		//ui->ponyLabel->setMovie(movie);
		//movie->start();
		ui->ponyLabel->movie()->stop();
		ui->ponyLabel->movie()->setFileName(derpy.getFileName());
		ui->ponyLabel->movie()->start();
	}
	move(QPoint(derpy.posx,derpy.posy));
}

MainWindow::~MainWindow() {
	delete ui;
}

