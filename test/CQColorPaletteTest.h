#include <QDialog>

class CQPalettePreview;
class CQColorPaletteSet;

class CQColorPaletteTest : public QDialog {
  Q_OBJECT

 public:
  CQColorPaletteTest();

 private slots:
  void setChangedSlot();

 private:
  CQPalettePreview  *preview_;
  CQColorPaletteSet *set_;
};
