
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>
#include <QMessageBox>
#include <QDateTime>
#include <QFontDatabase>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    currentDate = QDate::currentDate();
    ui->dateLabel->setText(currentDate.toString("yyyy-MM-dd"));

    setupUI();
    setupConnections();

    // Ensure data directory exists
    QDir dataDir(QDir::currentPath() + "/data");
    if (!dataDir.exists()) {
        dataDir.mkpath(".");
    }

    loadData();
}

MainWindow::~MainWindow()
{
    saveData();
    delete ui;
}

void MainWindow::setupUI()
{
    // Set window properties
    this->setStyleSheet("background-color: black; color: white; border: 1px solid white;");
    this->setWindowTitle("qtWispr");

    // Set fonts and styles
    ui->dateLabel->setStyleSheet("color: white;");
    ui->prevButton->setStyleSheet("color: white; background-color: black; border: none;");
    ui->nextButton->setStyleSheet("color: white; background-color: black; border: none;");

    // Apply font to all widgets
    QFont gohuFont = this->font();
    ui->dateLabel->setFont(gohuFont);
    ui->prevButton->setFont(gohuFont);
    ui->nextButton->setFont(gohuFont);
    ui->tabWidget->setFont(gohuFont);
    ui->todoListWidget->setFont(gohuFont);
    ui->todoLineEdit->setFont(gohuFont);
    ui->addTodoButton->setFont(gohuFont);
    ui->notepadTextEdit->setFont(gohuFont);
    ui->alarmTimeEdit->setFont(gohuFont);
    ui->alarmMessageLineEdit->setFont(gohuFont);
    ui->addAlarmButton->setFont(gohuFont);
    ui->alarmListWidget->setFont(gohuFont);
}

void MainWindow::setupConnections()
{
    connect(ui->prevButton, &QPushButton::clicked, this, &MainWindow::on_prevButton_clicked);
    connect(ui->nextButton, &QPushButton::clicked, this, &MainWindow::on_nextButton_clicked);
    connect(ui->addTodoButton, &QPushButton::clicked, this, &MainWindow::on_addTodoButton_clicked);
    connect(ui->addAlarmButton, &QPushButton::clicked, this, &MainWindow::on_addAlarmButton_clicked);
}

void MainWindow::on_prevButton_clicked()
{
    saveData();
    currentDate = currentDate.addDays(-1);
    ui->dateLabel->setText(currentDate.toString("yyyy-MM-dd"));
    loadData();
}

void MainWindow::on_nextButton_clicked()
{
    saveData();
    currentDate = currentDate.addDays(1);
    ui->dateLabel->setText(currentDate.toString("yyyy-MM-dd"));
    loadData();
}

void MainWindow::saveData()
{
    QString filename = QDir::currentPath() + "/data/" + currentDate.toString("yyyy-MM-dd") + ".json";
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QJsonObject json;

        // Save to-do list
        QJsonArray todoArray;
        for (int i = 0; i < ui->todoListWidget->count(); ++i) {
            todoArray.append(ui->todoListWidget->item(i)->text());
        }
        json["todoList"] = todoArray;

        // Save notepad text
        json["notes"] = ui->notepadTextEdit->toPlainText();

        // Save alarms
        QJsonArray alarmArray;
        for (int i = 0; i < ui->alarmListWidget->count(); ++i) {
            QListWidgetItem *item = ui->alarmListWidget->item(i);
            QStringList alarmData = item->text().split(" - ");
            if (alarmData.size() == 2) {
                QJsonObject alarmObject;
                alarmObject["time"] = alarmData[0];
                alarmObject["message"] = alarmData[1];
                alarmArray.append(alarmObject);
            }
        }
        json["alarms"] = alarmArray;

        QJsonDocument doc(json);
        file.write(doc.toJson());
        file.close();
    }
}

void MainWindow::loadData()
{
    ui->todoListWidget->clear();
    ui->notepadTextEdit->clear();
    ui->alarmListWidget->clear();

    QString filename = QDir::currentPath() + "/data/" + currentDate.toString("yyyy-MM-dd") + ".json";
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument doc(QJsonDocument::fromJson(data));
        QJsonObject json = doc.object();

        // Load to-do list
        QJsonArray todoArray = json["todoList"].toArray();
        for (const QJsonValue &value : todoArray) {
            ui->todoListWidget->addItem(value.toString());
        }

        // Load notepad text
        ui->notepadTextEdit->setPlainText(json["notes"].toString());

        // Load alarms
        QJsonArray alarmArray = json["alarms"].toArray();
        for (const QJsonValue &value : alarmArray) {
            QJsonObject alarmObject = value.toObject();
            QString time = alarmObject["time"].toString();
            QString message = alarmObject["message"].toString();
            ui->alarmListWidget->addItem(time + " - " + message);
            // Set the alarm
            QTime alarmTime = QTime::fromString(time, "HH:mm");
            setAlarm(alarmTime, message);
        }

        file.close();
    }
}

void MainWindow::on_addTodoButton_clicked()
{
    QString itemText = ui->todoLineEdit->text();
    if (!itemText.isEmpty()) {
        ui->todoListWidget->addItem(itemText);
        ui->todoLineEdit->clear();
    }
}

void MainWindow::on_addAlarmButton_clicked()
{
    QTime alarmTime = ui->alarmTimeEdit->time();
    QString message = ui->alarmMessageLineEdit->text();

    if (!message.isEmpty()) {
        QString alarmText = alarmTime.toString("HH:mm") + " - " + message;
        ui->alarmListWidget->addItem(alarmText);
        setAlarm(alarmTime, message);

        ui->alarmMessageLineEdit->clear();
    }
}

void MainWindow::setAlarm(QTime alarmTime, const QString &message)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QDateTime alarmDateTime(currentDate, alarmTime);

    if (alarmDateTime < currentDateTime) {
        // If the time has already passed, do not set the alarm
        return;
    }

    qint64 msecs = currentDateTime.msecsTo(alarmDateTime);

    QTimer::singleShot(msecs, this, [this, message]() {
        QMessageBox::information(this, "Alarm", message);
    });
}
