#ifndef TRANSLATEWINDOW_H
#define TRANSLATEWINDOW_H

#include <QWidget>
#include <QtGui>

class TranslateWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TranslateWindow(QWidget *parent);
    // ~TranslateWindow();

private slots:
    // void quit();
    void selectFileClicked();
    void translateClicked();

private:
    QWidget *iWidget;
    QString fileName;
    QVBoxLayout *layout;
    QTextEdit *selectedFileLabel;
    // QPushButton *translateButton;
    // QWidget *parent;
};

#endif // TRANSLATEWINDOW_H
