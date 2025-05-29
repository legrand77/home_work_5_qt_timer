#include "mainwindow.h"

Stopwatch::Stopwatch(QObject *parent) : QObject(parent), elapsedTime(0), running(false), lapCount(1), lastLapTime(0) {
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
    lastLapTime = 0;
    lapCount = 1;
    emit timeUpdated(Display(elapsedTime));
}

bool Stopwatch::isRunning() const {
    return running;
}

int Stopwatch::getCurrentTime() const {
    return elapsedTime;
}

int Stopwatch::getlapCount() const {
    return lapCount;
}


void Stopwatch::updateTime() {
    elapsedTime++;
    emit timeUpdated(Display(elapsedTime));
}

QString Stopwatch::Display(int seconds) {//вывод таймера
    int hours = seconds / 36000;
    int minutes = (seconds / 600) % 600;
    int secs = (seconds / 10) % 60;; // до 60 выводится текущее значение секунд
    int milsecs = seconds % 10; // до 10 выводится текущее значение секунд
    QString lapTimeStr = QString("%1:%2:%3.%4")
                             .arg(hours, 2, 10, QChar('0'))
                             .arg(minutes, 2, 10, QChar('0'))
                             .arg(secs, 2, 10, QChar('0'))
                             .arg(milsecs, 1, 10, QChar('0'));

    return lapTimeStr;

}

QString Stopwatch::onLapClicked() {
        int currentLapTime = getCurrentTime(); // Получаем общее время
        int lapTime = currentLapTime - lastLapTime; // Вычисляем время круга
        lastLapTime = currentLapTime; // Обновляем время последнего круга
        lapCount++; // Увеличиваем номер круга
        QString lapTimeStr = Display(lapTime);
        return lapTimeStr;
}
