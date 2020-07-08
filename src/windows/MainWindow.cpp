#include <QtWidgets/QFileDialog>
#include <QtWidgets/QPushButton>
#include "MainWindow.h"
#include <Document.h>
#include "ui_MainWindow.h"

using namespace BRLCAD;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QApplication::setStyle("fusion");
    showMaximized();
    setTheme();

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFileDialog);
    connect(ui->actionSave_As, &QAction::triggered, this, &MainWindow::saveFileDialog);
}

MainWindow::~MainWindow()
{
    for (std::pair<const int, Document *> pair: documents){
        Document * document = pair.second;
        delete document;
    }

    delete ui;
}

void MainWindow::openFile(const QString& filePath){
    Document & document = * (new Document(filePath.toUtf8().data()));

    ui->dockWidgetObjectsTree->setWidget(document.getObjectsTree());

    ui->documentArea->addSubWindow(document.getWindow());
    document.getWindow()->show();

    documents[documentsCount++] = &document;
}

void MainWindow::openFileDialog()
{
    QString filePath = QFileDialog::getOpenFileName(ui->documentArea, tr("Open BRL-CAD database"), QString(), "BRL-CAD Database (*.g)");
    openFile(filePath);
}

void MainWindow::saveFileDialog(){
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save BRL-CAD database"), QString(), "BRL-CAD Database (*.g)");
    //database->Save(filePath.toUtf8().data());
}

void MainWindow::setTheme() {

    // Hiden Window Title
    //setWindowFlags(Qt::FramelessWindowHint);

    //setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    //setWindowFlags(Qt::Popup);

    this->setStyleSheet("background-color:#f2f2f2;");
    //ui->documentArea->layout().setSpacing(0);
    // Set widget on the top right corner
    QPushButton* menuTopLeftButton = new QPushButton("TR", menuBar());
    menuBar()->setCornerWidget(menuTopLeftButton, Qt::TopRightCorner);
    //menuTopLeftButton->setFlat(true);
    //menuTopLeftButton->setStyle();


//    QFile stylesheet_file(":qdarkstyle/qss/MaterialDark.qss");
//    stylesheet_file.open(QIODevice::ReadOnly);
//    this->setStyleSheet(QLatin1String(stylesheet_file.readAll()));
}