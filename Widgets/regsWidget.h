#include <QStringList>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

class RegsWidget : public QWidget
{
    Q_OBJECT
private:
    QList<QLabel*> *values;
    QVBoxLayout *mainLayout;

public:
    RegsWidget(const QString &mainTitle, const QStringList &titles, const quint16 value);
    ~RegsWidget();

    void updateValues(const QList<quint16> &regValues);

private:
    void setupUI(const QString &mainTitle, const QStringList &titles, const quint16 value);
    QString toAnothSys(const int num, const int numSys, const int size);
    QLabel *createTitle(const QString &title);
};
