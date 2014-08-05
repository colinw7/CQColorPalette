#ifndef CQPalettePreview_H
#define CQPalettePreview_H

#include <QFrame>

class CQPalettePreview : public QFrame {
  Q_OBJECT

 public:
  CQPalettePreview();

 public slots:
  void setColorSet(const QString &primary, const QString &secondary, const QString &text);
};

#endif
