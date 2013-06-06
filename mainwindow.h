#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QGroupBox>
#include <QLabel>
#include <QActionGroup>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	void resizeWindow();
	~MainWindow();
private slots:
	void loop();
private:
	Ui::MainWindow *ui;
	
};

#endif // MAINWINDOW_H
