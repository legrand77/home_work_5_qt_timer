#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), stopwatch(new Stopwatch(this))  // Инициализация счетчика кругов
{
    ui->setupUi(this);
    ui->startStopButton->setText("Старт");
    ui->clearButton->setText("Очистить");
    ui->lapButton->setText("Круг");
    ui->label->setText("00:00:00.0");
    ui->label_2->setText("Время");

    // Подключение сигналов и слотов
    connect(ui->startStopButton, &QPushButton::clicked, this, &MainWindow::onStartStopClicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::onClearClicked);
    connect(ui->lapButton, &QPushButton::clicked, this, &MainWindow::onLapClickedMW);
    connect(stopwatch, &Stopwatch::timeUpdated, this, &MainWindow::updateTimeDisplay);
}

MainWindow::~MainWindow() {
    delete stopwatch;
    delete ui;
}

void MainWindow::onStartStopClicked() {
    if (stopwatch->isRunning()) {
        stopwatch->stop();
        ui->startStopButton->setText("Старт");
    } else {
        stopwatch->start();
        ui->startStopButton->setText("Стоп");
    }
}

void MainWindow::onClearClicked() {
    stopwatch->reset();
    ui->label->setText("00:00:00.0");
    ui->textBrowser->clear();
}

void MainWindow::updateTimeDisplay(QString seconds) {
   ui->label->setText(seconds);
}

void MainWindow::onLapClickedMW() {
    ui->textBrowser->append(QString("Круг %1, время: %2 сек").arg(stopwatch->getlapCount()).arg(stopwatch->onLapClicked()));

}




