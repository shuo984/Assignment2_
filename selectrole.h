#ifndef SELECTROLE_H
#define SELECTROLE_H

#include <QDialog>
#include <string>

namespace Ui {
class SelectRole;
}

class SelectRole : public QDialog
{
    Q_OBJECT

public:
    explicit SelectRole(QWidget *parent = 0);
    ~SelectRole();
    void enableButton(std::string);
private:
    Ui::SelectRole *ui;
};

#endif // SELECTROLE_H
