#include "window.h"


Window::Window() {
    my_bitset_ = new GoodBitset<kBits>(342);
    QString buttonStyle = R"(
        QPushButton {
            background-color: #ffffff;
            border: 2px solid #000000;
            color: #000000;
            padding: 10px 20px;
            font-size: 17px;
            margin: 5px;
            border-radius: 5px;
        }
        QPushButton:hover {
            background-color: #f0f0f0;
        }
        QPushButton:pressed {
            background-color: #d0d0d0;
            color: #333333;
        }
    )";

    QString textStyle = R"(
        font-size: 17px;
        color: #FFFFFF;
    )";

    QString textEditStyle = R"(
        font-size: 14px;
        background-color: #f9f9f9;
        color: #000000;
        border: 2px solid #000000;
        border-radius: 5px;
    )";


    auto* all_bits_button = new QPushButton("All", this);
    all_bits_button->setFixedSize(kButtonWidth, kButtonHeight);
    all_bits_button->setStyleSheet(buttonStyle);
    connect(all_bits_button, &QPushButton::clicked, this, &Window::ShowIfAllBits);

    auto* any_bits_button = new QPushButton("Any", this);
    any_bits_button->setFixedSize(kButtonWidth, kButtonHeight);
    any_bits_button->setStyleSheet(buttonStyle);
    connect(any_bits_button, &QPushButton::clicked, this, &Window::ShowIfAnyBits);

    auto* none_bits_button = new QPushButton("None", this);
    none_bits_button->setFixedSize(kButtonWidth, kButtonHeight);
    none_bits_button->setStyleSheet(buttonStyle);
    connect(none_bits_button, &QPushButton::clicked, this, &Window::ShowIfNoneBits);

    auto* count_bits_button = new QPushButton("Count", this);
    count_bits_button->setFixedSize(kButtonWidth, kButtonHeight);
    count_bits_button->setStyleSheet(buttonStyle);
    connect(count_bits_button, &QPushButton::clicked, this, &Window::ShowCountBits);

    auto* size_bits_button = new QPushButton("Size", this);
    size_bits_button->setFixedSize(kButtonWidth, kButtonHeight);
    size_bits_button->setStyleSheet(buttonStyle);
    connect(size_bits_button, &QPushButton::clicked, this, &Window::ShowSizeBits);

    auto* string_bits_button = new QPushButton("To String", this);
    string_bits_button->setFixedSize(kButtonWidth, kButtonHeight);
    string_bits_button->setStyleSheet(buttonStyle);
    connect(string_bits_button, &QPushButton::clicked, this, &Window::ShowStringBits);

    auto* ulong_bits_button = new QPushButton("To ULong", this);
    ulong_bits_button->setFixedSize(kButtonWidth, kButtonHeight);
    ulong_bits_button->setStyleSheet(buttonStyle);
    connect(ulong_bits_button, &QPushButton::clicked, this, &Window::ShowULongBits);

    auto* ullong_bits_button = new QPushButton("To ULLong", this);
    ullong_bits_button->setFixedSize(kButtonWidth, kButtonHeight);
    ullong_bits_button->setStyleSheet(buttonStyle);
    connect(ullong_bits_button, &QPushButton::clicked, this, &Window::ShowULLongBits);

    auto* set_all_bits_button = new QPushButton("Set all bits", this);
    set_all_bits_button->setFixedSize(kButtonWidth, kButtonHeight);
    set_all_bits_button->setStyleSheet(buttonStyle);
    connect(set_all_bits_button, &QPushButton::clicked, this, &Window::SetAllBits);

    auto* flip_all_bits_button = new QPushButton("Flip all bits", this);
    flip_all_bits_button->setFixedSize(kButtonWidth, kButtonHeight);
    flip_all_bits_button->setStyleSheet(buttonStyle);
    connect(flip_all_bits_button, &QPushButton::clicked, this, &Window::FlipAllBits);

    auto* reset_all_bits_button = new QPushButton("Reset all bits", this);
    reset_all_bits_button->setFixedSize(kButtonWidth, kButtonHeight);
    reset_all_bits_button->setStyleSheet(buttonStyle);
    connect(reset_all_bits_button, &QPushButton::clicked, this, &Window::ResetAllBits);

    auto* flip_bit_button = new QPushButton("Flip bit", this);
    flip_bit_button->setFixedSize(kButtonWidth, kButtonHeight);
    flip_bit_button->setStyleSheet(buttonStyle);
    connect(flip_bit_button, &QPushButton::clicked, this, &Window::FlipBit);

    auto* reset_bit_button = new QPushButton("Reset bit", this);
    reset_bit_button->setFixedSize(kButtonWidth, kButtonHeight);
    reset_bit_button->setStyleSheet(buttonStyle);
    connect(reset_bit_button, &QPushButton::clicked, this, &Window::ResetBit);

    auto* set_bit_button = new QPushButton("Set bit", this);
    set_bit_button->setFixedSize(kButtonWidth, kButtonHeight);
    set_bit_button->setStyleSheet(buttonStyle);
    connect(set_bit_button, &QPushButton::clicked, this, &Window::SetBit);

    auto* test_bit_button = new QPushButton("Test bit", this);
    test_bit_button->setFixedSize(kButtonWidth, kButtonHeight);
    test_bit_button->setStyleSheet(buttonStyle);
    connect(test_bit_button, &QPushButton::clicked, this, &Window::TestBit);

    auto* main_layout = new QGridLayout(this);
    main_layout->setSpacing(kSpacing);
    main_layout->setContentsMargins(kMargins,kMargins,kMargins,kMargins);
    main_layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    main_layout->addWidget(all_bits_button,0,0);
    main_layout->addWidget(any_bits_button,0,1);
    main_layout->addWidget(none_bits_button,0,2);
    main_layout->addWidget(count_bits_button,0,3);
    main_layout->addWidget(size_bits_button,0,4);
    main_layout->addWidget(string_bits_button,1,0);
    main_layout->addWidget(ulong_bits_button,1,1);
    main_layout->addWidget(ullong_bits_button,1,2);
    main_layout->addWidget(set_all_bits_button,1,3);
    main_layout->addWidget(flip_all_bits_button,1,4);
    main_layout->addWidget(reset_all_bits_button,2,0);
    main_layout->addWidget(flip_bit_button,2,1);
    main_layout->addWidget(reset_bit_button,2,2);
    main_layout->addWidget(set_bit_button,2,3);
    main_layout->addWidget(test_bit_button,2,4);

    setLayout(main_layout);
}

