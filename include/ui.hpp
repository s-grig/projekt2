#ifndef menu_hpp
#define menu_hpp
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QObject>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <string>
#include <iostream>
#include <drawer.hpp>
#include <QMessageBox>
#include <QApplication>

class Win : public QWidget {
	Q_OBJECT
public:
	Win(QWidget* parent = 0);
	QString get_path();
	void set_path(const QString& path_);
	void photo_processing();
	void error_occured();
	bool is_error();
public slots:
	void clicked_choose();
private:
	QLabel* label;
	QPushButton* exitButton;
	QPushButton* chooseButton;
	QString path;
	bool error = false;
	std::pair<std::vector<double>, std::vector<double>> data;
};

#endif
