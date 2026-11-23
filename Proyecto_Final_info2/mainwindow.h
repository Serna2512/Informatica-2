#ifndef MAINWINDOW_H
#define MAINWINDOW_H

using namespace std;
#include <QMainWindow>
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    vector<QPixmap> spritesRigby; //vector que cotiene los sprites de Rigby
    QGraphicsPixmapItem* imagenRigby; //imagen que aparece en la pantalla

    Ui::MainWindow *ui;
    QGraphicsScene *escena;
};
#endif // MAINWINDOW_H
