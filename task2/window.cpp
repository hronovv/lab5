#include "window.h"


Window::Window() {
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

    label_string_ = new QLabel("String: ",this);
    label_string_->setStyleSheet(textStyle);


    auto* input_string_button = new QPushButton("Input string", this);
    input_string_button->setFixedSize(kButtonWidth, kButtonHeight);
    input_string_button->setStyleSheet(buttonStyle);
    connect(input_string_button, &QPushButton::clicked, this, &Window::InputString);

    auto* show_string_button = new QPushButton("Show string", this);
    show_string_button->setFixedSize(kButtonWidth, kButtonHeight);
    show_string_button->setStyleSheet(buttonStyle);
    connect(show_string_button, &QPushButton::clicked, this, &Window::ShowString);

    auto* show_length_button = new QPushButton("Show length", this);
    show_length_button->setFixedSize(kButtonWidth, kButtonHeight);
    show_length_button->setStyleSheet(buttonStyle);
    connect(show_length_button, &QPushButton::clicked, this, &Window::ShowLength);

    auto* strerror_button = new QPushButton("Strerror", this);
    strerror_button->setFixedSize(kButtonWidth, kButtonHeight);
    strerror_button->setStyleSheet(buttonStyle);
    connect(strerror_button, &QPushButton::clicked, this, &Window::Strerror);

    auto* strcmp_button = new QPushButton("Strcmp", this);
    strcmp_button->setFixedSize(kButtonWidth, kButtonHeight);
    strcmp_button->setStyleSheet(buttonStyle);
    connect(strcmp_button, &QPushButton::clicked, this, &Window::Strcmp);

    auto* strcat_button = new QPushButton("Strcat", this);
    strcat_button->setFixedSize(kButtonWidth, kButtonHeight);
    strcat_button->setStyleSheet(buttonStyle);
    connect(strcat_button, &QPushButton::clicked, this, &Window::Strcat);

    auto* strcpy_button = new QPushButton("Strcpy", this);
    strcpy_button->setFixedSize(kButtonWidth, kButtonHeight);
    strcpy_button->setStyleSheet(buttonStyle);
    connect(strcpy_button, &QPushButton::clicked, this, &Window::Strcpy);

    auto* strtok_button = new QPushButton("Strtok", this);
    strtok_button->setFixedSize(kButtonWidth, kButtonHeight);
    strtok_button->setStyleSheet(buttonStyle);
    connect(strtok_button, &QPushButton::clicked, this, &Window::Strtok);

    auto* strncmp_button = new QPushButton("Strncmp", this);
    strncmp_button->setFixedSize(kButtonWidth, kButtonHeight);
    strncmp_button->setStyleSheet(buttonStyle);
    connect(strncmp_button, &QPushButton::clicked, this, &Window::Strncmp);

    auto* strncat_button = new QPushButton("Strncat", this);
    strncat_button->setFixedSize(kButtonWidth, kButtonHeight);
    strncat_button->setStyleSheet(buttonStyle);
    connect(strncat_button, &QPushButton::clicked, this, &Window::Strncat);

    auto* strncpy_button = new QPushButton("Strncpy", this);
    strncpy_button->setFixedSize(kButtonWidth, kButtonHeight);
    strncpy_button->setStyleSheet(buttonStyle);
    connect(strncpy_button, &QPushButton::clicked, this, &Window::Strncpy);

    auto* resize_button = new QPushButton("Resize", this);
    resize_button->setFixedSize(kButtonWidth, kButtonHeight);
    resize_button->setStyleSheet(buttonStyle);
    connect(resize_button, &QPushButton::clicked, this, &Window::Resize);


    auto* main_layout = new QGridLayout(this);
    main_layout->setSpacing(kSpacing);
    main_layout->setContentsMargins(kMargins,kMargins,kMargins,kMargins);
    main_layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    main_layout->addWidget(label_string_,0,0);
    main_layout->addWidget(input_string_button,1,0);
    main_layout->addWidget(show_string_button,1,1);
    main_layout->addWidget(show_length_button,1,2);
    main_layout->addWidget(strerror_button,1,3);
    main_layout->addWidget(strcmp_button,1,4);
    main_layout->addWidget(strcat_button,2,0);
    main_layout->addWidget(strcpy_button,2,1);
    main_layout->addWidget(strtok_button,2,2);
    main_layout->addWidget(strncmp_button,2,3);
    main_layout->addWidget(strncat_button,2,4);
    main_layout->addWidget(strncpy_button,3,0);
    main_layout->addWidget(resize_button,3,1);

    setLayout(main_layout);
}

void Window::InputString() {
    QString string = QInputDialog::getText(this, "String", "Input string: ");
    delete my_string_;
    my_string_ = new GoodString(string.toStdString().c_str());
}

void Window::ShowString() {
    if (my_string_) {
        label_string_->setText("String: " + QString(my_string_->data()));
    } else {
        label_string_->setText("String is empty");
    }
}

void Window::ShowLength() {
    if (my_string_) {
        QMessageBox::information(this, "Length", "Length of your string is " + QString::number(my_string_->strlen(my_string_->data())));
    } else {
        QMessageBox::warning(this,"Error","Firstly, create a string");
    }
}

