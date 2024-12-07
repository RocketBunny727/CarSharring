#ifndef SLIDE_H
#define SLIDE_H

#include <QMainWindow>

namespace Ui {
class Slide;
}

class Slide : public QMainWindow
{
    Q_OBJECT

public:
    explicit Slide(QWidget *parent = nullptr);
    ~Slide();

    Ui::Slide *ui;  // Make ui public for access in MainWindow

private:
    Ui::Slide *ui_private;
};

#endif // SLIDE_H
