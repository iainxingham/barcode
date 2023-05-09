#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QClipboard>

#include "about.h"
#include "rxr.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->barcode_gv->setScene(&barcodeScene);

    m_Barcode = new Code128Item();
    m_Barcode->setWidth( 300 );
    m_Barcode->setHeight( 120 );
    m_Barcode->setPos(0,0);
    barcodeScene.addItem( m_Barcode );
    barcodeScene.update();
    m_Barcode->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_barcode_but_clicked()
{
    if(validate_rxr(ui->rxr_edit->text())) {
         m_Barcode->setText(clean_rxr(ui->rxr_edit->text()));

     }

     else {
         QMessageBox msg(this);

         msg.setWindowTitle("Invalid RXR number");
         msg.setText("RXR numbers should consist of \"rxr\" or \"RXR\" followed by seven digits");
         msg.setIcon(QMessageBox::Critical);
         msg.exec();

         m_Barcode->setText("");
     }

     barcodeScene.update();
     m_Barcode->update();
}


void MainWindow::on_clear_but_clicked()
{
    ui->rxr_edit->setText("");
    m_Barcode->setText("");
    barcodeScene.update();
    m_Barcode->update();
}


void MainWindow::on_copy_but_clicked()
{
    QClipboard *clipboard = QGuiApplication::clipboard();

    clipboard->setText(ui->rxr_edit->text());
}


void MainWindow::on_actionExit_triggered()
{
    qApp->quit();
}


void MainWindow::on_actionAbout_triggered()
{
    About *about;

    about = new About(this);
    about->exec();
    delete about;
}

