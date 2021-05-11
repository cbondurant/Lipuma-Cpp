#include <QApplication>
#include <QMainWindow>
#include <QPainter>
#include <QMenu>
#include <QAction>
#include <QDockWidget>
#include <QTextEdit>
#include <QtWidgets>
#include "widget/canvas.hpp"

#include "widget/toolSelector.hpp"
#include "file/serializer.hpp"

int main (int argc, char **argv){
	QApplication a(argc, argv);
	QGraphicsScene scene;
	Lipuma::Canvas *canvas = new Lipuma::Canvas(&scene);
	QMainWindow *mainWin = new QMainWindow();
	mainWin->setCentralWidget(canvas);
	QMenu* fileMenu = mainWin->menuBar()->addMenu("File");

	QAction* saveAction = fileMenu->addAction("&Save As");
	QObject::connect(saveAction, &QAction::triggered, fileMenu,  [canvas, mainWin](){
		QString s = QFileDialog::getSaveFileName(mainWin, "Open Image", "$HOME/Documents/", "Lipuma Files (*.lpm)");
		Lipuma::SerializeCanvas(canvas,&s);
	});

	QAction* loadAction = fileMenu->addAction("&Open Canvas");
	QObject::connect(loadAction, &QAction::triggered, mainWin,  [mainWin](){
		QString s = QFileDialog::getOpenFileName(mainWin, "Open Image", "$HOME/Documents/", "Lipuma Files (*.lpm)");
		Lipuma::Canvas* newcan = Lipuma::LoadCanvas(&s);
		if (newcan){
			mainWin->setCentralWidget(newcan);
		}
	});

	QDockWidget *dock = new QDockWidget();
	Lipuma::ToolSelector *selector = new Lipuma::ToolSelector(dock);
	QObject::connect(selector, &Lipuma::ToolSelector::toolSelected, canvas, &Lipuma::Canvas::toolSelected);
	dock->setWidget(selector);
	mainWin->addDockWidget(Qt::LeftDockWidgetArea, dock);

	mainWin->show();
	return a.exec();
}
