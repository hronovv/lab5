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
#include <optional>
#include "bitset.h"


constexpr int kWindowSize = 1600;
constexpr int kSpacing = 25;
constexpr int kMargins = 10;
constexpr int kButtonWidth = 0xc8;
constexpr int kButtonHeight = 0x37;
constexpr int kBits = 21;


class Window : public QWidget {
Q_OBJECT

public:

    Window();

private:

    GoodBitset<kBits>* my_bitset_;
    void ShowIfAllBits();
    void ShowIfAnyBits();
    void ShowIfNoneBits();
    void ShowCountBits();
    void ShowSizeBits();
    void ShowStringBits();
    void ShowULongBits();
    void ShowULLongBits();
    void SetAllBits();
    void FlipAllBits();
    void ResetAllBits();
    void FlipBit();
    void ResetBit();
    void SetBit();
    void TestBit();

    // pos-function
    std::optional<size_t> GetPos();
};



#endif //WINDOW_H
