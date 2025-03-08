#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMouseEvent>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override; //mousepress
    void mouseMoveEvent(QMouseEvent *event) override; //mousepress

private:
    Ui::MainWindow *ui;
    QPoint m_dragPosition;

private slots:
    void NumPressed();
    void MathButtonPressed();
    void EqualButtonPressed();
    void ChangeNumberSign();
    void ClearButtonPressed();
    void MemAddButtonPressed();
    void MemClearButtonPressed();
    void MemGetButtonPressed();

};
#endif // MAINWINDOW_H
