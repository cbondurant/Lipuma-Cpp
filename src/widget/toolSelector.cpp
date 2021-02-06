#include "widget/toolSelector.hpp"

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QShortcut>

#include "tool/fractalTool.hpp"
#include "tool/toolManager.hpp"

namespace Lipuma {
	ToolSelector::ToolSelector(QWidget *w) : QWidget(w) {
		QGridLayout *layout = new QGridLayout();
		setLayout(layout);
		QPushButton *fractal = new QPushButton("Fractal");
		QShortcut *fshortcut = new QShortcut(Qt::Key_F, this);
		connect(fshortcut, &QShortcut::activated, this, [=](){ toolSelected(ToolManager::getFractalTool()); });
		connect(fractal, &QPushButton::clicked, this, [=](){ toolSelected(ToolManager::getFractalTool()); });
		layout->addWidget(fractal, 0, 0);

		QPushButton *select = new QPushButton("Select");
		QShortcut *sshortcut = new QShortcut(Qt::Key_S, this);
		connect(sshortcut, &QShortcut::activated, this, [=](){ toolSelected(ToolManager::getSelectionTool()); });
		connect(select, &QPushButton::clicked, this, [=](){ toolSelected(ToolManager::getSelectionTool()); });
		layout->addWidget(select, 0, 1);

		QPushButton *curve = new QPushButton("Curve");
		QShortcut *cshortcut = new QShortcut(Qt::Key_C, this);
		connect(cshortcut, &QShortcut::activated, this, [=](){ toolSelected(ToolManager::getFractalCurveTool()); });
		connect(curve, &QPushButton::clicked, this, [=](){ toolSelected(ToolManager::getFractalCurveTool()); });
		layout->addWidget(curve, 1, 0);
	}
}
