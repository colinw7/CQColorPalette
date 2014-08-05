#include <CQPalettePreview.h>
#include <CColorPalette.h>
#include <CQStyleWidget.h>

#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QSlider>
#include <QLineEdit>
#include <QCheckBox>
#include <QRadioButton>

CQPalettePreview::
CQPalettePreview() :
 QFrame()
{
  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->setMargin(2); layout->setSpacing(2);

  QLabel *settings = CQStyleWidgetMgrInst->addT(new QLabel("Settings"), "h1");

  layout->addWidget(settings);

  QLabel *basics = CQStyleWidgetMgrInst->addT(new QLabel("Basics"), "h2");

  layout->addWidget(basics);

  QGroupBox *group = CQStyleWidgetMgrInst->addT(new QGroupBox("Group"), "h3");

  QGridLayout *grid1 = new QGridLayout;

  grid1->addWidget(CQStyleWidgetMgrInst->addT(new QLabel("Label"), "p"), 0, 0);
  grid1->addWidget(CQStyleWidgetMgrInst->addT(new QLabel("Text" ), "control" ), 0, 1);

  grid1->addWidget(CQStyleWidgetMgrInst->addT(new QLabel     ("Button"), "p"), 1, 0);
  grid1->addWidget(CQStyleWidgetMgrInst->addT(new QPushButton("Press" ), "control" ), 1, 1);

  grid1->addWidget(CQStyleWidgetMgrInst->addT(new QLabel ("Slider"      ), "p"), 2, 0);
  grid1->addWidget(CQStyleWidgetMgrInst->addT(new QSlider(Qt::Horizontal), "control" ), 2, 1);

  grid1->addWidget(CQStyleWidgetMgrInst->addT(new QLabel   ("Line Edit"), "p"), 3, 0);
  grid1->addWidget(CQStyleWidgetMgrInst->addT(new QLineEdit(           ), "control" ), 3, 1);

  grid1->addWidget(CQStyleWidgetMgrInst->addT(new QLabel   ("Check"), "p"), 4, 0);
  grid1->addWidget(CQStyleWidgetMgrInst->addT(new QCheckBox("Yes"  ), "control" ), 4, 1);

  grid1->addWidget(CQStyleWidgetMgrInst->addT(new QLabel      ("Radio"), "p"), 5, 0);
  grid1->addWidget(CQStyleWidgetMgrInst->addT(new QRadioButton("Yes"  ), "control" ), 5, 1);

  grid1->setColumnStretch(2, 1);

  group->setLayout(grid1);

  layout->addWidget(group);
  layout->addStretch(1);

  // TODO: tabs, groups
  setColorSet("Red", "Pink", "Grey");
}

void
CQPalettePreview::
setColorSet(const QString &primary, const QString &secondary, const QString &text)
{
  // The basic set of styles are based on a typographic scale of 12, 14, 16, 20, and 34

  QColor primaryColor   = ColorPaletteInst->getColorSetBase(primary);
  QColor secondaryColor = ColorPaletteInst->getColorSetBase(secondary);

  CQStyleWidgetMgrInst->setBackground("h1", primaryColor);
  CQStyleWidgetMgrInst->setForeground("h1", ColorPalette::textColor(primaryColor));
  CQStyleWidgetMgrInst->setFont      ("h1", QFont("Sans Serif", 20));

  const ColorPalette::ColorSet &textSet = ColorPaletteInst->getColorSet(text);

  CQStyleWidgetMgrInst->setForeground("h2", textSet.getColor("800"));
  CQStyleWidgetMgrInst->setFont      ("h2", QFont("Sans Serif", 16));

  CQStyleWidgetMgrInst->setForeground("h3", textSet.getColor("700"));
  CQStyleWidgetMgrInst->setFont      ("h3", QFont("Sans Serif", 14));

  CQStyleWidgetMgrInst->setForeground("h4", textSet.getColor("600"));
  CQStyleWidgetMgrInst->setFont      ("h4", QFont("Sans Serif", 12));

  CQStyleWidgetMgrInst->setForeground("p", textSet.getColor("900"));
  CQStyleWidgetMgrInst->setFont      ("p", QFont("Sans Serif", 10));

  CQStyleWidgetMgrInst->setForeground("control", secondaryColor);
  CQStyleWidgetMgrInst->setFont      ("control", QFont("Sans Serif", 10));
}
