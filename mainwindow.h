#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDebug>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Stopwatch : public QObject{
    Q_OBJECT

public:
    Stopwatch(QObject *parent = nullptr);
    void start();
    void stop();
    void reset();
    bool isRunning() const;
    int getCurrentTime() const;
    int getlapCount() const;
    QString Display(int seconds);
    QString onLapClicked();

 Q_SIGNALS:
    void timeUpdated(QString seconds);

 private Q_SLOTS:
    void updateTime();

private:
    QTimer *timer;
    int elapsedTime; // в секундах
    bool running;
    int lapCount;
    int lastLapTime;
};


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

 private Q_SLOTS:
    void onStartStopClicked();
    void onClearClicked();
    void onLapClickedMW();
    void updateTimeDisplay(QString seconds);

private:
    Stopwatch *stopwatch;
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