void Window::ShowIfAllBits() {
    QMessageBox::information(this, "All bits", "Your bitset has all 1-bits - " + QString(my_bitset_->all() ? "True" : "False"));
}

void Window::ShowIfAnyBits() {
    QMessageBox::information(this, "Any bits", "Your bitset has any 1-bits - " + QString(my_bitset_->any() ? "True" : "False"));
}

void Window::ShowIfNoneBits() {
    QMessageBox::information(this, "None bits", "Your bitset has no 1-bits - " + QString(my_bitset_->none() ? "True" : "False"));
}

void Window::ShowCountBits() {
    QMessageBox::information(this, "Count bits", "Your bitset has " + QString::number(my_bitset_->count()) + " 1-bits");
}

void Window::ShowSizeBits() {
    QMessageBox::information(this, "Size", "Your bitset has " + QString::number(my_bitset_->size()) + " bits");
}

void Window::ShowStringBits() {
    QMessageBox::information(this, "To string", "Your bitset in string is " + QString::fromStdString(my_bitset_->to_string()));
}

void Window::ShowULongBits() {
    QMessageBox::information(this, "To ulong", "Your bitset in ulong is " + QString::number(my_bitset_->to_ulong()));
}

void Window::ShowULLongBits() {
    QMessageBox::information(this, "To ullong", "Your bitset in ullong is " + QString::number(my_bitset_->to_ullong()));
}

void Window::SetAllBits() {
    my_bitset_->set();
    QMessageBox::information(this, "Set all bits", "All bits in your bitset are set to 1");
}

void Window::FlipAllBits() {
    my_bitset_->flip();
    QMessageBox::information(this, "Flip all bits", "All bits in your bitset has been flipped");
}

void Window::ResetAllBits() {
    my_bitset_->reset();
    QMessageBox::information(this, "Reset all bits", "All bits in your bitset has been reset");
}


void Window::FlipBit() {
    auto pos_opt = GetPos();
    if (!pos_opt.has_value()) {
        QMessageBox::information(this, "Flip bit", "Operation cancelled.");
        return;
    }

    size_t pos = pos_opt.value();
    my_bitset_->flip(pos);
    QMessageBox::information(this, "Flip bit", "Bit in the position " + QString::number(pos) + " has been flipped");
}

void Window::ResetBit() {
    auto pos_opt = GetPos();
    if (!pos_opt.has_value()) {
        QMessageBox::information(this, "Reset bit", "Operation cancelled.");
        return;
    }

    size_t pos = pos_opt.value();
    my_bitset_->reset(pos);
    QMessageBox::information(this, "Reset bit", "Bit in the position " + QString::number(pos) + " has been reset");
}

void Window::SetBit() {
    auto pos_opt = GetPos();
    if (!pos_opt.has_value()) {
        QMessageBox::information(this, "Set bit", "Operation cancelled.");
        return;
    }

    size_t pos = pos_opt.value();
    my_bitset_->set(pos);
    QMessageBox::information(this, "Set bit", "Bit in the position " + QString::number(pos) + " has been set");
}

void Window::TestBit() {
    auto pos_opt = GetPos();
    if (!pos_opt.has_value()) {
        QMessageBox::information(this, "Set bit", "Operation cancelled.");
        return;
    }

    size_t pos = pos_opt.value();
    QMessageBox::information(this, "Set bit", "Bit in the position " + QString::number(pos) + " is 1 - " + QString(my_bitset_->test(pos) ? "True" : "False") );
}

std::optional<size_t> Window::GetPos() {
    bool input_ok = false;
    int pos = QInputDialog::getInt(this,"Position", "Input position: ", 0, 0, static_cast<int>(my_bitset_->size()) - 1, 1, &input_ok);
    if (input_ok)
        return static_cast<size_t>(pos);
    else
        return std::nullopt;
}

