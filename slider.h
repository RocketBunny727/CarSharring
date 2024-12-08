#ifndef SLIDER_H
#define SLIDER_H

#include <QWidget>

namespace Ui {
class Slide;
}

class Slide : public QWidget
{
    Q_OBJECT

public:
    explicit Slide(QWidget *parent = nullptr);
    ~Slide();

    Ui::Slide *ui;  // Make ui public for access in MainWindow

private:
    Ui::Slide *ui_private;
};

#endif // SLIDER_H
