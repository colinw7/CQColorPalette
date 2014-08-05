#include <CQColorPaletteDialog.h>
#include <CQColorPalette.h>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

CQColorPaletteDialog::
CQColorPaletteDialog(QWidget *parent) :
 QDialog(parent)
{
  setObjectName("colorPaletteDialog");

  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->setMargin(2); layout->setSpacing(2);

  pal_ = new CQColorPalette;

  layout->addWidget(pal_);

  QHBoxLayout *blayout = new QHBoxLayout;
  blayout->setMargin(2); blayout->setSpacing(2);

  blayout->addStretch();

  QPushButton *okButton = new QPushButton("OK");

  connect(okButton, SIGNAL(clicked()), this, SLOT(okSlot()));

  blayout->addWidget(okButton);

  // add close/cancel button
  QPushButton *cancelButton = new QPushButton("Close");

  connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelSlot()));

  blayout->addWidget(cancelButton);

  layout->addLayout(blayout);
}

void
CQColorPaletteDialog::
setStyle(const CQColorPalette::Style &style)
{
  pal_->setStyle(style);
}

void
CQColorPaletteDialog::
setColorSet(const QString &setName)
{
  pal_->setColorSet(setName);
}

void
CQColorPaletteDialog::
setColorId(const QString &idName)
{
  pal_->setColorId(idName);
}

void
CQColorPaletteDialog::
okSlot()
{
  emit colorSelected(pal_->colorSet(), pal_->colorId());

  QDialog::accept();
}

void
CQColorPaletteDialog::
cancelSlot()
{
  QDialog::accept();
}
