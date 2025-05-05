#ifndef WINDOW_H
#define WINDOW_H
#include <QApplication>
#include <QPushButton>
#include <QFileDialog>
#include "QInputDialog"
#include <QGridLayout>
#include "bits/stdc++.h"
#include "QMessageBox"
#include "QComboBox"
#include "QLabel"
#include "QString"
#include <QTextEdit>
#include <sstream>
#include "string.h"


constexpr int kWindowSize = 1600;
constexpr int kSpacing = 15;
constexpr int kMargins = 30;
constexpr int kButtonWidth = 0xc8;
constexpr int kButtonHeight = 0x37;
constexpr int kMaxErrorNumber = 18;


class Window : public QWidget {
Q_OBJECT

public:

    Window();

private:

    GoodString* my_string_;
    QLabel* label_string_;
    void InputString();
    void ShowString();
    void ShowLength();
    void Strerror();
    void Strcmp();
    void Strcat();
    void Strcpy();
    void Strtok();
    void Strncmp();
    void Strncat();
    void Strncpy();
    void Resize();
    // DRY
    std::optional<size_t> GetSymbolsCount();
};



#endif //WINDOW_H
