#include "selectrole.h"
#include "ui_selectrole.h"

SelectRole::SelectRole(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectRole)
{
    ui->setupUi(this);
    setWindowTitle("Select role");
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    ui->readerButton->setVisible(false);
    ui->librarianButton->setVisible(false);
    ui->usermanagerButton->setVisible(false);
    connect(ui->loginButton, SIGNAL(clicked(bool)), this, SLOT(startProgram()));
}
void SelectRole::enableButton(std::string role)
{
    if (role[0] == '1')
        ui->readerButton->setVisible(true);
    if (role[1] == '1')
        ui->librarianButton->setVisible(true);
    if (role[2] == '1')
        ui->usermanagerButton->setVisible(true);
}



SelectRole::~SelectRole()
{
    delete ui;
}
