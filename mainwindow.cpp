#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Compilador");

    QStringList titulos;
    ui->tableWidget->setColumnCount(2);
    titulos << "Tipo" << "Token";
    ui->tableWidget->setHorizontalHeaderLabels(titulos);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->tableWidget->setRowCount(0);
    ///obtiene todo el texto del textEdit
    QString myText = ui->textEdit->toPlainText();

    ///convertir QString a std::string
    Lexer lexer(myText.toStdString());
    vector<Token> tokens = lexer.scan();

    for(size_t i(0); i < tokens.size(); i++) {
        //cout << tokens.at(i).toString() << endl;
        ui->tableWidget->insertRow( ui->tableWidget->rowCount() );

        //tipo
        QString tipo =  QString::fromStdString(tokens.at(i).getType());
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1,0,new QTableWidgetItem (tipo));
        //token
        QString token = QString::fromStdString(tokens.at(i).getToken());
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1,1,new QTableWidgetItem (token));
    }


}

void MainWindow::on_clearButton_clicked()
{
    ui->textEdit->clear();
}
