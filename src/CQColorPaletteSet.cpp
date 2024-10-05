#include <CQColorPaletteSet.h>
#include <CQColorPaletteDialog.h>
#include <CQPalettePreview.h>
#include <QStylePainter>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

CQColorPaletteSet::
CQColorPaletteSet(QWidget *parent) :
 QFrame(parent), primary_("Indigo"), secondary_("Pink"), text_("Grey")
{
  QGridLayout *layout = new QGridLayout(this);

  layout->addWidget(new QLabel("Primary"  ), 0, 0);
  layout->addWidget(new QLabel("Secondary"), 1, 0);
  layout->addWidget(new QLabel("Text"     ), 2, 0);

  primaryButton_   = new CQColorSetButton(CQColorSetButton::Primary  , primary_  );
  secondaryButton_ = new CQColorSetButton(CQColorSetButton::Secondary, secondary_);
  textButton_      = new CQColorSetButton(CQColorSetButton::Text     , text_     );

  connect(primaryButton_  , SIGNAL(clicked()), this, SLOT(primarySlot()));
  connect(secondaryButton_, SIGNAL(clicked()), this, SLOT(secondarySlot()));
  connect(textButton_     , SIGNAL(clicked()), this, SLOT(textSlot()));

  layout->addWidget(primaryButton_  , 0, 1);
  layout->addWidget(secondaryButton_, 1, 1);
  layout->addWidget(textButton_     , 2, 1);

  layout->setRowStretch(3, 1);
}

void
CQColorPaletteSet::
primarySlot()
{
  if (! primaryDialog_) {
    primaryDialog_ = new CQColorPaletteDialog;

    primaryDialog_->setStyle(CQColorPalette::SetStyle);

    connect(primaryDialog_, SIGNAL(colorSelected(const QString &, const QString &)),
            this, SLOT(primaryColorSlot(const QString &, const QString &)));
  }

  primaryDialog_->setColorSet(primary_);

  primaryDialog_->exec();
}

void
CQColorPaletteSet::
secondarySlot()
{
  if (! secondaryDialog_) {
    secondaryDialog_ = new CQColorPaletteDialog;

    connect(secondaryDialog_, SIGNAL(colorSelected(const QString &, const QString &)),
            this, SLOT(secondaryColorSlot(const QString &, const QString &)));
  }

  secondaryDialog_->setColorSet(secondary_);

  secondaryDialog_->exec();
}

void
CQColorPaletteSet::
textSlot()
{
  if (! textDialog_) {
    textDialog_ = new CQColorPaletteDialog;

    connect(textDialog_, SIGNAL(colorSelected(const QString &, const QString &)),
            this, SLOT(textColorSlot(const QString &, const QString &)));
  }

  textDialog_->setColorSet(text_);

  textDialog_->exec();
}

void
CQColorPaletteSet::
primaryColorSlot(const QString &setName, const QString & /*colorName*/)
{
  primary_ = setName;

  primaryButton_->setColorSet(primary_);

  emit valueChanged();
}

void
CQColorPaletteSet::
secondaryColorSlot(const QString &setName, const QString & /*colorName*/)
{
  secondary_ = setName;

  secondaryButton_->setColorSet(secondary_);

  emit valueChanged();
}

void
CQColorPaletteSet::
textColorSlot(const QString &setName, const QString & /*colorName*/)
{
  text_ = setName;

  textButton_->setColorSet(text_);

  emit valueChanged();
}

//------

CQColorSetButton::
CQColorSetButton(const Type &type, const QString &colorSet) :
 QPushButton(), type_(type), colorSet_(colorSet)
{
  updateText();
}

void
CQColorSetButton::
setColorSet(const QString &colorSet)
{
  colorSet_ = colorSet;

  updateText();

  update();
}

void
CQColorSetButton::
updateText()
{
  QColor color = ColorPaletteInst->getColorSetBase(colorSet_);

  QString str;

  //if      (type_ == Primary  ) str += "Primary -> ";
  //else if (type_ == Secondary) str += "Secondary -> ";
  //else if (type_ == Text     ) str += "Text -> ";

  str += colorSet_ + " : 500 ";

  str += color.name();

  setText(str);
}

void
CQColorSetButton::
paintEvent(QPaintEvent *)
{
  QStylePainter p(this);

  QStyleOptionButton option;

  initStyleOption(&option);

  QColor bg = ColorPaletteInst->getColorSetBase(colorSet_);
  QColor fg = ColorPalette::textColor(bg);

  option.palette.setColor(backgroundRole(), bg);
  option.palette.setColor(foregroundRole(), fg);

  p.drawControl(QStyle::CE_PushButton, option);
}