void Window::Strerror() {
    bool input_ok = false;
    int res = QInputDialog::getInt(this,"Strerror", "Input error number: ", 0, 0, kMaxErrorNumber,1, &input_ok);
    QMessageBox::information(this, "Stterror", "The error of this number is " + QString::fromStdString(my_string_->strerror(res)));
}

void Window::Strcmp() {
    if (my_string_) {
        QString string_to_compare = QInputDialog::getText(this, "String to compare", "Input string to compare: ");
        int res_cmp = my_string_->strcmp(my_string_->data(),string_to_compare.toStdString().c_str());
        QMessageBox::information(this, "Strcmp", res_cmp == 1? "First string is larger" : res_cmp == 0? "Strings are equal" : "Second string is larger");
    } else {
        QMessageBox::warning(this,"Error","Firstly, create a string");
    }
}

void Window::Strcat() {
    if (my_string_) {
        QString string_to_concatenate = QInputDialog::getText(this, "String to concatenate", "Input string to concatenate: ");
        my_string_->strcat(my_string_->data(),string_to_concatenate.toStdString().c_str());
        QMessageBox::information(this,"Success","Your strings have been concatenated");
    } else {
        QMessageBox::warning(this,"Error","Firstly, create a string");
    }
}

void Window::Strcpy() {
    if (my_string_) {
        QString string_to_copy = QInputDialog::getText(this, "String to copy", "Input string to copy: ");
        my_string_->strcpy(my_string_->data(),string_to_copy.toStdString().c_str());
        QMessageBox::information(this,"Success","Your string has been copied");
    } else {
        QMessageBox::warning(this,"Error","Firstly, create a string");
    }
}

void Window::Strtok() {
    if (my_string_) {
        QString delimStr = QInputDialog::getText(this, "Delimiters", "Enter delimiters (e.g., ,.; ):");
        std::string copy = my_string_->data();
        char *cstr = copy.data();
        const char *delims = delimStr.toStdString().c_str();
        QString result;
        char *token = std::strtok(cstr, delims);
        while (token) {
            result += QString(token) + '\n';
            token = std::strtok(nullptr, delims);
        }
        if (result.isEmpty()) {
            result = "No tokens found";
        }
        QMessageBox::information(this, "Tokens", result);
    } else {
        QMessageBox::warning(this, "Error", "Firstly, create a string");
    }
}

void Window::Strncmp() {
    if (my_string_) {
        QString string_to_compare = QInputDialog::getText(this, "String to compare", "Input string to compare: ");
        auto symbols_opt = GetSymbolsCount();
        if (!symbols_opt.has_value()) {
            QMessageBox::information(this, "Strncmp", "Operation cancelled.");
            return;
        }
        size_t symbols_count = symbols_opt.value();
        int res_cmp = my_string_->strncmp(my_string_->data(),string_to_compare.toStdString().c_str(),symbols_count);
        QMessageBox::information(this, "Strncmp", res_cmp == 1? "First string is larger" : res_cmp == 0? "Strings are equal" : "Second string is larger");
    } else {
        QMessageBox::warning(this,"Error","Firstly, create a string");
    }
}

void Window::Strncat() {
    if (my_string_) {
        QString string_to_concatenate = QInputDialog::getText(this, "String to concatenate", "Input string to concatenate: ");
        auto symbols_opt = GetSymbolsCount();
        if (!symbols_opt.has_value()) {
            QMessageBox::information(this, "Strncat", "Operation cancelled.");
            return;
        }
        size_t symbols_count = symbols_opt.value();
        my_string_->strncat(my_string_->data(),string_to_concatenate.toStdString().c_str(),symbols_count);
        QMessageBox::information(this,"Success","Your strings have been concatenated");
    } else {
        QMessageBox::warning(this,"Error","Firstly, create a string");
    }
}

void Window::Strncpy() {
    if (my_string_) {
        QString string_to_copy = QInputDialog::getText(this, "String to copy", "Input string to copy: ");
        auto symbols_opt = GetSymbolsCount();
        if (!symbols_opt.has_value()) {
            QMessageBox::information(this, "Strncpy", "Operation cancelled.");
            return;
        }
        size_t symbols_count = symbols_opt.value();
        my_string_->strncpy(my_string_->data(),string_to_copy.toStdString().c_str(),symbols_count);
        QMessageBox::information(this,"Success","Your string has been copied");
    } else {
        QMessageBox::warning(this,"Error","Firstly, create a string");
    }
}

void Window::Resize() {
    bool ok = false;
    unsigned long long new_size = -1;
    QString number = QInputDialog::getText(nullptr, "New Size","Input new size:",QLineEdit::Normal, "", &ok);
    if (ok && !number.isEmpty()) {
        bool nOk;
        new_size = number.toULongLong(&nOk);
        if (nOk && new_size >= 0) {
            my_string_->resize(new_size);
            QMessageBox::information(this,"Success", "New size is set");
        } else {
            QMessageBox::warning(nullptr, "Error","Incorrect size");
        }
    } else {
        QMessageBox::warning(nullptr, "Error","Input proper size");
    }
}

std::optional<size_t> Window::GetSymbolsCount() {
    bool input_ok = false;
    int pos = QInputDialog::getInt(this,"Symbols", "Input the amount of symbols: ", 0, 0, INT32_MAX, 1, &input_ok);
    if (input_ok)
        return static_cast<size_t>(pos);
    else
        return std::nullopt;
}