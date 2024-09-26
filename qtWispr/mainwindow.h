
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QTimer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setAlarm(QTime alarmTime, const QString &message);

private slots:
    void on_prevButton_clicked();
    void on_nextButton_clicked();
    void on_addTodoButton_clicked();
    void on_addAlarmButton_clicked();

    void saveData();
    void loadData();

private:
    Ui::MainWindow *ui;
    QDate currentDate;

    void setupUI();
    void setupConnections();
};

#endif // MAINWINDOW_H
