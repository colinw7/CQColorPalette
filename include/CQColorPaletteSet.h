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
  CQColorPaletteSet(QWidget *parent=nullptr);

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
  CQPalettePreview *preview_ { nullptr };

  QString primary_;
  QString secondary_;
  QString text_;

  CQColorSetButton     *primaryButton_   { nullptr };
  CQColorSetButton     *secondaryButton_ { nullptr };
  CQColorSetButton     *textButton_      { nullptr };
  CQColorPaletteDialog *primaryDialog_   { nullptr };
  CQColorPaletteDialog *secondaryDialog_ { nullptr };
  CQColorPaletteDialog *textDialog_      { nullptr };
};

//---

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
