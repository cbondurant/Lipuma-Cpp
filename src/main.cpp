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

int main (int argc, char **argv){
	QApplication a(argc, argv);
	QGraphicsScene scene;
	Lipuma::Canvas *canvas = new Lipuma::Canvas(&scene);
	QMainWindow *mainWin = new QMainWindow();
	mainWin->setCentralWidget(canvas);

	QDockWidget *dock = new QDockWidget();
	Lipuma::ToolSelector *selector = new Lipuma::ToolSelector(dock);
	QObject::connect(selector, &Lipuma::ToolSelector::toolSelected, canvas, &Lipuma::Canvas::toolSelected);
	dock->setWidget(selector);
	mainWin->addDockWidget(Qt::LeftDockWidgetArea, dock);

	mainWin->show();
	return a.exec();
}
