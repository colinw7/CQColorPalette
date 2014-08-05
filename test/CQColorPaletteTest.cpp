#include <CQColorPaletteTest.h>
#include <CQColorPalette.h>
#include <CQPalettePreview.h>
#include <CQColorPaletteSet.h>
#include <CQStyleWidget.h>

#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

int
main(int argc, char **argv)
{
  QApplication app(argc, argv);

  CQColorPaletteTest *test = new CQColorPaletteTest;

  test->resize(600, 400);

  test->show();

  return app.exec();
}

CQColorPaletteTest::
CQColorPaletteTest()
{
  QHBoxLayout *layout = new QHBoxLayout(this);
  layout->setMargin(2); layout->setSpacing(2);

  preview_ = new CQPalettePreview;

  layout->addWidget(preview_);

  set_ = new CQColorPaletteSet;

  connect(set_, SIGNAL(valueChanged()), this, SLOT(setChangedSlot()));

  layout->addWidget(set_);

  preview_->setColorSet(set_->primary(), set_->secondary(), set_->text());
}

void
CQColorPaletteTest::
setChangedSlot()
{
  preview_->setColorSet(set_->primary(), set_->secondary(), set_->text());
}
