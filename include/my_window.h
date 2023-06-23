#pragma once

#include <QPushButton>
#include <QSlider>
#include <QLabel>

class MY_WINDOW : public QWidget
{
    Q_OBJECT
public:

    MY_WINDOW();
    void choice_picture();
    void save_picture();
    void bluer_effect();
private:
    QString imagePath;
    QLabel *label;
    QSlider *meanBlure;
    QPushButton *newImage;
    QPushButton *saveImage;
    QImage *originalImage;
    void Rendering(const int& numBlure);
private slots:
    void newBlure(int value);
    void clickedNew();
    void clickImage();
};
