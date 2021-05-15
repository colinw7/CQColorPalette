#ifndef CQColorPaletteSet_H
#define CQColorPaletteSet_H

#include <QFrame>
#include <QPushButton>

class CQPalettePreview;
class CQColorSetButton;
class CQColorPaletteDialog;

class CQColorPaletteSet : public QFrame {
  Q_OBJECT

 public:
  CQColorPaletteSet(QWidget *parent=0);

  const QString &primary() const { return primary_; }
  const QString &secondary() const { return secondary_; }
  const QString &text() const { return text_; }

 signals:
  void valueChanged();

 private slots:
  void primarySlot();
  void secondarySlot();
  void textSlot();

  void primaryColorSlot(const QString &setName, const QString &colorName);
  void secondaryColorSlot(const QString &setName, const QString &colorName);
  void textColorSlot(const QString &setName, const QString &colorName);

 private:
  CQPalettePreview     *preview_;
  QString               primary_;
  QString               secondary_;
  QString               text_;
  CQColorSetButton     *primaryButton_;
  CQColorSetButton     *secondaryButton_;
  CQColorSetButton     *textButton_;
  CQColorPaletteDialog *primaryDialog_;
  CQColorPaletteDialog *secondaryDialog_;
  CQColorPaletteDialog *textDialog_;
};

class CQColorSetButton : public QPushButton {
 public:
  enum Type {
    Primary,
    Secondary,
    Text
  };

 public:
  CQColorSetButton(const Type &type, const QString &colorSet);

  const Type &type() const { return type_; }

  const QString &colorSet() const { return colorSet_; }
  void setColorSet(const QString &colorSet);

 private:
  void updateText();

  void paintEvent(QPaintEvent *) override;

 private:
  Type    type_;
  QString colorSet_;
};

#endif
