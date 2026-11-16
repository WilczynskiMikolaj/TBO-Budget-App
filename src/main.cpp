#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QLabel okno("Qt działa!");
    okno.resize(300, 100);
    okno.show();

    return app.exec();
}