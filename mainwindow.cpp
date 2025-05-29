#include "mainwindow.h"
#include "./ui_mainwindow.h"

Stopwatch::Stopwatch(QObject *parent) : QObject(parent), elapsedTime(0), running(false) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Stopwatch::updateTime);
}

void Stopwatch::start() {
    if (!running) {
        running = true;
        timer->start(100); // обновление каждую 0,1 секунды
    }
}

void Stopwatch::stop() {
    if (running) {
        running = false;
        timer->stop();
    }
}

void Stopwatch::reset() {
    elapsedTime = 0;
    emit timeUpdated(elapsedTime);
}

bool Stopwatch::isRunning() const {
    return running;
}

int Stopwatch::getCurrentTime() const {
    return elapsedTime;
}

void Stopwatch::updateTime() {
    elapsedTime++;
    emit timeUpdated(elapsedTime);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), stopwatch(new Stopwatch(this)), lapCount(0), lastLapTime(0)  // Инициализация счетчика кругов
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
    connect(ui->lapButton, &QPushButton::clicked, this, &MainWindow::onLapClicked);
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
    lastLapTime = 0;
    ui->label->setText("00:00:00.0");
    ui->textBrowser->clear();
    lapCount = 0; // Сброс счетчика кругов
}



void MainWindow::onLapClicked() {
    if (stopwatch->isRunning()) {
        int currentLapTime = stopwatch->getCurrentTime(); // Получаем общее время
        int lapTime = currentLapTime - lastLapTime; // Вычисляем время круга
        lastLapTime = currentLapTime; // Обновляем время последнего круга
        lapCount++; // Увеличиваем номер круга
        updateLapDisplay(lapTime); // Передаем время круга для отображения
    }
}

QString MainWindow::Display(int seconds) {//вывод таймера
    int hours = seconds / 36000;
    int minutes = (seconds / 600) % 600;
    int secs = (seconds / 10) % 60;; // до 60 выводится текущее значение секунд
    int milsecs = seconds % 10; // до 60 выводится текущее значение секунд
    QString lapTimeStr = QString("%1:%2:%3.%4")
                             .arg(hours, 2, 10, QChar('0'))
                             .arg(minutes, 2, 10, QChar('0'))
                             .arg(secs, 2, 10, QChar('0'))
                             .arg(milsecs, 1, 10, QChar('0'));

    return lapTimeStr;

}

void MainWindow::updateTimeDisplay(int seconds) {
   ui->label->setText(Display(seconds));
}

void MainWindow::updateLapDisplay(int lapTime) {
    QString lapTimeStr = Display(lapTime);
    ui->textBrowser->append(QString("Круг %1, время: %2 сек").arg(lapCount).arg(lapTimeStr));
}
