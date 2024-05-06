#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include "Base.h"
#include <QTextEdit>
#include <QTextCursor>
#include <QLabel>

class polinomemenager : public QMainWindow
{
    Q_OBJECT

public:
    polinomemenager(QWidget *parent = nullptr);
    ~polinomemenager() = default;

    Base base;
    Polinome c;
    
    int error_counter = 0;

    void RTFD();

    void ShowWarning(std::string problem);
    void Update();

private slots:

    void AddSlot();
    void InPointSlot();
    void PlusSlot();
    void MultiplicateSlot();
    void DefSlot();
    void DelSlot();
    void RootSlot();
    void DocumentationSlot();
    void SaveSlot();
    void LoadSlot();
    void SameSlot();
    void DeleteSlot();

private:
    QPushButton* Add;
    QPushButton* InPoint;
    QPushButton* Plus;
    QPushButton* Multiplicate;
    QPushButton* Def;
    QPushButton* Del;
    QPushButton* Roots;
    QPushButton* Documentation;
    QPushButton* SaveToFile;
    QPushButton* LoadFromFile;
    QPushButton* IsTheSame;
    QPushButton* Delete;


    QMessageBox* warning;
    QLabel* rtfd;
    QTextEdit* data;
};
