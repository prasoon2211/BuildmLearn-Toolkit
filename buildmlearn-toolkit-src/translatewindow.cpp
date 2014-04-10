#include <zmq.h>
#include <cstring>
#include "translatewindow.h"

TranslateWindow::TranslateWindow(QWidget *parent):
    QMainWindow(parent)
{
    // fileName = "";
    setFixedSize(480, 320);
    setWindowTitle(tr("&Translate"));

    iWidget = new QWidget(this);
    iWidget->setFixedSize(200, 200);

    QVBoxLayout *v_layout = new QVBoxLayout(iWidget);
    QHBoxLayout *h_layout_tl = new QHBoxLayout();

    QPushButton *iFileChooser = new QPushButton(tr("&Select A File"), this);
    QTextEdit *iSelectedFile = new QTextEdit(this);
    iSelectedFile->setReadOnly(true);
    iSelectedFile->resize(iSelectedFile->width(), 20);
    iSelectedFile->setText(tr("No file selected"));

    QPushButton *iTranslateButton = new QPushButton(tr("&Translate"), this);

    h_layout_tl->addWidget(iFileChooser);
    h_layout_tl->addWidget(iSelectedFile);

    v_layout->addLayout(h_layout_tl);
    v_layout->addWidget(iTranslateButton);
    this->layout = v_layout;
    this->selectedFileLabel = iSelectedFile;

    // Connect signals and slots
    connect(iFileChooser, SIGNAL(clicked()), this, SLOT(selectFileClicked()));
    connect(iTranslateButton, SIGNAL(clicked()), this, SLOT(translateClicked()));
}


void TranslateWindow::selectFileClicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("&Select File"),
                                                            "",tr("*.csv"));
    selectedFileLabel->setText(fileName);
}

void TranslateWindow::translateClicked()
{
    QMessageBox mbox;
    if(fileName != "")
    {
        // make an IPC call to the Python scripts
        // Assming that python process is running
        void *context = zmq_ctx_new();
        void *requester = zmq_socket(context, ZMQ_REQ);
        zmq_connect(requester, "tcp://localhost:5555");

        char newFileName[256];
        QByteArray barray = fileName.toLocal8Bit();
        const char *file_name_c = barray.data();
        zmq_send(requester, file_name_c, strlen(file_name_c) , 0);
        zmq_recv(requester, newFileName, 256, 0);

        if(strcmp(newFileName, "0") == 0)
        {
            mbox.setText(tr("Could not initialize file. Please try again"));
        }
        else
        {
            // handle the generated file
            // For now, just show the file name
            mbox.setText(tr(newFileName));
        }
        zmq_close(requester);
        zmq_ctx_destroy(context);
    }
    else
        mbox.setText(tr("No file chosen."));
    mbox.exec();
}
