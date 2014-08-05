#ifndef CQColorPaletteDialog_H
#define CQColorPaletteDialog_H

#include <QDialog>
#include <CQColorPalette.h>

class CQColorPaletteDialog : public QDialog {
  Q_OBJECT

 public:
  CQColorPaletteDialog(QWidget *dialog=0);

  void setStyle(const CQColorPalette::Style &style);

  void setColorSet(const QString &setName);

  void setColorId (const QString &idName);

 signals:
  void colorSelected(const QString &, const QString &);

 private slots:
  void okSlot();
  void cancelSlot();

 private:
  CQColorPalette *pal_;
};

#endif
