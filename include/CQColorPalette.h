#ifndef CQColorPalette_H
#define CQColorPalette_H

#include <CColorPalette.h>

#include <QFrame>
#include <QTableWidget>
#include <QListWidget>
#include <QToolButton>
#include <QLabel>

class CQColorTable;
class CQColorList;
class CQColorItemList;
class CQColorLabel;
class QListWIdgetItem;

//------

class CQColorPalette : public QFrame {
  Q_OBJECT

  Q_ENUMS(Style)

  Q_PROPERTY(Style   style    READ style    WRITE setStyle   )
  Q_PROPERTY(QString colorSet READ colorSet WRITE setColorSet)
  Q_PROPERTY(QString colorId  READ colorId  WRITE setColorId )

 public:
  enum Style {
    ColorStyle,
    SetStyle
  };

 public:
  CQColorPalette();

  const Style &style() const { return style_; }
  const QString &colorSet() const { return colorSet_; }
  const QString &colorId () const { return colorId_; }

  void setStyle(const Style &style);
  void setColorSet(const QString &setName);
  void setColorId(const QString &idName);

 signals:
  void colorChanged(const QString &, const QString &, const QColor &);

 private:
  void emitColorChanged();

  void updateList();
  void updateLabel();

 private Q_SLOTS:
  void colorSelected(const QString &name);
  void colorItemSelected(const QString &name);

 private:
  Style            style_;
  QString          colorSet_;
  QString          colorId_;
  CQColorTable    *colorTable_;
  CQColorList     *colorList_;
  CQColorItemList *itemList_;
  CQColorLabel    *fgStatusLabel_;
  CQColorLabel    *bgStatusLabel_;
};

//------

class CQColorTable : public QTableWidget {
  Q_OBJECT

 public:
  CQColorTable(CQColorPalette *pal);

  void setColorSet(const QString &name);

  QSize cellSizeHint() const;
  QSize cellSize() const;

 private:
  void addItems();
  void addItem(int row, int col, const QString &name, const QColor &c);

  void resizeEvent(QResizeEvent *) override;

 signals:
  void colorSelected(const QString &);

 private Q_SLOTS:
  void itemSlot(QTableWidgetItem *, QTableWidgetItem *);

 private:
  CQColorPalette *pal_;
  int             nrows_ { 0 };
  int             ncols_ { 0 };
};

//------

class CQColorList : public QListWidget {
  Q_OBJECT

 public:
  CQColorList(CQColorPalette *pal);

  void setColorSet(const QString &name);

 private:
  void addItems();
  void addItem(const QString &name, const QColor &c);

 signals:
  void colorSelected(const QString &);

 private Q_SLOTS:
  void itemSlot(QListWidgetItem *, QListWidgetItem *);

 private:
  CQColorPalette *pal_ { nullptr };
};

//---

class CQColorItemList : public QListWidget {
  Q_OBJECT

 public:
  CQColorItemList(CQColorPalette *pal);

  void addColorTitle(const QString &name, const QColor &color);

  void addTitle(const QString &name);

  void addSeparator();

  void addItem(const QString &name, const QColor &c);

 signals:
  void colorItemSelected(const QString &);

 private Q_SLOTS:
  void itemSlot(QListWidgetItem *, QListWidgetItem *);

 private:
  CQColorPalette *pal_ { nullptr };
};

//------

class CQColorButton : public QToolButton {
  Q_OBJECT

 public:
  CQColorButton(const QString &name, const QColor &c);

 signals:
  void buttonClicked(const QString &name);

 private Q_SLOTS:
  void clickSlot();

 private:
  QString name_;
  QColor  c_;
};

//------

class CQColorLabel : public QLabel {
  Q_OBJECT

 public:
  enum Type {
    FgType,
    BgType
  };

 public:
  CQColorLabel(const Type &type=BgType);

 public Q_SLOTS:
  void colorChanged(const QString &name, const QString &id, const QColor &c);

 private:
  Type type_ { FgType };
};

#endif
